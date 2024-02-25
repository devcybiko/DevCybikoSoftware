/******************************************************************************
 *
 * Copyright (c) 2001-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: FrmGlue.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *		Glue providing compatibility for applications that wish
 *		to make calls to the Form Manager, but which might be running
 *		on a system which does not support newer calls.
 *
 * History:
 *		08/29/00	kwk	Created by Ken Krugler.
 *		01/08/01	tlw	Added FrmGlueGetObjectUsable.
 *
 *****************************************************************************/

#ifndef __FRMGLUE_H__
#define __FRMGLUE_H__

#include <Field.h>
#include <Form.h>

#ifdef __cplusplus
	extern "C" {
#endif

extern FieldType* FrmGlueGetActiveField(const FormType* formP);
extern Boolean FrmGlueGetObjectUsable(const FormType *formP, UInt16 objIndex);

extern UInt16 FrmGlueGetDefaultButtonID (const FormType *formP);
extern void FrmGlueSetDefaultButtonID (FormType *formP, UInt16 defaultButton);
extern UInt16 FrmGlueGetHelpID (const FormType *formP);
extern void FrmGlueSetHelpID (FormType *formP, UInt16 helpRscID);
extern UInt16 FrmGlueGetMenuBarID (const FormType *formP);
extern FontID FrmGlueGetLabelFont (const FormType *formP, UInt16 labelID);
extern void FrmGlueSetLabelFont (FormType *formP, UInt16 labelID, FontID fontID);
extern FormEventHandlerType* FrmGlueGetEventHandler (const FormType *formP);

#ifdef __cplusplus
	}
#endif

#endif	// __FRMGLUE_H__
