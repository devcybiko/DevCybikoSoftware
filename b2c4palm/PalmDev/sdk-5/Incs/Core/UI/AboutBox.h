/******************************************************************************
 *
 * Copyright (c) 1995-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: AboutBox.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *	  This file defines About Box routines
 *
 * History:
 *		October 25th, 1995	Created by Christopher Raff
 *
 *****************************************************************************/

#ifndef __ABOUTBOX_H__
#define __ABOUTBOX_H__

#include <PalmTypes.h>
#include <CoreTraps.h>

#ifdef __cplusplus
extern "C" {
#endif

// WARNING!!! This routine is for the private use of Palm applications.
// It is released with the public headers so that the sample apps
// released with the SDK can be compiled by developers.
void AbtShowAbout (UInt32 creator)
		SYS_TRAP(sysTrapAbtShowAbout);
		
#ifdef __cplusplus 
}
#endif

#endif // __ABOUTBOX_H__
