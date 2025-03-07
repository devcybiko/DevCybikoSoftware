/******************************************************************************
 *
 * Copyright (c) 1999-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: UIColor.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 * 	This file defines structs and functions for setting the "system
 *		colors" that the UI routines use.
 *
 * History:
 *		January 20, 1999	Created by Bob Ebert
 *		08/21/99	kwk	Added UIFieldFepRawText...UIFieldFepConvertedBackground
 *							to the UIColorTableEntries enum.
 *		10/09/99	kwk	Added UIFieldFepUnderline to UIColorTableEntries enum.
 *
 *****************************************************************************/

#ifndef __UICOLOR_H__
#define __UICOLOR_H__

#include <PalmTypes.h>
#include <CoreTraps.h>

#include <Window.h>

typedef enum UIColorTableEntries {
	UIObjectFrame = 0,
	UIObjectFill,
	UIObjectForeground,
	UIObjectSelectedFill,
	UIObjectSelectedForeground,

	UIMenuFrame,
	UIMenuFill,
	UIMenuForeground,
	UIMenuSelectedFill,
	UIMenuSelectedForeground,

	UIFieldBackground,
	UIFieldText,
	UIFieldTextLines,
	UIFieldCaret,
	UIFieldTextHighlightBackground,
	UIFieldTextHighlightForeground,
	UIFieldFepRawText,
	UIFieldFepRawBackground,
	UIFieldFepConvertedText,
	UIFieldFepConvertedBackground,
	UIFieldFepUnderline,

	UIFormFrame,
	UIFormFill,

	UIDialogFrame,
	UIDialogFill,

	UIAlertFrame,
	UIAlertFill,

	UIOK,
	UICaution,
	UIWarning,

	UILastColorTableEntry
} UIColorTableEntries;



#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------
// UI Color Table Manipulation Routines 
//------------------------------------------------------------

extern IndexedColorType UIColorGetTableEntryIndex(UIColorTableEntries which)
							SYS_TRAP(sysTrapUIColorGetTableEntryIndex);

extern void UIColorGetTableEntryRGB(UIColorTableEntries which, RGBColorType *rgbP)
							SYS_TRAP(sysTrapUIColorGetTableEntryRGB);

extern Err UIColorSetTableEntry(UIColorTableEntries which, const RGBColorType *rgbP)
							SYS_TRAP(sysTrapUIColorSetTableEntry);

extern Err UIColorPushTable(void)
							SYS_TRAP(sysTrapUIColorPushTable);

extern Err UIColorPopTable(void)
							SYS_TRAP(sysTrapUIColorPopTable);


#ifdef __cplusplus 
}
#endif

#endif //__UICOLOR_H__
