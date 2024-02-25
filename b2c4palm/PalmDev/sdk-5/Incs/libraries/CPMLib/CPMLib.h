/******************************************************************************
 *
 * Copyright (c) 1994-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: CPMLib.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *    This module contains the interface definition for the Cryptographic
 *    Provider Manager library on Pilot.
 *
 * History:
 *			Created by Richard Levenberg
 *
 *****************************************************************************/

#ifndef CPMLIB_H_
#define	CPMLIB_H_

#if defined(_WIN32) || defined(__arm)
#include "CPMLibARMInterface.h"
#else
#include "CPMLib68KInterface.h"
#endif 

#endif /* CPMLIB_H_ */
