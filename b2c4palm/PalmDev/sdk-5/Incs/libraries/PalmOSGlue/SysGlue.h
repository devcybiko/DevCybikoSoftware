/******************************************************************************
 *
 * Copyright (c) 2000-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: SysGlue.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *		Header file for SysGlue library routines.
 *
 *		Glue providing system manager utility routines & bug-fixed routines.
 *
 * History:
 *		01/31/00	kwk	Created by Ken Krugler.
 *		02/09/00	kwk	Added the SysGlueTrapExists macro.
 *
 *****************************************************************************/

#ifndef __SYSGLUE_H__
#define __SYSGLUE_H__

#include <PalmTypes.h>

// On the Simulator, we always assume that the trap (actually the routine) exists,
// since we're also assuming that the user is linking against the latest Palm OS
// core code, which will have a routine for every implemented trap. Since
// SysGetTrapAddress doesn't work on the Simulator, this is the best we can do.

#if (EMULATION_LEVEL == EMULATION_NONE)
#define	SysGlueTrapExists(trapNum)	(SysGlueGetTrapAddress(trapNum) != SysGlueGetTrapAddress(sysTrapSysUnimplemented))
#else
#define	SysGlueTrapExists(trapNum)	true
#endif

#ifdef __cplusplus
	extern "C" {
#endif

void* SysGlueGetTrapAddress(UInt16 trapNum);

#ifdef __cplusplus
	}
#endif

#endif	// __SYSGLUE_H__
