/******************************************************************************
 *
 * Copyright (c) 2001-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: LstGlue.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 * Description:
 *    Glue providing compatibility for applications that wish to make calls to
 *    some recent list functions, but which might actually be running on a
 *    system which does not support these newer calls.
 *
 * History:
 *		2001-02-26	jwm	Created.
 *
 *****************************************************************************/

#ifndef __LSTGLUE_H__
#define __LSTGLUE_H__

#include <List.h>

#ifdef __cplusplus
extern "C" {
#endif

extern Int16 LstGlueGetTopItem (const ListType *listP);

extern FontID LstGlueGetFont (const ListType *listP);
extern void LstGlueSetFont (ListType *listP, FontID fontID);
extern Char** LstGlueGetItemsText (const ListType *listP);
extern void LstGlueSetIncrementalSearch (ListType *listP, Boolean incrementalSearch);

#ifdef __cplusplus
}
#endif

#endif
