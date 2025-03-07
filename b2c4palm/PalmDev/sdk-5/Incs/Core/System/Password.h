/******************************************************************************
 *
 * Copyright (c) 1994-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: Password.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *		Password include file
 *
 * History:
 *		4/1/95 - created by Roger Flores
 *
 *****************************************************************************/

#ifndef __PASSWORD_H__
#define __PASSWORD_H__

// Include elementary types
#include <PalmTypes.h>					// Basic types
#include <CoreTraps.h>					// Trap Numbers.


#define pwdLength						32
#define pwdEncryptionKeyLength	64

#ifdef __cplusplus
extern "C" {
#endif

Boolean 	PwdExists()
				SYS_TRAP(sysTrapPwdExists);
				
Boolean 	PwdVerify(Char *string)
				SYS_TRAP(sysTrapPwdVerify);
				
void 		PwdSet(Char *oldPassword, Char *newPassword)
				SYS_TRAP(sysTrapPwdSet);
				
void 		PwdRemove(void)
				SYS_TRAP(sysTrapPwdRemove);
				
#ifdef __cplusplus 
}
#endif
				
#endif // __PASSWORD_H__
