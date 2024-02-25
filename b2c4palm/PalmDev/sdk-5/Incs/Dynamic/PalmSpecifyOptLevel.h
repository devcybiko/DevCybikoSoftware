/******************************************************************************
 *
 * Copyright (c) 1999-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: PalmSpecifyOptLevel.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 *****************************************************************************/

// Include this file (perhaps as a prefix) if the default optimization level doesn't work
// or needs to be adjusted in some way.
//
// Example usages:
//
// #ifdef SPECIFY_OPT_LEVEL
// #pramga optimization_level 1
// #endif
//
// #ifdef SPECIFY_OPT_LEVEL
// #pragma global_optimization off
// #endif

#define SPECIFY_OPT_LEVEL
