/******************************************************************************
 *
 * Copyright (c) 1994-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: SelTime.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *	  This file defines select time structures and routines.
 *
 * History:
 *		December 6, 1994	Created by Roger Flores
 *           Nick Twyman 8/4/98. Added SelectOneTime trap
 *
 *****************************************************************************/

#ifndef	__SELTIME_H__
#define	__SELTIME_H__

#include <PalmTypes.h>
#include <CoreTraps.h>

#include <DateTime.h>
//-------------------------------------------------------------------
// structures
//-------------------------------------------------------------------


typedef struct {
	 UInt8 hours;
	 UInt8 minutes;
	 UInt8 seconds;
	 UInt8 reserved;
} HMSTime;

#ifdef __cplusplus
extern "C" {
#endif

// This is slated to be deleted in the next version.
extern Boolean SelectTimeV33 (TimeType *startTimeP, TimeType *EndTimeP,
	Boolean untimed, const Char *titleP, Int16 startOfDay)
						SYS_TRAP(sysTrapSelectTimeV33);

extern Boolean SelectTime (TimeType *startTimeP, TimeType *EndTimeP,
	Boolean untimed, const Char *titleP, Int16 startOfDay, Int16 endOfDay, 
	Int16 startOfDisplay)
						SYS_TRAP(sysTrapSelectTime);

extern Boolean SelectOneTime(Int16 *hour, Int16 *minute, const Char *titleP)
						SYS_TRAP(sysTrapSelectOneTime);

#ifdef __cplusplus 
}
#endif

#endif // __SELTIME_H__
