/******************************************************************************
 *
 * Copyright (c) 2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: AddressSortLib.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *	Include file for the Address Book to access sort routines
 *	found in an ARM library, for performance reasons.
 *
 * History:
 *	2002-01-16	???	Created by Vincent Leclaire.
 *	2002-01-18	kwk	Added library type/creator defines. Removed
 *					useless const from routine APIs.
 *
 *****************************************************************************/

#ifndef __ADDRESSSORTLIB_H__
#define	__ADDRESSSORTLIB_H__

#define AddressSortLibTrapAddrDBSort (sysLibTrapCustom)
#define AddressSortLibTrapAddrJDBSort (sysLibTrapCustom + 1)

// Type and creator of library.
#define	addrSortLibType		sysFileTLibrary
#define addrSortLibCreator	'adbs'

Err		AddrDBSort(UInt16 libRefnum, DmOpenRef dbR, Int16 other) 
			SYS_TRAP(AddressSortLibTrapAddrDBSort);

Err		AddrJDBSort(UInt16 libRefnum, DmOpenRef dbR, Int16 other) 
			SYS_TRAP(AddressSortLibTrapAddrJDBSort);


#endif 	//__ADDRESSSORTLIB_H__
