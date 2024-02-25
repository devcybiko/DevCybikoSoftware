/******************************************************************************
 *
 * Copyright (c) 1994-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: ConsoleMgr.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *		This module implements simple text in and text out to a console 
 *  application on the other end of the serial port. It talks through
 *  the Serial Link Manager and sends and receives packets of type slkPktTypeConsole.
 *
 * History:
 *   	10/25/94  RM - Created by Ron Marianetti
 *
 *****************************************************************************/

#ifndef __CONSOLEMGR_H__
#define __CONSOLEMGR_H__

// Include elementary types
#include <PalmTypes.h>					// Basic types
#include <CoreTraps.h>					// Trap Numbers.


/********************************************************************
 * Console Manager Routines
 ********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

Err		ConPutS(const Char *message)
				SYS_TRAP(sysTrapConPutS);
				
Err		ConGetS(Char *message, Int32 timeout)
				SYS_TRAP(sysTrapConGetS);


#ifdef __cplusplus 
}
#endif




#endif // __CONSOLEMGR_H__
