/******************************************************************************
 *
 * Copyright (c) 1995-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: TimeMgr.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *		Time manager functions
 *
 * History:
 *   	1/19/95  roger - Created by Roger Flores
 *
 *****************************************************************************/

#ifndef __TIMEMGR_H__
#define __TIMEMGR_H__


// Include elementary types
#include <PalmTypes.h>
#include <CoreTraps.h>				// Trap Numbers.



/************************************************************
 * Time Manager result codes
 * (timErrorClass is defined in SystemMgr.h)
 *************************************************************/
#define timErrMemory			(timErrorClass | 1)



/************************************************************
 * Function Prototypes
 *************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------------------------------------
// Initialization
//-------------------------------------------------------------------
Err			TimInit(void)	SYS_TRAP(sysTrapTimInit);


//-------------------------------------------------------------------
// API
//-------------------------------------------------------------------

// seconds since 1/1/1904
UInt32		TimGetSeconds(void)		
						SYS_TRAP(sysTrapTimGetSeconds);
					
// seconds since 1/1/1904
void  		TimSetSeconds(UInt32 seconds) 	
						SYS_TRAP(sysTrapTimSetSeconds);
					
// ticks since power on
UInt32 		TimGetTicks(void)					
						SYS_TRAP(sysTrapTimGetTicks);


#ifdef __cplusplus 
}
#endif



#endif // __TIMEMGR_H__
