/******************************************************************************
 *
 * Copyright (c) 1998-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: TxtGlue.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *		Header file for TxtGlue library routines.
 *
 * TxtGlue provides compatibility for applications that wish to make
 *	calls to Text Manager, but which might actually be running on devices
 *	with roms that do not have this support available, in which case the glue
 *	code executes the standard (Latin only) routines instead. This library
 *	can only be used on post-1.0 roms!!!
 *
 * History:
 *		09/14/98	CS		Added this header and changed name (from IntlMgrLib.h).
 *					CS		Added new Text<xxx> library-using macros.
 *					CS		All the Txt<xxx> macros #defined in TextMgr.h are
 *							now #undef'ed here (#ifndef DIRECT_INTLMGR_CALLS) and
 *							then redefined to use our Text<xxx> library-using macros.
 *					CS		Added an extern "C" wrapper around the routine
 *							declarations so non-C++ guys will see them.
 *		09/15/98	kwk	Sync'd with latest TextMgr.h header file.
 *		10/15/98	kwk	Sync'd again with latest TextMgr.h header file.
 *					kwk	Added some missing macros for remapping Txt->Text routine names.
 *					kwk	Added GetIntlRoutineAddress routine declaration.
 *		06/02/99	kwk	Changed names of routines to TxtGlueXXXX.
 *		07/14/99	kek	Deleted TxtGluePrepFindString.
 *		11/06/99	kwk	Put back in TxtGluePrepFindString, using the old API.
 *		02/03/00	kwk	Added TxtGlueTruncateString.
 *		05/12/00	kwk	Deprecated TxtGlueCharWidth.
 *		12/11/00	kwk	Removed duplicated declarations for TxtGlueUpper/LowerChar, etc.
 *  2000-12-22	jwm	TxtGlueCharWidth is still deprecated -- use
 *							FntGlueWCharWidth instead -- but we don't want to break code.
 *
 *****************************************************************************/

#ifndef __TXTGLUE_H__
#define __TXTGLUE_H__

#include <TextMgr.h>

// Duplicate versions of all of the macros in TextMgr.h that call the library
// routines instead:

#define TxtGlueCharIsSpace(ch)		((TxtGlueCharAttr(ch) & charAttrSpace) != 0)
#define TxtGlueCharIsPrint(ch)		((TxtGlueCharAttr(ch) & charAttrPrint) != 0)
#define TxtGlueCharIsDigit(ch)      ((TxtGlueCharAttr(ch) & charAttr_DI) != 0)
#define TxtGlueCharIsAlNum(ch)		((TxtGlueCharAttr(ch) & charAttrAlNum) != 0)
#define TxtGlueCharIsAlpha(ch)		((TxtGlueCharAttr(ch) & charAttrAlpha) != 0)
#define TxtGlueCharIsCntrl(ch)		((TxtGlueCharAttr(ch) & charAttrCntrl) != 0)
#define TxtGlueCharIsGraph(ch)		((TxtGlueCharAttr(ch) & charAttrGraph) != 0)
#define TxtGlueCharIsLower(ch)      ((TxtGlueCharAttr(ch) & charAttr_LO) != 0)
#define TxtGlueCharIsPunct(ch)      ((TxtGlueCharAttr(ch) & charAttr_PU) != 0)
#define TxtGlueCharIsUpper(ch)      ((TxtGlueCharAttr(ch) & charAttr_UP) != 0)
#define TxtGlueCharIsHex(ch)        ((TxtGlueCharAttr(ch) & charAttr_XD) != 0)
#define TxtGlueCharIsDelim(ch)		((TxtGlueCharAttr(ch) & charAttrDelim) != 0)

#define	TxtGluePreviousCharSize(inText, inOffset)	TxtGlueGetPreviousChar((inText), (inOffset), NULL)
#define	TxtGlueNextCharSize(inText, inOffset)		TxtGlueGetNextChar((inText), (inOffset), NULL)

#ifdef __cplusplus
	extern "C" {
#endif

UInt8 TxtGlueByteAttr(UInt8 inByte);

UInt16 TxtGlueCharAttr(WChar inChar);

UInt16 TxtGlueCharXAttr(WChar inChar);

UInt16 TxtGlueCharSize(WChar inChar);

Int16 TxtGlueCharWidth(WChar inChar);

UInt16 TxtGlueGetPreviousChar(const Char* inText, UInt32 inOffset, WChar* outChar);

UInt16 TxtGlueGetNextChar(const Char* inText, UInt32 inOffset, WChar* outChar);

WChar TxtGlueGetChar(const Char* inText, UInt32 inOffset);

UInt16 TxtGlueReplaceStr(Char* ioStr, UInt16 inMaxLen, const Char* inParamStr, UInt16 inParamNum);

UInt16 TxtGlueSetNextChar(Char* ioText, UInt32 inOffset, WChar inChar);

WChar TxtGlueCharBounds(const Char* inText, UInt32 inOffset, UInt32* outStart, UInt32* outEnd);

Boolean TxtGlueFindString(const Char* inSourceStr, const Char* inTargetStr,
			UInt32* outPos, UInt16* outLength);

Boolean TxtGlueWordBounds(const Char* inText, UInt32 inLength, UInt32 inOffset,
			UInt32* outStart, UInt32* outEnd);

CharEncodingType TxtGlueCharEncoding(WChar inChar);

CharEncodingType TxtGlueStrEncoding(const Char* inStr);

CharEncodingType TxtGlueMaxEncoding(CharEncodingType a, CharEncodingType b);

const Char* TxtGlueEncodingName(CharEncodingType inEncoding);

Err TxtGlueTransliterate(const Char* inSrcText, UInt16 inSrcLength, Char* outDstText,
			UInt16* ioDstLength, TranslitOpType inOp);

void TxtGlueUpperStr(Char* ioString, UInt16 inMaxLength);

void TxtGlueLowerStr(Char* ioString, UInt16 inMaxLength);

WChar TxtGlueUpperChar(WChar inChar);

WChar TxtGlueLowerChar(WChar inChar);

UInt32 TxtGlueGetTruncationOffset(const Char* inText, UInt32 inOffset);

Boolean TxtGlueTruncateString(Char* ioStringP, UInt16 inMaxWidth);

Boolean TxtGlueCharIsValid(WChar inChar);

Int16 TxtGlueCaselessCompare(const Char* s1, UInt16 s1Len, UInt16* s1MatchLen,
			const Char* s2, UInt16 s2Len, UInt16* s2MatchLen);

Int16 TxtGlueCompare(const Char* s1, UInt16 s1Len, UInt16* s1MatchLen,
			const Char* s2, UInt16 s2Len, UInt16* s2MatchLen);

WChar TxtGlueGetNumericSpaceChar(void);

WChar TxtGlueGetHorizEllipsisChar(void);

Boolean TxtGlueCharIsVirtual(UInt16 inModifiers, WChar inChar);

Char* TxtGlueStripSpaces(Char* ioStr, Boolean leading, Boolean trailing);

Char* TxtGlueParamString(const Char* inTemplate, const Char* param0,
			const Char* param1, const Char* param2, const Char* param3);

void TxtGluePrepFindString(const Char* inSrcP, Char* outDstP, UInt16 inDstSize);

#ifdef __cplusplus
	}
#endif

#endif	// __TXTGLUE_H__
