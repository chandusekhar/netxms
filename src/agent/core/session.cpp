/* 
** NetXMS multiplatform core agent
** Copyright (C) 2003, 2004 Victor Kirhenshtein
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** $module: session.cpp
**
**/

#include "nxagentd.h"


//
// Constants
//

#define RAW_MSG_SIZE    262144


//
// Client session class constructor
//

CommSession::CommSession(SOCKET hSocket, DWORD dwHostAddr)
{
   m_pSendQueue = new Queue;
   m_pMessageQueue = new Queue;
   m_hSocket = hSocket;
   m_dwIndex = INVALID_INDEX;
   m_pMsgBuffer = (CSCP_BUFFER *)malloc(sizeof(CSCP_BUFFER));
   m_hCondWriteThreadStopped = ConditionCreate(FALSE);
   m_hCondProcessingThreadStopped = ConditionCreate(FALSE);
   m_dwHostAddr = dwHostAddr;
   m_bIsAuthenticated = (g_dwFlags & AF_REQUIRE_AUTH) ? FALSE : TRUE;
}


//
// Destructor
//

CommSession::~CommSession()
{
   shutdown(m_hSocket, 2);
   closesocket(m_hSocket);
   delete m_pSendQueue;
   delete m_pMessageQueue;
   safe_free(m_pMsgBuffer);
   ConditionDestroy(m_hCondWriteThreadStopped);
   ConditionDestroy(m_hCondProcessingThreadStopped);
}


//
// Reading thread
//

void CommSession::ReadThread(void)
{
   CSCP_MESSAGE *pRawMsg;
   CSCPMessage *pMsg;
   int iErr;
   char szBuffer[32];

   // Initialize raw message receiving function
   RecvCSCPMessage(0, NULL, m_pMsgBuffer, 0);

   pRawMsg = (CSCP_MESSAGE *)malloc(RAW_MSG_SIZE);
   while(1)
   {
      if ((iErr = RecvCSCPMessage(m_hSocket, pRawMsg, m_pMsgBuffer, RAW_MSG_SIZE)) <= 0)
         break;

      // Check if message is too large
      if (iErr == 1)
         continue;

      // Check that actual received packet size is equal to encoded in packet
      if ((int)ntohl(pRawMsg->dwSize) != iErr)
      {
         DebugPrintf("Actual message size doesn't match wSize value (%d,%d)\n", iErr, ntohl(pRawMsg->dwSize));
         continue;   // Bad packet, wait for next
      }

      // Create message object from raw message
      pMsg = new CSCPMessage(pRawMsg);
      m_pMessageQueue->Put(pMsg);
   }
   if (iErr < 0)
      WriteLog(MSG_SESSION_BROKEN, EVENTLOG_WARNING_TYPE, "e", WSAGetLastError());
   free(pRawMsg);

   // Notify other threads to exit
   m_pSendQueue->Put(INVALID_POINTER_VALUE);
   m_pMessageQueue->Put(INVALID_POINTER_VALUE);

   // Wait for other threads to finish
   ConditionWait(m_hCondWriteThreadStopped, INFINITE);
   ConditionWait(m_hCondProcessingThreadStopped, INFINITE);

   DebugPrintf("Session with %s closed", IpToStr(m_dwHostAddr, szBuffer));
}


//
// Writing thread
//

void CommSession::WriteThread(void)
{
   CSCP_MESSAGE *pMsg;
   char szBuffer[128];

   while(1)
   {
      pMsg = (CSCP_MESSAGE *)m_pSendQueue->GetOrBlock();
      if (pMsg == INVALID_POINTER_VALUE)    // Session termination indicator
         break;

      DebugPrintf("Sending message %s\n", CSCPMessageCodeName(ntohs(pMsg->wCode), szBuffer));
      if (send(m_hSocket, (const char *)pMsg, ntohl(pMsg->dwSize), 0) <= 0)
      {
         MemFree(pMsg);
         break;
      }
      MemFree(pMsg);
   }
   ConditionSet(m_hCondWriteThreadStopped);
}


//
// Message processing thread
//

void CommSession::ProcessingThread(void)
{
   CSCPMessage *pMsg;
   char szBuffer[128];
   CSCPMessage msg;

   while(1)
   {
      pMsg = (CSCPMessage *)m_pMessageQueue->GetOrBlock();
      if (pMsg == INVALID_POINTER_VALUE)    // Session termination indicator
         break;
      DebugPrintf("Received message %s\n", CSCPMessageCodeName(pMsg->GetCode(), szBuffer));

      // Prepare responce message
      msg.SetCode(CMD_REQUEST_COMPLETED);
      msg.SetId(pMsg->GetId());

      // Check if authentication required
      if ((!m_bIsAuthenticated) && (pMsg->GetCode() != CMD_AUTHENTICATE))
      {
         msg.SetVariable(VID_RCC, ERR_AUTH_REQUIRED);
      }
      else
      {
         switch(pMsg->GetCode())
         {
            case CMD_AUTHENTICATE:
               Authenticate(pMsg, &msg);
               break;
            case CMD_GET_PARAMETER:
               GetParameter(pMsg, &msg);
               break;
            case CMD_GET_LIST:
               msg.SetVariable(VID_RCC, ERR_NOT_IMPLEMENTED);
               break;
            default:
               msg.SetVariable(VID_RCC, ERR_UNKNOWN_COMMAND);
               break;
         }
      }
      delete pMsg;

      // Send responce
      SendMessage(&msg);
      msg.DeleteAllVariables();
   }
   ConditionSet(m_hCondProcessingThreadStopped);
}


//
// Authenticate peer
//

void CommSession::Authenticate(CSCPMessage *pRequest, CSCPMessage *pMsg)
{
   if (m_bIsAuthenticated)
   {
      // Already authenticated
      pMsg->SetVariable(VID_RCC, (g_dwFlags & AF_REQUIRE_AUTH) ? ERR_ALREADY_AUTHENTICATED : ERR_AUTH_NOT_REQUIRED);
   }
   else
   {
      char szSecret[MAX_SECRET_LENGTH];
      WORD wAuthMethod;

      wAuthMethod = pRequest->GetVariableShort(VID_AUTH_METHOD);
      switch(wAuthMethod)
      {
         case AUTH_PLAINTEXT:
            pRequest->GetVariableStr(VID_SHARED_SECRET, szSecret, MAX_SECRET_LENGTH);
            if (!strcmp(szSecret, g_szSharedSecret))
            {
               m_bIsAuthenticated = TRUE;
               pMsg->SetVariable(VID_RCC, ERR_SUCCESS);
            }
            else
            {
               WriteLog(MSG_AUTH_FAILED, EVENTLOG_WARNING_TYPE, "as", m_dwHostAddr, "PLAIN");
               pMsg->SetVariable(VID_RCC, ERR_AUTH_FAILED);
            }
            break;
         default:
            pMsg->SetVariable(VID_RCC, ERR_NOT_IMPLEMENTED);
            break;
      }
   }
}


//
// Get parameter's value
//

void CommSession::GetParameter(CSCPMessage *pRequest, CSCPMessage *pMsg)
{
   char szParameter[MAX_PARAM_NAME], szValue[MAX_RESULT_LENGTH];
   DWORD dwErrorCode;

   pRequest->GetVariableStr(VID_PARAMETER, szParameter, MAX_PARAM_NAME);
   dwErrorCode = GetParameterValue(szParameter, szValue);
   pMsg->SetVariable(VID_RCC, dwErrorCode);
   if (dwErrorCode == ERR_SUCCESS)
      pMsg->SetVariable(VID_VALUE, szValue);
}
