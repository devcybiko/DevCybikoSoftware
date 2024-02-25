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
#include "b2c.h"
#include "bterm.h"

FILE *outfile;
FILE *infile;
Bprogram *bprogram;
extern Node *body_stack[32];
int yyparse();
extern int body_stack_n;

char *node_types[] = {
  "dim",
  "if",
  "for",
  "open",
  "close",
  "print",
  "function",
  "max",
  "then",
  "else",
  "elseif",
  "while",
  "function",
  "program",
  "op",
  "term",
  "body",
  "expr",
  "stmt",
  "read",
  "append",
  "write",
  "parm",
  "statement",
  "exit",
  "list",
  "param",
  "funccall",
  "wait",
  "input",
  "line",
  "point",
  "ink",
  "paper",
  "cls",
  "printxy",
  "math",
  "key",
  "eof",
  "put",
  "get",
  "printno",
  "mid",
  "right",
  "inline",
  "font",
  "goto",
  "label",
  "type",
  "sprite",
  "move",
  "redraw",
  "collision",
  "music",
  "vibrate",
  "on_goto",
  "on_gosub",
  "score",
  "menu",
  "keyclick",
  "exitprogram",
  "outline",
  "getchar",
  "getkey",
  "char",
  "sendmessage",
  "sprint",
  "tokenize",
  "usermenu",
  "tocyid",
  "touser",
  "dialog",
  "3droom",
  "3dsprite",
  "3dredraw",
  "3dwall",
  "3dcollision",
  "3dmove",
  "3drmove",
  "3dget",
  "sprite_get",
  "findfile",
  "nextfile",
  "filelist",
  "inputxy",
  "rect",
  "rectfill",
  "page",
  "pagecopy",
  "remove",
  "rename",
  "exists",
  "load",
  "len",
  "wrap",
  "circle",
  "circfill",
0};

char *data_type[] = {
  "void",
  "char",
  "int",
  "long",
  "fixed",
  "struct",
  0};

static int dbg0_level=0;

static void tab()
{
  int i;
  for(i=0; i<dbg0_level; i++)
    printf(" | ");
}

void dbg0(char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);

  if (fmt[0] == '<') dbg0_level--;
  tab();
  vprintf(fmt, ap);
  if (fmt[0] == '>') dbg0_level++;
  va_end(ap);
}

void doerr(s)
     char *s;
{
  perror(s);
  exit(1);
}

void doerr2(char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);

  vprintf(fmt, ap);
  printf("\n");
  exit(1);
}

extern int yydebug;
char g_infname[256];
char g_outfname[256];

main(argc, argv)
     int argc;
     char **argv;
{
//    yydebug = 1;

	fprintf(stderr, "B2C - Basic to C Compiler Version %s\n", VERSION);
    fprintf(stderr, "Copyright (C) 2001-2002 The Alcor Group, Inc.\n");
    fprintf(stderr, "Written by Gregory Smith\n");
	fflush(stderr);

    if (argc > 1)
    {
		strcpy(g_infname, argv[1]);
		infile = fopen(g_infname, "r");
		if (!infile) doerr(g_infname);
		if (argc > 2)
		{
			strcpy(g_outfname, argv[2]);
		}
		else
		{
			strcpy(g_outfname, g_infname);
			strtok(g_outfname, ".");
			strcat(g_outfname, ".c");
		}
		outfile = fopen(g_outfname, "w");
		if (!outfile) doerr(g_outfname);
    }
	else
    {
		infile = stdin;
		outfile = stdout;
    }
  memcpy(&_iob[0], infile, sizeof(_iob[0]));

  bprogram = bprogram_new(g_infname);
  body_stack[0] = (Node *)bprogram;

  yyparse();
  if (body_stack_n) 
  {
	  printf("ERROR: Missing Endif, Next, or Wend\n");
	  exit(1);
  }
  //bprogram->dump(bprogram);
  bprogram->b2c(bprogram);
  return 0;
}
