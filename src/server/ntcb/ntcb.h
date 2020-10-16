/*
** NetXMS - Network Management System
** Copyright (C) 2003-2020 Raden Solutions
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
** File: ntcb.h
**
**/

#ifndef _ntcb_h_
#define _ntcb_h_

#include <nms_common.h>
#include <nms_util.h>
#include <nms_core.h>
#include <nxmodule.h>
#include <nxconfig.h>

#define DEBUG_TAG_NTCB  _T("ntcb")

/**
 * Telemetry data types
 */
enum class TelemetryDataType
{
   U64,    // uint64_t
   U32,    // uint32_t
   U16,    // uint16_t
   U8,     // uint8_t, unsigned char
   I64,    // int64_t
   I32,    // int32_t
   I16,    // int16_t
   I8,     // int8_t, char
   F32,    // float
   F64,    // double,
   STRUCT  // structure
};

/**
 * Received telemetry value
 */
union TelemetryValue
{
   uint64_t u64;
   uint32_t u32;
   uint16_t u16;
   uint8_t u8;
   int64_t i64;
   int32_t i32;
   int16_t i16;
   int8_t i8;
   float f32;
   double f64;
   BYTE raw[8];
};

/**
 * Telemetry field definition
 */
struct TelemetryField
{
   size_t size;
   TelemetryDataType dataType;
   const TCHAR *name;  // Parameter name if value can be pushed directly or nullptr
   void (*handler)(TelemetryDataType, TelemetryValue, shared_ptr<MobileDevice>);   // Custom handler or nullptr
};

/**
 * NTCB device session
 */
class NTCBDeviceSession
{
private:
   uint32_t m_id;
   SocketConnection m_socket;
   InetAddress m_address;
   uint32_t m_ntcbSenderId;
   uint32_t m_ntcbReceiverId;
   int m_flexProtoVersion;
   int m_flexStructVersion;
   int m_flexFieldCount;
   uint8_t m_flexFieldMask[32];
   shared_ptr<MobileDevice> m_device;

   void readThread();
   void processNTCBMessage(const void *data, size_t size);
   void processFLEXMessage();
   void processArchiveTelemetry();
   void processCurrentTelemetry();
   void processExtraordinaryTelemetry();
   bool readTelemetryRecord();

   void sendNTCBMessage(const void *data, size_t size);

   void debugPrintf(int level, const TCHAR *format, ...);

public:
   NTCBDeviceSession(SOCKET s, const InetAddress& addr);
   ~NTCBDeviceSession();

   bool start();
};

extern uint32_t g_ntcbSocketTimeout;

#endif
