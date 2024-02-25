/******************************************************************************
 *
 * Copyright (c) 2000-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: BmpGlue.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *    Glue providing compatibility for applications that wish to make calls to
 *    some recent bitmap functions, but which might actually be running on a
 *    system which does not support newer calls.
 *
 * History:
 *		2000-12-22	jwm	Created.
 *
 *****************************************************************************/

#ifndef __BMPGLUE_H__
#define __BMPGLUE_H__

#include <Bitmap.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void BmpGlueGetDimensions (const BitmapType *bitmapP,
                                  Coord *widthP, Coord *heightP, UInt16 *rowBytesP);
extern UInt8 BmpGlueGetBitDepth (const BitmapType *bitmapP);
extern BitmapType *BmpGlueGetNextBitmap (BitmapType *bitmapP);

extern BitmapCompressionType BmpGlueGetCompressionType (const BitmapType *bitmapP);
extern Boolean BmpGlueGetTransparentValue (const BitmapType *bitmapP, UInt32 *transparentValueP);
extern void BmpGlueSetTransparentValue (BitmapType *bitmapP, UInt32 transparentValue);

#ifdef __cplusplus
}
#endif

#endif
