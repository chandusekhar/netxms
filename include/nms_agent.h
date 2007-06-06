/* 
** NetXMS - Network Management System
** Copyright (C) 2003, 2004, 2005, 2006 Victor Kirhenshtein
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
** File: nms_agent.h
**
**/

#ifndef _nms_agent_h_
#define _nms_agent_h_

#include <nms_common.h>
#include <nms_util.h>


//
// Initialization function declaration macro
//

#if defined(_STATIC_AGENT) || defined(_NETWARE)
#define DECLARE_SUBAGENT_ENTRY_POINT(name) extern "C" BOOL NxSubAgentRegister_##name(NETXMS_SUBAGENT_INFO **ppInfo, TCHAR *pszConfigFile)
#else
#ifdef _WIN32
#define DECLSPEC_EXPORT __declspec(dllexport) __cdecl
#else
#define DECLSPEC_EXPORT
#endif
#define DECLARE_SUBAGENT_ENTRY_POINT(name) extern "C" BOOL DECLSPEC_EXPORT NxSubAgentRegister(NETXMS_SUBAGENT_INFO **ppInfo, TCHAR *pszConfigFile)
#endif


//
// Some constants
//

#define AGENT_LISTEN_PORT        4700
#define AGENT_PROTOCOL_VERSION   2
#define MAX_RESULT_LENGTH        256
#define MAX_CMD_LEN              256
#define COMMAND_TIMEOUT          60
#define MAX_SUBAGENT_NAME        64

#ifndef EVENTLOG_DEBUG_TYPE
#define EVENTLOG_DEBUG_TYPE		255
#endif


//
// Error codes
//

#define ERR_SUCCESS                 ((DWORD)0)
#define ERR_UNKNOWN_COMMAND         ((DWORD)400)
#define ERR_AUTH_REQUIRED           ((DWORD)401)
#define ERR_ACCESS_DENIED           ((DWORD)403)
#define ERR_UNKNOWN_PARAMETER       ((DWORD)404)
#define ERR_REQUEST_TIMEOUT         ((DWORD)408)
#define ERR_AUTH_FAILED             ((DWORD)440)
#define ERR_ALREADY_AUTHENTICATED   ((DWORD)441)
#define ERR_AUTH_NOT_REQUIRED       ((DWORD)442)
#define ERR_INTERNAL_ERROR          ((DWORD)500)
#define ERR_NOT_IMPLEMENTED         ((DWORD)501)
#define ERR_OUT_OF_RESOURCES        ((DWORD)503)
#define ERR_NOT_CONNECTED           ((DWORD)900)
#define ERR_CONNECTION_BROKEN       ((DWORD)901)
#define ERR_BAD_RESPONSE            ((DWORD)902)
#define ERR_IO_FAILURE              ((DWORD)903)
#define ERR_RESOURCE_BUSY           ((DWORD)904)
#define ERR_EXEC_FAILED             ((DWORD)905)
#define ERR_ENCRYPTION_REQUIRED     ((DWORD)906)
#define ERR_NO_CIPHERS              ((DWORD)907)
#define ERR_INVALID_PUBLIC_KEY      ((DWORD)908)
#define ERR_INVALID_SESSION_KEY     ((DWORD)909)
#define ERR_CONNECT_FAILED          ((DWORD)910)
#define ERR_MAILFORMED_COMMAND      ((DWORD)911)
#define ERR_SOCKET_ERROR            ((DWORD)912)


//
// Parameter handler return codes
//

#define SYSINFO_RC_SUCCESS       0
#define SYSINFO_RC_UNSUPPORTED   1
#define SYSINFO_RC_ERROR         2


//
// Descriptions for common parameters
//

#define DCIDESC_DISK_AVAIL			"Available disk space on {instance}"
#define DCIDESC_DISK_AVAILPERC			"Percentage of available disk space on {instance}"
#define DCIDESC_DISK_FREE			"Free disk space on {instance}"
#define DCIDESC_DISK_FREEPERC			"Percentage of free disk space on {instance}"
#define DCIDESC_DISK_TOTAL			"Total disk space on {instance}"
#define DCIDESC_DISK_USED			"Used disk space on {instance}"
#define DCIDESC_DISK_USEDPERC			"Percentage of used disk space on {instance}"
#define DCIDESC_NET_INTERFACE_ADMINSTATUS	"Administrative status of interface {instance}"
#define DCIDESC_NET_INTERFACE_BYTESIN		"Number of input bytes on interface {instance}"
#define DCIDESC_NET_INTERFACE_BYTESOUT		"Number of output bytes on interface {instance}"
#define DCIDESC_NET_INTERFACE_DESCRIPTION	"Description of interface {instance}"
#define DCIDESC_NET_INTERFACE_INERRORS		"Number of input errors on interface {instance}"
#define DCIDESC_NET_INTERFACE_LINK		"Link status for interface {instance}"
#define DCIDESC_NET_INTERFACE_OUTERRORS		"Number of output errors on interface {instance}"
#define DCIDESC_NET_INTERFACE_PACKETSIN		"Number of input packets on interface {instance}"
#define DCIDESC_NET_INTERFACE_PACKETSOUT	"Number of output packets on interface {instance}"
#define DCIDESC_NET_INTERFACE_SPEED		"Speed of interface {instance}"
#define DCIDESC_NET_IP_FORWARDING		"IP forwarding status"
#define DCIDESC_NET_IP6_FORWARDING		"IPv6 forwarding status"
#define DCIDESC_PHYSICALDISK_FIRMWARE		"Firmware version of hard disk {instance}"
#define DCIDESC_PHYSICALDISK_MODEL		"Model of hard disk {instance}"
#define DCIDESC_PHYSICALDISK_SERIALNUMBER	"Serial number of hard disk {instance}"
#define DCIDESC_PHYSICALDISK_SMARTATTR		""
#define DCIDESC_PHYSICALDISK_SMARTSTATUS	"Status of hard disk {instance} reported by SMART"
#define DCIDESC_PHYSICALDISK_TEMPERATURE	"Temperature of hard disk {instance}"
#define DCIDESC_SYSTEM_CPU_COUNT		"Number of CPU in the system"
#define DCIDESC_SYSTEM_HOSTNAME			"Host name"
#define DCIDESC_SYSTEM_MEMORY_PHYSICAL_FREE	"Free physical memory"
#define DCIDESC_SYSTEM_MEMORY_PHYSICAL_TOTAL	"Total amount of physical memory"
#define DCIDESC_SYSTEM_MEMORY_PHYSICAL_USED	"Used physical memory"
#define DCIDESC_SYSTEM_MEMORY_VIRTUAL_FREE	"Free virtual memory"
#define DCIDESC_SYSTEM_MEMORY_VIRTUAL_TOTAL	"Total amount of virtual memory"
#define DCIDESC_SYSTEM_MEMORY_VIRTUAL_USED	"Used virtual memory"
#define DCIDESC_SYSTEM_MEMORY_SWAP_FREE		"Free swap space"
#define DCIDESC_SYSTEM_MEMORY_SWAP_TOTAL	"Total amount of swap space"
#define DCIDESC_SYSTEM_MEMORY_SWAP_USED		"Used swap space"
#define DCIDESC_SYSTEM_UNAME			"System uname"
#define DCIDESC_AGENT_ACCEPTEDCONNECTIONS	"Number of connections accepted by agent"
#define DCIDESC_AGENT_ACCEPTERRORS		"Number of accept() call errors"
#define DCIDESC_AGENT_ACTIVECONNECTIONS		"Number of active connections to agent"
#define DCIDESC_AGENT_AUTHENTICATIONFAILURES	"Number of authentication failures"
#define DCIDESC_AGENT_FAILEDREQUESTS		"Number of failed requests to agent"
#define DCIDESC_AGENT_PROCESSEDREQUESTS		"Number of requests processed by agent"
#define DCIDESC_AGENT_REJECTEDCONNECTIONS	"Number of connections rejected by agent"
#define DCIDESC_AGENT_SOURCEPACKAGESUPPORT	""
#define DCIDESC_AGENT_SUPPORTEDCIPHERS		"List of ciphers supported by agent"
#define DCIDESC_AGENT_TIMEDOUTREQUESTS		"Number of timed out requests to agent"
#define DCIDESC_AGENT_UNSUPPORTEDREQUESTS	"Number of requests for unsupported parameters"
#define DCIDESC_AGENT_UPTIME			"Agent's uptime"
#define DCIDESC_AGENT_VERSION			"Agent's version"
#define DCIDESC_FILE_COUNT			"Number of files {instance}"
#define DCIDESC_FILE_HASH_CRC32			"CRC32 checksum of {instance}"
#define DCIDESC_FILE_HASH_MD5			"MD5 hash of {instance}"
#define DCIDESC_FILE_HASH_SHA1			"SHA1 hash of {instance}"
#define DCIDESC_FILE_SIZE			"Size of file {instance}"
#define DCIDESC_FILE_TIME_ACCESS		"Time of last access to file {instance}"
#define DCIDESC_FILE_TIME_CHANGE		"Time of last status change of file {instance}"
#define DCIDESC_FILE_TIME_MODIFY		"Time of last modification of file {instance}"
#define DCIDESC_SYSTEM_PLATFORMNAME		"Platform name"
#define DCIDESC_PROCESS_COUNT			"Number of {instance} processes"
#define DCIDESC_PROCESS_COUNTEX			"Number of {instance} processes (extended)"
#define DCIDESC_PROCESS_GDIOBJ			""
#define DCIDESC_PROCESS_IO_OTHERB		""
#define DCIDESC_PROCESS_IO_OTHEROP		""
#define DCIDESC_PROCESS_IO_READB		""
#define DCIDESC_PROCESS_IO_READOP		""
#define DCIDESC_PROCESS_IO_WRITEB		""
#define DCIDESC_PROCESS_IO_WRITEOP		""
#define DCIDESC_PROCESS_KERNELTIME		""
#define DCIDESC_PROCESS_PAGEFAULTS		""
#define DCIDESC_PROCESS_THREADS			""
#define DCIDESC_PROCESS_USEROBJ			""
#define DCIDESC_PROCESS_USERTIME		""
#define DCIDESC_PROCESS_VMSIZE			""
#define DCIDESC_PROCESS_WKSET			""
#define DCIDESC_SYSTEM_CONNECTEDUSERS		"Number of logged in users"
#define DCIDESC_SYSTEM_PROCESSCOUNT		"Total number of processes"
#define DCIDESC_SYSTEM_SERVICESTATE		"State of {instance} service"
#define DCIDESC_SYSTEM_PROCESSCOUNT		"Total number of processes"
#define DCIDESC_SYSTEM_THREADCOUNT		"Total number of threads"
#define DCIDESC_PDH_COUNTERVALUE		""
#define DCIDESC_PDH_VERSION			"Version of PDH.DLL"
#define DCIDESC_SYSTEM_UPTIME			"System uptime"
#define DCIDESC_SYSTEM_CPU_LOADAVG		"Average CPU load for last minute"
#define DCIDESC_SYSTEM_CPU_LOADAVG5		"Average CPU load for last 5 minutes"
#define DCIDESC_SYSTEM_CPU_LOADAVG15		"Average CPU load for last 15 minutes"
#define DCIDESC_SYSTEM_CPU_USAGE_EX		"Average CPU {instance} utilization for last minute"
#define DCIDESC_SYSTEM_CPU_USAGE5_EX		"Average CPU {instance} utilization for last 5 minutes"
#define DCIDESC_SYSTEM_CPU_USAGE15_EX		"Average CPU {instance} utilization for last 15 minutes"
#define DCIDESC_SYSTEM_CPU_USAGE		"Average CPU utilization for last minute"
#define DCIDESC_SYSTEM_CPU_USAGE5		"Average CPU utilization for last 5 minutes"
#define DCIDESC_SYSTEM_CPU_USAGE15		"Average CPU utilization for last 15 minutes"
#define DCIDESC_SYSTEM_IO_DISKQUEUE		"Average disk queue length for last minute"
#define DCIDESC_SERVICECHECK_POP3		""
#define DCIDESC_SERVICECHECK_SMTP		""
#define DCIDESC_SERVICECHECK_SSH		""
#define DCIDESC_SERVICECHECK_HTTP		""
#define DCIDESC_SERVICECHECK_CUSTOM		""
#define DCIDESC_SERVICECHECK_TELNET		""


//
// Connection handle
//

typedef void *HCONN;


//
// Structure for holding enumeration results
//

typedef struct
{
   DWORD dwNumStrings;
   TCHAR **ppStringList;
} NETXMS_VALUES_LIST;


//
// Subagent's parameter information
//

typedef struct
{
   TCHAR szName[MAX_PARAM_NAME];
   LONG (* fpHandler)(TCHAR *, TCHAR *, TCHAR *);
   TCHAR *pArg;
   int iDataType;
   TCHAR szDescription[MAX_DB_STRING];
} NETXMS_SUBAGENT_PARAM;


//
// Subagent's enum information
//

typedef struct
{
   TCHAR szName[MAX_PARAM_NAME];
   LONG (* fpHandler)(TCHAR *, TCHAR *, NETXMS_VALUES_LIST *);
   TCHAR *pArg;
} NETXMS_SUBAGENT_ENUM;


//
// Subagent's action information
//

typedef struct
{
   TCHAR szName[MAX_PARAM_NAME];
   LONG (* fpHandler)(TCHAR *, NETXMS_VALUES_LIST *, TCHAR *);
   TCHAR *pArg;
   TCHAR szDescription[MAX_DB_STRING];
} NETXMS_SUBAGENT_ACTION;


//
// Subagent initialization structure
//

#define NETXMS_SUBAGENT_INFO_MAGIC     ((DWORD)0x20070424)

class CSCPMessage;

typedef struct
{
   DWORD dwMagic;    // Magic number to check if subagent uses correct version of this structure
   TCHAR szName[MAX_SUBAGENT_NAME];
   TCHAR szVersion[32];
	BOOL (* pInit)(TCHAR *);   // Called to initialize subagent. Can be NULL.
   void (* pShutdown)(void);  // Called at subagent unload. Can be NULL.
   BOOL (* pCommandHandler)(DWORD dwCommand, CSCPMessage *pRequest,
                            CSCPMessage *pResponse);
   DWORD dwNumParameters;
   NETXMS_SUBAGENT_PARAM *pParamList;
   DWORD dwNumEnums;
   NETXMS_SUBAGENT_ENUM *pEnumList;
   DWORD dwNumActions;
   NETXMS_SUBAGENT_ACTION *pActionList;
} NETXMS_SUBAGENT_INFO;


//
// Inline functions for returning parameters
//

#ifdef __cplusplus
#ifndef LIBNETXMS_INLINE

#include <nms_agent.h>

inline void ret_string(TCHAR *rbuf, TCHAR *value)
{
   _tcsncpy(rbuf, value, MAX_RESULT_LENGTH - 1);
   rbuf[MAX_RESULT_LENGTH - 1] = 0;
}

inline void ret_int(TCHAR *rbuf, LONG value)
{
   _stprintf(rbuf, _T("%d"), value);
}

inline void ret_uint(TCHAR *rbuf, DWORD value)
{
   _stprintf(rbuf, _T("%u"), value);
}

inline void ret_double(TCHAR *rbuf, double value)
{
   _stprintf(rbuf, _T("%f"), value);
}

inline void ret_int64(TCHAR *rbuf, INT64 value)
{
#ifdef _WIN32
   _stprintf(rbuf, _T("%I64d"), value);
#else    /* _WIN32 */
   _stprintf(rbuf, _T("%lld"), value);
#endif   /* _WIN32 */
}

inline void ret_uint64(TCHAR *rbuf, QWORD value)
{
#ifdef _WIN32
   _stprintf(rbuf, _T("%I64u"), value);
#else    /* _WIN32 */
   _stprintf(rbuf, _T("%llu"), value);
#endif   /* _WIN32 */
}

#endif   /* LIBNETXMS_INLINE */
#else    /* __cplusplus */

void LIBNETXMS_EXPORTABLE ret_string(TCHAR *rbuf, TCHAR *value);
void LIBNETXMS_EXPORTABLE ret_int(TCHAR *rbuf, long value);
void LIBNETXMS_EXPORTABLE ret_uint(TCHAR *rbuf, unsigned long value);
void LIBNETXMS_EXPORTABLE ret_double(TCHAR *rbuf, double value);
void LIBNETXMS_EXPORTABLE ret_int64(TCHAR *rbuf, INT64 value);
void LIBNETXMS_EXPORTABLE ret_uint64(TCHAR *rbuf, QWORD value);

#endif   /* __cplusplus */


//
// Functions from libnetxms
//

#ifdef __cplusplus
extern "C" {
#endif

BOOL LIBNETXMS_EXPORTABLE NxGetParameterArg(TCHAR *param, int index, TCHAR *arg, int maxSize);
void LIBNETXMS_EXPORTABLE NxAddResultString(NETXMS_VALUES_LIST *pList, TCHAR *pszString);
void LIBNETXMS_EXPORTABLE NxDestroyValuesList(NETXMS_VALUES_LIST *pList);
void LIBNETXMS_EXPORTABLE NxWriteAgentLog(int iLevel, TCHAR *pszFormat, ...);
void LIBNETXMS_EXPORTABLE NxSendTrap(DWORD dwEvent, char *pszFormat, ...);
void LIBNETXMS_EXPORTABLE NxSendTrap2(DWORD dwEvent, int nCount, TCHAR **ppszArgList);

#ifdef __cplusplus
}
#endif

#endif   /* _nms_agent_h_ */
