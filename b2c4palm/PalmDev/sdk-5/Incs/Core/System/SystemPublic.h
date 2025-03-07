/******************************************************************************
 *
 * Copyright (c) 1999-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: SystemPublic.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *		Group file, include this to get all public System includes.
 *
 * History:
 *		07/13/99	bob	Created by Bob Ebert
 *		08/08/99	kwk	Deleted JapaneseFEP.h from include list, since it's
 *							a private header in /Libraries/TextServices.
 *		04/30/00	CS		Added new LocaleMgr.h.
 *		05/12/00	kwk	Removed Blitter.h.
 *		06/02/00	CS		Added new PalmLocale.h.
 *		10/05/00	kwk	Removed CharAttr.h, since everything useful in it is now in
 *							in TextMgr.h
 *
 *****************************************************************************/

#ifndef 	__SYSTEMPUBLIC_H__
#define	__SYSTEMPUBLIC_H__

#include <PalmTypes.h>

#include <AlarmMgr.h>
#include <AppLaunchCmd.h>
#include <Bitmap.h>
#include <Chars.h>
#include <ConnectionMgr.h>
#include <ConsoleMgr.h>
#include <Crc.h>
#include <DataMgr.h>
#include <DateTime.h>
#include <DebugMgr.h>
#include <Encrypt.h>
#include <ErrorBase.h>
#include <ErrorMgr.h>
#include <ExgLib.h>
#include <ExgMgr.h>
#include <FeatureMgr.h>
#include <FileStream.h>
#include <FloatMgr.h>
#include <Font.h>
#include <Graffiti.h>
#include <HostControl.h>
#include <IMCUtils.h>
#include <IntlMgr.h>
#include <IrLib.h>
#include <KeyMgr.h>
#include <LocaleMgr.h>
#include <Localize.h>
#include <MemoryMgr.h>
#include <ModemMgr.h>
#include <NetBitUtils.h>
#include <SysEvent.h>			// must come before NetMgr.h due to weird dependency in NetMgr.h
#include <NetMgr.h>
#include <NotifyMgr.h>
#include <OverlayMgr.h>
#include <PalmLocale.h>
#include <Password.h>
#include <PenMgr.h>
#include <Preferences.h>
#include <Rect.h>
#include <ScriptPlugin.h>
#include <SerialDrvr.h>
#include <SerialMgr.h>
#include <SerialLinkMgr.h>
#include <SoundMgr.h>
// #include <StdIOProvider.h>
// #include <StdIOPalm.h>
#include <StringMgr.h>
#include <SysEvtMgr.h>
#include <SystemMgr.h>
#include <SystemResources.h>
#include <SystemPkt.h>
#include <SysUtils.h>
#include <TextMgr.h>
#include <TextServicesMgr.h>
#include <TimeMgr.h>
#include <Window.h>

// from Unix sub-folder
/*
#include <sys_types.h>
#include <arpa_inet.h>
#include <netdb.h>
#include <netinet_in.h>
#include <netinet_in_systm.h>
#include <netinet_ip.h>
#include <netinet_tcp.h>
#include <sys_errno.h>
#include <sys_socket.h>
#include <sys_socketvar.h>
#include <sys_time.h>
#include <sys_uio.h>
#include <unix_fcntl.h>
#include <unix_netdb.h>
#include <unix_stdarg.h>
#include <unix_stdio.h>
#include <unix_stdlib.h>
#include <unix_string.h>
*/


#endif // __SYSTEMPUBLIC_H__
