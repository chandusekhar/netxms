/* 
** NetXMS - Network Management System
** Client Library
** Copyright (C) 2004 Victor Kirhenshtein
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
** $module: main.cpp
**
**/

#include "libnxcl.h"


//
// Global variables
//

NXC_EVENT_HANDLER g_pEventHandler = NULL;
NXC_DEBUG_CALLBACK g_pDebugCallBack = NULL;
DWORD g_dwState = STATE_DISCONNECTED;
DWORD g_dwCommandTimeout = 3000;    // Default timeout is 3 seconds


//
// Initialization function
//

BOOL LIBNXCL_EXPORTABLE NXCInitialize(void)
{
   ObjectsInit();
   InitSyncStuff();
   return TRUE;
}


//
// Shutdown function
//

void LIBNXCL_EXPORTABLE NXCShutdown(void)
{
   SyncCleanup();
}


//
// Get library version
//

DWORD LIBNXCL_EXPORTABLE NXCGetVersion(void)
{
   return (NETXMS_VERSION_MAJOR << 24) | (NETXMS_VERSION_MINOR << 16) | LIBNXCL_VERSION;
}


//
// Set event handler
//

void LIBNXCL_EXPORTABLE NXCSetEventHandler(NXC_EVENT_HANDLER pHandler)
{
   g_pEventHandler = pHandler;
}


//
// Set callback for debug messages
//

void LIBNXCL_EXPORTABLE NXCSetDebugCallback(NXC_DEBUG_CALLBACK pFunc)
{
   g_pDebugCallBack = pFunc;
}


//
// Set command timeout
//

void LIBNXCL_EXPORTABLE NXCSetCommandTimeout(DWORD dwTimeout)
{
   if ((dwTimeout >= 1000) && (dwTimeout <= 60000))
      g_dwCommandTimeout = dwTimeout;
}


//
// Get text for error
//

const TCHAR LIBNXCL_EXPORTABLE *NXCGetErrorText(DWORD dwError)
{
   static TCHAR *pszErrorText[] =
   {
      _T("Request completed successfully"),
      _T("Component locked"),
      _T("Access denied"),
      _T("Invalid request"),
      _T("Request timed out"),
      _T("Request is out of state"),
      _T("Database failure"),
      _T("Invalid object ID"),
      _T("Object already exist"),
      _T("Communication failure"),
      _T("System failure"),
      _T("Invalid user ID"),
      _T("Invalid argument"),
      _T("Duplicate DCI"),
      _T("Invalid DCI ID"),
      _T("Out of memory"),
      _T("Input/Output error"),
      _T("Incompatible operation"),
      _T("Object creation failed"),
      _T("Loop in object relationship detected"),
      _T("Invalid object name"),
      _T("Invalid alarm ID"),
      _T("Invalid action ID"),
      _T("Operation in progress"),
      _T("Copy operation failed for one or more DCI(s)")
   };
   return ((dwError >= 0) && (dwError <= RCC_DCI_COPY_ERRORS)) ? pszErrorText[dwError] : _T("Unknown error code");
}


//
// DLL entry point
//

#if defined(_WIN32) && !defined(UNDER_CE)

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   return TRUE;
}

#endif   /* _WIN32 */
