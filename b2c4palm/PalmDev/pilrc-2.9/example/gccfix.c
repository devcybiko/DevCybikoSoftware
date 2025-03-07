/*
 * @(#)gccfix.c
 *
 * Copyright 2000, Aaron Ardiri (mailto:aaron@ardiri.com)
 * All rights reserved.
 *
 * This file was generated as part of the "pilrctst" program developed for 
 * the Palm Computing Platform designed by Palm: http://www.palm.com/ 
 *
 * The contents of this file are to be used for educational purposes
 * only in understanding the PilRC application.  Redistribution or 
 * modification without prior consent of the original author is prohibited. 
 *
 * - source code obtained from John Marshall (john_w_marshall@palm.com)
 */

#include "palm.h"

void
_GccReleaseCode(UInt16 cmd UNUSED, void *pbp UNUSED, UInt16 flags)
{
  if (flags & sysAppLaunchFlagNewGlobals) {

    MemHandle codeH;
    int resno;

    for (resno = 2; (codeH = DmGet1Resource ('code', resno)) != NULL; resno++) {
      MemHandleUnlock (codeH);
      DmReleaseResource (codeH);
    }
  }
}
