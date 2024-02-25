/******************************************************************************
 *
 * Copyright (c) 1994-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: Locale_jpJP.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *	This file is used for CodeWarrior projects incorporating Japanese resources.
 *
 * History:
 *	12/13/94	PBS	Created by Phillip Shoemaker.
 *	09/17/99	kwk	Modified for new Simulator locale strategy.
 *	09/20/99	kwk	Sync SIMULATOR_SYSRESOURCE_NAME w/Vivek's latest.
 *	10/05/99	kwk	Added LOCALE_SUFFIX
 *	04/11/00	jmp	Conditionalized SIMULATOR_MEMORYCARD1_SIZE since
 *					the Launcher's Simulator build already makes it
 *					bigger.
 *	06/06/00	kwk	Change default location of SIMULATOR_NONLATIN_SUPPORT file
 *					to be in /Core/Locales/ShiftJIS/
 *	07/05/00	kwk	Bumped SIMULATOR_MEMORYCARD1_SIZE, for larger Japanese data
 *
 *****************************************************************************/

#ifndef __LOCALE_JPJP_H__
#define __LOCALE_JPJP_H__

#define RESOURCE_FILE_PREFIX				"Localized:jpJP:"
#define LOCALE_SUFFIX						"_jpJP"

#define SIMULATOR_CHARENCODING			charEncodingPalmSJIS
#ifndef SIMULATOR_MEMORYCARD1_SIZE
// DOLATER kwk - trim this to the minimum size, once Japanese data is compressed.
#define SIMULATOR_MEMORYCARD1_SIZE		0x160000
#endif
#define SIMULATOR_SYSTRES_NAME			"sys_jpJP.tres"

#define SIMULATOR_NONLATIN_SUPPORT		"PalmRez Japanese Support"

#endif
