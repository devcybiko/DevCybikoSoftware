/******************************************************************************
 *
 * Copyright (c) 1999-2002 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: PalmOptUserMode.h
 *
 * Release: Palm OS SDK 5.0 (111823)
 *
 *****************************************************************************/

#include <BuildDefines.h>
#ifdef USER_MODE
#undef USER_MODE
#endif
#define USER_MODE USER_MODE_NORMAL
