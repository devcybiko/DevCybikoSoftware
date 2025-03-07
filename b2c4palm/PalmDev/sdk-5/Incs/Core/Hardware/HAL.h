/******************************************************************************
 *
 * Copyright (c) 1999-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: HAL.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *		General HAL Equates. This header file contains function prototypes for
 *  HAL routines, and is used by both Palm OS and the HAL module.
 *
 * History:
 *		 5/31/99	SCL		Created by Steve Lemke
 *		 8/24/00	SCL		Cleanup; moved boot-related prototypes (HwrInitProcPtr,
 *								HwrPreRAMInit, and HwrInit) to "HwrBoot.h"
 *
 *****************************************************************************/


// #ifdef	NON_PORTABLE	   // So app's don't mistakenly include this

#ifndef __HAL_H__
#define __HAL_H__

//#include <PalmOptErrorCheckLevel.h>
#include <ErrorBase.h>

/***********************************************************************
 * Hardware Manager (HAL) constants
 **********************************************************************/

// Error codes related to HwrCustom() API
#define	hwrErrHwrCustomNotImplemented	(hwrErrorClass | 1)
#define	hwrErrCreatorNotSupported		(hwrErrorClass | 2)
#define	hwrErrSelectorNotSupported		(hwrErrorClass | 3)
#define hwrErrParamTooSmall				(hwrErrorClass | 4)


/************************************************************
 * HAL trap macros
 *************************************************************/

#if DISABLE_HAL_TRAPS
	#define HAL_CALL(trapNum) 
#else
 	#define HAL_CALL(trapNum) \
		_HAL_API(_CALL)(_HAL_TABLE, trapNum)
#endif


/**************************************************************************
 * Prototypes of functions used only when running on the real hardware
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


// HwrCustom call is new in Palm OS 4.0, and many HALs may not support it.
// This won't cause problems though, since the OS installs a default handler
// (in case the HAL doesn't install its own). The default OS handler simply
// always returns hwrErrHwrCustomNotImplemented.
Err HwrCustom(UInt32 creator, UInt32 opCode, void * paramP, UInt16 * paramSizeP)
				HAL_CALL(sysTrapHwrCustom);


#ifdef __cplusplus 
}
#endif


#endif 	//__HAL_H__

// #endif 	// NON_PORTABLE
