/*
** NetXMS Tuxedo subagent
** Copyright (C) 2014 Raden Solutions
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
** File: main.cpp
**
**/

#include "tuxedo_subagent.h"

/**
 * Handlers
 */
LONG H_ClientInfo(const TCHAR *param, const TCHAR *arg, TCHAR *value);
LONG H_ClientsList(const TCHAR *param, const TCHAR *arg, StringList *value);
LONG H_ClientsTable(const TCHAR *param, const TCHAR *arg, Table *value);
LONG H_DomainInfo(const TCHAR *param, const TCHAR *arg, TCHAR *value);
LONG H_MachineInfo(const TCHAR *param, const TCHAR *arg, TCHAR *value);
LONG H_MachinesList(const TCHAR *param, const TCHAR *arg, StringList *value);
LONG H_MachinesTable(const TCHAR *param, const TCHAR *arg, Table *value);
LONG H_QueueInfo(const TCHAR *param, const TCHAR *arg, TCHAR *value);
LONG H_QueuesList(const TCHAR *param, const TCHAR *arg, StringList *value);
LONG H_QueuesTable(const TCHAR *param, const TCHAR *arg, Table *value);
LONG H_ServerInfo(const TCHAR *param, const TCHAR *arg, TCHAR *value);
LONG H_ServersList(const TCHAR *param, const TCHAR *arg, StringList *value);
LONG H_ServersTable(const TCHAR *param, const TCHAR *arg, Table *value);
LONG H_ServiceInfo(const TCHAR *param, const TCHAR *arg, TCHAR *value);
LONG H_ServicesList(const TCHAR *param, const TCHAR *arg, StringList *value);
LONG H_ServicesTable(const TCHAR *param, const TCHAR *arg, Table *value);

/**
 * Connect count
 */
static int s_connectCount = 0;
static MUTEX s_connectLock = MutexCreate();

/**
 * Connect to Tuxedo app
 */
bool TuxedoConnect()
{
   bool success = true;
   MutexLock(s_connectLock);
   if (s_connectCount == 0)
   {
      if (tpinit(NULL) != -1)
      {
         s_connectCount++;
      }
      else
      {
         AgentWriteDebugLog(3, _T("Tuxedo: tpinit() call failed (%d)"), tperrno);
         success = false;
      }
   }
   else
   {
      s_connectCount++;
   }
   MutexUnlock(s_connectLock);
   return success;
}

/**
 * Disconnect from Tuxedo app
 */
void TuxedoDisconnect()
{
   MutexLock(s_connectLock);
   if (s_connectCount > 0)
   {
      s_connectCount--;
      if (s_connectCount == 0)
         tpterm();
   }
   MutexUnlock(s_connectLock);
}

/**
 * Helper function to get string field
 */
bool CFgetString(FBFR32 *fb, FLDID32 fieldid, FLDOCC32 oc, char *buf, size_t size)
{
   FLDLEN32 len = (FLDLEN32)size;
   if (CFget32(fb, fieldid, oc, buf, &len, FLD_STRING) == -1)
   {
      buf[0] = 0;
      return false;
   }
   return true;
}

/**
 * Subagent initialization
 */
static BOOL SubAgentInit(Config *config)
{
   const char *tc = getenv("TUXCONFIG");
   if (tc == NULL)
   {
      AgentWriteLog(NXLOG_ERROR, _T("Tuxedo: TUXCONFIG environment variable not set"));
      return FALSE;
   }
   AgentWriteDebugLog(2, _T("Tuxedo: using configuration file %hs"), tc);
   return TRUE;
}

/**
 * Called by master agent at unload
 */
static void SubAgentShutdown()
{
   tpterm();
}

/**
 * Subagent parameters
 */
static NETXMS_SUBAGENT_PARAM m_parameters[] =
{
   { _T("Tuxedo.Client.ActiveConversations(*)"), H_ClientInfo, _T("a"), DCI_DT_INT, _T("Tuxedo client {instance}: active conversations") },
   { _T("Tuxedo.Client.ActiveRequests(*)"), H_ClientInfo, _T("A"), DCI_DT_INT, _T("Tuxedo client {instance} machine") },
   { _T("Tuxedo.Client.Machine(*)"), H_ClientInfo, _T("N"), DCI_DT_STRING, _T("Tuxedo client {instance} name") },
   { _T("Tuxedo.Client.Name(*)"), H_ClientInfo, _T("N"), DCI_DT_STRING, _T("Tuxedo client {instance} name") },
   { _T("Tuxedo.Client.State(*)"), H_ClientInfo, _T("S"), DCI_DT_STRING, _T("Tuxedo client {instance} state") },
	{ _T("Tuxedo.Domain.ID"), H_DomainInfo, _T("I"), DCI_DT_STRING, _T("Tuxedo domain ID") },
   { _T("Tuxedo.Domain.Master"), H_DomainInfo, _T("M"), DCI_DT_STRING, _T("Tuxedo domain master/backup machines") },
   { _T("Tuxedo.Domain.Model"), H_DomainInfo, _T("m"), DCI_DT_STRING, _T("Tuxedo domain model") },
   { _T("Tuxedo.Domain.Queues"), H_DomainInfo, _T("Q"), DCI_DT_INT,  _T("Tuxedo: number of queues") },
   { _T("Tuxedo.Domain.Routes"), H_DomainInfo, _T("R"), DCI_DT_INT, _T("Tuxedo: bulletin board routing table entries") },
   { _T("Tuxedo.Domain.Servers"), H_DomainInfo, _T("S"), DCI_DT_INT, _T("Tuxedo: number of servers") },
   { _T("Tuxedo.Domain.Services"), H_DomainInfo, _T("s"), DCI_DT_INT, _T("Tuxedo: number of services") },
   { _T("Tuxedo.Domain.State"), H_DomainInfo, _T("T"), DCI_DT_STRING, _T("Tuxedo domain state") },
   { _T("Tuxedo.Machine.Accessers(*)"), H_MachineInfo, _T("A"), DCI_DT_INT, _T("Tuxedo machine {instance}: accessers") },
   { _T("Tuxedo.Machine.Bridge(*)"), H_MachineInfo, _T("B"), DCI_DT_STRING, _T("Tuxedo machine {instance} bridge") },
   { _T("Tuxedo.Machine.Clients(*)"), H_MachineInfo, _T("C"), DCI_DT_INT, _T("Tuxedo machine {instance}: clients") },
   { _T("Tuxedo.Machine.Conversations(*)"), H_MachineInfo, _T("o"), DCI_DT_INT, _T("Tuxedo machine {instance}: conversations") },
   { _T("Tuxedo.Machine.Load(*)"), H_MachineInfo, _T("L"), DCI_DT_INT, _T("Tuxedo machine {instance}: load") },
   { _T("Tuxedo.Machine.PhysicalID(*)"), H_MachineInfo, _T("P"), DCI_DT_STRING, _T("Tuxedo machine {instance} physical machine ID") },
   { _T("Tuxedo.Machine.Role(*)"), H_MachineInfo, _T("R"), DCI_DT_STRING, _T("Tuxedo machine {instance} role") },
   { _T("Tuxedo.Machine.SoftwareRelease(*)"), H_MachineInfo, _T("s"), DCI_DT_STRING, _T("Tuxedo machine {instance}: software release") },
   { _T("Tuxedo.Machine.State(*)"), H_MachineInfo, _T("S"), DCI_DT_STRING, _T("Tuxedo machine {instance} state") },
   { _T("Tuxedo.Machine.Type(*)"), H_MachineInfo, _T("T"), DCI_DT_STRING, _T("Tuxedo machine {instance} type") },
   { _T("Tuxedo.Machine.WorkloadsInitiated(*)"), H_MachineInfo, _T("W"), DCI_DT_INT, _T("Tuxedo machine {instance}: workloads initiated") },
   { _T("Tuxedo.Machine.WorkloadsProcessed(*)"), H_MachineInfo, _T("w"), DCI_DT_INT, _T("Tuxedo machine {instance}: workloads processed") },
   { _T("Tuxedo.Machine.WorkstationClients(*)"), H_MachineInfo, _T("c"), DCI_DT_INT, _T("Tuxedo machine {instance}: workstation clients") },
   { _T("Tuxedo.Queue.Machine(*)"), H_QueueInfo, _T("M"), DCI_DT_STRING, _T("Tuxedo queue {instance}: hosting machine") },
   { _T("Tuxedo.Queue.RequestsCurrent(*)"), H_QueueInfo, _T("r"), DCI_DT_STRING, _T("Tuxedo queue {instance}: current requests queued") },
   { _T("Tuxedo.Queue.RequestsTotal(*)"), H_QueueInfo, _T("R"), DCI_DT_STRING, _T("Tuxedo queue {instance}: total requests queued") },
   { _T("Tuxedo.Queue.Server(*)"), H_QueueInfo, _T("S"), DCI_DT_STRING, _T("Tuxedo queue {instance}: server executable") },
   { _T("Tuxedo.Queue.ServerCount(*)"), H_QueueInfo, _T("C"), DCI_DT_STRING, _T("Tuxedo queue {instance}: server count") },
   { _T("Tuxedo.Queue.State(*)"), H_QueueInfo, _T("s"), DCI_DT_STRING, _T("Tuxedo queue {instance} state") },
   { _T("Tuxedo.Queue.WorkloadsCurrent(*)"), H_QueueInfo, _T("w"), DCI_DT_STRING, _T("Tuxedo queue {instance}: current workloads queued") },
   { _T("Tuxedo.Queue.WorkloadsTotal(*)"), H_QueueInfo, _T("W"), DCI_DT_STRING, _T("Tuxedo queue {instance}: total workloads queued") },
   { _T("Tuxedo.Server.ActiveRequests(*)"), H_ServerInfo, _T("A"), DCI_DT_INT, _T("Tuxedo server {instance}: active requests") },
   { _T("Tuxedo.Server.BaseID(*)"), H_ServerInfo, _T("B"), DCI_DT_INT, _T("Tuxedo server {instance} base ID") },
   { _T("Tuxedo.Server.CommandLine(*)"), H_ServerInfo, _T("C"), DCI_DT_STRING, _T("Tuxedo server {instance}: command line") },
   { _T("Tuxedo.Server.CurrentService(*)"), H_ServerInfo, _T("c"), DCI_DT_STRING, _T("Tuxedo server {instance}: current service") },
   { _T("Tuxedo.Server.Generation(*)"), H_ServerInfo, _T("G"), DCI_DT_INT, _T("Tuxedo server {instance}: generation") },
   { _T("Tuxedo.Server.Group(*)"), H_ServerInfo, _T("g"), DCI_DT_STRING, _T("Tuxedo server {instance}: server group") },
   { _T("Tuxedo.Server.Machine(*)"), H_ServerInfo, _T("M"), DCI_DT_STRING, _T("Tuxedo server {instance}: machine ID") },
   { _T("Tuxedo.Server.Name(*)"), H_ServerInfo, _T("N"), DCI_DT_STRING, _T("Tuxedo server {instance} name") },
   { _T("Tuxedo.Server.PID(*)"), H_ServerInfo, _T("P"), DCI_DT_INT, _T("Tuxedo server {instance} process ID") },
   { _T("Tuxedo.Server.ProcessedRequests(*)"), H_ServerInfo, _T("R"), DCI_DT_INT, _T("Tuxedo server {instance}: processed requests") },
   { _T("Tuxedo.Server.ProcessedWorkloads(*)"), H_ServerInfo, _T("W"), DCI_DT_INT, _T("Tuxedo server {instance}: processed workloads") },
   { _T("Tuxedo.Server.State(*)"), H_ServerInfo, _T("S"), DCI_DT_STRING, _T("Tuxedo server {instance} state") },
   { _T("Tuxedo.Service.Load(*)"), H_ServiceInfo, _T("L"), DCI_DT_INT, _T("Tuxedo service {instance} load") },
   { _T("Tuxedo.Service.Priority(*)"), H_ServiceInfo, _T("P"), DCI_DT_INT, _T("Tuxedo service {instance} priority") },
   { _T("Tuxedo.Service.RoutingName(*)"), H_ServiceInfo, _T("R"), DCI_DT_STRING, _T("Tuxedo service {instance} routing name") },
   { _T("Tuxedo.Service.State(*)"), H_ServiceInfo, _T("S"), DCI_DT_STRING, _T("Tuxedo service {instance} state") }
};

/**
 * Subagent lists
 */
static NETXMS_SUBAGENT_LIST s_lists[] =
{
   { _T("Tuxedo.Clients"), H_ClientsList, NULL },
   { _T("Tuxedo.Machines"), H_MachinesList, NULL },
   { _T("Tuxedo.Queues"), H_QueuesList, NULL },
   { _T("Tuxedo.Servers"), H_ServersList, NULL },
   { _T("Tuxedo.Services"), H_ServicesList, NULL }
};

/**
 * Subagent tables
 */
static NETXMS_SUBAGENT_TABLE s_tables[] =
{
   { _T("Tuxedo.Clients"), H_ClientsTable, NULL, _T("ID"), _T("Tuxedo clients") },
   { _T("Tuxedo.Machines"), H_MachinesTable, NULL, _T("ID"), _T("Tuxedo machines") },
   { _T("Tuxedo.Queues"), H_QueuesTable, NULL, _T("NAME"), _T("Tuxedo queues") },
   { _T("Tuxedo.Servers"), H_ServersTable, NULL, _T("ID"), _T("Tuxedo servers") },
   { _T("Tuxedo.Services"), H_ServicesTable, NULL, _T("NAME"), _T("Tuxedo services") }
};

/**
 * Subagent information
 */
static NETXMS_SUBAGENT_INFO m_info =
{
	NETXMS_SUBAGENT_INFO_MAGIC,
	_T("TUXEDO"), NETXMS_VERSION_STRING,
	SubAgentInit, SubAgentShutdown, NULL,
	sizeof(m_parameters) / sizeof(NETXMS_SUBAGENT_PARAM),
	m_parameters,
	sizeof(s_lists) / sizeof(NETXMS_SUBAGENT_LIST),
   s_lists,
	sizeof(s_tables) / sizeof(NETXMS_SUBAGENT_TABLE),
   s_tables,
	0, NULL, // actions
	0, NULL	// push parameters
};

/**
 * Entry point for NetXMS agent
 */
DECLARE_SUBAGENT_ENTRY_POINT(TUXEDO)
{
	*ppInfo = &m_info;
	return TRUE;
}

#ifdef _WIN32

/**
 * DLL entry point
 */
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		DisableThreadLibraryCalls(hInstance);
	return TRUE;
}

#endif
