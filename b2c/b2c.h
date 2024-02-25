/**
  * The B2C project is a set of programs and libraries
  * that comprise a languate translator.  B2C compiles
  * a BASIC program into C which is compiled by the Cybiko
  * SDK 2.10 into an application.
  *
  *  Copyright 2004 by Gregory Smith
  *  (greg@alcorgrp.com)
  *
  *  This program is free software; you can redistribute it and/or
  *  modify it under the terms of the GNU General Public License
  *  as published by the Free Software Foundation; either version 2
  *  of the License, or (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  *
  * @author Gregory Smith (http://www.greg-smith.com, Greg@AlcorGrp.com)
  * @version 1.0
  */
#ifndef _B2C_H_
#define _B2C_H_

#define VERSION "5b"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>
#include "bprogram.h"

#define FALSE 0
#define TRUE (!FALSE)

#define WHITE_SPACE " \t\n\r"
#define SAME(a,b) (strcmp(a?a:"", b?b:"")==0)
#define NSAME(a,b,c) (strncmp(a?a:"", b?b:"", c)==0)
#define class typedef struct 

#define MALLOC(a,b) (b *)malloc(sizeof(b)*a)
#define CALLOC(a,b) (b *)calloc(sizeof(b), a)

void dbg0(char *fmt, ...);

//#define DBG0 dbg0
#define DBG0 
enum {
  TYPE_DIM,
  TYPE_IF,
  TYPE_FOR,
  TYPE_OPEN,
  TYPE_CLOSE,
  TYPE_PRINT,
  TYPE_FUNC,
  TYPE_MAX,
  TYPE_THEN,
  TYPE_ELSE,
  TYPE_ELSEIF,
  TYPE_WHILE,
  TYPE_FUNCTION,
  TYPE_PROGRAM,
  TYPE_OP,
  TYPE_TERM,
  TYPE_BODY,
  TYPE_EXPR,
  TYPE_STMT,
  TYPE_READ,
  TYPE_APPEND,
  TYPE_WRITE,
  TYPE_PARM,
  TYPE_STATEMENT,
  TYPE_EXIT,
  TYPE_LIST,
  TYPE_PARAM,
  TYPE_FUNCCALL,
  TYPE_WAIT,
  TYPE_INPUT,
  TYPE_LINE,
  TYPE_POINT,
  TYPE_INK,
  TYPE_PAPER,
  TYPE_CLS,
  TYPE_PRINTXY,
  TYPE_MATH,
  TYPE_KEY,
  TYPE_EOF,
  TYPE_PUT,
  TYPE_GET,
  TYPE_PRINTNO,
  TYPE_MID,
  TYPE_RIGHT,
  TYPE_INLINE,
  TYPE_FONT,
  TYPE_GOTO,
  TYPE_LABEL,
  TYPE_TYPE,
  TYPE_SPRITE,
  TYPE_MOVE,
  TYPE_REDRAW,
  TYPE_COLLISION,
  TYPE_MUSIC,
  TYPE_VIBRATE,
  TYPE_ONGOTO,
  TYPE_ONGOSUB,
  TYPE_SCORE,
  TYPE_MENU,
  TYPE_KEYCLICK,
  TYPE_EXITPROGRAM,
  TYPE_OUTLINE,
  TYPE_GETCHAR,
  TYPE_GETKEY,
  TYPE_CHAR,
  TYPE_SENDMESSAGE,
  TYPE_SPRINT,
  TYPE_TOKENIZE,
  TYPE_USERMENU,
  TYPE_TOCYID,
  TYPE_TOUSER,
  TYPE_DIALOG,
  TYPE_3DROOM,
  TYPE_3DSPRITE,
  TYPE_3DREDRAW,
  TYPE_3DWALL,
  TYPE_3DCOLLISION,
  TYPE_3DMOVE,
  TYPE_3DRMOVE,
  TYPE_3DGET,
  TYPE_SPRITE_GET,
  TYPE_FINDFILE,
  TYPE_NEXTFILE,
  TYPE_FILELIST,
  TYPE_INPUTXY,
  TYPE_RECT,
  TYPE_RECTFILL,
  TYPE_PAGE,
  TYPE_PAGECOPY,
  TYPE_REMOVE,
  TYPE_RENAME,
  TYPE_EXISTS,
  TYPE_LOAD,
  TYPE_LEN,
  TYPE_WRAP,
  TYPE_CIRCLE,
  TYPE_CIRCFILL,
  TYPE_COMMAND
};

enum {
  MODE_READ,
  MODE_WRITE,
  MODE_APPEND,
  MODE_ARCHIVE
};

enum {
  MUSIC_LOAD,
  MUSIC_PLAY,
  MUSIC_STOP,
};

enum {
  MUSIC_BACKGROUND,
  MUSIC_FOREGROUND
};

extern FILE *infile;
extern FILE *outfile;
extern char *data_type[];
extern char *node_types[];
extern Bprogram *bprogram;
extern char g_infname[256];
extern char g_outfname[256];
extern void doerr2(char *fmt, ...);

#endif
