/* 
** Project X - Network Management System
** Copyright (C) 2003 Victor Kirhenshtein
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
** $module: interface.cpp
**
**/

#include "nxcore.h"


//
// Default constructor for Interface object
//

Interface::Interface()
          : NetObj()
{
   m_dwIpNetMask = 0;
   m_dwIfIndex = 0;
   m_dwIfType = IFTYPE_OTHER;
}


//
// Constructor for "fake" interface object
//

Interface::Interface(DWORD dwAddr, DWORD dwNetMask)
          : NetObj()
{
   strcpy(m_szName, "lan0");
   m_dwIpAddr = dwAddr;
   m_dwIpNetMask = dwNetMask;
   m_dwIfIndex = 1;
   m_dwIfType = IFTYPE_OTHER;
   memset(m_bMacAddr, 0, MAC_ADDR_LENGTH);
   m_bIsHidden = TRUE;
}


//
// Constructor for normal interface object
//

Interface::Interface(char *szName, DWORD dwIndex, DWORD dwAddr, DWORD dwNetMask, DWORD dwType)
          : NetObj()
{
   strncpy(m_szName, szName, MAX_OBJECT_NAME);
   m_dwIfIndex = dwIndex;
   m_dwIfType = dwType;
   m_dwIpAddr = dwAddr;
   m_dwIpNetMask = dwNetMask;
   memset(m_bMacAddr, 0, MAC_ADDR_LENGTH);
   m_bIsHidden = TRUE;
}


//
// Interfacet class destructor
//

Interface::~Interface()
{
}


//
// Create object from database data
//

BOOL Interface::CreateFromDB(DWORD dwId)
{
   TCHAR szQuery[256];
   DB_RESULT hResult;
   DWORD dwNodeId;
   NetObj *pObject;
   BOOL bResult = FALSE;

   m_dwId = dwId;

   if (!LoadCommonProperties())
      return FALSE;

   _sntprintf(szQuery, 256, _T("SELECT ip_addr,ip_netmask,if_type,if_index,node_id,"
                               "mac_addr FROM interfaces WHERE id=%ld"), dwId);
   hResult = DBSelect(g_hCoreDB, szQuery);
   if (hResult == NULL)
      return FALSE;     // Query failed

   if (DBGetNumRows(hResult) != 0)
   {
      m_dwIpAddr = DBGetFieldIPAddr(hResult, 0, 0);
      m_dwIpNetMask = DBGetFieldIPAddr(hResult, 0, 1);
      m_dwIfType = DBGetFieldULong(hResult, 0, 2);
      m_dwIfIndex = DBGetFieldULong(hResult, 0, 3);
      dwNodeId = DBGetFieldULong(hResult, 0, 4);
      StrToBin(DBGetField(hResult, 0, 5), m_bMacAddr, MAC_ADDR_LENGTH);

      // Link interface to node
      if (!m_bIsDeleted)
      {
         pObject = FindObjectById(dwNodeId);
         if (pObject == NULL)
         {
            WriteLog(MSG_INVALID_NODE_ID, EVENTLOG_ERROR_TYPE, "dd", dwId, dwNodeId);
         }
         else if (pObject->Type() != OBJECT_NODE)
         {
            WriteLog(MSG_NODE_NOT_NODE, EVENTLOG_ERROR_TYPE, "dd", dwId, dwNodeId);
         }
         else
         {
            pObject->AddChild(this);
            AddParent(pObject);
            bResult = TRUE;
         }
      }
      else
      {
         bResult = TRUE;
      }
   }

   DBFreeResult(hResult);

   // Load access list
   LoadACLFromDB();

   return bResult;
}


//
// Save interface object to database
//

BOOL Interface::SaveToDB(void)
{
   char szQuery[1024], szMacStr[16], szIpAddr[16], szNetMask[16];
   BOOL bNewObject = TRUE;
   DWORD dwNodeId;
   DB_RESULT hResult;

   // Lock object's access
   Lock();

   SaveCommonProperties();

   // Check for object's existence in database
   sprintf(szQuery, "SELECT id FROM interfaces WHERE id=%ld", m_dwId);
   hResult = DBSelect(g_hCoreDB, szQuery);
   if (hResult != 0)
   {
      if (DBGetNumRows(hResult) > 0)
         bNewObject = FALSE;
      DBFreeResult(hResult);
   }

   // Determine owning node's ID
   if (m_dwParentCount > 0)   // Always should be
      dwNodeId = m_pParentList[0]->Id();
   else
      dwNodeId = 0;

   // Form and execute INSERT or UPDATE query
   BinToStr(m_bMacAddr, MAC_ADDR_LENGTH, szMacStr);
   if (bNewObject)
      sprintf(szQuery, "INSERT INTO interfaces (id,ip_addr,"
                       "ip_netmask,node_id,if_type,if_index,mac_addr) "
                       "VALUES (%ld,'%s','%s',%ld,%ld,%ld,'%s')",
              m_dwId, IpToStr(m_dwIpAddr, szIpAddr),
              IpToStr(m_dwIpNetMask, szNetMask), dwNodeId,
              m_dwIfType, m_dwIfIndex, szMacStr);
   else
      sprintf(szQuery, "UPDATE interfaces SET ip_addr='%s',ip_netmask='%s',"
                       "node_id=%ld,if_type=%ld,if_index=%ld,"
                       "mac_addr='%s' WHERE id=%ld",
              IpToStr(m_dwIpAddr, szIpAddr),
              IpToStr(m_dwIpNetMask, szNetMask), dwNodeId,
              m_dwIfType, m_dwIfIndex, szMacStr, m_dwId);
   DBQuery(g_hCoreDB, szQuery);

   // Save access list
   SaveACLToDB();

   // Clear modifications flag and unlock object
   m_bIsModified = FALSE;
   Unlock();

   return TRUE;
}


//
// Delete interface object from database
//

BOOL Interface::DeleteFromDB(void)
{
   char szQuery[128];
   BOOL bSuccess;

   bSuccess = NetObj::DeleteFromDB();
   if (bSuccess)
   {
      sprintf(szQuery, "DELETE FROM interfaces WHERE id=%ld", m_dwId);
      QueueSQLRequest(szQuery);
   }
   return bSuccess;
}


//
// Perform status poll on interface
//

void Interface::StatusPoll(ClientSession *pSession, DWORD dwRqId)
{
   int iOldStatus = m_iStatus;
   DWORD dwPingStatus;
   BOOL bNeedPoll = TRUE;
   Node *pNode;

   m_pPollRequestor = pSession;
   pNode = GetParentNode();
   if (pNode == NULL)
   {
      m_iStatus = STATUS_UNKNOWN;
      return;     // Cannot find parent node, which is VERY strange
   }

   SendPollerMsg(dwRqId, "   Starting status poll on interface %s\r\n"
                         "      Current interface status is %s\r\n",
                 m_szName, g_pszStatusName[m_iStatus]);

   // Poll interface using different methods
   if (m_dwIfType != IFTYPE_NETXMS_NAT_ADAPTER)
   {
      if (pNode->Flags() & NF_IS_NATIVE_AGENT)
      {
         SendPollerMsg(dwRqId, "      Retrieving interface status from NetXMS agent\r\n");
         m_iStatus = pNode->GetInterfaceStatusFromAgent(m_dwIfIndex);
         if (m_iStatus != STATUS_UNKNOWN)
            bNeedPoll = FALSE;
      }
   
      if ((pNode->Flags() & NF_IS_SNMP) && bNeedPoll)
      {
         SendPollerMsg(dwRqId, "      Retrieving interface status from SNMP agent\r\n");
         m_iStatus = pNode->GetInterfaceStatusFromSNMP(m_dwIfIndex);
         if (m_iStatus != STATUS_UNKNOWN)
            bNeedPoll = FALSE;
      }
   }
   
   if (bNeedPoll)
   {
      // Use ICMP ping as a last option
      if ((m_dwIpAddr != 0) && 
           ((!(pNode->Flags() & NF_BEHIND_NAT)) || 
            (m_dwIfType == IFTYPE_NETXMS_NAT_ADAPTER)))
      {
         SendPollerMsg(dwRqId, "      Starting ICMP ping\r\n");
         dwPingStatus = IcmpPing(htonl(m_dwIpAddr), 3, 1500, NULL);
         if (dwPingStatus == ICMP_RAW_SOCK_FAILED)
            WriteLog(MSG_RAW_SOCK_FAILED, EVENTLOG_WARNING_TYPE, NULL);
         m_iStatus = (dwPingStatus == ICMP_SUCCESS) ? STATUS_NORMAL : STATUS_CRITICAL;
      }
      else
      {
         // Interface doesn't have an IP address, so we can't ping it
         m_iStatus = STATUS_UNKNOWN;
      }
   }

   if (m_iStatus != iOldStatus)
   {
      SendPollerMsg(dwRqId, "      Interface status changed to %s\r\n", g_pszStatusName[m_iStatus]);
      PostEvent(m_iStatus == STATUS_NORMAL ? EVENT_INTERFACE_UP : EVENT_INTERFACE_DOWN,
                pNode->Id(), "dsaad", m_dwId, m_szName, m_dwIpAddr, m_dwIpNetMask,
                m_dwIfIndex);
      Modify();
   }
   SendPollerMsg(dwRqId, "   Finished status poll on interface %s\r\n", m_szName);
}


//
// Create CSCP message with object's data
//

void Interface::CreateMessage(CSCPMessage *pMsg)
{
   NetObj::CreateMessage(pMsg);
   pMsg->SetVariable(VID_IF_INDEX, m_dwIfIndex);
   pMsg->SetVariable(VID_IF_TYPE, m_dwIfType);
   pMsg->SetVariable(VID_IP_NETMASK, m_dwIpNetMask);
   pMsg->SetVariable(VID_MAC_ADDR, m_bMacAddr, MAC_ADDR_LENGTH);
}


//
// Wake up node bound to this interface by sending magic packet
//

DWORD Interface::WakeUp(void)
{
   DWORD dwAddr, dwResult = RCC_NO_MAC_ADDRESS;

   if (memcmp(m_bMacAddr, "\x00\x00\x00\x00\x00\x00", 6))
   {
      dwAddr = htonl(m_dwIpAddr | ~m_dwIpNetMask);
      if (SendMagicPacket(dwAddr, m_bMacAddr, 5))
         dwResult = RCC_SUCCESS;
      else
         dwResult = RCC_COMM_FAILURE;
   }
   return dwResult;
}


//
// Get interface's parent node
//

Node *Interface::GetParentNode(void)
{
   DWORD i;
   Node *pNode = NULL;

   Lock();
   for(i = 0; i < m_dwParentCount; i++)
      if (m_pParentList[i]->Type() == OBJECT_NODE)
      {
         pNode = (Node *)m_pParentList[i];
         break;
      }
   Unlock();
   return pNode;
}
