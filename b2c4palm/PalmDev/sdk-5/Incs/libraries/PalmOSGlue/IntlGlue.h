/******************************************************************************
 *
 * Copyright (c) 1998-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: IntlGlue.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *         	Header file for IntlGlue library routines.
 *
 * IntlGlue provides compatibility for applications that wish to make
 *	calls to Text Manager, but which might actually be running on devices
 *	with roms that do not have this support available, in which case the glue
 *	code executes the standard (Latin only) routines instead. This library
 *	can only be used on post-1.0 roms!!!
 *
 * Written by TransPac Software, Inc.
 *
 * History:
 *			Created by Ken Krugler
 *	14 Sep 98	CSS	Added this header and changed name (from IntlMgrLib.h).
 *				CSS	Added new Text<xxx> library-using macros.
 *				CSS	All the Txt<xxx> macros #defined in TextMgr.h are
 *					now #undef'ed here (#ifndef DIRECT_INTLMGR_CALLS) and
 *					then redefined to use our Text<xxx> library-using macros.
 *				CSS	Added an extern "C" wrapper around the routine
 *					declarations so non-C++ guys will see them.
 *	15 Sep 98	kwk	Sync'd with latest TextMgr.h header file.
 *	15 Oct 98	kwk	Sync'd again with latest TextMgr.h header file.
 *				kwk	Added some missing macros for remapping Txt->Text routine names.
 *				kwk	Added GetIntlRoutineAddress routine declaration.
 *	02 Jun 99	kwk	Changed names of routines to TxtGlueXXXX.
 *	2000-11-15	jwm	Reengineered IntlGlueGetRoutineAddress.
 *
 *****************************************************************************/

#ifndef __INTLGLUE_H__
#define __INTLGLUE_H__

#include <IntlMgr.h>

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef _BUILDING_TXTLATIN
extern void
	TxtLatinByteAttr(), TxtLatinCharAttr(), TxtLatinCharXAttr(),
	TxtLatinCharSize(), TxtLatinCharWidth(),
	TxtLatinGetPreviousChar(), TxtLatinGetNextChar(), TxtLatinGetChar(),
	TxtLatinSetNextChar(), TxtLatinReplaceStr(), TxtLatinParamString(),
	TxtLatinCharBounds(), TxtLatinGetTruncationOffset(), TxtLatinFindString(),
	TxtLatinWordBounds(), TxtLatinGetWordWrapOffset(), TxtLatinCharEncoding(),
	TxtLatinStrEncoding(), TxtLatinMaxEncoding(), TxtLatinEncodingName(),
	TxtLatinNameToEncoding(), TxtLatinTransliterate(), TxtLatinCharIsValid(),
	TxtLatinCaselessCompare(), TxtLatinCompare(), TxtLatinPrepFindString();
#endif

// IntlGlueGetRoutineAddress must be passed the desired selector (from the
// list in IntlMgr.h), just as with IntlGetRoutineAddress.  You must also
// pass the corresponding latinSymbol from the list above.  Being passed
// as an argument to IntlGlueGetRoutineAddress is the only useful use for
// these symbols -- don't try to do anything else with them. 
//
// If the Int'l Mgr (and the appropriate Text Mgr routines) exists, then
// the result will be the same as calling IntlGetRoutineAddress() with the
// appropriate routine selector. If Text Mgr support is not available, then
// this call returns the address of the corresponding glue code routine.
//
// Note that the address returned is only valid so long as the application
// stays locked in memory, thus this routine should be called at or after
// your StartApplication routine, and only used up to the point where your
// application terminates.
//
// (In previous SDKs, there was an IntlGlueGetRoutineAddress function which
// took different parameters.  It was never documented, and has been
// replaced by this one.)

void *IntlGlueGetRoutineAddress(IntlSelector selector, const void *latinSymbol);

#ifdef __cplusplus
	}
#endif

#endif // __INTLGLUE_H__
