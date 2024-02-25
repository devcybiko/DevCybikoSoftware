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

/*  A Bison parser, made from b2cy.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	LITERAL_CHAR	258
#define	LITERAL_INT	259
#define	LITERAL_LONG	260
#define	LITERAL_STRING	261
#define	LITERAL_DOUBLE	262
#define	VAR	263
#define	DIM	264
#define	CHAR	265
#define	INT	266
#define	LONG	267
#define	DOUBLE	268
#define	AS	269
#define	COMMENT	270
#define	FOR	271
#define	TO	272
#define	STEP	273
#define	NEXT	274
#define	EXIT	275
#define	IF	276
#define	THEN	277
#define	END	278
#define	ELSE	279
#define	ELSEIF	280
#define	PRINT	281
#define	SPRINT	282
#define	WHILE	283
#define	WEND	284
#define	FUNCTION	285
#define	SUB	286
#define	CALL	287
#define	WAIT	288
#define	INPUT	289
#define	INPUTXY	290
#define	LINE	291
#define	POINT	292
#define	INK	293
#define	PAPER	294
#define	CLS	295
#define	PRINTXY	296
#define	SIN	297
#define	SINH	298
#define	ASIN	299
#define	ASINH	300
#define	COS	301
#define	COSH	302
#define	ACOS	303
#define	ACOSH	304
#define	TAN	305
#define	ACTAN	306
#define	ACTANH	307
#define	ATAN	308
#define	ATANH	309
#define	SQRT	310
#define	EXP	311
#define	LOG	312
#define	LOG10	313
#define	LOG2	314
#define	POW2	315
#define	RND	316
#define	INV	317
#define	POW	318
#define	SQR_POW	319
#define	KEY	320
#define	BEOF	321
#define	OPEN	322
#define	READ	323
#define	WRITE	324
#define	APPEND	325
#define	CLOSE	326
#define	PUT	327
#define	GET	328
#define	AND	329
#define	OR	330
#define	NEQ	331
#define	BEEP	332
#define	BY_REF	333
#define	BY_VAL	334
#define	LE	335
#define	GE	336
#define	MID	337
#define	RIGHT	338
#define	INLINE	339
#define	OUTLINE	340
#define	FONT	341
#define	GOTO	342
#define	TYPE	343
#define	SPRITE	344
#define	MOVE	345
#define	REDRAW	346
#define	COLLISION	347
#define	MUSIC	348
#define	FOREGROUND	349
#define	BACKGROUND	350
#define	STOP	351
#define	PLAY	352
#define	FLIP_X	353
#define	FLIP_Y	354
#define	VIBRATE	355
#define	OPTION	356
#define	C_STRINGS	357
#define	CYBASIC_STRINGS	358
#define	ON	359
#define	GOSUB	360
#define	ALL	361
#define	SHOW	362
#define	C_COORDS	363
#define	CYBASIC_COORDS	364
#define	SPRITES	365
#define	D3SPRITES	366
#define	D3ROOMS	367
#define	WHITE	368
#define	LTGREY	369
#define	DKGREY	370
#define	BLACK	371
#define	SCORE	372
#define	MENU	373
#define	MENUXY	374
#define	ENDIF	375
#define	FILENAME	376
#define	KEYCLICK	377
#define	OFF	378
#define	PROGRAM	379
#define	NOT	380
#define	MOD	381
#define	ABS	382
#define	DABS	383
#define	ESCAPE	384
#define	HELP	385
#define	MULTITASK	386
#define	GETCHAR	387
#define	GETKEY	388
#define	SENDMESSAGE	389
#define	TOKENIZE	390
#define	USERMENU	391
#define	TOCYID	392
#define	TOUSER	393
#define	DIALOG	394
#define	D3ROOM	395
#define	D3SPRITE	396
#define	D3WALL	397
#define	D3COLLISION	398
#define	D3MOVE	399
#define	D3REDRAW	400
#define	D3RMOVE	401
#define	D3GET	402
#define	CAMERA	403
#define	B2C_TRUE	404
#define	B2C_FALSE	405
#define	ERROR	406
#define	SPRITE_GET	407
#define	FINDFILE	408
#define	REMOVE	409
#define	RENAME	410
#define	EXISTS	411
#define	NEXTFILE	412
#define	FILELIST	413
#define	MAIN	414
#define	RECT	415
#define	RECTFILL	416
#define	PAGE	417
#define	PAGECOPY	418
#define	LOAD	419
#define	LEN	420
#define	STRINGWIDTH	421
#define	STRINGHEIGHT	422
#define	WRAP	423
#define	LEFT	424
#define	CENTER	425
#define	WORD	426
#define	ARCHIVE	427
#define	CIRCLE	428
#define	CIRCFILL	429
#define	NEG	430

#line 1 "b2cy.y"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "b2c.h"
#include "bterm.h"
#include "bprogram.h"
#include "bstatement.h"
#include "bdim.h"
#include "bop.h"
#include "bstatement.h"
#include "bfor.h"
#include "bif.h"
#include "bthen.h"
#include "belse.h"
#include "bexit.h"
#include "belseif.h"
#include "bprint.h"
#include "blist.h"
#include "bwhile.h"
#include "bfunction.h"
#include "bparam.h"
#include "bfunccall.h"
#include "binput.h"
#include "binputxy.h"
#include "bprintxy.h"
#include "bmath.h"
#include "bopen.h"
#include "bput.h"
#include "bexitfunction.h"
#include "bprintno.h"
#include "bmid.h"
#include "binline.h"
#include "boutline.h"
#include "blabel.h"
#include "bgoto.h"
#include "btype.h"
#include "bsprite.h"
#include "bredraw.h"
#include "bmusic.h"
#include "bongoto.h"
#include "bongosub.h"
#include "bscore.h"
#include "bmenu.h"
#include "bmenuxy.h"
#include "bexitprogram.h"
#include "bchar.h"
#include "bsprint.h"
#include "btokenize.h"
#include "bcommand.h"
#include "bsprite_get.h"
#include "bget.h"

//#define DBG0 printf
#define YYERROR_VERBOSE 6

char yacctext[1024];
char tmp_filename[256];
int c_strings=0;
int c_coords=0;
int n_sprites=32;
int n_3dsprites=8;
int n_rooms=8;
int _show_=1;
int _escape_ = 1;
int _help_ = 1;
int _multitask_=1;
int _onmessage_defined_ = 0;
int _show_main_ = 1;

extern int yylineno;
extern int yylex();
extern void yyerror(char *s);

Node *curr_func=0;
Node *in_function=0;

Node *body_stack[256];
int body_stack_n=0;

#define YYDEBUG 1

char *fix_string(char *s);
char *uppercase(char *s);
char *lowercase(char *s);

Node *do_bterm(
     char *name,
     int datatype,
     int literal,
	 int dimension);
Node *do_bstatement(
  Node *expr,
  int lineno);
Node *do_bdim(
	char *var,
	int datatype,
	Node *expr,
	char *typename);
Node *do_bexpr(Bterm *term);
Bexpr *do_bop(
     Bexpr *left,
     int op,
     Bexpr *right);
Node *do_bfor(
     char *name,
     Node *from,
     Node *to,
     Node *step);
Node *do_bwhile(Node *expr);
Node *do_bfunction(
     char *name,
     Node *parameters,
     int datatype);
Node *do_bif(Node *exp);
Node *do_bif2(Node *exp, Node *stmp);
Node *do_belseif(Node *exp);
Node *do_belse();
Node *do_bexitfor();
Node *do_bexitwhile();
Node *do_bexitfunction();
void push(Node *node);
Node *pop(int type);
Node *pop2(int type1, int type2);
Node *pop3(
     int type1,
     int type2,
     int type3);
Node *do_bprint(Node *list);
Node *do_bsprint(Node *var, Node *list);
Node *do_bprintxy(
     Bexpr *x,
     Bexpr *y,
     Node *list);
Node *do_list(
     Node *expr1,
     Node *expr2);
Node *do_paramlist(
     Node *expr1,
     Node *expr2);
Node *do_param(
     char *name,
     int datatype,
     int dimension,
     int passed_by,
     Bexpr *initial_value);
Bexpr *do_funccall(
     char *name,
     Blist *paramlist);
Node *do_funclist(
     Node *expr1,
     Node *expr2);
Node *do_input(
     Bexpr *prompt,
     Bterm *term);
Node *do_inputxy(
	 Bexpr *x,
	 Bexpr *y,
     Bexpr *prompt,
     Bterm *term);
Node *do_char(Bexpr *exp);
Node *do_math(
     char *name,
     Bexpr *exp,
	 int type);
Node *do_math2(
     char *name,
     Bexpr *exp1,
     Bexpr *exp2,
	 int type);
Node *do_open(
     Bexpr *exp1, /* filename */
     int mode,
     Bexpr *exp2); /* filenumber */
Node *do_put(
     Bexpr *exp1, /* filenumber */
     Bexpr *exp2, /* filepos - optional */
     Bterm *name); /* variable name */
Node *do_bprintno(
     Bexpr *fileno,
     Node *list);
Node *do_mid(
     Bterm *dest,
     Bexpr *src,
     Bexpr *start,
     Bexpr *len);
Node *do_binline(
     char *code);
Node *do_boutline(
     char *code);
Node *do_bgoto(char *name);
Node *do_blabel(char *label);
Node *do_btype(char *name);
Node *do_btype2(char *varname, Node *subscript, int datatype, char *typename);
Node *do_bsprite(Bexpr *n, Bexpr *name);
Node *do_bredraw(Bexpr *n);
Node *do_bmusic(int opn, int channel, Bexpr *bexp);
Node *do_bongoto(Bexpr *exp, Node *list);
Node *do_bongosub(Bexpr *exp, Node *list);
Node *do_varterm(char *name);
Node *do_bscore(Bexpr *exp);
Node *do_bmenu(char *varname, Node *list);
Node *do_bmenuxy(Bexpr *x, Bexpr *y, char *varname, Node *list);
void update_lineno(char *filename, char *lineno);
Node *do_bexitprogram();
Node *do_variable(Bterm *bterm, Node *subscript);
Node *do_btokenize(Node *var, Node *tokens, Node *list);
Node *do_bcommand(char *command_name, ...);
Bdim *find_member_name(Btype *btype, char *name);
Node *do_bsprite_get(Bexpr *n, Node *x, Node *y, Node *z, Node *mode, Node *w, Node *h);
Node *do_get(exp1,exp2, name);

#define null_term bterm_new("NULL")
#define zero_term bterm_new("0")


#line 404 "b2cy.y"
typedef union {
  char *string;
  int num;
  int mode;
  Bexpr *expr;
  Node *node;
  Bterm *term;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		826
#define	YYFLAG		-32768
#define	YYNTBASE	192

#define YYTRANSLATE(x) ((unsigned)(x) <= 430 ? yytranslate[x] : 220)

static const short yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,   175,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,   187,     2,     2,     2,     2,   180,
   181,   178,   177,   186,   176,   191,   179,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,   188,     2,   189,
   184,   190,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
   182,     2,   183,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
   116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
   126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
   136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
   146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
   156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172,   173,   174,   185
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,    11,    16,    17,    23,    29,    36,
    43,    47,    50,    53,    61,    71,    74,    78,    83,    88,
    91,    96,   100,   103,   111,   117,   121,   124,   131,   139,
   143,   146,   150,   159,   165,   169,   173,   180,   184,   188,
   192,   196,   206,   212,   215,   219,   223,   227,   231,   237,
   247,   255,   263,   269,   273,   276,   280,   286,   290,   298,
   305,   311,   319,   326,   332,   340,   350,   358,   360,   362,
   366,   370,   374,   378,   383,   389,   394,   400,   404,   408,
   414,   417,   421,   433,   443,   453,   463,   467,   473,   489,
   497,   507,   519,   522,   526,   530,   534,   538,   542,   548,
   554,   560,   566,   572,   578,   582,   588,   594,   598,   601,
   607,   617,   620,   623,   626,   636,   646,   656,   664,   672,
   676,   690,   694,   697,   700,   703,   706,   710,   714,   718,
   722,   726,   730,   734,   738,   742,   746,   750,   754,   758,
   760,   762,   764,   766,   771,   776,   781,   786,   791,   796,
   801,   806,   811,   816,   821,   826,   831,   836,   841,   846,
   851,   856,   861,   866,   871,   876,   881,   886,   893,   900,
   902,   907,   909,   914,   916,   921,   928,   937,   944,   949,
   954,   961,   972,   977,   986,   991,   996,  1001,  1006,  1023,
  1025,  1029,  1031,  1035,  1039,  1045,  1050,  1055,  1056,  1058,
  1062,  1064,  1066,  1070,  1074,  1080,  1085,  1090,  1092,  1093,
  1095,  1099,  1101,  1103,  1107,  1111,  1115,  1119,  1123,  1127,
  1131,  1135,  1139,  1143,  1147,  1151,  1155,  1158,  1161,  1164,
  1168,  1169,  1171,  1173,  1175,  1177,  1179,  1181,  1183,  1185,
  1188,  1190,  1193,  1195,  1199,  1201,  1203,  1205,  1207,  1209,
  1212,  1214,  1216,  1218,  1220,  1222,  1224,  1226,  1228,  1230,
  1232,  1234,  1236,  1238,  1240,  1242,  1244,  1246,  1248,  1250,
  1252,  1254
};

static const short yyrhs[] = {    -1,
   192,   193,     0,   192,   201,     0,   192,   194,   201,     0,
   192,   210,   211,   201,     0,     0,     9,   209,    14,   219,
   201,     0,     9,   209,    14,   209,   201,     0,     9,   209,
   203,    14,   219,   201,     0,     9,   209,   203,    14,   209,
   201,     0,    32,   205,   201,     0,   205,   201,     0,   202,
   201,     0,    16,   209,   184,   207,    17,   207,   201,     0,
    16,   209,   184,   207,    17,   207,    18,   207,   201,     0,
    19,   201,     0,    20,    16,   201,     0,    21,   207,    22,
   201,     0,    21,   207,    22,   193,     0,    24,   201,     0,
    25,   207,    22,   201,     0,    23,    21,   201,     0,   120,
   201,     0,   135,   207,   186,   207,   186,   197,   201,     0,
    27,   215,   186,   197,   201,     0,    26,   197,   201,     0,
    26,   201,     0,    26,   187,   218,   186,   197,   201,     0,
    41,   207,   186,   207,   186,   197,   201,     0,    28,   207,
   201,     0,    29,   201,     0,    20,    28,   201,     0,    30,
   209,   180,   200,   181,    14,   219,   201,     0,    30,   209,
    14,   219,   201,     0,    20,    30,   201,     0,    23,    30,
   201,     0,    31,   209,   180,   200,   181,   201,     0,    31,
   209,   201,     0,    20,    31,   201,     0,    23,    31,   201,
     0,    33,   207,   201,     0,    36,   207,   186,   207,   186,
   207,   186,   207,   201,     0,    37,   207,   186,   207,   201,
     0,    40,   201,     0,    38,   207,   201,     0,    77,   207,
   201,     0,    39,   207,   201,     0,    34,   215,   201,     0,
    34,   207,   186,   215,   201,     0,    35,   207,   186,   207,
   186,   207,   186,   215,   201,     0,    35,   207,   186,   207,
   186,   215,   201,     0,    67,   207,    16,   195,    14,   207,
   201,     0,    67,   207,    14,   207,   201,     0,    71,   207,
   201,     0,    71,   201,     0,   153,   207,   201,     0,   155,
   207,   186,   207,   201,     0,   154,   207,   201,     0,    72,
   207,   186,   207,   186,   215,   201,     0,    72,   207,   186,
   186,   215,   201,     0,    72,   207,   186,   207,   201,     0,
    73,   207,   186,   207,   186,   215,   201,     0,    73,   207,
   186,   186,   215,   201,     0,    73,   207,   186,   207,   201,
     0,    82,   215,   186,   207,   186,   207,   201,     0,    82,
   215,   186,   207,   186,   207,   186,   207,   201,     0,    83,
   215,   186,   207,   186,   207,   201,     0,   213,     0,   214,
     0,    86,   207,   201,     0,    87,   209,   201,     0,   209,
   188,   201,     0,    88,   209,   201,     0,   209,    14,   219,
   201,     0,   209,   203,    14,   219,   201,     0,   209,    14,
   209,   201,     0,   209,   203,    14,   209,   201,     0,    23,
    88,   201,     0,   140,   207,   201,     0,   141,   207,   186,
   207,   201,     0,   145,   201,     0,   145,   207,   201,     0,
   142,   207,   186,   207,   186,   207,   186,   207,   186,   207,
   201,     0,   144,   207,   186,   207,   186,   207,   186,   207,
   201,     0,   146,   207,   186,   207,   186,   207,   186,   207,
   201,     0,   147,   207,   186,   209,   186,   209,   186,   209,
   201,     0,    89,   207,   201,     0,    89,   207,   186,   207,
   201,     0,   152,   207,   186,   215,   186,   215,   186,   215,
   186,   215,   186,   215,   186,   215,   201,     0,    90,   207,
   186,   207,   186,   207,   201,     0,    90,   207,   186,   207,
   186,   207,   186,   207,   201,     0,    90,   207,   186,   207,
   186,   207,   186,   207,   186,   207,   201,     0,    91,   201,
     0,    91,   207,   201,     0,    91,   106,   201,     0,    91,
   107,   201,     0,    93,    95,   201,     0,    93,    94,   201,
     0,    93,    95,   186,   207,   201,     0,    93,    94,   186,
   207,   201,     0,    93,    95,   186,    96,   201,     0,    93,
    94,   186,    96,   201,     0,    93,    95,   186,    97,   201,
     0,    93,    94,   186,    97,   201,     0,   100,   207,   201,
     0,   104,   207,    87,   198,   201,     0,   104,   207,   105,
   197,   201,     0,   117,   207,   201,     0,   117,   201,     0,
   118,   209,   186,   197,   201,     0,   119,   207,   186,   207,
   186,   209,   186,   197,   201,     0,   122,   104,     0,   122,
   123,     0,    20,   124,     0,   134,   207,   186,   207,   186,
   207,   186,   207,   201,     0,   160,   207,   186,   207,   186,
   207,   186,   207,   201,     0,   161,   207,   186,   207,   186,
   207,   186,   207,   201,     0,   173,   207,   186,   207,   186,
   207,   201,     0,   174,   207,   186,   207,   186,   207,   201,
     0,   162,   207,   201,     0,   163,   207,   186,   207,   186,
   207,   186,   207,   186,   207,   186,   207,   201,     0,   164,
   207,   201,     0,   101,   102,     0,   101,   103,     0,   101,
   108,     0,   101,   109,     0,   101,   110,     4,     0,   101,
   111,     4,     0,   101,   112,     4,     0,   101,   107,   104,
     0,   101,   107,   123,     0,   101,   129,   104,     0,   101,
   129,   123,     0,   101,   130,   104,     0,   101,   130,   123,
     0,   101,   131,   104,     0,   101,   131,   123,     0,   101,
   159,   123,     0,   101,   159,   104,     0,    68,     0,    69,
     0,    70,     0,   172,     0,    42,   180,   207,   181,     0,
    43,   180,   207,   181,     0,    44,   180,   207,   181,     0,
    45,   180,   207,   181,     0,   127,   180,   207,   181,     0,
   128,   180,   207,   181,     0,    11,   180,   207,   181,     0,
    46,   180,   207,   181,     0,    47,   180,   207,   181,     0,
    48,   180,   207,   181,     0,    49,   180,   207,   181,     0,
    50,   180,   207,   181,     0,    51,   180,   207,   181,     0,
    52,   180,   207,   181,     0,    53,   180,   207,   181,     0,
    54,   180,   207,   181,     0,    55,   180,   207,   181,     0,
    62,   180,   207,   181,     0,    56,   180,   207,   181,     0,
    57,   180,   207,   181,     0,    58,   180,   207,   181,     0,
    59,   180,   207,   181,     0,    60,   180,   207,   181,     0,
    61,   180,   207,   181,     0,    63,   180,   207,   186,   207,
   181,     0,    64,   180,   207,   186,   207,   181,     0,    65,
     0,    65,   180,   207,   181,     0,   133,     0,    10,   180,
   207,   181,     0,   132,     0,    66,   180,   207,   181,     0,
    92,   180,   207,   186,   207,   181,     0,   143,   180,   207,
   186,   207,   186,   207,   181,     0,   136,   180,   207,   186,
   207,   181,     0,   137,   180,   207,   181,     0,   138,   180,
   207,   181,     0,   139,   180,   207,   186,   207,   181,     0,
   139,   180,   207,   186,   207,   186,   208,   186,   207,   181,
     0,   157,   180,   208,   181,     0,   158,   180,   207,   186,
   207,   186,   208,   181,     0,   156,   180,   207,   181,     0,
   165,   180,   207,   181,     0,   166,   180,   207,   181,     0,
   167,   180,   207,   181,     0,   168,   180,   207,   186,   207,
   186,   207,   186,   207,   186,   207,   186,   207,   186,   207,
   181,     0,   207,     0,   197,   186,   207,     0,   208,     0,
   198,   186,   208,     0,   209,    14,   219,     0,   209,   182,
   183,    14,   219,     0,    78,   209,    14,   219,     0,    79,
   209,    14,   219,     0,     0,   199,     0,   200,   186,   199,
     0,   175,     0,    15,     0,   218,   184,   207,     0,   182,
   207,   183,     0,   182,   207,   186,   207,   183,     0,   209,
   180,   206,   181,     0,   209,   180,   206,   181,     0,   209,
     0,     0,   207,     0,   206,   186,   207,     0,   218,     0,
   204,     0,   207,   177,   207,     0,   207,   176,   207,     0,
   207,   178,   207,     0,   207,   179,   207,     0,   207,   126,
   207,     0,   207,   189,   207,     0,   207,   190,   207,     0,
   207,    81,   207,     0,   207,    80,   207,     0,   207,    76,
   207,     0,   207,    74,   207,     0,   207,    75,   207,     0,
   207,   184,   207,     0,   125,   207,     0,   176,   207,     0,
   177,   207,     0,   180,   207,   181,     0,     0,     8,     0,
     8,     0,   121,     0,     4,     0,     8,     0,    84,     0,
    85,     0,   209,     0,   209,   203,     0,   209,     0,   209,
   203,     0,   216,     0,   216,   191,   217,     0,     4,     0,
     5,     0,     7,     0,     6,     0,     3,     0,   187,   212,
     0,   196,     0,   217,     0,   215,     0,   113,     0,   114,
     0,   115,     0,   116,     0,    98,     0,    99,     0,   148,
     0,   149,     0,   150,     0,   151,     0,   169,     0,   170,
     0,    83,     0,    10,     0,   171,     0,    10,     0,    11,
     0,    13,     0,    12,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   415,   416,   417,   418,   419,   421,   423,   424,   425,   426,
   427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
   437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
   447,   448,   450,   452,   453,   454,   455,   456,   457,   458,
   459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
   469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
   479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
   489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
   499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
   509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
   519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
   529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
   539,   540,   542,   543,   544,   545,   546,   547,   548,   549,
   550,   551,   552,   553,   554,   555,   556,   557,   558,   560,
   561,   562,   563,   565,   566,   567,   568,   569,   570,   571,
   572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
   582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
   592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
   602,   603,   604,   605,   606,   607,   608,   609,   610,   612,
   613,   615,   616,   618,   619,   620,   621,   627,   628,   629,
   631,   632,   634,   637,   638,   640,   642,   643,   645,   646,
   647,   649,   650,   651,   652,   653,   654,   655,   656,   657,
   658,   659,   660,   661,   662,   663,   664,   665,   666,   667,
   669,   670,   672,   674,   676,   678,   680,   682,   684,   685,
   687,   688,   690,   691,   693,   694,   695,   696,   697,   698,
   699,   700,   701,   702,   703,   704,   705,   706,   707,   708,
   709,   710,   711,   712,   713,   714,   715,   716,   718,   719,
   720,   721
};

static const char * const yytname[] = {   "$","error","$undefined.","LITERAL_CHAR",
"LITERAL_INT","LITERAL_LONG","LITERAL_STRING","LITERAL_DOUBLE","VAR","DIM","CHAR",
"INT","LONG","DOUBLE","AS","COMMENT","FOR","TO","STEP","NEXT","EXIT","IF","THEN",
"END","ELSE","ELSEIF","PRINT","SPRINT","WHILE","WEND","FUNCTION","SUB","CALL",
"WAIT","INPUT","INPUTXY","LINE","POINT","INK","PAPER","CLS","PRINTXY","SIN",
"SINH","ASIN","ASINH","COS","COSH","ACOS","ACOSH","TAN","ACTAN","ACTANH","ATAN",
"ATANH","SQRT","EXP","LOG","LOG10","LOG2","POW2","RND","INV","POW","SQR_POW",
"KEY","BEOF","OPEN","READ","WRITE","APPEND","CLOSE","PUT","GET","AND","OR","NEQ",
"BEEP","BY_REF","BY_VAL","LE","GE","MID","RIGHT","INLINE","OUTLINE","FONT","GOTO",
"TYPE","SPRITE","MOVE","REDRAW","COLLISION","MUSIC","FOREGROUND","BACKGROUND",
"STOP","PLAY","FLIP_X","FLIP_Y","VIBRATE","OPTION","C_STRINGS","CYBASIC_STRINGS",
"ON","GOSUB","ALL","SHOW","C_COORDS","CYBASIC_COORDS","SPRITES","D3SPRITES",
"D3ROOMS","WHITE","LTGREY","DKGREY","BLACK","SCORE","MENU","MENUXY","ENDIF",
"FILENAME","KEYCLICK","OFF","PROGRAM","NOT","MOD","ABS","DABS","ESCAPE","HELP",
"MULTITASK","GETCHAR","GETKEY","SENDMESSAGE","TOKENIZE","USERMENU","TOCYID",
"TOUSER","DIALOG","D3ROOM","D3SPRITE","D3WALL","D3COLLISION","D3MOVE","D3REDRAW",
"D3RMOVE","D3GET","CAMERA","B2C_TRUE","B2C_FALSE","ERROR","SPRITE_GET","FINDFILE",
"REMOVE","RENAME","EXISTS","NEXTFILE","FILELIST","MAIN","RECT","RECTFILL","PAGE",
"PAGECOPY","LOAD","LEN","STRINGWIDTH","STRINGHEIGHT","WRAP","LEFT","CENTER",
"WORD","ARCHIVE","CIRCLE","CIRCFILL","'\\n'","'-'","'+'","'*'","'/'","'('","')'",
"'['","']'","'='","NEG","','","'#'","':'","'<'","'>'","'.'","input","statement",
"options","mode","math_fn","list","label_list","param","paramlist","comment",
"assignment","subscript","function_call","sub_call","explist","exp","varterm",
"varname","filename","lineno","defname","inline","outline","scalar","tscalar",
"type_scalar_var","term","datatype",""
};
#endif

static const short yyr1[] = {     0,
   192,   192,   192,   192,   192,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
   193,   193,   194,   194,   194,   194,   194,   194,   194,   194,
   194,   194,   194,   194,   194,   194,   194,   194,   194,   195,
   195,   195,   195,   196,   196,   196,   196,   196,   196,   196,
   196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
   196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
   196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
   196,   196,   196,   196,   196,   196,   196,   196,   196,   197,
   197,   198,   198,   199,   199,   199,   199,   200,   200,   200,
   201,   201,   202,   203,   203,   204,   205,   205,   206,   206,
   206,   207,   207,   207,   207,   207,   207,   207,   207,   207,
   207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
   208,   208,   209,   210,   211,   212,   213,   214,   215,   215,
   216,   216,   217,   217,   218,   218,   218,   218,   218,   218,
   218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
   218,   218,   218,   218,   218,   218,   218,   218,   219,   219,
   219,   219
};

static const short yyr2[] = {     0,
     0,     2,     2,     3,     4,     0,     5,     5,     6,     6,
     3,     2,     2,     7,     9,     2,     3,     4,     4,     2,
     4,     3,     2,     7,     5,     3,     2,     6,     7,     3,
     2,     3,     8,     5,     3,     3,     6,     3,     3,     3,
     3,     9,     5,     2,     3,     3,     3,     3,     5,     9,
     7,     7,     5,     3,     2,     3,     5,     3,     7,     6,
     5,     7,     6,     5,     7,     9,     7,     1,     1,     3,
     3,     3,     3,     4,     5,     4,     5,     3,     3,     5,
     2,     3,    11,     9,     9,     9,     3,     5,    15,     7,
     9,    11,     2,     3,     3,     3,     3,     3,     5,     5,
     5,     5,     5,     5,     3,     5,     5,     3,     2,     5,
     9,     2,     2,     2,     9,     9,     9,     7,     7,     3,
    13,     3,     2,     2,     2,     2,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
     1,     1,     1,     4,     4,     4,     4,     4,     4,     4,
     4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     4,     4,     4,     4,     4,     4,     4,     6,     6,     1,
     4,     1,     4,     1,     4,     6,     8,     6,     4,     4,
     6,    10,     4,     8,     4,     4,     4,     4,    16,     1,
     3,     1,     3,     3,     5,     4,     4,     0,     1,     3,
     1,     1,     3,     3,     5,     4,     4,     1,     0,     1,
     3,     1,     1,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     2,     2,     2,     3,
     0,     1,     1,     1,     1,     1,     1,     1,     1,     2,
     1,     2,     1,     3,     1,     1,     1,     1,     1,     2,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1
};

static const short yydefact[] = {     1,
     0,   249,   245,   246,   248,   247,   233,     0,   267,     0,
   202,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   170,     0,     0,
     0,     0,     0,     0,     0,   266,   237,   238,     0,     0,
     0,     0,     0,     0,     0,     0,   258,   259,     0,     0,
     0,   254,   255,   256,   257,     0,     0,     0,     0,   234,
     0,     0,     0,   174,   172,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   260,
   261,   262,   263,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   264,
   265,   268,     0,     0,   201,     0,     2,     0,   251,     3,
     0,     0,   208,     0,    68,    69,   253,   243,   252,     0,
     0,     0,     0,     0,    16,     0,     0,     0,     0,   114,
   266,     0,     0,     0,     0,   213,     0,   239,   212,     0,
     0,     0,     0,    20,     0,     0,     0,    27,   190,   239,
     0,     0,    31,     0,     0,     0,   208,     0,     0,   253,
     0,     0,     0,     0,     0,    44,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    55,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
     0,     0,     0,   123,   124,     0,   125,   126,     0,     0,
     0,     0,     0,     0,     0,     0,   109,     0,     0,     0,
    23,   112,   113,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    81,     0,     0,     0,
     0,     0,     0,     0,     0,   231,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   236,   250,
     4,    13,    12,     0,   209,     0,     0,   240,   235,     0,
     0,     0,     0,     0,     0,     0,     0,    17,    32,    35,
    39,   227,   228,   229,     0,     6,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   209,
   240,    22,    36,    40,    78,     0,   236,   239,     0,     0,
    26,   240,     0,    30,     0,   198,   198,    38,    11,    41,
     0,    48,     0,     0,     0,    45,    47,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    54,     0,     0,    46,     0,
     0,    70,    71,    73,     0,    87,     0,    95,    96,    94,
     0,     0,    98,     0,    97,   105,   130,   131,   127,   128,
   129,   132,   133,   134,   135,   136,   137,   139,   138,   231,
     0,   108,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    79,     0,     0,     0,     0,    82,     0,     0,
     0,    56,    58,     0,     0,   232,     0,     0,     0,     0,
   120,     0,   122,     0,     0,     0,     0,     0,     0,   269,
   270,   272,   271,     0,     0,     0,   210,     0,    72,     0,
     5,   241,   244,   203,     0,     0,     0,   173,   150,     0,
   230,    19,    18,   224,   225,   223,   222,   221,   218,   215,
   214,   216,   217,   226,   219,   220,     0,    21,     0,   191,
     0,     0,     0,     0,   199,     0,     0,     0,     0,     0,
     0,     0,     0,   144,   145,   146,   147,   151,   152,   153,
   154,   155,   156,   157,   158,   159,   160,   162,   163,   164,
   165,   166,   167,   161,     0,     0,   171,   175,     0,   140,
   141,   142,   143,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   192,     0,     0,     0,   148,   149,     0,     0,     0,   179,
   180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   185,   183,     0,     0,     0,     0,   186,   187,   188,     0,
     0,     0,    76,    74,   207,     0,   204,     0,     0,     0,
   242,     8,     7,     0,     0,     0,   206,     0,    25,    34,
     0,     0,     0,     0,     0,     0,     0,    49,     0,     0,
    43,     0,     0,     0,    53,     0,     0,     0,    61,     0,
     0,    64,     0,     0,    88,     0,     0,   102,   104,   100,
   101,   103,    99,   231,   106,   107,   110,     0,     0,     0,
     0,     0,    80,     0,     0,     0,     0,     0,     0,    57,
     0,     0,     0,     0,     0,     0,     0,   211,     0,    77,
    75,    10,     9,     0,    28,     0,     0,     0,   200,   194,
     0,    37,     0,   253,     0,     0,   168,   169,     0,    60,
     0,    63,     0,     0,     0,     0,   176,   193,     0,     0,
     0,   178,   181,   231,     0,     0,     0,     0,     0,     0,
   231,     0,     0,     0,     0,     0,     0,   205,     0,    14,
   196,   197,     0,     0,     0,    51,     0,    29,    52,    59,
    62,     0,    65,    67,     0,    90,     0,     0,    24,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   118,   119,     0,    33,   195,     0,     0,     0,     0,
     0,     0,     0,     0,   177,     0,     0,     0,     0,   184,
     0,     0,     0,     0,    15,    50,    42,    66,     0,    91,
   111,   115,     0,     0,    84,    85,    86,     0,   116,   117,
     0,     0,     0,   182,     0,     0,     0,     0,    92,    83,
     0,     0,     0,     0,     0,     0,     0,   121,     0,     0,
     0,    89,     0,   189,     0,     0
};

static const short yydefgoto[] = {     1,
   137,   138,   554,   139,   177,   570,   515,   516,   140,   141,
   341,   166,   142,   476,   179,   457,   168,   144,   310,   300,
   145,   146,   147,   148,   149,   169,   475
};

static const short yypact[] = {-32768,
  1613,-32768,-32768,-32768,-32768,-32768,-32768,     1,  -175,  -160,
-32768,     1,    -3,    32,  3219,     5,    -3,  3219,  2137,     1,
  3219,    -3,     1,     1,     1,  3219,  3219,  3219,  3219,  3219,
  3219,  3219,    -3,  3219,  -140,  -138,  -136,  -112,   -98,   -90,
   -89,   -78,   -71,   -69,   -68,   -58,   -57,   -56,   -53,   -52,
   -47,   -37,   -34,   -33,   -32,   -31,   -30,   -27,   -26,  3219,
  2315,  3219,  3219,  3219,     1,     1,-32768,-32768,  3219,     1,
     1,  3219,  3219,  1959,   -22,   -28,-32768,-32768,  3219,   360,
  3219,-32768,-32768,-32768,-32768,  2315,     1,  3219,    -3,-32768,
   -74,   -21,   -17,-32768,-32768,  3219,  3219,   -16,   -13,   -12,
   -11,  3219,  3219,  3219,    -4,  3219,  2315,  3219,  3219,-32768,
-32768,-32768,-32768,  3219,  3219,  3219,  3219,    25,    48,    51,
  3219,  3219,  3219,  3219,  3219,    52,    53,    66,    79,-32768,
-32768,-32768,  3219,  3219,-32768,   121,-32768,    -3,-32768,-32768,
    -3,    -3,    20,   126,-32768,-32768,-32768,   -59,-32768,   -10,
     4,  3219,  3219,    23,-32768,    -3,    -3,    -3,    -3,-32768,
-32768,  3219,  3219,  3219,  3219,-32768,   657,  -153,-32768,    -3,
    -3,    -3,    -3,-32768,  1129,  3397,    -2,-32768,  5705,    38,
   -35,  1090,-32768,    11,    18,    -3,    82,  1090,  1138,    -3,
  1170,  1255,  1309,  1090,  1090,-32768,  1338,  3219,  3219,  3219,
  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,
  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,
  3219,  3219,    45,-32768,  1090,  1403,  1904,  1090,    -8,    39,
  1090,    -3,    -3,    61,  1979,    -3,    -3,-32768,  1090,  3219,
    13,    17,  1090,-32768,-32768,   -73,-32768,-32768,   130,   148,
   237,   -51,   -50,   -48,   -46,   355,-32768,  1090,    58,  2038,
-32768,-32768,-32768,  3219,  3219,  2157,  2216,  3219,  3219,  3219,
  3219,  1090,  2335,  2394,  3219,  2519,-32768,  1090,  2685,  2700,
  2870,  1090,  1090,  3055,  3219,   256,  3219,  3233,  3248,  1090,
  3393,  1090,  3219,  3219,  3219,  3219,  3411,  3426,-32768,-32768,
-32768,-32768,-32768,    84,  3219,  3219,    -3,    -6,-32768,    -3,
     1,  3219,    84,   254,  3447,  3518,  3219,-32768,-32768,-32768,
-32768,    27,    27,    27,  3533,  1786,  3219,  3219,  3219,  3219,
  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,  3219,
    78,-32768,-32768,-32768,-32768,    -3,  -108,  -111,    87,  3219,
-32768,-32768,  3219,-32768,   104,     9,     9,-32768,-32768,-32768,
     1,-32768,  3219,  3219,  3219,-32768,-32768,  3219,  3558,  3574,
  3589,  3605,  3645,  3716,  3731,  3756,  3772,  3787,  3803,  3843,
  3914,  3929,  3954,  3970,  3985,  4001,  4041,  4112,  4127,  4152,
  4168,  4183,  4199,  3219,   -54,-32768,  2849,  3034,-32768,  3219,
  3219,-32768,-32768,-32768,  3219,-32768,  3219,-32768,-32768,-32768,
  4239,  2493,-32768,  2671,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   256,
  3219,-32768,  3219,  3219,  4259,  4275,  3219,  3219,  4316,  4331,
  4346,  4387,-32768,  3219,  3219,  4402,  3219,-32768,  3219,     1,
     1,-32768,-32768,  3219,  4423,-32768,    93,  4457,  3219,  3219,
-32768,  3219,-32768,  4472,  4494,  4534,  4543,  3219,  3219,-32768,
-32768,-32768,-32768,    -3,    -3,   -97,  5705,   894,-32768,    84,
-32768,    38,-32768,  5705,    -3,    -3,    84,-32768,-32768,   196,
-32768,-32768,-32768,   -29,   -29,  5705,  5705,  5705,   243,    64,
    64,   243,   243,    27,  5705,  5705,   -82,-32768,  3219,  5705,
    -2,    -3,     1,     1,-32768,   -81,     7,   -80,    -3,  4564,
  4583,  1090,  4605,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,  3219,  3219,-32768,-32768,  1090,-32768,
-32768,-32768,-32768,   261,     1,   212,     1,   268,  4620,  4690,
  1090,  4712,  3219,    -3,    -3,  1090,    -3,    -3,  1090,    40,
-32768,    -2,    -2,  4727,-32768,-32768,  4744,  4759,  3219,-32768,
-32768,  3219,  1090,  4774,  3219,  4851,  4866,    92,    95,  1090,
-32768,-32768,  3219,  4881,  4898,  4913,-32768,-32768,-32768,  3219,
  4928,  5005,-32768,-32768,-32768,  3219,-32768,  3219,    -3,    -3,
-32768,-32768,-32768,    -3,    -3,  3219,-32768,    -2,-32768,-32768,
   265,   270,   271,     9,   104,   106,    -3,-32768,  3219,  3219,
-32768,  3219,  5020,  5035,-32768,  3219,    -3,     1,-32768,    -3,
     1,-32768,  3219,  3219,-32768,  3219,  5052,-32768,-32768,-32768,
-32768,-32768,-32768,   256,-32768,-32768,-32768,     1,  3219,  3219,
  5067,  1109,-32768,  3219,  5076,  3219,  3219,     1,     1,-32768,
  5091,  3219,  3219,  3219,  5146,  3219,  3219,  5705,   569,-32768,
-32768,-32768,-32768,   339,-32768,   104,   104,   104,-32768,-32768,
   277,-32768,  5208,    -3,  5223,    -2,-32768,-32768,  1090,-32768,
    -3,-32768,    -3,   426,  1090,   496,-32768,-32768,   108,  5238,
    -2,-32768,-32768,   256,  5263,  3219,  5278,  5293,   109,   112,
   256,  5355,  5370,  5385,  3219,  1090,  1090,-32768,  3219,-32768,
-32768,-32768,    -3,   104,     1,-32768,  3219,-32768,-32768,-32768,
-32768,  3219,-32768,-32768,  3219,-32768,  3219,  3219,-32768,   113,
  3219,  5410,  3219,  3219,     1,     1,   119,  3219,  3219,  3219,
  5425,-32768,-32768,  1090,-32768,-32768,    -3,  1090,  1090,   861,
    -2,  1090,  3219,  5440,-32768,  1090,  1090,    -3,   115,-32768,
  1090,  1090,  5502,  3219,-32768,-32768,-32768,-32768,  3219,-32768,
-32768,-32768,  5532,  3219,-32768,-32768,-32768,     1,-32768,-32768,
  3219,  5557,  1090,-32768,  1090,   118,  5572,  3219,-32768,-32768,
     1,  3219,  5588,   123,  1090,  3219,     1,-32768,  5619,    -3,
  3219,-32768,  5643,-32768,   305,-32768
};

static const short yypgoto[] = {-32768,
   -15,-32768,-32768,-32768,  -352,-32768,  -303,   -25,    24,-32768,
  -141,-32768,   301,    -7,   794,  -424,    -1,-32768,-32768,-32768,
-32768,-32768,   293,-32768,    16,     3,  -310
};


#define	YYLAST		5895


static const short yytable[] = {   143,
   511,   308,   486,   150,   152,   571,   151,   480,     7,   314,
   154,    11,    11,   550,   551,   552,     7,   313,   180,   153,
   625,   184,   185,   187,   355,   170,   340,    11,   306,   262,
   417,    11,    11,   304,   171,   172,   155,  -241,   352,   198,
   174,   199,   178,   200,   512,   183,   329,   156,   263,   418,
   330,   331,   422,   424,    11,   426,   196,   428,   394,   157,
   395,   158,   159,   180,   180,   241,   242,   201,   232,   233,
   306,   423,   425,  -233,   427,    11,   429,  -233,   572,  -241,
   573,   202,  -233,   605,   224,   259,   513,   514,   606,   203,
   204,     7,   173,   470,   471,   472,   473,   238,   617,   623,
   627,   205,   329,   606,   624,   624,   330,   331,   206,   257,
   207,   208,   261,   470,   471,   472,   473,   553,   327,   328,
   329,   209,   210,   211,   330,   331,   212,   213,   299,   309,
   277,   311,   214,   419,   327,   328,   329,   327,   328,   329,
   330,   331,   215,   330,   331,   216,   217,   218,   219,   220,
   353,   420,   221,   222,   337,   160,   618,   240,   264,   338,
   339,   301,   265,   268,   302,   303,   269,   270,   271,   610,
   332,   135,   135,   312,   348,   275,   615,   400,   349,   318,
   319,   320,   321,   350,  -242,   306,   332,   135,   626,   332,
   356,   135,   135,   342,   343,   344,   345,   357,   412,   305,
   351,   306,   414,  -239,   285,   354,   317,   307,   358,   359,
  -241,   360,   616,   362,   135,   338,   339,   366,   367,   306,
   333,   334,   335,   336,   401,   654,    11,   286,   337,   708,
   287,   293,   294,   338,   339,   135,   333,   334,   335,   336,
   421,   335,   336,   433,   337,   295,   405,   337,   396,   338,
   339,   399,   338,   339,   402,   403,   404,   406,   296,   408,
   409,   305,   410,   456,   413,   415,   416,   487,  -242,   327,
   328,   329,   509,   592,   636,   330,   331,   668,   686,   696,
   669,   432,    11,   687,   688,   327,   328,   329,   691,   750,
   734,   330,   331,   747,   755,   443,   757,   756,   773,   780,
   798,   448,   474,   811,   826,   452,   453,   711,   817,   482,
   492,   485,   181,   461,   690,   463,   327,   328,   329,   190,
   689,   332,   330,   331,   143,   186,   483,     0,   150,     0,
   479,   518,   507,   481,     0,     0,     0,   332,     0,     0,
   611,   327,   328,   329,     0,     0,     0,   330,   331,   493,
     0,     0,     0,    11,   517,   517,   729,   229,   230,   180,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   508,
     0,   333,   334,   335,   336,   731,   732,   733,     0,   337,
     0,     0,     0,     0,   338,   339,   135,   333,   334,   335,
   336,     0,     0,   332,   771,   337,     0,   638,     0,     0,
   338,   339,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   327,   328,   329,     0,     0,     0,   330,   331,
     0,     0,     0,   766,     0,     0,   337,     0,   327,   328,
   329,   338,   339,     0,   330,   331,     0,     0,     0,     0,
    11,   430,   135,   333,   334,   335,   336,     0,   588,   180,
     0,   337,     0,   641,     0,     0,   338,   339,     0,   431,
     0,   244,   245,     0,   332,     0,   246,   247,   248,   249,
   250,   251,     0,     0,     0,     0,     0,     0,   609,     0,
   332,     0,     0,     0,     0,   614,     0,     0,   252,   253,
   254,     0,     0,     0,     0,     0,     0,   603,   604,   327,
   328,   329,     0,     0,     0,   330,   331,     0,   612,   613,
    11,   621,   622,   135,   333,   334,   335,   336,   255,     0,
     0,     0,   337,     0,     0,     0,     0,   338,   339,     0,
   333,   334,   335,   336,   619,   620,     0,     0,   337,     0,
     0,     0,   628,   338,   339,   631,     0,     0,     0,     0,
     0,   332,     0,   180,     0,   180,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   327,
   328,   329,   635,     0,     0,   330,   331,     0,     0,   639,
     0,   642,     0,     0,   645,     0,     0,   648,   649,   650,
   651,   652,   653,   655,     0,   656,   657,     0,     0,     0,
   135,   333,   334,   335,   336,     0,   663,     0,     0,   337,
     0,   742,     0,   670,   338,   339,     0,     0,     0,     0,
     0,   332,   517,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   680,   681,     0,     0,   180,   682,   683,   180,
     0,   685,   327,   328,   329,     0,     0,     0,   330,   331,
   692,     0,     0,   519,     0,     0,   709,     0,     0,     0,
   700,     0,     0,   702,     0,     0,   719,   180,     0,     0,
   135,   333,   334,   335,   336,     0,     0,     0,   326,   337,
     0,   745,     0,     0,   338,   339,     0,     0,     0,     0,
     0,     0,     0,     0,   332,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   730,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   736,     0,   738,
     0,     0,   739,     0,   740,     0,   741,   743,   744,   746,
   327,   328,   329,   180,   749,     0,   330,   331,     0,     0,
     0,     0,     0,   589,   333,   334,   335,   336,     0,   762,
   763,   728,   337,   778,   180,     0,   765,   338,   339,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   332,     0,     0,     0,     0,   785,     0,     0,
   786,   787,   788,   790,   791,   792,   180,     0,     0,   795,
   796,   797,     0,     0,   799,   800,     0,     0,   167,   180,
     0,   175,     0,     0,   182,   180,     0,     0,     0,   188,
   189,   191,   192,   193,   194,   195,   809,   197,   810,     0,
     0,     0,   333,   334,   335,   336,     0,     0,   818,     0,
   337,     0,     0,   822,     0,   338,   339,   637,     0,   640,
     0,     0,     0,   223,   225,   226,   227,   228,     0,     0,
     0,     0,   231,     0,     0,   234,   235,   239,     0,     0,
     0,     0,   243,     0,   256,    11,     0,     0,     0,   258,
     0,   260,     0,     0,     0,     0,     0,     0,     0,   266,
   267,     0,     0,     0,     0,   272,   273,   274,     0,   276,
   278,   279,   280,     0,     0,     0,     0,   281,   282,   283,
   284,     0,     0,     0,   288,   289,   290,   291,   292,     0,
     0,   694,     0,     0,     0,     0,   297,   298,     0,     0,
   701,     0,     0,   703,   327,   328,   329,     0,     0,     0,
   330,   331,     0,     0,     0,   315,   316,     0,     0,     0,
     0,     0,     0,     0,     0,   322,   323,   324,   325,     0,
     0,   720,     0,     0,     0,     0,     0,   327,   328,   329,
     0,     0,     0,   330,   331,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   332,     0,     0,     0,
     0,   369,   370,   371,   372,   373,   374,   375,   376,   377,
   378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
   388,   389,   390,   391,   392,   393,     0,     0,     0,   332,
     0,     0,     0,     0,     0,     0,     0,   767,     0,     0,
     0,     0,     0,   411,     0,   135,   333,   334,   335,   336,
     0,     0,     0,     0,   337,     0,   789,     0,   779,   338,
   339,     0,     0,     0,     0,     0,     0,   435,   436,     0,
     0,   439,   440,   441,   442,     0,     0,     0,   446,   333,
   334,   335,   336,     0,     0,     0,   607,   337,   455,   608,
   458,     0,   338,   339,     0,     0,   464,   465,   466,   467,
   806,     0,     0,     0,     0,     0,     0,     0,   477,   478,
     0,     0,     0,   814,    11,   484,     0,     0,     0,   820,
   490,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
   504,   505,   506,   477,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   510,     0,     0,     0,     0,     0,     0,
   346,     0,     0,     0,     0,     0,   520,   521,   522,     0,
     0,   523,     0,   327,   328,   329,     0,     0,     0,   330,
   331,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   327,   328,   329,     0,     0,   549,   330,   331,
   556,   558,     0,   559,   560,     0,     0,     0,   561,     0,
   562,     0,   327,   328,   329,   566,     0,   569,   330,   331,
     0,   327,   328,   329,     0,   332,     0,   330,   331,     0,
     0,     0,     0,     0,     0,     0,     0,   574,     0,     0,
   577,   578,     0,     0,   332,     0,     0,   583,   584,     0,
   586,     0,   587,   327,   328,   329,     0,   590,     0,   330,
   331,     0,   594,   595,   332,   596,     0,     0,     0,     0,
     0,   601,   602,   332,   135,   333,   334,   335,   336,     0,
     0,     0,     0,   337,     0,     0,     0,     0,   338,   339,
     0,     0,     0,     0,   333,   334,   335,   336,     0,   713,
     0,     0,   337,     0,   714,   332,     0,   338,   339,     0,
     0,     0,     0,     0,   333,   334,   335,   336,     0,     0,
     0,     0,   337,   333,   334,   335,   336,   338,   339,     0,
     0,   337,     0,   361,     0,     0,   338,   339,   327,   328,
   329,     0,     0,     0,   330,   331,     0,     0,   633,   634,
     0,     0,     0,     0,     0,   333,   334,   335,   336,     0,
     0,     0,     0,   337,     0,   363,   647,     0,   338,   339,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   661,     0,     0,   662,     0,     0,   665,     0,
   332,     0,   327,   328,   329,     0,   671,     0,   330,   331,
     0,     0,     0,   675,     0,     0,     0,     0,     0,   678,
     0,   679,     0,     0,     0,     0,     0,     0,     0,   684,
     0,   327,   328,   329,     0,     0,     0,   330,   331,     0,
     0,     0,   693,   695,     0,     0,     0,     0,     0,   699,
   333,   334,   335,   336,   332,     0,   704,   705,   337,   706,
   364,     0,     0,   338,   339,     0,     0,     0,     0,     0,
     0,     0,   710,     0,     0,     0,     0,   715,     0,   717,
   718,     0,     0,   332,     0,   722,   723,   724,     0,   726,
   727,     0,     0,     0,     0,     0,   327,   328,   329,     0,
     0,     0,   330,   331,   333,   334,   335,   336,     0,     0,
     0,     0,   337,     0,   365,     0,     0,   338,   339,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   752,
     0,     0,     0,   333,   334,   335,   336,     0,   761,     0,
     0,   337,   764,   368,     0,     0,   338,   339,   332,     0,
   768,     0,     0,     0,     0,   769,     0,     0,   770,     0,
     0,   772,     0,     0,   774,     0,   776,   777,     0,     0,
     0,   781,   782,   783,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   793,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   802,   333,   334,
   335,   336,   803,     0,     0,     0,   337,   805,   397,     0,
     0,   338,   339,     0,   807,     0,     0,     0,     0,     0,
     0,   813,     0,     0,     0,   815,     0,     0,     0,   819,
     0,     0,   825,     0,   823,     2,     3,     4,     5,     6,
     7,     8,     9,    10,     0,     0,     0,    11,    12,     0,
     0,    13,    14,    15,     0,    16,    17,    18,    19,    20,
    21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
    31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
    41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     0,     0,     0,    61,    62,    63,     0,     0,     0,    64,
     0,     0,     0,     0,    65,    66,    67,    68,    69,    70,
    71,    72,    73,    74,    75,    76,     0,     0,     0,     0,
    77,    78,    79,    80,     0,     0,    81,     0,     0,     0,
     0,     0,     0,     0,     0,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,     0,     0,     0,     0,    92,
    93,     0,     0,     0,    94,    95,    96,    97,    98,    99,
   100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
   110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
   120,     0,   121,   122,   123,   124,   125,   126,   127,   128,
   129,   130,   131,   132,     0,   133,   134,   135,     2,     3,
     4,     5,     6,     7,     8,     9,    10,     0,     0,   136,
    11,    12,     0,     0,    13,    14,    15,     0,    16,    17,
    18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
    28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
    38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
    48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
    58,    59,    60,     0,     0,     0,    61,    62,    63,     0,
     0,     0,    64,     0,     0,     0,     0,    65,    66,    67,
    68,    69,    70,    71,    72,    73,    74,    75,    76,     0,
     0,     0,     0,    77,    78,    79,     0,     0,     0,    81,
     0,     0,     0,     0,     0,     0,     0,     0,    82,    83,
    84,    85,    86,    87,    88,    89,     0,    91,     0,     0,
     0,     0,    92,    93,     0,     0,     0,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119,   120,     0,   121,   122,   123,   124,   125,
   126,   127,   128,   129,   130,   131,   132,     0,   133,   134,
   135,     2,     3,     4,     5,     6,     7,     0,     9,    10,
     0,     0,   136,    11,     0,     0,     0,   327,   328,   329,
     0,     0,     0,   330,   331,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    59,     0,     0,     0,     0,   332,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   161,     0,     0,     0,     0,     0,     0,     0,     0,
    75,     0,   327,   328,   329,     0,    77,    78,   330,   331,
     0,     0,     0,     0,   236,   237,     0,     0,     0,     0,
     0,    82,    83,    84,    85,     0,     0,     0,     0,   333,
   334,   335,   336,   162,     0,    92,    93,   337,     0,   398,
    94,    95,   338,   339,    98,    99,   100,   101,     0,     0,
     0,   105,     0,     0,   332,     0,   110,   111,   112,   113,
     0,   327,   328,   329,   118,   119,   120,   330,   331,     0,
     0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     0,     0,     0,   135,   163,   164,     0,     0,   165,     2,
     3,     4,     5,     6,     7,   136,     9,    10,     0,     0,
     0,    11,     0,     0,   333,   334,   335,   336,     0,     0,
     0,     0,   337,   332,   407,     0,     0,   338,   339,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   333,   334,   335,   336,     0,     0,   161,
     0,   337,     0,   434,     0,     0,   338,   339,    75,     0,
   327,   328,   329,     0,    77,    78,   330,   331,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
    83,    84,    85,     0,     0,     0,     0,     0,     0,     0,
     0,   162,     0,    92,    93,     0,     0,     0,    94,    95,
     0,     0,    98,    99,   100,   101,     0,     0,     0,   105,
     0,     0,   332,     0,   110,   111,   112,   113,     0,   327,
   328,   329,   118,   119,   120,   330,   331,     0,     0,     0,
     0,   126,   127,   128,   129,   130,   131,   132,     0,     0,
     0,   135,   163,   164,     0,     0,   165,     2,     3,     4,
     5,     6,     7,   176,     9,    10,     0,     0,     0,    11,
     0,     0,   333,   334,   335,   336,     0,     0,     0,     0,
   337,   332,   437,     0,     0,   338,   339,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    35,    36,    37,    38,
    39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
    49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
    59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   333,   334,   335,   336,     0,     0,   161,     0,   337,
     0,   438,     0,     0,   338,   339,    75,     0,   327,   328,
   329,     0,    77,    78,   330,   331,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    82,    83,    84,
    85,     0,     0,     0,     0,     0,     0,     0,     0,   162,
     0,    92,    93,     0,     0,     0,    94,    95,     0,     0,
    98,    99,   100,   101,     0,     0,     0,   105,     0,     0,
   332,     0,   110,   111,   112,   113,     0,   327,   328,   329,
   118,   119,   120,   330,   331,     0,     0,     0,     0,   126,
   127,   128,   129,   130,   131,   132,     0,     0,     0,   135,
   163,   164,     0,     0,   165,     2,     3,     4,     5,     6,
     7,   136,     9,    10,     0,     0,     0,     0,     0,     0,
   333,   334,   335,   336,     0,     0,     0,     0,   337,   332,
   444,     0,     0,   338,   339,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    35,    36,    37,    38,    39,    40,
    41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   333,
   334,   335,   336,     0,     0,   161,     0,   337,     0,   445,
     0,     0,   338,   339,    75,     0,     0,     0,   564,   565,
    77,    78,   327,   328,   329,     0,     0,     0,   330,   331,
     0,     0,     0,     0,     0,    82,    83,    84,    85,     0,
     0,     0,     0,     0,     0,     0,     0,   162,     0,    92,
    93,     0,     0,     0,    94,    95,     0,     0,    98,    99,
   100,   101,     0,     0,     0,   105,     0,     0,     0,     0,
   110,   111,   112,   113,   332,     0,     0,     0,   118,   119,
   120,     0,     0,     0,     0,     0,     0,   126,   127,   128,
   129,   130,   131,   132,     0,     0,     0,     0,   163,   164,
     0,     0,   165,     2,     3,     4,     5,     6,     7,   136,
     9,    10,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   333,   334,   335,   336,     0,     0,
     0,     0,   337,     0,   447,     0,     0,   338,   339,     0,
     0,     0,    35,    36,    37,    38,    39,    40,    41,    42,
    43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
    53,    54,    55,    56,    57,    58,    59,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   161,     0,     0,     0,     0,   327,   328,
   329,     0,    75,     0,   330,   331,   567,   568,    77,    78,
     0,     0,     0,   327,   328,   329,     0,     0,     0,   330,
   331,     0,     0,    82,    83,    84,    85,     0,     0,     0,
     0,     0,     0,     0,     0,   162,     0,    92,    93,     0,
     0,     0,    94,    95,     0,     0,    98,    99,   100,   101,
   332,     0,     0,   105,     0,     0,     0,     0,   110,   111,
   112,   113,     0,     0,     0,   332,   118,   119,   120,     0,
     0,     0,     0,     0,     0,   126,   127,   128,   129,   130,
   131,   132,     0,     0,     0,     0,   163,   164,     0,     0,
   165,     2,     3,     4,     5,     6,     7,   136,     9,    10,
   333,   334,   335,   336,     0,     0,     0,     0,   337,     0,
   449,     0,     0,   338,   339,   333,   334,   335,   336,     0,
     0,     0,     0,   337,     0,   450,     0,     0,   338,   339,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    59,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   161,     0,     0,     0,     0,     0,     0,     0,     0,
    75,     0,     0,   327,   328,   329,    77,    78,     0,   330,
   331,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    82,    83,    84,    85,     0,     0,     0,     0,     0,
     0,     0,     0,   162,     0,    92,    93,     0,     0,     0,
    94,    95,     0,     0,    98,    99,   100,   101,     0,     0,
     0,   105,     0,     0,     0,   332,   110,   111,   112,   113,
     0,     0,     0,     0,   118,   119,   120,     0,     0,     0,
     0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     0,     0,     0,     0,   163,   164,     0,     0,   165,     0,
     0,     0,     0,     0,   555,   136,     2,     3,     4,     5,
     6,     7,     0,     9,    10,   333,   334,   335,   336,     0,
     0,     0,     0,   337,     0,   451,     0,     0,   338,   339,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    35,    36,    37,    38,    39,
    40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
    50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   161,     0,     0,     0,
     0,     0,     0,     0,     0,    75,     0,     0,   327,   328,
   329,    77,    78,     0,   330,   331,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    82,    83,    84,    85,
     0,     0,     0,     0,     0,     0,     0,     0,   162,     0,
    92,    93,     0,     0,     0,    94,    95,     0,     0,    98,
    99,   100,   101,     0,     0,     0,   105,     0,     0,     0,
   332,   110,   111,   112,   113,     0,     0,     0,     0,   118,
   119,   120,     0,     0,     0,     0,     0,     0,   126,   127,
   128,   129,   130,   131,   132,     0,     0,     0,     0,   163,
   164,     0,     0,   165,     0,     0,     0,     0,     0,   557,
   136,     2,     3,     4,     5,     6,     7,     0,     9,    10,
   333,   334,   335,   336,     0,     0,     0,     0,   337,     0,
   454,     0,     0,   338,   339,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    59,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   161,     0,     0,     0,     0,   327,   328,   329,     0,
    75,     0,   330,   331,     0,     0,    77,    78,     0,     0,
     0,   327,   328,   329,     0,     0,     0,   330,   331,     0,
     0,    82,    83,    84,    85,     0,     0,     0,     0,     0,
     0,     0,     0,   162,     0,    92,    93,     0,     0,     0,
    94,    95,     0,     0,    98,    99,   100,   101,   332,     0,
     0,   105,     0,     0,     0,     0,   110,   111,   112,   113,
     0,     0,     0,   332,   118,   119,   120,     0,     0,     0,
     0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     0,     0,     0,     0,   163,   164,     0,     0,   165,     2,
     3,     4,     5,     6,   347,   136,     9,    10,   333,   334,
   335,   336,     0,     0,     0,     0,   337,     0,   459,     0,
     0,   338,   339,   333,   334,   335,   336,     0,     0,     0,
     0,   337,     0,   460,     0,     0,   338,   339,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,     0,     0,     0,   327,   328,   329,     0,
     0,     0,   330,   331,     0,     0,     0,     0,     0,   161,
     0,     0,     0,     0,   327,   328,   329,     0,    75,     0,
   330,   331,     0,     0,    77,    78,     0,     0,     0,   327,
   328,   329,     0,     0,     0,   330,   331,     0,     0,    82,
    83,    84,    85,     0,     0,     0,     0,     0,   332,     0,
   327,   328,   329,    92,    93,     0,   330,   331,    94,    95,
     0,     0,    98,    99,   100,   101,   332,     0,     0,   105,
     0,     0,     0,     0,   110,   111,   112,   113,     0,     0,
     0,   332,   118,   119,   120,     0,     0,     0,     0,     0,
     0,   126,   127,   128,   129,   130,   131,   132,   333,   334,
   335,   336,   332,     0,     0,     0,   337,     0,   462,     0,
     0,   338,   339,   136,     0,     0,   333,   334,   335,   336,
     0,   327,   328,   329,   337,     0,   468,   330,   331,   338,
   339,   333,   334,   335,   336,     0,   327,   328,   329,   337,
     0,   469,   330,   331,   338,   339,     0,     0,     0,     0,
     0,     0,   333,   334,   335,   336,     0,   488,     0,     0,
   337,   327,   328,   329,     0,   338,   339,   330,   331,     0,
     0,     0,     0,   332,     0,     0,     0,   327,   328,   329,
     0,     0,     0,   330,   331,     0,     0,     0,   332,     0,
     0,     0,   327,   328,   329,     0,     0,     0,   330,   331,
     0,     0,     0,     0,     0,     0,     0,     0,   327,   328,
   329,     0,     0,   332,   330,   331,     0,     0,     0,     0,
     0,     0,     0,   333,   334,   335,   336,     0,   489,   332,
     0,   337,     0,     0,     0,     0,   338,   339,   333,   334,
   335,   336,     0,   491,   332,     0,   337,     0,   327,   328,
   329,   338,   339,     0,   330,   331,     0,     0,     0,     0,
   332,     0,     0,   333,   334,   335,   336,     0,   524,     0,
     0,   337,     0,     0,     0,     0,   338,   339,     0,   333,
   334,   335,   336,     0,   525,     0,     0,   337,     0,     0,
     0,     0,   338,   339,   333,   334,   335,   336,     0,   526,
   332,     0,   337,     0,     0,     0,     0,   338,   339,     0,
   333,   334,   335,   336,     0,   527,     0,     0,   337,   327,
   328,   329,     0,   338,   339,   330,   331,     0,     0,     0,
     0,     0,     0,     0,   327,   328,   329,     0,     0,     0,
   330,   331,     0,     0,     0,     0,     0,     0,     0,     0,
   333,   334,   335,   336,     0,   528,     0,     0,   337,   327,
   328,   329,     0,   338,   339,   330,   331,     0,     0,     0,
     0,   332,     0,     0,     0,   327,   328,   329,     0,     0,
     0,   330,   331,     0,     0,     0,   332,     0,     0,     0,
   327,   328,   329,     0,     0,     0,   330,   331,     0,     0,
     0,     0,     0,     0,     0,     0,   327,   328,   329,     0,
     0,   332,   330,   331,     0,     0,     0,     0,     0,     0,
     0,   333,   334,   335,   336,     0,   529,   332,     0,   337,
     0,     0,     0,     0,   338,   339,   333,   334,   335,   336,
     0,   530,   332,     0,   337,     0,   327,   328,   329,   338,
   339,     0,   330,   331,     0,     0,     0,     0,   332,     0,
     0,   333,   334,   335,   336,     0,   531,     0,     0,   337,
     0,     0,     0,     0,   338,   339,     0,   333,   334,   335,
   336,     0,   532,     0,     0,   337,     0,     0,     0,     0,
   338,   339,   333,   334,   335,   336,     0,   533,   332,     0,
   337,     0,     0,     0,     0,   338,   339,     0,   333,   334,
   335,   336,     0,   534,     0,     0,   337,   327,   328,   329,
     0,   338,   339,   330,   331,     0,     0,     0,     0,     0,
     0,     0,   327,   328,   329,     0,     0,     0,   330,   331,
     0,     0,     0,     0,     0,     0,     0,     0,   333,   334,
   335,   336,     0,   535,     0,     0,   337,   327,   328,   329,
     0,   338,   339,   330,   331,     0,     0,     0,     0,   332,
     0,     0,     0,   327,   328,   329,     0,     0,     0,   330,
   331,     0,     0,     0,   332,     0,     0,     0,   327,   328,
   329,     0,     0,     0,   330,   331,     0,     0,     0,     0,
     0,     0,     0,     0,   327,   328,   329,     0,     0,   332,
   330,   331,     0,     0,     0,     0,     0,     0,     0,   333,
   334,   335,   336,     0,   536,   332,     0,   337,     0,     0,
     0,     0,   338,   339,   333,   334,   335,   336,     0,   537,
   332,     0,   337,     0,   327,   328,   329,   338,   339,     0,
   330,   331,     0,     0,     0,     0,   332,     0,     0,   333,
   334,   335,   336,     0,   538,     0,     0,   337,     0,     0,
     0,     0,   338,   339,     0,   333,   334,   335,   336,     0,
   539,     0,     0,   337,     0,     0,     0,     0,   338,   339,
   333,   334,   335,   336,     0,   540,   332,     0,   337,     0,
     0,     0,     0,   338,   339,     0,   333,   334,   335,   336,
     0,   541,     0,     0,   337,   327,   328,   329,     0,   338,
   339,   330,   331,     0,     0,     0,     0,     0,     0,     0,
   327,   328,   329,     0,     0,     0,   330,   331,     0,     0,
     0,     0,     0,     0,     0,     0,   333,   334,   335,   336,
     0,   542,     0,     0,   337,   327,   328,   329,     0,   338,
   339,   330,   331,     0,     0,     0,     0,   332,     0,     0,
     0,   327,   328,   329,     0,     0,     0,   330,   331,     0,
     0,     0,   332,     0,     0,     0,   327,   328,   329,     0,
     0,     0,   330,   331,     0,     0,     0,     0,     0,     0,
     0,     0,   327,   328,   329,     0,     0,   332,   330,   331,
     0,     0,     0,     0,     0,     0,     0,   333,   334,   335,
   336,     0,   543,   332,     0,   337,     0,     0,     0,     0,
   338,   339,   333,   334,   335,   336,     0,   544,   332,     0,
   337,     0,   327,   328,   329,   338,   339,     0,   330,   331,
     0,     0,     0,     0,   332,     0,     0,   333,   334,   335,
   336,     0,   327,   328,   329,   337,     0,   545,   330,   331,
   338,   339,     0,   333,   334,   335,   336,     0,   327,   328,
   329,   337,     0,   546,   330,   331,   338,   339,   333,   334,
   335,   336,     0,   547,   332,     0,   337,     0,     0,     0,
     0,   338,   339,     0,   333,   334,   335,   336,     0,   548,
     0,     0,   337,     0,   332,     0,     0,   338,   339,   327,
   328,   329,     0,     0,     0,   330,   331,     0,     0,     0,
   332,     0,     0,     0,   327,   328,   329,     0,     0,     0,
   330,   331,     0,     0,   333,   334,   335,   336,     0,   327,
   328,   329,   337,     0,   563,   330,   331,   338,   339,     0,
     0,     0,     0,     0,   333,   334,   335,   336,     0,   575,
     0,   332,   337,     0,     0,     0,     0,   338,   339,     0,
   333,   334,   335,   336,     0,   576,   332,     0,   337,     0,
   327,   328,   329,   338,   339,     0,   330,   331,     0,     0,
     0,   332,     0,     0,     0,   327,   328,   329,     0,     0,
     0,   330,   331,     0,     0,     0,     0,     0,     0,     0,
     0,   333,   334,   335,   336,     0,   327,   328,   329,   337,
     0,   579,   330,   331,   338,   339,   333,   334,   335,   336,
     0,   580,   332,     0,   337,     0,     0,     0,     0,   338,
   339,   333,   334,   335,   336,     0,   581,   332,     0,   337,
   327,   328,   329,     0,   338,   339,   330,   331,     0,     0,
     0,     0,     0,     0,     0,   327,   328,   329,   332,     0,
     0,   330,   331,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   333,   334,   335,   336,     0,   327,   328,   329,
   337,     0,   582,   330,   331,   338,   339,   333,   334,   335,
   336,     0,   332,     0,     0,   337,     0,   585,     0,     0,
   338,   339,     0,     0,     0,     0,     0,   332,   333,   334,
   335,   336,     0,   591,     0,     0,   337,   327,   328,   329,
     0,   338,   339,   330,   331,     0,   327,   328,   329,   332,
     0,     0,   330,   331,     0,     0,     0,     0,     0,     0,
     0,     0,   333,   334,   335,   336,     0,   327,   328,   329,
   337,     0,   593,   330,   331,   338,   339,   333,   334,   335,
   336,     0,   597,     0,     0,   337,   327,   328,   329,   332,
   338,   339,   330,   331,     0,     0,     0,     0,   332,   333,
   334,   335,   336,     0,   598,     0,     0,   337,   327,   328,
   329,     0,   338,   339,   330,   331,     0,     0,     0,   332,
     0,     0,     0,   327,   328,   329,     0,     0,     0,   330,
   331,     0,     0,     0,     0,     0,     0,     0,   332,   333,
   334,   335,   336,     0,   599,     0,     0,   337,   333,   334,
   335,   336,   338,   339,     0,     0,   337,     0,   600,     0,
   332,   338,   339,     0,     0,     0,     0,     0,     0,   333,
   334,   335,   336,     0,     0,   332,     0,   337,     0,   629,
     0,     0,   338,   339,     0,     0,     0,     0,   333,   334,
   335,   336,     0,   327,   328,   329,   337,     0,   630,   330,
   331,   338,   339,     0,     0,     0,     0,     0,     0,     0,
   333,   334,   335,   336,     0,   327,   328,   329,   337,     0,
   632,   330,   331,   338,   339,   333,   334,   335,   336,     0,
   327,   328,   329,   337,     0,   643,   330,   331,   338,   339,
     0,     0,     0,     0,     0,   332,     0,   327,   328,   329,
     0,     0,     0,   330,   331,     0,     0,     0,     0,     0,
     0,     0,   327,   328,   329,     0,     0,   332,   330,   331,
     0,     0,     0,     0,     0,     0,     0,   327,   328,   329,
     0,     0,   332,   330,   331,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   333,   334,   335,   336,   332,
     0,     0,     0,   337,     0,   644,     0,     0,   338,   339,
     0,     0,     0,     0,   332,     0,     0,   333,   334,   335,
   336,     0,     0,     0,     0,   337,     0,   646,     0,   332,
   338,   339,   333,   334,   335,   336,     0,     0,     0,     0,
   337,     0,   658,     0,     0,   338,   339,     0,     0,   333,
   334,   335,   336,     0,   327,   328,   329,   337,     0,   659,
   330,   331,   338,   339,   333,   334,   335,   336,     0,   327,
   328,   329,   337,     0,   660,   330,   331,   338,   339,   333,
   334,   335,   336,     0,   327,   328,   329,   337,     0,   664,
   330,   331,   338,   339,     0,     0,     0,     0,     0,     0,
     0,   327,   328,   329,     0,     0,   332,   330,   331,     0,
     0,     0,     0,     0,     0,     0,   327,   328,   329,     0,
     0,   332,   330,   331,     0,     0,     0,     0,     0,     0,
     0,   327,   328,   329,     0,     0,   332,   330,   331,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   332,     0,     0,   333,   334,   335,   336,
     0,     0,     0,     0,   337,     0,   666,     0,   332,   338,
   339,   333,   334,   335,   336,     0,     0,     0,     0,   337,
     0,   667,     0,   332,   338,   339,   333,   334,   335,   336,
     0,     0,     0,     0,   337,     0,   672,     0,     0,   338,
   339,     0,     0,   333,   334,   335,   336,     0,   327,   328,
   329,   337,     0,   673,   330,   331,   338,   339,   333,   334,
   335,   336,     0,   327,   328,   329,   337,     0,   674,   330,
   331,   338,   339,   333,   334,   335,   336,     0,   327,   328,
   329,   337,     0,   676,   330,   331,   338,   339,     0,     0,
     0,     0,     0,     0,     0,   327,   328,   329,     0,     0,
   332,   330,   331,     0,     0,     0,     0,     0,     0,     0,
   327,   328,   329,     0,     0,   332,   330,   331,     0,   327,
   328,   329,     0,     0,     0,   330,   331,     0,     0,     0,
   332,     0,     0,     0,   327,   328,   329,     0,     0,     0,
   330,   331,     0,     0,     0,     0,     0,   332,     0,     0,
   333,   334,   335,   336,     0,     0,     0,     0,   337,     0,
   677,     0,   332,   338,   339,   333,   334,   335,   336,     0,
   697,   332,     0,   337,     0,     0,     0,     0,   338,   339,
   333,   334,   335,   336,     0,   698,   332,     0,   337,   327,
   328,   329,     0,   338,   339,   330,   331,   333,   334,   335,
   336,     0,   707,     0,     0,   337,     0,     0,     0,     0,
   338,   339,   333,   334,   335,   336,     0,   712,     0,     0,
   337,   333,   334,   335,   336,   338,   339,     0,     0,   337,
     0,   716,     0,     0,   338,   339,   333,   334,   335,   336,
     0,   332,     0,     0,   337,     0,   721,     0,     0,   338,
   339,   327,   328,   329,     0,     0,     0,   330,   331,     0,
     0,     0,     0,     0,     0,     0,   327,   328,   329,     0,
     0,     0,   330,   331,     0,     0,     0,     0,     0,     0,
     0,   327,   328,   329,     0,     0,     0,   330,   331,     0,
     0,   333,   334,   335,   336,     0,     0,     0,     0,   337,
     0,   725,     0,   332,   338,   339,   327,   328,   329,     0,
     0,     0,   330,   331,     0,     0,     0,     0,   332,     0,
     0,   327,   328,   329,     0,     0,     0,   330,   331,     0,
     0,     0,     0,   332,     0,     0,   327,   328,   329,     0,
     0,     0,   330,   331,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   333,   334,   335,   336,     0,   332,     0,
     0,   337,     0,   735,     0,     0,   338,   339,   333,   334,
   335,   336,     0,   332,     0,     0,   337,     0,   737,     0,
     0,   338,   339,   333,   334,   335,   336,     0,   332,     0,
     0,   337,     0,   748,     0,     0,   338,   339,   327,   328,
   329,     0,     0,     0,   330,   331,     0,     0,   333,   334,
   335,   336,     0,   327,   328,   329,   337,     0,   751,   330,
   331,   338,   339,   333,   334,   335,   336,     0,   327,   328,
   329,   337,     0,   753,   330,   331,   338,   339,   333,   334,
   335,   336,     0,     0,     0,     0,   337,     0,   754,     0,
   332,   338,   339,   327,   328,   329,     0,     0,     0,   330,
   331,     0,     0,     0,     0,   332,     0,     0,   327,   328,
   329,     0,     0,     0,   330,   331,     0,     0,     0,     0,
   332,     0,     0,   327,   328,   329,     0,     0,     0,   330,
   331,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   333,   334,   335,   336,     0,   332,     0,     0,   337,     0,
   758,     0,     0,   338,   339,   333,   334,   335,   336,     0,
   332,     0,     0,   337,     0,   759,     0,     0,   338,   339,
   333,   334,   335,   336,     0,   332,     0,     0,   337,     0,
   760,     0,     0,   338,   339,   327,   328,   329,     0,     0,
     0,   330,   331,     0,     0,   333,   334,   335,   336,     0,
   775,     0,     0,   337,     0,     0,     0,     0,   338,   339,
   333,   334,   335,   336,     0,   327,   328,   329,   337,     0,
   784,   330,   331,   338,   339,   333,   334,   335,   336,     0,
     0,     0,     0,   337,     0,   794,     0,   332,   338,   339,
   327,   328,   329,     0,     0,     0,   330,   331,     0,     0,
     0,     0,     0,     0,     0,   327,   328,   329,     0,     0,
     0,   330,   331,     0,     0,     0,     0,   332,     0,     0,
     0,   327,   328,   329,     0,     0,     0,   330,   331,     0,
     0,     0,     0,     0,     0,     0,     0,   333,   334,   335,
   336,     0,   332,     0,     0,   337,     0,   801,     0,     0,
   338,   339,   327,   328,   329,     0,     0,   332,   330,   331,
     0,     0,     0,     0,     0,     0,     0,   333,   334,   335,
   336,     0,   804,   332,     0,   337,   327,   328,   329,     0,
   338,   339,   330,   331,     0,     0,     0,     0,     0,     0,
     0,     0,   333,   334,   335,   336,     0,     0,     0,     0,
   337,     0,   808,     0,   332,   338,   339,   333,   334,   335,
   336,     0,     0,     0,     0,   337,     0,   812,     0,     0,
   338,   339,     0,   333,   334,   335,   336,     0,   332,     0,
     0,   337,     0,   816,     0,     0,   338,   339,   327,   328,
   329,     0,     0,     0,   330,   331,     0,     0,     0,     0,
     0,     0,     0,     0,   333,   334,   335,   336,     0,     0,
     0,     0,   337,     0,   821,     0,     0,   338,   339,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   333,   334,
   335,   336,     0,   824,     0,     0,   337,     0,     0,     0,
   332,   338,   339,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   333,   334,   335,   336,     0,     0,     0,     0,   337,     0,
     0,     0,     0,   338,   339
};

static const short yycheck[] = {     1,
   353,   143,   313,     1,   180,   430,     8,    14,     8,   151,
    12,    15,    15,    68,    69,    70,     8,    14,    20,   180,
    14,    23,    24,    25,    14,    21,   180,    15,   182,   104,
   104,    15,    15,    14,    30,    31,    13,   191,   180,   180,
    17,   180,    19,   180,   355,    22,    76,    16,   123,   123,
    80,    81,   104,   104,    15,   104,    33,   104,    14,    28,
    16,    30,    31,    65,    66,    94,    95,   180,    70,    71,
   182,   123,   123,   182,   123,    15,   123,   186,   431,   191,
   433,   180,   191,   181,    61,    87,    78,    79,   186,   180,
   180,     8,    88,    10,    11,    12,    13,    74,   181,   181,
   181,   180,    76,   186,   186,   186,    80,    81,   180,    86,
   180,   180,    89,    10,    11,    12,    13,   172,    74,    75,
    76,   180,   180,   180,    80,    81,   180,   180,     8,     4,
   107,   191,   180,     4,    74,    75,    76,    74,    75,    76,
    80,    81,   180,    80,    81,   180,   180,   180,   180,   180,
   186,     4,   180,   180,   184,   124,   509,   180,   180,   189,
   190,   138,   180,   180,   141,   142,   180,   180,   180,   480,
   126,   175,   175,   184,   176,   180,   487,   186,   176,   156,
   157,   158,   159,   186,   191,   182,   126,   175,   182,   126,
   180,   175,   175,   170,   171,   172,   173,   180,   186,   180,
   177,   182,   186,   184,   180,   182,   184,   188,   185,   186,
   191,   188,    17,   190,   175,   189,   190,   194,   195,   182,
   176,   177,   178,   179,   186,   186,    15,   180,   184,   654,
   180,   180,   180,   189,   190,   175,   176,   177,   178,   179,
     4,   178,   179,   186,   184,   180,   186,   184,   225,   189,
   190,   228,   189,   190,   231,   232,   233,   234,   180,   236,
   237,   180,   239,     8,   241,   242,   243,    14,   191,    74,
    75,    76,   186,   181,    14,    80,    81,   186,    14,   632,
   186,   258,    15,    14,    14,    74,    75,    76,   183,   714,
    14,    80,    81,   186,   186,   272,   721,   186,   186,   181,
   186,   278,   304,   186,     0,   282,   283,   660,   186,   311,
   326,   313,    20,   290,   625,   292,    74,    75,    76,    27,
   624,   126,    80,    81,   326,    25,   311,    -1,   326,    -1,
   307,   357,   340,   310,    -1,    -1,    -1,   126,    -1,    -1,
   482,    74,    75,    76,    -1,    -1,    -1,    80,    81,   326,
    -1,    -1,    -1,    15,   356,   357,    18,    65,    66,   361,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   346,
    -1,   176,   177,   178,   179,   686,   687,   688,    -1,   184,
    -1,    -1,    -1,    -1,   189,   190,   175,   176,   177,   178,
   179,    -1,    -1,   126,   747,   184,    -1,   186,    -1,    -1,
   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,
    -1,    -1,    -1,   734,    -1,    -1,   184,    -1,    74,    75,
    76,   189,   190,    -1,    80,    81,    -1,    -1,    -1,    -1,
    15,    87,   175,   176,   177,   178,   179,    -1,   450,   451,
    -1,   184,    -1,   186,    -1,    -1,   189,   190,    -1,   105,
    -1,   102,   103,    -1,   126,    -1,   107,   108,   109,   110,
   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,   480,    -1,
   126,    -1,    -1,    -1,    -1,   487,    -1,    -1,   129,   130,
   131,    -1,    -1,    -1,    -1,    -1,    -1,   474,   475,    74,
    75,    76,    -1,    -1,    -1,    80,    81,    -1,   485,   486,
    15,   513,   514,   175,   176,   177,   178,   179,   159,    -1,
    -1,    -1,   184,    -1,    -1,    -1,    -1,   189,   190,    -1,
   176,   177,   178,   179,   511,   512,    -1,    -1,   184,    -1,
    -1,    -1,   519,   189,   190,   522,    -1,    -1,    -1,    -1,
    -1,   126,    -1,   555,    -1,   557,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
    75,    76,   549,    -1,    -1,    80,    81,    -1,    -1,   556,
    -1,   558,    -1,    -1,   561,    -1,    -1,   564,   565,   566,
   567,   568,   569,   570,    -1,   572,   573,    -1,    -1,    -1,
   175,   176,   177,   178,   179,    -1,   583,    -1,    -1,   184,
    -1,   186,    -1,   590,   189,   190,    -1,    -1,    -1,    -1,
    -1,   126,   624,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   609,   610,    -1,    -1,   638,   614,   615,   641,
    -1,   618,    74,    75,    76,    -1,    -1,    -1,    80,    81,
   627,    -1,    -1,   361,    -1,    -1,   658,    -1,    -1,    -1,
   637,    -1,    -1,   640,    -1,    -1,   668,   669,    -1,    -1,
   175,   176,   177,   178,   179,    -1,    -1,    -1,    22,   184,
    -1,   186,    -1,    -1,   189,   190,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   684,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   694,    -1,   696,
    -1,    -1,   699,    -1,   701,    -1,   703,   704,   705,   706,
    74,    75,    76,   735,   711,    -1,    80,    81,    -1,    -1,
    -1,    -1,    -1,   451,   176,   177,   178,   179,    -1,   726,
   727,   183,   184,   755,   756,    -1,   733,   189,   190,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   126,    -1,    -1,    -1,    -1,   764,    -1,    -1,
   767,   768,   769,   770,   771,   772,   798,    -1,    -1,   776,
   777,   778,    -1,    -1,   781,   782,    -1,    -1,    15,   811,
    -1,    18,    -1,    -1,    21,   817,    -1,    -1,    -1,    26,
    27,    28,    29,    30,    31,    32,   803,    34,   805,    -1,
    -1,    -1,   176,   177,   178,   179,    -1,    -1,   815,    -1,
   184,    -1,    -1,   820,    -1,   189,   190,   555,    -1,   557,
    -1,    -1,    -1,    60,    61,    62,    63,    64,    -1,    -1,
    -1,    -1,    69,    -1,    -1,    72,    73,    74,    -1,    -1,
    -1,    -1,    79,    -1,    81,    15,    -1,    -1,    -1,    86,
    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
    97,    -1,    -1,    -1,    -1,   102,   103,   104,    -1,   106,
   107,   108,   109,    -1,    -1,    -1,    -1,   114,   115,   116,
   117,    -1,    -1,    -1,   121,   122,   123,   124,   125,    -1,
    -1,   629,    -1,    -1,    -1,    -1,   133,   134,    -1,    -1,
   638,    -1,    -1,   641,    74,    75,    76,    -1,    -1,    -1,
    80,    81,    -1,    -1,    -1,   152,   153,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   162,   163,   164,   165,    -1,
    -1,   669,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,    -1,
    -1,   198,   199,   200,   201,   202,   203,   204,   205,   206,
   207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
   217,   218,   219,   220,   221,   222,    -1,    -1,    -1,   126,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   735,    -1,    -1,
    -1,    -1,    -1,   240,    -1,   175,   176,   177,   178,   179,
    -1,    -1,    -1,    -1,   184,    -1,   186,    -1,   756,   189,
   190,    -1,    -1,    -1,    -1,    -1,    -1,   264,   265,    -1,
    -1,   268,   269,   270,   271,    -1,    -1,    -1,   275,   176,
   177,   178,   179,    -1,    -1,    -1,   183,   184,   285,   186,
   287,    -1,   189,   190,    -1,    -1,   293,   294,   295,   296,
   798,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   305,   306,
    -1,    -1,    -1,   811,    15,   312,    -1,    -1,    -1,   817,
   317,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
   337,   338,   339,   340,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   350,    -1,    -1,    -1,    -1,    -1,    -1,
    22,    -1,    -1,    -1,    -1,    -1,   363,   364,   365,    -1,
    -1,   368,    -1,    74,    75,    76,    -1,    -1,    -1,    80,
    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    74,    75,    76,    -1,    -1,   394,    80,    81,
   397,   398,    -1,   400,   401,    -1,    -1,    -1,   405,    -1,
   407,    -1,    74,    75,    76,   412,    -1,   414,    80,    81,
    -1,    74,    75,    76,    -1,   126,    -1,    80,    81,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   434,    -1,    -1,
   437,   438,    -1,    -1,   126,    -1,    -1,   444,   445,    -1,
   447,    -1,   449,    74,    75,    76,    -1,   454,    -1,    80,
    81,    -1,   459,   460,   126,   462,    -1,    -1,    -1,    -1,
    -1,   468,   469,   126,   175,   176,   177,   178,   179,    -1,
    -1,    -1,    -1,   184,    -1,    -1,    -1,    -1,   189,   190,
    -1,    -1,    -1,    -1,   176,   177,   178,   179,    -1,   181,
    -1,    -1,   184,    -1,   186,   126,    -1,   189,   190,    -1,
    -1,    -1,    -1,    -1,   176,   177,   178,   179,    -1,    -1,
    -1,    -1,   184,   176,   177,   178,   179,   189,   190,    -1,
    -1,   184,    -1,   186,    -1,    -1,   189,   190,    74,    75,
    76,    -1,    -1,    -1,    80,    81,    -1,    -1,   545,   546,
    -1,    -1,    -1,    -1,    -1,   176,   177,   178,   179,    -1,
    -1,    -1,    -1,   184,    -1,   186,   563,    -1,   189,   190,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   579,    -1,    -1,   582,    -1,    -1,   585,    -1,
   126,    -1,    74,    75,    76,    -1,   593,    -1,    80,    81,
    -1,    -1,    -1,   600,    -1,    -1,    -1,    -1,    -1,   606,
    -1,   608,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   616,
    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,
    -1,    -1,   629,   630,    -1,    -1,    -1,    -1,    -1,   636,
   176,   177,   178,   179,   126,    -1,   643,   644,   184,   646,
   186,    -1,    -1,   189,   190,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   659,    -1,    -1,    -1,    -1,   664,    -1,   666,
   667,    -1,    -1,   126,    -1,   672,   673,   674,    -1,   676,
   677,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
    -1,    -1,    80,    81,   176,   177,   178,   179,    -1,    -1,
    -1,    -1,   184,    -1,   186,    -1,    -1,   189,   190,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   716,
    -1,    -1,    -1,   176,   177,   178,   179,    -1,   725,    -1,
    -1,   184,   729,   186,    -1,    -1,   189,   190,   126,    -1,
   737,    -1,    -1,    -1,    -1,   742,    -1,    -1,   745,    -1,
    -1,   748,    -1,    -1,   751,    -1,   753,   754,    -1,    -1,
    -1,   758,   759,   760,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   773,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   784,   176,   177,
   178,   179,   789,    -1,    -1,    -1,   184,   794,   186,    -1,
    -1,   189,   190,    -1,   801,    -1,    -1,    -1,    -1,    -1,
    -1,   808,    -1,    -1,    -1,   812,    -1,    -1,    -1,   816,
    -1,    -1,     0,    -1,   821,     3,     4,     5,     6,     7,
     8,     9,    10,    11,    -1,    -1,    -1,    15,    16,    -1,
    -1,    19,    20,    21,    -1,    23,    24,    25,    26,    27,
    28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
    38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
    48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
    58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
    -1,    -1,    -1,    71,    72,    73,    -1,    -1,    -1,    77,
    -1,    -1,    -1,    -1,    82,    83,    84,    85,    86,    87,
    88,    89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
    98,    99,   100,   101,    -1,    -1,   104,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
   118,   119,   120,   121,   122,    -1,    -1,    -1,    -1,   127,
   128,    -1,    -1,    -1,   132,   133,   134,   135,   136,   137,
   138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
   148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
   158,    -1,   160,   161,   162,   163,   164,   165,   166,   167,
   168,   169,   170,   171,    -1,   173,   174,   175,     3,     4,
     5,     6,     7,     8,     9,    10,    11,    -1,    -1,   187,
    15,    16,    -1,    -1,    19,    20,    21,    -1,    23,    24,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
    65,    66,    67,    -1,    -1,    -1,    71,    72,    73,    -1,
    -1,    -1,    77,    -1,    -1,    -1,    -1,    82,    83,    84,
    85,    86,    87,    88,    89,    90,    91,    92,    93,    -1,
    -1,    -1,    -1,    98,    99,   100,    -1,    -1,    -1,   104,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,
   115,   116,   117,   118,   119,   120,    -1,   122,    -1,    -1,
    -1,    -1,   127,   128,    -1,    -1,    -1,   132,   133,   134,
   135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
   145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
   155,   156,   157,   158,    -1,   160,   161,   162,   163,   164,
   165,   166,   167,   168,   169,   170,   171,    -1,   173,   174,
   175,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
    -1,    -1,   187,    15,    -1,    -1,    -1,    74,    75,    76,
    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,   126,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    92,    -1,    74,    75,    76,    -1,    98,    99,    80,    81,
    -1,    -1,    -1,    -1,   106,   107,    -1,    -1,    -1,    -1,
    -1,   113,   114,   115,   116,    -1,    -1,    -1,    -1,   176,
   177,   178,   179,   125,    -1,   127,   128,   184,    -1,   186,
   132,   133,   189,   190,   136,   137,   138,   139,    -1,    -1,
    -1,   143,    -1,    -1,   126,    -1,   148,   149,   150,   151,
    -1,    74,    75,    76,   156,   157,   158,    80,    81,    -1,
    -1,    -1,    -1,   165,   166,   167,   168,   169,   170,   171,
    -1,    -1,    -1,   175,   176,   177,    -1,    -1,   180,     3,
     4,     5,     6,     7,     8,   187,    10,    11,    -1,    -1,
    -1,    15,    -1,    -1,   176,   177,   178,   179,    -1,    -1,
    -1,    -1,   184,   126,   186,    -1,    -1,   189,   190,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
    44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
    54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   176,   177,   178,   179,    -1,    -1,    83,
    -1,   184,    -1,   186,    -1,    -1,   189,   190,    92,    -1,
    74,    75,    76,    -1,    98,    99,    80,    81,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
   114,   115,   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   125,    -1,   127,   128,    -1,    -1,    -1,   132,   133,
    -1,    -1,   136,   137,   138,   139,    -1,    -1,    -1,   143,
    -1,    -1,   126,    -1,   148,   149,   150,   151,    -1,    74,
    75,    76,   156,   157,   158,    80,    81,    -1,    -1,    -1,
    -1,   165,   166,   167,   168,   169,   170,   171,    -1,    -1,
    -1,   175,   176,   177,    -1,    -1,   180,     3,     4,     5,
     6,     7,     8,   187,    10,    11,    -1,    -1,    -1,    15,
    -1,    -1,   176,   177,   178,   179,    -1,    -1,    -1,    -1,
   184,   126,   186,    -1,    -1,   189,   190,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   176,   177,   178,   179,    -1,    -1,    83,    -1,   184,
    -1,   186,    -1,    -1,   189,   190,    92,    -1,    74,    75,
    76,    -1,    98,    99,    80,    81,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,
   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
    -1,   127,   128,    -1,    -1,    -1,   132,   133,    -1,    -1,
   136,   137,   138,   139,    -1,    -1,    -1,   143,    -1,    -1,
   126,    -1,   148,   149,   150,   151,    -1,    74,    75,    76,
   156,   157,   158,    80,    81,    -1,    -1,    -1,    -1,   165,
   166,   167,   168,   169,   170,   171,    -1,    -1,    -1,   175,
   176,   177,    -1,    -1,   180,     3,     4,     5,     6,     7,
     8,   187,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
   176,   177,   178,   179,    -1,    -1,    -1,    -1,   184,   126,
   186,    -1,    -1,   189,   190,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,    47,
    48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
    58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,
   177,   178,   179,    -1,    -1,    83,    -1,   184,    -1,   186,
    -1,    -1,   189,   190,    92,    -1,    -1,    -1,    96,    97,
    98,    99,    74,    75,    76,    -1,    -1,    -1,    80,    81,
    -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,   127,
   128,    -1,    -1,    -1,   132,   133,    -1,    -1,   136,   137,
   138,   139,    -1,    -1,    -1,   143,    -1,    -1,    -1,    -1,
   148,   149,   150,   151,   126,    -1,    -1,    -1,   156,   157,
   158,    -1,    -1,    -1,    -1,    -1,    -1,   165,   166,   167,
   168,   169,   170,   171,    -1,    -1,    -1,    -1,   176,   177,
    -1,    -1,   180,     3,     4,     5,     6,     7,     8,   187,
    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   176,   177,   178,   179,    -1,    -1,
    -1,    -1,   184,    -1,   186,    -1,    -1,   189,   190,    -1,
    -1,    -1,    42,    43,    44,    45,    46,    47,    48,    49,
    50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
    60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    74,    75,
    76,    -1,    92,    -1,    80,    81,    96,    97,    98,    99,
    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,
    81,    -1,    -1,   113,   114,   115,   116,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   125,    -1,   127,   128,    -1,
    -1,    -1,   132,   133,    -1,    -1,   136,   137,   138,   139,
   126,    -1,    -1,   143,    -1,    -1,    -1,    -1,   148,   149,
   150,   151,    -1,    -1,    -1,   126,   156,   157,   158,    -1,
    -1,    -1,    -1,    -1,    -1,   165,   166,   167,   168,   169,
   170,   171,    -1,    -1,    -1,    -1,   176,   177,    -1,    -1,
   180,     3,     4,     5,     6,     7,     8,   187,    10,    11,
   176,   177,   178,   179,    -1,    -1,    -1,    -1,   184,    -1,
   186,    -1,    -1,   189,   190,   176,   177,   178,   179,    -1,
    -1,    -1,    -1,   184,    -1,   186,    -1,    -1,   189,   190,
    42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    92,    -1,    -1,    74,    75,    76,    98,    99,    -1,    80,
    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   113,   114,   115,   116,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   125,    -1,   127,   128,    -1,    -1,    -1,
   132,   133,    -1,    -1,   136,   137,   138,   139,    -1,    -1,
    -1,   143,    -1,    -1,    -1,   126,   148,   149,   150,   151,
    -1,    -1,    -1,    -1,   156,   157,   158,    -1,    -1,    -1,
    -1,    -1,    -1,   165,   166,   167,   168,   169,   170,   171,
    -1,    -1,    -1,    -1,   176,   177,    -1,    -1,   180,    -1,
    -1,    -1,    -1,    -1,   186,   187,     3,     4,     5,     6,
     7,     8,    -1,    10,    11,   176,   177,   178,   179,    -1,
    -1,    -1,    -1,   184,    -1,   186,    -1,    -1,   189,   190,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    74,    75,
    76,    98,    99,    -1,    80,    81,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,
   127,   128,    -1,    -1,    -1,   132,   133,    -1,    -1,   136,
   137,   138,   139,    -1,    -1,    -1,   143,    -1,    -1,    -1,
   126,   148,   149,   150,   151,    -1,    -1,    -1,    -1,   156,
   157,   158,    -1,    -1,    -1,    -1,    -1,    -1,   165,   166,
   167,   168,   169,   170,   171,    -1,    -1,    -1,    -1,   176,
   177,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,   186,
   187,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
   176,   177,   178,   179,    -1,    -1,    -1,    -1,   184,    -1,
   186,    -1,    -1,   189,   190,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    83,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
    92,    -1,    80,    81,    -1,    -1,    98,    99,    -1,    -1,
    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,
    -1,   113,   114,   115,   116,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   125,    -1,   127,   128,    -1,    -1,    -1,
   132,   133,    -1,    -1,   136,   137,   138,   139,   126,    -1,
    -1,   143,    -1,    -1,    -1,    -1,   148,   149,   150,   151,
    -1,    -1,    -1,   126,   156,   157,   158,    -1,    -1,    -1,
    -1,    -1,    -1,   165,   166,   167,   168,   169,   170,   171,
    -1,    -1,    -1,    -1,   176,   177,    -1,    -1,   180,     3,
     4,     5,     6,     7,     8,   187,    10,    11,   176,   177,
   178,   179,    -1,    -1,    -1,    -1,   184,    -1,   186,    -1,
    -1,   189,   190,   176,   177,   178,   179,    -1,    -1,    -1,
    -1,   184,    -1,   186,    -1,    -1,   189,   190,    42,    43,
    44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
    54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,    -1,    -1,    -1,    74,    75,    76,    -1,
    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    83,
    -1,    -1,    -1,    -1,    74,    75,    76,    -1,    92,    -1,
    80,    81,    -1,    -1,    98,    99,    -1,    -1,    -1,    74,
    75,    76,    -1,    -1,    -1,    80,    81,    -1,    -1,   113,
   114,   115,   116,    -1,    -1,    -1,    -1,    -1,   126,    -1,
    74,    75,    76,   127,   128,    -1,    80,    81,   132,   133,
    -1,    -1,   136,   137,   138,   139,   126,    -1,    -1,   143,
    -1,    -1,    -1,    -1,   148,   149,   150,   151,    -1,    -1,
    -1,   126,   156,   157,   158,    -1,    -1,    -1,    -1,    -1,
    -1,   165,   166,   167,   168,   169,   170,   171,   176,   177,
   178,   179,   126,    -1,    -1,    -1,   184,    -1,   186,    -1,
    -1,   189,   190,   187,    -1,    -1,   176,   177,   178,   179,
    -1,    74,    75,    76,   184,    -1,   186,    80,    81,   189,
   190,   176,   177,   178,   179,    -1,    74,    75,    76,   184,
    -1,   186,    80,    81,   189,   190,    -1,    -1,    -1,    -1,
    -1,    -1,   176,   177,   178,   179,    -1,   181,    -1,    -1,
   184,    74,    75,    76,    -1,   189,   190,    80,    81,    -1,
    -1,    -1,    -1,   126,    -1,    -1,    -1,    74,    75,    76,
    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,   126,    -1,
    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,
    76,    -1,    -1,   126,    80,    81,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   176,   177,   178,   179,    -1,   181,   126,
    -1,   184,    -1,    -1,    -1,    -1,   189,   190,   176,   177,
   178,   179,    -1,   181,   126,    -1,   184,    -1,    74,    75,
    76,   189,   190,    -1,    80,    81,    -1,    -1,    -1,    -1,
   126,    -1,    -1,   176,   177,   178,   179,    -1,   181,    -1,
    -1,   184,    -1,    -1,    -1,    -1,   189,   190,    -1,   176,
   177,   178,   179,    -1,   181,    -1,    -1,   184,    -1,    -1,
    -1,    -1,   189,   190,   176,   177,   178,   179,    -1,   181,
   126,    -1,   184,    -1,    -1,    -1,    -1,   189,   190,    -1,
   176,   177,   178,   179,    -1,   181,    -1,    -1,   184,    74,
    75,    76,    -1,   189,   190,    80,    81,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   176,   177,   178,   179,    -1,   181,    -1,    -1,   184,    74,
    75,    76,    -1,   189,   190,    80,    81,    -1,    -1,    -1,
    -1,   126,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
    -1,    80,    81,    -1,    -1,    -1,   126,    -1,    -1,    -1,
    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
    -1,   126,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   176,   177,   178,   179,    -1,   181,   126,    -1,   184,
    -1,    -1,    -1,    -1,   189,   190,   176,   177,   178,   179,
    -1,   181,   126,    -1,   184,    -1,    74,    75,    76,   189,
   190,    -1,    80,    81,    -1,    -1,    -1,    -1,   126,    -1,
    -1,   176,   177,   178,   179,    -1,   181,    -1,    -1,   184,
    -1,    -1,    -1,    -1,   189,   190,    -1,   176,   177,   178,
   179,    -1,   181,    -1,    -1,   184,    -1,    -1,    -1,    -1,
   189,   190,   176,   177,   178,   179,    -1,   181,   126,    -1,
   184,    -1,    -1,    -1,    -1,   189,   190,    -1,   176,   177,
   178,   179,    -1,   181,    -1,    -1,   184,    74,    75,    76,
    -1,   189,   190,    80,    81,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,   177,
   178,   179,    -1,   181,    -1,    -1,   184,    74,    75,    76,
    -1,   189,   190,    80,    81,    -1,    -1,    -1,    -1,   126,
    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,
    81,    -1,    -1,    -1,   126,    -1,    -1,    -1,    74,    75,
    76,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,   126,
    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,
   177,   178,   179,    -1,   181,   126,    -1,   184,    -1,    -1,
    -1,    -1,   189,   190,   176,   177,   178,   179,    -1,   181,
   126,    -1,   184,    -1,    74,    75,    76,   189,   190,    -1,
    80,    81,    -1,    -1,    -1,    -1,   126,    -1,    -1,   176,
   177,   178,   179,    -1,   181,    -1,    -1,   184,    -1,    -1,
    -1,    -1,   189,   190,    -1,   176,   177,   178,   179,    -1,
   181,    -1,    -1,   184,    -1,    -1,    -1,    -1,   189,   190,
   176,   177,   178,   179,    -1,   181,   126,    -1,   184,    -1,
    -1,    -1,    -1,   189,   190,    -1,   176,   177,   178,   179,
    -1,   181,    -1,    -1,   184,    74,    75,    76,    -1,   189,
   190,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   176,   177,   178,   179,
    -1,   181,    -1,    -1,   184,    74,    75,    76,    -1,   189,
   190,    80,    81,    -1,    -1,    -1,    -1,   126,    -1,    -1,
    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,
    -1,    -1,   126,    -1,    -1,    -1,    74,    75,    76,    -1,
    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    74,    75,    76,    -1,    -1,   126,    80,    81,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,   177,   178,
   179,    -1,   181,   126,    -1,   184,    -1,    -1,    -1,    -1,
   189,   190,   176,   177,   178,   179,    -1,   181,   126,    -1,
   184,    -1,    74,    75,    76,   189,   190,    -1,    80,    81,
    -1,    -1,    -1,    -1,   126,    -1,    -1,   176,   177,   178,
   179,    -1,    74,    75,    76,   184,    -1,   186,    80,    81,
   189,   190,    -1,   176,   177,   178,   179,    -1,    74,    75,
    76,   184,    -1,   186,    80,    81,   189,   190,   176,   177,
   178,   179,    -1,   181,   126,    -1,   184,    -1,    -1,    -1,
    -1,   189,   190,    -1,   176,   177,   178,   179,    -1,   181,
    -1,    -1,   184,    -1,   126,    -1,    -1,   189,   190,    74,
    75,    76,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,
   126,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
    80,    81,    -1,    -1,   176,   177,   178,   179,    -1,    74,
    75,    76,   184,    -1,   186,    80,    81,   189,   190,    -1,
    -1,    -1,    -1,    -1,   176,   177,   178,   179,    -1,   181,
    -1,   126,   184,    -1,    -1,    -1,    -1,   189,   190,    -1,
   176,   177,   178,   179,    -1,   181,   126,    -1,   184,    -1,
    74,    75,    76,   189,   190,    -1,    80,    81,    -1,    -1,
    -1,   126,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   176,   177,   178,   179,    -1,    74,    75,    76,   184,
    -1,   186,    80,    81,   189,   190,   176,   177,   178,   179,
    -1,   181,   126,    -1,   184,    -1,    -1,    -1,    -1,   189,
   190,   176,   177,   178,   179,    -1,   181,   126,    -1,   184,
    74,    75,    76,    -1,   189,   190,    80,    81,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    74,    75,    76,   126,    -1,
    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   176,   177,   178,   179,    -1,    74,    75,    76,
   184,    -1,   186,    80,    81,   189,   190,   176,   177,   178,
   179,    -1,   126,    -1,    -1,   184,    -1,   186,    -1,    -1,
   189,   190,    -1,    -1,    -1,    -1,    -1,   126,   176,   177,
   178,   179,    -1,   181,    -1,    -1,   184,    74,    75,    76,
    -1,   189,   190,    80,    81,    -1,    74,    75,    76,   126,
    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   176,   177,   178,   179,    -1,    74,    75,    76,
   184,    -1,   186,    80,    81,   189,   190,   176,   177,   178,
   179,    -1,   181,    -1,    -1,   184,    74,    75,    76,   126,
   189,   190,    80,    81,    -1,    -1,    -1,    -1,   126,   176,
   177,   178,   179,    -1,   181,    -1,    -1,   184,    74,    75,
    76,    -1,   189,   190,    80,    81,    -1,    -1,    -1,   126,
    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,
    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,   176,
   177,   178,   179,    -1,   181,    -1,    -1,   184,   176,   177,
   178,   179,   189,   190,    -1,    -1,   184,    -1,   186,    -1,
   126,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,   176,
   177,   178,   179,    -1,    -1,   126,    -1,   184,    -1,   186,
    -1,    -1,   189,   190,    -1,    -1,    -1,    -1,   176,   177,
   178,   179,    -1,    74,    75,    76,   184,    -1,   186,    80,
    81,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   176,   177,   178,   179,    -1,    74,    75,    76,   184,    -1,
   186,    80,    81,   189,   190,   176,   177,   178,   179,    -1,
    74,    75,    76,   184,    -1,   186,    80,    81,   189,   190,
    -1,    -1,    -1,    -1,    -1,   126,    -1,    74,    75,    76,
    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    74,    75,    76,    -1,    -1,   126,    80,    81,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
    -1,    -1,   126,    80,    81,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   176,   177,   178,   179,   126,
    -1,    -1,    -1,   184,    -1,   186,    -1,    -1,   189,   190,
    -1,    -1,    -1,    -1,   126,    -1,    -1,   176,   177,   178,
   179,    -1,    -1,    -1,    -1,   184,    -1,   186,    -1,   126,
   189,   190,   176,   177,   178,   179,    -1,    -1,    -1,    -1,
   184,    -1,   186,    -1,    -1,   189,   190,    -1,    -1,   176,
   177,   178,   179,    -1,    74,    75,    76,   184,    -1,   186,
    80,    81,   189,   190,   176,   177,   178,   179,    -1,    74,
    75,    76,   184,    -1,   186,    80,    81,   189,   190,   176,
   177,   178,   179,    -1,    74,    75,    76,   184,    -1,   186,
    80,    81,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    74,    75,    76,    -1,    -1,   126,    80,    81,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
    -1,   126,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    74,    75,    76,    -1,    -1,   126,    80,    81,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   126,    -1,    -1,   176,   177,   178,   179,
    -1,    -1,    -1,    -1,   184,    -1,   186,    -1,   126,   189,
   190,   176,   177,   178,   179,    -1,    -1,    -1,    -1,   184,
    -1,   186,    -1,   126,   189,   190,   176,   177,   178,   179,
    -1,    -1,    -1,    -1,   184,    -1,   186,    -1,    -1,   189,
   190,    -1,    -1,   176,   177,   178,   179,    -1,    74,    75,
    76,   184,    -1,   186,    80,    81,   189,   190,   176,   177,
   178,   179,    -1,    74,    75,    76,   184,    -1,   186,    80,
    81,   189,   190,   176,   177,   178,   179,    -1,    74,    75,
    76,   184,    -1,   186,    80,    81,   189,   190,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
   126,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    74,    75,    76,    -1,    -1,   126,    80,    81,    -1,    74,
    75,    76,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,
   126,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
    80,    81,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
   176,   177,   178,   179,    -1,    -1,    -1,    -1,   184,    -1,
   186,    -1,   126,   189,   190,   176,   177,   178,   179,    -1,
   181,   126,    -1,   184,    -1,    -1,    -1,    -1,   189,   190,
   176,   177,   178,   179,    -1,   181,   126,    -1,   184,    74,
    75,    76,    -1,   189,   190,    80,    81,   176,   177,   178,
   179,    -1,   181,    -1,    -1,   184,    -1,    -1,    -1,    -1,
   189,   190,   176,   177,   178,   179,    -1,   181,    -1,    -1,
   184,   176,   177,   178,   179,   189,   190,    -1,    -1,   184,
    -1,   186,    -1,    -1,   189,   190,   176,   177,   178,   179,
    -1,   126,    -1,    -1,   184,    -1,   186,    -1,    -1,   189,
   190,    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,
    -1,   176,   177,   178,   179,    -1,    -1,    -1,    -1,   184,
    -1,   186,    -1,   126,   189,   190,    74,    75,    76,    -1,
    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,   126,    -1,
    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,
    -1,    -1,    -1,   126,    -1,    -1,    74,    75,    76,    -1,
    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   176,   177,   178,   179,    -1,   126,    -1,
    -1,   184,    -1,   186,    -1,    -1,   189,   190,   176,   177,
   178,   179,    -1,   126,    -1,    -1,   184,    -1,   186,    -1,
    -1,   189,   190,   176,   177,   178,   179,    -1,   126,    -1,
    -1,   184,    -1,   186,    -1,    -1,   189,   190,    74,    75,
    76,    -1,    -1,    -1,    80,    81,    -1,    -1,   176,   177,
   178,   179,    -1,    74,    75,    76,   184,    -1,   186,    80,
    81,   189,   190,   176,   177,   178,   179,    -1,    74,    75,
    76,   184,    -1,   186,    80,    81,   189,   190,   176,   177,
   178,   179,    -1,    -1,    -1,    -1,   184,    -1,   186,    -1,
   126,   189,   190,    74,    75,    76,    -1,    -1,    -1,    80,
    81,    -1,    -1,    -1,    -1,   126,    -1,    -1,    74,    75,
    76,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
   126,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,
    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   176,   177,   178,   179,    -1,   126,    -1,    -1,   184,    -1,
   186,    -1,    -1,   189,   190,   176,   177,   178,   179,    -1,
   126,    -1,    -1,   184,    -1,   186,    -1,    -1,   189,   190,
   176,   177,   178,   179,    -1,   126,    -1,    -1,   184,    -1,
   186,    -1,    -1,   189,   190,    74,    75,    76,    -1,    -1,
    -1,    80,    81,    -1,    -1,   176,   177,   178,   179,    -1,
   181,    -1,    -1,   184,    -1,    -1,    -1,    -1,   189,   190,
   176,   177,   178,   179,    -1,    74,    75,    76,   184,    -1,
   186,    80,    81,   189,   190,   176,   177,   178,   179,    -1,
    -1,    -1,    -1,   184,    -1,   186,    -1,   126,   189,   190,
    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
    -1,    80,    81,    -1,    -1,    -1,    -1,   126,    -1,    -1,
    -1,    74,    75,    76,    -1,    -1,    -1,    80,    81,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,   177,   178,
   179,    -1,   126,    -1,    -1,   184,    -1,   186,    -1,    -1,
   189,   190,    74,    75,    76,    -1,    -1,   126,    80,    81,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,   177,   178,
   179,    -1,   181,   126,    -1,   184,    74,    75,    76,    -1,
   189,   190,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   176,   177,   178,   179,    -1,    -1,    -1,    -1,
   184,    -1,   186,    -1,   126,   189,   190,   176,   177,   178,
   179,    -1,    -1,    -1,    -1,   184,    -1,   186,    -1,    -1,
   189,   190,    -1,   176,   177,   178,   179,    -1,   126,    -1,
    -1,   184,    -1,   186,    -1,    -1,   189,   190,    74,    75,
    76,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   176,   177,   178,   179,    -1,    -1,
    -1,    -1,   184,    -1,   186,    -1,    -1,   189,   190,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,   177,
   178,   179,    -1,   181,    -1,    -1,   184,    -1,    -1,    -1,
   126,   189,   190,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   176,   177,   178,   179,    -1,    -1,    -1,    -1,   184,    -1,
    -1,    -1,    -1,   189,   190
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 416 "b2cy.y"
{ if (yyvsp[0].node) body_stack[body_stack_n]->addchild(body_stack[body_stack_n], yyvsp[0].node); ;
    break;}
case 3:
#line 417 "b2cy.y"
{yyval.node=NULL;;
    break;}
case 4:
#line 418 "b2cy.y"
{yyval.node=NULL;;
    break;}
case 5:
#line 419 "b2cy.y"
{ update_lineno(yyvsp[-2].string, yyvsp[-1].string); ;
    break;}
case 7:
#line 423 "b2cy.y"
{ yyval.node = do_bdim(yyvsp[-3].string, yyvsp[-1].num, 0, NULL); ;
    break;}
case 8:
#line 424 "b2cy.y"
{ yyval.node = do_bdim(yyvsp[-3].string, DATATYPE_TYPE, 0, yyvsp[-1].string); ;
    break;}
case 9:
#line 425 "b2cy.y"
{ yyval.node = do_bdim(yyvsp[-4].string, yyvsp[-1].num, (Node *) yyvsp[-3].expr, NULL); ;
    break;}
case 10:
#line 426 "b2cy.y"
{ yyval.node = do_bdim(yyvsp[-4].string, DATATYPE_TYPE, (Node *) yyvsp[-3].expr, yyvsp[-1].string); ;
    break;}
case 11:
#line 427 "b2cy.y"
{ yyval.node = do_bstatement(yyvsp[-1].node, yylineno); ;
    break;}
case 12:
#line 428 "b2cy.y"
{ yyval.node = do_bstatement(yyvsp[-1].node, yylineno); ;
    break;}
case 13:
#line 429 "b2cy.y"
{ yyval.node = do_bstatement(yyvsp[-1].node, yylineno); ;
    break;}
case 14:
#line 430 "b2cy.y"
{ yyval.node = do_bfor(yyvsp[-5].string, yyvsp[-3].node, yyvsp[-1].node, 0); push(yyval.node); yyval.node=0;;
    break;}
case 15:
#line 431 "b2cy.y"
{ yyval.node = do_bfor(yyvsp[-7].string, yyvsp[-5].node, yyvsp[-3].node, yyvsp[-1].node); push(yyval.node); yyval.node=0;;
    break;}
case 16:
#line 432 "b2cy.y"
{ yyval.node = pop(TYPE_FOR); ;
    break;}
case 17:
#line 433 "b2cy.y"
{ yyval.node = do_bexitfor(); ;
    break;}
case 18:
#line 434 "b2cy.y"
{ yyval.node = do_bif((Node *)yyvsp[-2].expr); yyval.node=0;;
    break;}
case 19:
#line 435 "b2cy.y"
{ yyval.node = do_bif2((Node *)yyvsp[-2].expr, (Node *)yyvsp[0].expr); yyval.node = do_bstatement(yyval.node, yylineno);;
    break;}
case 20:
#line 436 "b2cy.y"
{ pop2(TYPE_THEN, TYPE_ELSEIF); do_belse(); yyval.node=0;;
    break;}
case 21:
#line 437 "b2cy.y"
{ pop2(TYPE_THEN, TYPE_ELSEIF); yyval.node = do_belseif((Node *)yyvsp[-2].expr); yyval.node=0;;
    break;}
case 22:
#line 438 "b2cy.y"
{ pop3(TYPE_THEN, TYPE_ELSE, TYPE_ELSEIF); yyval.node = pop(TYPE_IF);;
    break;}
case 23:
#line 439 "b2cy.y"
{ pop3(TYPE_THEN, TYPE_ELSE, TYPE_ELSEIF); yyval.node = pop(TYPE_IF);;
    break;}
case 24:
#line 440 "b2cy.y"
{ yyval.node = do_btokenize(yyvsp[-5].node, yyvsp[-3].node, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 25:
#line 441 "b2cy.y"
{ yyval.node = do_bsprint(yyvsp[-3].node, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 26:
#line 442 "b2cy.y"
{ yyval.node = do_bprint(yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 27:
#line 443 "b2cy.y"
{ yyval.node = do_bprint(NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 28:
#line 444 "b2cy.y"
{ yyval.node = do_bprintno(yyvsp[-3].expr, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 29:
#line 445 "b2cy.y"
{ yyval.node = do_bprintxy(yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 30:
#line 446 "b2cy.y"
{ yyval.node = do_bwhile(yyvsp[-1].node); push(yyval.node); yyval.node=0; ;
    break;}
case 31:
#line 447 "b2cy.y"
{ yyval.node = pop(TYPE_WHILE); ;
    break;}
case 32:
#line 448 "b2cy.y"
{ yyval.node = do_bexitwhile(); ;
    break;}
case 33:
#line 450 "b2cy.y"
{ yyval.node = do_bfunction(yyvsp[-6].string, yyvsp[-4].node, yyvsp[-1].num); push(yyval.node); in_function = yyval.node; yyval.node=0; ;
    break;}
case 34:
#line 452 "b2cy.y"
{ yyval.node = do_bfunction(yyvsp[-3].string, NULL, yyvsp[-1].num); push(yyval.node); in_function = yyval.node; yyval.node=0; ;
    break;}
case 35:
#line 453 "b2cy.y"
{ yyval.node = do_bexitfunction(); ;
    break;}
case 36:
#line 454 "b2cy.y"
{ yyval.node = pop(TYPE_FUNCTION); in_function = NULL; ;
    break;}
case 37:
#line 455 "b2cy.y"
{ yyval.node = do_bfunction(yyvsp[-4].string, yyvsp[-2].node, DATATYPE_VOID); push(yyval.node); in_function = yyval.node; yyval.node=0; ;
    break;}
case 38:
#line 456 "b2cy.y"
{ yyval.node = do_bfunction(yyvsp[-1].string, NULL, DATATYPE_VOID); push(yyval.node); in_function = yyval.node; yyval.node=0; ;
    break;}
case 39:
#line 457 "b2cy.y"
{ yyval.node = do_bexitfunction(); ;
    break;}
case 40:
#line 458 "b2cy.y"
{ yyval.node = pop(TYPE_FUNCTION); in_function = NULL; ;
    break;}
case 41:
#line 459 "b2cy.y"
{ yyval.node = do_bcommand("_wait", yyvsp[-1].node, 0); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 42:
#line 460 "b2cy.y"
{ yyval.node = do_bcommand("_line", yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 43:
#line 461 "b2cy.y"
{ yyval.node = do_bcommand("_point", yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 44:
#line 462 "b2cy.y"
{ yyval.node = do_bcommand("_cls", NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 45:
#line 463 "b2cy.y"
{ yyval.node = do_bcommand("_ink", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 46:
#line 464 "b2cy.y"
{ yyval.node = do_bcommand("_beep", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 47:
#line 465 "b2cy.y"
{ yyval.node = do_bcommand("_paper", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 48:
#line 466 "b2cy.y"
{ yyval.node = do_input(NULL, yyvsp[-1].term); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 49:
#line 467 "b2cy.y"
{ yyval.node = do_input(yyvsp[-3].expr, yyvsp[-1].term); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 50:
#line 468 "b2cy.y"
{ yyval.node = do_inputxy(yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].term); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 51:
#line 469 "b2cy.y"
{ yyval.node = do_inputxy(yyvsp[-5].expr, yyvsp[-3].expr, NULL, yyvsp[-1].term); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 52:
#line 470 "b2cy.y"
{ yyval.node = do_open(yyvsp[-5].expr, yyvsp[-3].mode, yyvsp[-1].expr); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 53:
#line 471 "b2cy.y"
{ yyval.node = do_open(yyvsp[-3].expr, MODE_READ, yyvsp[-1].expr); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 54:
#line 472 "b2cy.y"
{ yyval.node = do_bcommand("_close", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 55:
#line 473 "b2cy.y"
{ yyval.node = do_bcommand("_close", NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 56:
#line 474 "b2cy.y"
{ yyval.node = do_bcommand("_findfile", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 57:
#line 475 "b2cy.y"
{ yyval.node = do_bcommand("File_rename", yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 58:
#line 476 "b2cy.y"
{ yyval.node = do_bcommand("File_remove", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 59:
#line 477 "b2cy.y"
{ yyval.node = do_put(yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].term); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 60:
#line 478 "b2cy.y"
{ yyval.node = do_put(yyvsp[-4].expr, NULL, yyvsp[-1].term); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 61:
#line 479 "b2cy.y"
{ yyval.node = do_put(yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 62:
#line 480 "b2cy.y"
{ yyval.node = do_get(yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].term); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 63:
#line 481 "b2cy.y"
{ yyval.node = do_get(yyvsp[-4].expr, NULL, yyvsp[-1].term); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 64:
#line 482 "b2cy.y"
{ yyval.node = do_get(yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 65:
#line 483 "b2cy.y"
{ yyval.node = do_mid(yyvsp[-5].term, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 66:
#line 484 "b2cy.y"
{ yyval.node = do_mid(yyvsp[-7].term, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 67:
#line 485 "b2cy.y"
{ yyval.node = do_bcommand("_right", yyvsp[-5].term, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 68:
#line 486 "b2cy.y"
{ yyval.node= do_binline(yyvsp[0].string); ;
    break;}
case 69:
#line 487 "b2cy.y"
{ yyval.node= do_boutline(yyvsp[0].string); ;
    break;}
case 70:
#line 488 "b2cy.y"
{ yyval.node = do_bcommand("_font", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 71:
#line 489 "b2cy.y"
{ yyval.node = do_bgoto(yyvsp[-1].string); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 72:
#line 490 "b2cy.y"
{ yyval.node = do_blabel(yyvsp[-2].string); ;
    break;}
case 73:
#line 491 "b2cy.y"
{ yyval.node = do_btype(yyvsp[-1].string); push(yyval.node); yyval.node=0;;
    break;}
case 74:
#line 492 "b2cy.y"
{ yyval.node = do_btype2(yyvsp[-3].string, NULL, yyvsp[-1].num, NULL); ;
    break;}
case 75:
#line 493 "b2cy.y"
{ yyval.node = do_btype2(yyvsp[-4].string, yyvsp[-3].node, yyvsp[-1].num, NULL); ;
    break;}
case 76:
#line 494 "b2cy.y"
{ yyval.node = do_btype2(yyvsp[-3].string, NULL, DATATYPE_TYPE, yyvsp[-1].string); ;
    break;}
case 77:
#line 495 "b2cy.y"
{ yyval.node = do_btype2(yyvsp[-4].string, yyvsp[-3].node, DATATYPE_TYPE, yyvsp[-1].string); ;
    break;}
case 78:
#line 496 "b2cy.y"
{ yyval.node = pop(TYPE_TYPE); ;
    break;}
case 79:
#line 497 "b2cy.y"
{ yyval.node = do_bcommand("_3d_room", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 80:
#line 498 "b2cy.y"
{ yyval.node = do_bcommand("_3d_sprite", yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 81:
#line 499 "b2cy.y"
{ yyval.node = do_bcommand("_3d_redraw", null_term, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 82:
#line 500 "b2cy.y"
{ yyval.node = do_bcommand("_3d_redraw", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 83:
#line 501 "b2cy.y"
{ yyval.node = do_bcommand("_3d_wall", yyvsp[-9].expr, yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 84:
#line 502 "b2cy.y"
{ yyval.node = do_bcommand("_3d_move", yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 85:
#line 503 "b2cy.y"
{ yyval.node = do_bcommand("_3d_rmove", yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 86:
#line 504 "b2cy.y"
{ yyval.node = do_bcommand("_3d_get", yyvsp[-7].expr, yyvsp[-5].string, yyvsp[-3].string, yyvsp[-1].string, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 87:
#line 505 "b2cy.y"
{ yyval.node = do_bcommand("_sprite", yyvsp[-1].expr, null_term, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 88:
#line 506 "b2cy.y"
{ yyval.node = do_bcommand("_sprite", yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 89:
#line 507 "b2cy.y"
{ yyval.node = do_bsprite_get(yyvsp[-13].expr, yyvsp[-11].node, yyvsp[-9].node, yyvsp[-7].node, yyvsp[-5].node, yyvsp[-3].node, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 90:
#line 508 "b2cy.y"
{ yyval.node = do_bcommand("_move", yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, zero_term, zero_term, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 91:
#line 509 "b2cy.y"
{ yyval.node = do_bcommand("_move", yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, zero_term, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 92:
#line 510 "b2cy.y"
{ yyval.node = do_bcommand("_move", yyvsp[-9].expr, yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 93:
#line 511 "b2cy.y"
{ yyval.node = do_bredraw(NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 94:
#line 512 "b2cy.y"
{ yyval.node = do_bredraw(yyvsp[-1].expr); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 95:
#line 513 "b2cy.y"
{ yyval.node = do_bredraw((Bexpr *)-1); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 96:
#line 514 "b2cy.y"
{ yyval.node = do_bredraw((Bexpr *)-2); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 97:
#line 515 "b2cy.y"
{ yyval.node = do_bmusic(MUSIC_LOAD, MUSIC_BACKGROUND, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 98:
#line 516 "b2cy.y"
{ yyval.node = do_bmusic(MUSIC_LOAD, MUSIC_FOREGROUND, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 99:
#line 517 "b2cy.y"
{ yyval.node = do_bmusic(MUSIC_LOAD, MUSIC_BACKGROUND, yyvsp[-1].expr); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 100:
#line 518 "b2cy.y"
{ yyval.node = do_bmusic(MUSIC_LOAD, MUSIC_FOREGROUND, yyvsp[-1].expr); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 101:
#line 519 "b2cy.y"
{ yyval.node = do_bmusic(MUSIC_STOP, MUSIC_BACKGROUND, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 102:
#line 520 "b2cy.y"
{ yyval.node = do_bmusic(MUSIC_STOP, MUSIC_FOREGROUND, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 103:
#line 521 "b2cy.y"
{ yyval.node = do_bmusic(MUSIC_PLAY, MUSIC_BACKGROUND, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 104:
#line 522 "b2cy.y"
{ yyval.node = do_bmusic(MUSIC_PLAY, MUSIC_FOREGROUND, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 105:
#line 523 "b2cy.y"
{ yyval.node = do_bcommand("_vibrate", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 106:
#line 524 "b2cy.y"
{ yyval.node = do_bongoto(yyvsp[-3].expr, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 107:
#line 525 "b2cy.y"
{ yyval.node = do_bongosub(yyvsp[-3].expr, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 108:
#line 526 "b2cy.y"
{ yyval.node = do_bscore(yyvsp[-1].expr); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 109:
#line 527 "b2cy.y"
{ yyval.node = do_bscore(NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 110:
#line 528 "b2cy.y"
{ yyval.node = do_bmenu(yyvsp[-3].string, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 111:
#line 529 "b2cy.y"
{ yyval.node = do_bmenuxy(yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].string, yyvsp[-1].node); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 112:
#line 530 "b2cy.y"
{ yyval.node = do_bcommand("_keyclick", bterm_new("1"), NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 113:
#line 531 "b2cy.y"
{ yyval.node = do_bcommand("_keyclick", bterm_new("0"), NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 114:
#line 532 "b2cy.y"
{ yyval.node = do_bexitprogram(); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 115:
#line 533 "b2cy.y"
{ yyval.node = do_bcommand("_msg_send", yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 116:
#line 534 "b2cy.y"
{ yyval.node = do_bcommand("_rect", yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 117:
#line 535 "b2cy.y"
{ yyval.node = do_bcommand("_rectfill", yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 118:
#line 536 "b2cy.y"
{ yyval.node = do_bcommand("_circle", yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 119:
#line 537 "b2cy.y"
{ yyval.node = do_bcommand("_circfill", yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 120:
#line 538 "b2cy.y"
{ yyval.node = do_bcommand("_page", yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 121:
#line 539 "b2cy.y"
{ yyval.node = do_bcommand("_pagecopy", yyvsp[-11].expr, yyvsp[-9].expr, yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 122:
#line 540 "b2cy.y"
{yyval.node = do_bcommand("_load", yyvsp[-1].expr, NULL);  yyval.node = do_bstatement(yyval.node, yylineno); ;
    break;}
case 123:
#line 542 "b2cy.y"
{c_strings = 1;;
    break;}
case 124:
#line 543 "b2cy.y"
{c_strings = 0;;
    break;}
case 125:
#line 544 "b2cy.y"
{c_coords = 1;;
    break;}
case 126:
#line 545 "b2cy.y"
{c_coords = 0;;
    break;}
case 127:
#line 546 "b2cy.y"
{n_sprites = atoi(yacctext); ;
    break;}
case 128:
#line 547 "b2cy.y"
{n_3dsprites = atoi(yacctext); ;
    break;}
case 129:
#line 548 "b2cy.y"
{n_rooms = atoi(yacctext); ;
    break;}
case 130:
#line 549 "b2cy.y"
{_show_ = 1;;
    break;}
case 131:
#line 550 "b2cy.y"
{_show_ = 0;;
    break;}
case 132:
#line 551 "b2cy.y"
{_escape_ = 1;;
    break;}
case 133:
#line 552 "b2cy.y"
{_escape_ = 0; ;
    break;}
case 134:
#line 553 "b2cy.y"
{_help_ = 1;;
    break;}
case 135:
#line 554 "b2cy.y"
{_help_ = 0; ;
    break;}
case 136:
#line 555 "b2cy.y"
{_multitask_ = 1;;
    break;}
case 137:
#line 556 "b2cy.y"
{_multitask_ = 0; ;
    break;}
case 138:
#line 557 "b2cy.y"
{_show_main_ = 0; ;
    break;}
case 139:
#line 558 "b2cy.y"
{_show_main_ = 1; ;
    break;}
case 140:
#line 560 "b2cy.y"
{ yyval.mode = MODE_READ; ;
    break;}
case 141:
#line 561 "b2cy.y"
{ yyval.mode = MODE_WRITE; ;
    break;}
case 142:
#line 562 "b2cy.y"
{ yyval.mode = MODE_APPEND; ;
    break;}
case 143:
#line 563 "b2cy.y"
{ yyval.mode = MODE_ARCHIVE; ;
    break;}
case 144:
#line 565 "b2cy.y"
{ yyval.node = do_math("sin", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 145:
#line 566 "b2cy.y"
{ yyval.node = do_math("sinh", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 146:
#line 567 "b2cy.y"
{ yyval.node = do_math("asin", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 147:
#line 568 "b2cy.y"
{ yyval.node = do_math("asinh", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 148:
#line 569 "b2cy.y"
{ yyval.node = do_math("abs", yyvsp[-1].expr, DATATYPE_INT); ;
    break;}
case 149:
#line 570 "b2cy.y"
{ yyval.node = do_math("abs", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 150:
#line 571 "b2cy.y"
{ yyval.node = do_math("int", yyvsp[-1].expr, DATATYPE_INT); ;
    break;}
case 151:
#line 572 "b2cy.y"
{ yyval.node = do_math("cos", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 152:
#line 573 "b2cy.y"
{ yyval.node = do_math("cosh", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 153:
#line 574 "b2cy.y"
{ yyval.node = do_math("acos", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 154:
#line 575 "b2cy.y"
{ yyval.node = do_math("acosh", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 155:
#line 576 "b2cy.y"
{ yyval.node = do_math("tan", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 156:
#line 577 "b2cy.y"
{ yyval.node = do_math("actan", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 157:
#line 578 "b2cy.y"
{ yyval.node = do_math("actanh", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 158:
#line 579 "b2cy.y"
{ yyval.node = do_math("atan", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 159:
#line 580 "b2cy.y"
{ yyval.node = do_math("atanh", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 160:
#line 581 "b2cy.y"
{ yyval.node = do_math("sqrt", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 161:
#line 582 "b2cy.y"
{ yyval.node = do_math("inv", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 162:
#line 583 "b2cy.y"
{ yyval.node = do_math("exp", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 163:
#line 584 "b2cy.y"
{ yyval.node = do_math("log", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 164:
#line 585 "b2cy.y"
{ yyval.node = do_math("log10", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 165:
#line 586 "b2cy.y"
{ yyval.node = do_math("log2", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 166:
#line 587 "b2cy.y"
{ yyval.node = do_math("pow2", yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 167:
#line 588 "b2cy.y"
{ yyval.node = do_math("rnd", yyvsp[-1].expr, DATATYPE_INT); ;
    break;}
case 168:
#line 589 "b2cy.y"
{ yyval.node = do_math2("pow", yyvsp[-3].expr, yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 169:
#line 590 "b2cy.y"
{ yyval.node = do_math2("sqr_pow", yyvsp[-3].expr, yyvsp[-1].expr, DATATYPE_DOUBLE); ;
    break;}
case 170:
#line 591 "b2cy.y"
{ yyval.node = do_bcommand("_key", zero_term, NULL); ;
    break;}
case 171:
#line 592 "b2cy.y"
{ yyval.node = do_bcommand("_key", yyvsp[-1].expr, NULL); ;
    break;}
case 172:
#line 593 "b2cy.y"
{ yyval.node = do_bcommand("_getkey", NULL); ;
    break;}
case 173:
#line 594 "b2cy.y"
{ yyval.node = do_char(yyvsp[-1].expr); ;
    break;}
case 174:
#line 595 "b2cy.y"
{ yyval.node = do_bcommand("_getchar", NULL); ;
    break;}
case 175:
#line 596 "b2cy.y"
{ yyval.node = do_bcommand("_eof", yyvsp[-1].expr, NULL); ;
    break;}
case 176:
#line 597 "b2cy.y"
{ yyval.node = do_bcommand("_collision", yyvsp[-3].expr, yyvsp[-1].expr, NULL); ;
    break;}
case 177:
#line 598 "b2cy.y"
{ yyval.node = do_bcommand("_3d_collision", yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr, NULL); ;
    break;}
case 178:
#line 599 "b2cy.y"
{ yyval.node = do_bcommand("_usermenu", yyvsp[-3].node, yyvsp[-1].node, NULL); ;
    break;}
case 179:
#line 600 "b2cy.y"
{ yyval.node = do_bcommand("_tocyid", yyvsp[-1].node, NULL); ;
    break;}
case 180:
#line 601 "b2cy.y"
{ yyval.node = do_bcommand("_touser", yyvsp[-1].node, NULL); ;
    break;}
case 181:
#line 602 "b2cy.y"
{ yyval.node = do_bcommand("_dialog", yyvsp[-3].node, yyvsp[-1].node, null_term, zero_term, NULL); ;
    break;}
case 182:
#line 603 "b2cy.y"
{ yyval.node = do_bcommand("_dialog", yyvsp[-7].node, yyvsp[-5].node, yyvsp[-3].node, yyvsp[-1].node, NULL); ;
    break;}
case 183:
#line 604 "b2cy.y"
{ yyval.node = do_bcommand("_nextfile", yyvsp[-1].node, NULL); ;
    break;}
case 184:
#line 605 "b2cy.y"
{ yyval.node = do_bcommand("_filelist", yyvsp[-5].node, yyvsp[-3].node, yyvsp[-1].node, bterm_new("_ptr_main_module"), NULL); ;
    break;}
case 185:
#line 606 "b2cy.y"
{ yyval.node = do_bcommand("_exists", yyvsp[-1].expr, NULL); ;
    break;}
case 186:
#line 607 "b2cy.y"
{ yyval.node = do_bcommand("strlen", yyvsp[-1].expr, NULL); ;
    break;}
case 187:
#line 608 "b2cy.y"
{ yyval.node = do_math("stringwidth", yyvsp[-1].expr, DATATYPE_INT); ;
    break;}
case 188:
#line 609 "b2cy.y"
{ yyval.node = do_math("stringheight", yyvsp[-1].expr, DATATYPE_INT); ;
    break;}
case 189:
#line 610 "b2cy.y"
{ yyval.node = do_bcommand("_wrap", yyvsp[-13].expr, yyvsp[-11].expr, yyvsp[-9].expr, yyvsp[-7].expr, yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[-1].expr); ;
    break;}
case 190:
#line 612 "b2cy.y"
{ yyval.expr = yyvsp[0].expr; ;
    break;}
case 191:
#line 613 "b2cy.y"
{ yyval.node = do_list(yyvsp[-2].node, yyvsp[0].node); ;
    break;}
case 192:
#line 615 "b2cy.y"
{ yyval.node = yyvsp[0].node; ;
    break;}
case 193:
#line 616 "b2cy.y"
{ yyval.node = do_list(yyvsp[-2].node, yyvsp[0].node); ;
    break;}
case 194:
#line 618 "b2cy.y"
{ yyval.node = do_param(yyvsp[-2].string, yyvsp[0].num, 0, BDIM_BY_VAL, NULL); ;
    break;}
case 195:
#line 619 "b2cy.y"
{ yyval.node = do_param(yyvsp[-4].string, yyvsp[0].num, 1, BDIM_BY_VAL, NULL); ;
    break;}
case 196:
#line 620 "b2cy.y"
{ yyval.node = do_param(yyvsp[-2].string, yyvsp[0].num, 0, BDIM_BY_REF, NULL); ;
    break;}
case 197:
#line 621 "b2cy.y"
{ yyval.node = do_param(yyvsp[-2].string, yyvsp[0].num, 0, BDIM_BY_VAL, NULL); ;
    break;}
case 198:
#line 627 "b2cy.y"
{ yyval.node = NULL; ;
    break;}
case 199:
#line 628 "b2cy.y"
{ yyval.node = yyvsp[0].node; ;
    break;}
case 200:
#line 629 "b2cy.y"
{ yyval.node = do_paramlist(yyvsp[-2].node, yyvsp[0].node); ;
    break;}
case 201:
#line 631 "b2cy.y"
{yyval.node=NULL;;
    break;}
case 202:
#line 632 "b2cy.y"
{yyval.node=NULL;;
    break;}
case 203:
#line 635 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_EQ, yyvsp[0].expr); ;
    break;}
case 204:
#line 637 "b2cy.y"
{ yyval.expr = yyvsp[-1].expr; ;
    break;}
case 205:
#line 638 "b2cy.y"
{ yyval.node = do_list(yyvsp[-3].node, yyvsp[-1].node); ;
    break;}
case 206:
#line 640 "b2cy.y"
{ yyval.expr = do_funccall(yyvsp[-3].string, (Blist *)yyvsp[-1].expr); ;
    break;}
case 207:
#line 642 "b2cy.y"
{ yyval.expr = do_funccall(yyvsp[-3].string, (Blist *)yyvsp[-1].expr); ;
    break;}
case 208:
#line 643 "b2cy.y"
{ yyval.expr = do_funccall(yyvsp[0].string, NULL); ;
    break;}
case 209:
#line 645 "b2cy.y"
{ yyval.node = NULL; ;
    break;}
case 210:
#line 646 "b2cy.y"
{ yyval.node = yyvsp[0].node; ;
    break;}
case 211:
#line 647 "b2cy.y"
{ yyval.node = do_funclist(yyvsp[-2].node, yyvsp[0].node); ;
    break;}
case 212:
#line 649 "b2cy.y"
{ yyval.node = do_bexpr(yyvsp[0].term); ;
    break;}
case 213:
#line 650 "b2cy.y"
{ yyval.node = yyvsp[0].node; ;
    break;}
case 214:
#line 651 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_ADD, yyvsp[0].expr);;
    break;}
case 215:
#line 652 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_SUB, yyvsp[0].expr);;
    break;}
case 216:
#line 653 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_MUL, yyvsp[0].expr);;
    break;}
case 217:
#line 654 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_DIV, yyvsp[0].expr);;
    break;}
case 218:
#line 655 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_MOD, yyvsp[0].expr);;
    break;}
case 219:
#line 656 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_LESSER, yyvsp[0].expr);;
    break;}
case 220:
#line 657 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_GREATER, yyvsp[0].expr);;
    break;}
case 221:
#line 658 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_GEQ, yyvsp[0].expr);;
    break;}
case 222:
#line 659 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_LEQ, yyvsp[0].expr);;
    break;}
case 223:
#line 660 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_NEQ, yyvsp[0].expr);;
    break;}
case 224:
#line 661 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_AND, yyvsp[0].expr);;
    break;}
case 225:
#line 662 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_OR, yyvsp[0].expr);;
    break;}
case 226:
#line 663 "b2cy.y"
{ yyval.expr = do_bop(yyvsp[-2].expr, OP_EQEQ, yyvsp[0].expr);;
    break;}
case 227:
#line 664 "b2cy.y"
{ yyval.expr = do_bop(NULL, OP_NOT, yyvsp[0].expr);;
    break;}
case 228:
#line 665 "b2cy.y"
{ yyval.expr = do_bop(NULL, OP_UNARY_MINUS, yyvsp[0].expr);;
    break;}
case 229:
#line 666 "b2cy.y"
{ yyval.expr = do_bop(NULL, OP_UNARY_PLUS, yyvsp[0].expr);;
    break;}
case 230:
#line 667 "b2cy.y"
{ yyval.expr = do_bop(NULL, OP_LPAREN, yyvsp[-1].expr); ;
    break;}
case 231:
#line 669 "b2cy.y"
{yyval.node = do_varterm(""); ;
    break;}
case 232:
#line 670 "b2cy.y"
{ yyval.node = do_varterm(lowercase(yacctext)); ;
    break;}
case 233:
#line 672 "b2cy.y"
{ yyval.string=strdup(lowercase(yacctext)); ;
    break;}
case 234:
#line 674 "b2cy.y"
{ yyval.string=strdup(yacctext);;
    break;}
case 235:
#line 676 "b2cy.y"
{ yyval.string=strdup(yacctext);;
    break;}
case 236:
#line 678 "b2cy.y"
{ yyval.string=strdup(uppercase(yacctext)); ;
    break;}
case 237:
#line 680 "b2cy.y"
{ yyval.string=strdup(yacctext); ;
    break;}
case 238:
#line 682 "b2cy.y"
{ yyval.string=strdup(yacctext); ;
    break;}
case 239:
#line 684 "b2cy.y"
{ yyval.node = do_variable((Bterm *)do_bterm(yyvsp[0].string, 0, 0, 0), 0); ;
    break;}
case 240:
#line 685 "b2cy.y"
{ yyval.node = do_variable((Bterm *)do_bterm(yyvsp[-1].string, 0, 0, 0), yyvsp[0].node); ;
    break;}
case 241:
#line 687 "b2cy.y"
{ yyval.node = do_bterm(yyvsp[0].string, 0, 0, 0); ;
    break;}
case 242:
#line 688 "b2cy.y"
{ yyval.node = do_bterm(yyvsp[-1].string, 0, 0, 0); yyval.expr->addchild(yyval.expr, yyvsp[0].expr); ;
    break;}
case 244:
#line 691 "b2cy.y"
{ yyval.node = yyvsp[-2].node; yyvsp[-2].node->addchild(yyvsp[-2].node, yyvsp[0].node); ;
    break;}
case 245:
#line 693 "b2cy.y"
{ yyval.node = do_bterm(yacctext, DATATYPE_INT, 1, 0); ;
    break;}
case 246:
#line 694 "b2cy.y"
{ yyval.node = do_bterm(yacctext, DATATYPE_LONG, 1, 0); ;
    break;}
case 247:
#line 695 "b2cy.y"
{ yyval.node = do_bterm(yacctext, DATATYPE_DOUBLE, 1, 0); ;
    break;}
case 248:
#line 696 "b2cy.y"
{ yyval.node = do_bterm(fix_string(yacctext), DATATYPE_CHAR, 1, 1); ;
    break;}
case 249:
#line 697 "b2cy.y"
{ yyval.node = do_bterm(yacctext, DATATYPE_CHAR, 1, 0); ;
    break;}
case 250:
#line 698 "b2cy.y"
{ yyval.node = do_bterm(yyvsp[0].string, DATATYPE_INT, 1, 0); ;
    break;}
case 251:
#line 699 "b2cy.y"
{ yyval.node = yyvsp[0].node; ;
    break;}
case 252:
#line 700 "b2cy.y"
{ yyval.node = do_variable((Bterm *)yyvsp[0].node, NULL); ;
    break;}
case 253:
#line 701 "b2cy.y"
{ yyval.node = yyvsp[0].node; ;
    break;}
case 254:
#line 702 "b2cy.y"
{ yyval.node = do_bterm("0", DATATYPE_INT, 1, 0); ;
    break;}
case 255:
#line 703 "b2cy.y"
{ yyval.node = do_bterm("1", DATATYPE_INT, 1, 0); ;
    break;}
case 256:
#line 704 "b2cy.y"
{ yyval.node = do_bterm("2", DATATYPE_INT, 1, 0); ;
    break;}
case 257:
#line 705 "b2cy.y"
{ yyval.node = do_bterm("3", DATATYPE_INT, 1, 0); ;
    break;}
case 258:
#line 706 "b2cy.y"
{ yyval.node = do_bterm("1", DATATYPE_INT, 1, 0); ;
    break;}
case 259:
#line 707 "b2cy.y"
{ yyval.node = do_bterm("2", DATATYPE_INT, 1, 0); ;
    break;}
case 260:
#line 708 "b2cy.y"
{ yyval.node = do_bterm("0", DATATYPE_INT, 1, 0); ;
    break;}
case 261:
#line 709 "b2cy.y"
{ yyval.node = do_bterm("_true_", DATATYPE_INT, 1, 0); ;
    break;}
case 262:
#line 710 "b2cy.y"
{ yyval.node = do_bterm("_false_", DATATYPE_INT, 1, 0); ;
    break;}
case 263:
#line 711 "b2cy.y"
{ yyval.node = do_bterm("error", DATATYPE_INT, 1, 0); ;
    break;}
case 264:
#line 712 "b2cy.y"
{ yyval.node = do_bterm("ALIGN_LEFT", DATATYPE_INT, 1, 0); ;
    break;}
case 265:
#line 713 "b2cy.y"
{ yyval.node = do_bterm("ALIGN_CENTER", DATATYPE_INT, 1, 0); ;
    break;}
case 266:
#line 714 "b2cy.y"
{ yyval.node = do_bterm("ALIGN_RIGHT", DATATYPE_INT, 1, 0); ;
    break;}
case 267:
#line 715 "b2cy.y"
{ yyval.node = do_bterm("WRAP_CHAR", DATATYPE_INT, 1, 0); ;
    break;}
case 268:
#line 716 "b2cy.y"
{ yyval.node = do_bterm("WRAP_WORD", DATATYPE_INT, 1, 0); ;
    break;}
case 269:
#line 718 "b2cy.y"
{yyval.num=DATATYPE_CHAR;;
    break;}
case 270:
#line 719 "b2cy.y"
{yyval.num=DATATYPE_INT;;
    break;}
case 271:
#line 720 "b2cy.y"
{yyval.num=DATATYPE_DOUBLE;;
    break;}
case 272:
#line 721 "b2cy.y"
{yyval.num=DATATYPE_LONG;;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}


#line 723 "b2cy.y"

void yyerror(s)
     char *s;
{
  printf("%s(%d): (level=%d) ERROR - %s\n", g_infname, yylineno, body_stack_n, s );
  exit(1);
}

char *fix_string(char *s)
{
  char buf[256];
  char *x;
  char *y;
  if (c_strings) return s;
  for(x=s, y=buf; *x; x++, y++)
  {
	if (*x=='\\') {*y='\\'; y++;}
	*y=*x;
  }
  *y = 0;
  return strdup(buf);
}

Bdim *find_function_name(name)
     char *name;
{
	Bfunction *bfunction;
	Node *n = NULL;

	DBG0(">find_function_name\n");

	for(bfunction=(Bfunction *)bprogram->child; 
		bfunction; 
		bfunction=(Bfunction *)bfunction->next)
	{
		if (bfunction->type != TYPE_FUNCTION) continue;
		if (SAME(bfunction->name, name)) break;
	}

	if (bfunction == NULL)
	{
		int i;
		for(i=0; i<=body_stack_n; i++)
		{
			bfunction = (Bfunction *)body_stack[i];
			if (bfunction->type != TYPE_FUNCTION) continue;
			if (SAME(bfunction->name, name)) break;
		}
		if (i > body_stack_n) bfunction = NULL;
	}

	DBG0("<find_function_name\n");
	return (Bdim *)bfunction;
}

Bdim *find_function_dim(name)
     char *name;
{
  Bfunction *bfunction;
  int i;
  Node *n = NULL;
  Bdim *bdim;

  DBG0(">find_function_dim\n");
  for(i=body_stack_n; i>=0; i--)
    {
		if (body_stack[i]->type == TYPE_FUNCTION)
		break;
    }
  if (i != -1)
    {
		bfunction = (Bfunction *)body_stack[i];
		for(n=bfunction->child; n; n=n->next)
		{
			if (n->type == TYPE_DIM)
			{
			  bdim = (Bdim *)n;
			  if (SAME(bdim->name, name)) break;
			}
		}
    }
  DBG0("<find_function_dim\n");
  return (Bdim *) n;
}

Bdim *find_function_return(name)
     char *name;
{
  Bfunction *bfunction = NULL;
  Bdim *bdim = NULL;
  int i;

  DBG0(">find_function_return\n");
  for(i=body_stack_n; i>=0; i--)
    {
      if (body_stack[i]->type == TYPE_FUNCTION)
      {
		bfunction = (Bfunction *) body_stack[i];
		if (SAME(bfunction->name, name)) 
		{
			bdim = (Bdim *) bfunction;
			break;
		}
      }
    }
  DBG0("<find_function_return\n");
  return bdim;
}

Bdim *find_function_param(name)
     char *name;
{
  Bfunction *bfunction;
  int i;
  Node *n=NULL;
  Bdim *bdim;

  DBG0(">find_function_param\n");
  for(i=body_stack_n; i>=0; i--)
    {
      if (body_stack[i]->type == TYPE_FUNCTION)
	break;
    }
  if (i != -1) 
    {
      bfunction = (Bfunction *) body_stack[i];
      if (bfunction->child->type == TYPE_LIST) 
	bfunction = (Bfunction *)bfunction->child;
      for(n=bfunction->child; n; n=n->next)
	{	
	  bdim = (Bdim *) n;
	  if (n->type == TYPE_PARAM)
	    {
	      if (SAME(bdim->name, name)) break;
	    }
	}
    }
  DBG0("<find_function_param\n");
  return (Bdim *) n;
}

Bdim *find_program_dim(name)
     char *name;
{
  Node *n;
  Bdim *bdim;

  DBG0(">find_program_dim\n");
  for(n=bprogram->child; n; n=n->next)
    {
      if (n->type == TYPE_DIM)
		{
		  bdim = (Bdim *) n;
		  if (SAME(bdim->name, name)) break;
		}
    }
  DBG0("<find_program_dim\n");
  return (Bdim *) n;
}

Node *do_bterm(name, datatype, literal, dimension)
     char *name;
     int datatype;
     int literal;
	 int dimension;
{
   Bterm *bterm= bterm_new(name); 

   DBG0(">do_bterm\n");

   bterm->datatype=datatype; 
   bterm->literal = literal;
   bterm->dimension = dimension;

   DBG0("<do_bterm\n");
   return (Node *) bterm;
}

Node *do_variable(Bterm *bterm, Node *subscript)
{
	Bdim *bdim;

	DBG0(">do_variable name=%s\n", bterm->name);

	bdim = find_function_return(bterm->name);
	if (bdim) // found a function return value, use _name
	{
		Bfunction *bfunction = (Bfunction *) bdim;
		bterm->datatype = bfunction->datatype;
		bterm->dim = (Bdim *) bfunction;
		if (bterm->name) free(bterm->name);
		bterm->name = malloc(strlen(bfunction->name)+2);
		sprintf(bterm->name, "_%s", bfunction->name);
		goto EARLY_EXIT;
	}
	if (bdim == NULL) bdim = find_function_dim(bterm->name);
	if (bdim == NULL) bdim = find_function_param(bterm->name);
	if (bdim == NULL) bdim = find_program_dim(bterm->name);
	if (bdim == NULL) bdim = find_function_name(bterm->name);
	if (bdim == NULL) doerr2("%s(%d) ERROR - Variable %s undefined in line %d", g_infname, yylineno, bterm->name, yylineno);
	if (bdim->type == TYPE_DIM || bdim->type == TYPE_PARAM)
	{
		DBG0("...Its a DIM or PARAM\n");
		bterm->datatype = bdim->datatype;
		bterm->dim = bdim;
		bterm->dimension = bdim->dimension;
		if (subscript)
		{
			bterm->addchild(bterm, subscript);
			if (subscript->type == TYPE_LIST) 
				bterm->dimension = bterm->dimension - 2;
			else 
				bterm->dimension = bterm->dimension - 1;
		}
		if (bdim->datatype == DATATYPE_TYPE)
		{
			Bterm *member=(Bterm *)bterm->last;
			Bdim  *found=(Bdim *)find_member_name(bdim->btype, member->name);
			if (found==NULL)
				doerr2("could not find member %s", member->name);
			else
			{
				bterm->datatype = found->datatype;
				if (found->child)
				{
					if (found->child->type == TYPE_EXPR)
					{
						bterm->dimension = 1;
					}
					else if (found->child->type == TYPE_LIST)
					{
						bterm->dimension = 2;
					}
				}
			}
		}
	}
	else if (bdim->type == TYPE_FUNCTION)  // found a function call use name()
	{
		Bfunccall *bfunccall = bfunccall_new();
		Bfunction *bfunction = (Bfunction *) bdim;
		bfunccall->bfunction = bfunction;
		bterm = (Bterm *) do_bexpr((Bterm *)bfunccall);
	}
	else
	{
		doerr2("%d(%s) ERROR - Variable %s is not defined (line %d) type=%d\n", g_infname, yylineno, bterm->name, yylineno, bdim->type);
	}
EARLY_EXIT:
	DBG0("<do_variable name=%s\n", bterm->name);
	return (Node *)bterm;
}

Node *do_bstatement(expr, lineno)
  Node *expr;
  int lineno;
{
  Bstatement *bstatement = bstatement_new();

  DBG0(">do_bstatement\n");

  bstatement->addchild(bstatement, expr); 
  bstatement->lineno = lineno-1;

  DBG0("<do_bstatement\n");

  return (Node *) bstatement;
}

Node *find_type_name(char *name)
{
	Btype *n;

	for(n=(Btype *)bprogram->child; n; n=(Btype *)n->next)
	{
		if (n->type == TYPE_TYPE && SAME(name, n->name))
		{
			return (Node *)n;
		}
	}
	return NULL;
}

Bdim *find_member_name(Btype *btype, char *name)
{
	Bdim *n;

	for(n=(Bdim *)btype->child; n; n=(Bdim *)n->next)
	{
		if (SAME(name, n->name))
		{
			return (Bdim *)n;
		}
	}
	return NULL;
}

Node *do_bdim(var, datatype, expr, typename)
	char *var;
	int datatype;
	Node *expr;
	char *typename;
{
  Bdim *bdim = bdim_new();
  int i;
  Bfunction *bfunction;

DBG0(">do_bdim\n");
  strcpy(bdim->name, var);
  bdim->datatype = datatype;
  bdim->dimension = 0;
  if (expr) 
  {
	bdim->addchild(bdim, expr);
	if (expr->type == TYPE_EXPR)
		bdim->dimension=1;
	else if (expr->type == TYPE_LIST)
		bdim->dimension=2;
  }

  for(i=body_stack_n; i>=0; i--)
    {
      if (body_stack[i]->type == TYPE_FUNCTION ||
		  body_stack[i]->type == TYPE_PROGRAM)
      {
		bfunction = (Bfunction *) body_stack[i];
		bfunction->addchild(bfunction, bdim);
		break;
      }
    }
  if (typename)
  {
	  bdim->btype = (Btype *)find_type_name(typename);
	  if (bdim->btype == NULL)
	  {
	      doerr2("%s(%d) ERROR - user defined type '%s' is unknown", g_infname, yylineno, typename );
	  }
  }
DBG0("<do_bdim\n");

  return (Node *)NULL;
}

Node *do_bexpr(term)
	Bterm *term;
{
  Bexpr *bexpr = bexpr_new();

  DBG0(">do_bexpr\n");

  bexpr->addchild(bexpr, term);

  /** pass the literal flag up **/
  bexpr->datatype = term->datatype;
  bexpr->literal = term->literal;
  bexpr->dimension = term->dimension;

  DBG0("<do_bexpr\n");

  return (Node *)bexpr;
}

Bexpr *do_bop(left, op, right)
     Bexpr *left;
     int op;
     Bexpr *right;
{
  Bop *bop = bop_new(op);

  DBG0(">do_bop\n");

  if (left) bop->addchild(bop, left);
  if (right) bop->addchild(bop, right);

	switch(bop->op) {
	  case OP_NOT:
	  case OP_UNARY_MINUS:
	  case OP_UNARY_PLUS:
	  case OP_LPAREN: 
		  bop->datatype = right->datatype;
		  break;
	  case OP_AND:
	  case OP_OR: 
	  case OP_NEQ:
	  case OP_LEQ:
	  case OP_GEQ:
	  case OP_GREATER:
	  case OP_EQEQ:
	  case OP_LESSER:
	      bop->datatype = DATATYPE_INT;
		  break;
	  case OP_ADD:
	  case OP_SUB:
	  case OP_MUL:
	  case OP_DIV:
	  case OP_MOD:
		if (left->datatype == right->datatype)
		{
			bop->datatype = left->datatype;
		}
		else if (left->datatype > right->datatype)
	    {
	      bop->datatype = left->datatype;
	    }
		else 
	    {
	      bop->datatype = right->datatype;
	    }
		break;
  	  case OP_EQ: 
		bop->datatype = left->datatype;
		break;
	  case OP_LBRACKET: 
		bop->datatype = left->datatype;
		break;
	  default:
		doerr2("%s(%d) ERROR - Internal Error - bad Op", g_infname, yylineno );
	}

  DBG0("<do_bop\n");

  return (Bexpr *) bop;
}

Node *do_bfor(name, from, to, step)
     char *name;
     Node *from;
     Node *to;
     Node *step;
{
  Bfor *bfor;
  Bdim *bdim;
  Bterm *counter= bterm_new(name); 
  int i;

  DBG0(">do_bfor\n");

  bfor = bfor_new();

  bdim = find_function_dim(name);
  if (!bdim) bdim = find_program_dim(name);
  if (!bdim)
  {
     for(i=body_stack_n; i>=0; i--)
     {
		if (body_stack[i]->type == TYPE_FUNCTION || 
			body_stack[i]->type == TYPE_PROGRAM)
		{
			do_bdim(name, DATATYPE_INT, NULL, NULL);
			break;
		}
     }
  }
  bfor->addchild(bfor, counter);
  bfor->addchild(bfor, from);
  bfor->addchild(bfor, to);
  if (step) bfor->addchild(bfor, step);

  DBG0(">do_bfor\n");

  return (Node *) bfor;
}

Node *do_bwhile(expr)
     Node *expr;
{
  Bwhile *bwhile;

  DBG0(">do_bwhile\n");

  if (expr == NULL)
  {
	doerr2("%s(%d) ERROR - Function WHILE has missing expression.\n", 
		g_infname, yylineno);
  }

  bwhile = bwhile_new();
  bwhile->addchild(bwhile, expr);

  DBG0("<do_bwhile\n");
  return (Node *) bwhile;
}

Node *do_bfunction(name, parameters, datatype)
     char *name;
     Node *parameters;
     int datatype;
{
	Bfunction *bfunction;

	DBG0(">do_bfunction\n");

	bfunction = (Bfunction *) find_function_name(name);
	// if the function was previously defined...
	if (bfunction && bfunction->child)
	{
		doerr2("%s(%d) ERROR - Function %s previously defined.\n", 
			g_infname, yylineno, name);
	}
	// if the function was called but not defined
	else if (bfunction)
	{
		bfunction->remchild(bfunction);
	}
	// if the function was never called nor defined
	else if (bfunction == NULL)
	{
		bfunction = bfunction_new();
	}

	strcpy(bfunction->name, name);
	if (SAME(name, "onmessage"))
	{
		_onmessage_defined_ = 1;
	}
	bfunction->datatype = datatype;
	if (!parameters)
	  parameters = (Node *) blist_new();
	bfunction->addchild(bfunction, parameters);
	DBG0("<do_bfunction\n");
	return (Node *) bfunction;
}

Node *do_bif(exp)
     Node *exp;
{
  Bif *bif;
  Bthen *bthen;
  DBG0(">do_bif\n");
  bif = bif_new();
  bthen = bthen_new();
  bif->addchild(bif, exp);
  bif->addchild(bif, bthen);
  push((Node *) bif);
  push((Node *) bthen);
  DBG0("<do_bif\n");
  return (Node *) bif;
}

Node *do_bif2(exp, stmt)
     Node *exp;
	 Node *stmt;
{
  Bif *bif;
  Bthen *bthen;
  DBG0(">do_bif2\n");
  bif = bif_new();
  bthen = bthen_new();
  bif->addchild(bif, exp);
  bif->addchild(bif, bthen);
  bthen->addchild(bthen, stmt);
  DBG0("<do_bif2\n");
  return (Node *) bif;
}

Node *do_belseif(exp)
     Node *exp;
{
  Belseif *belseif;
  Bif *bif = (Bif *) body_stack[body_stack_n];

  DBG0(">do_belseif\n");

  belseif = belseif_new();
  belseif->addchild(belseif, exp);
  bif->addchild(bif, belseif);
  push((Node *) belseif);
  DBG0("<do_belseif\n");
  return (Node *)belseif;
}

Node *do_belse()
{
  Belse *belse;
  Bif *bif = (Bif *)body_stack[body_stack_n];
  DBG0(">do_belse\n");
  belse = belse_new();
  bif->addchild(bif, belse);
  push((Node *) belse);
  DBG0("<do_belse\n");
  return (Node *) belse;
}

Node *do_bexitfor()
{
	int i;
    Bexit *bexit = bexit_new();
    DBG0(">do_bexitfor\n");
	for(i=body_stack_n; i>=0; i--)
	{
		if (body_stack[i]->type == TYPE_FOR) break;
		if (body_stack[i]->type == TYPE_PROGRAM ||
			body_stack[i]->type == TYPE_FUNCTION ||
			body_stack[i]->type == TYPE_WHILE)
			{
				doerr2("%s(%d) ERROR - Misplaced Exit For (line %d)\n", g_infname, yylineno, yylineno);
			}
	}
    DBG0("<do_bexitfor\n");
    return (Node *) bexit;
}

Node *do_bexitwhile()
{
	int i;
    Bexit *bexit = bexit_new();
    DBG0(">do_bexitwhile\n");
	for(i=body_stack_n; i>=0; i--)
	{
		if (body_stack[i]->type == TYPE_WHILE) break;
		if (body_stack[i]->type == TYPE_PROGRAM ||
			body_stack[i]->type == TYPE_FUNCTION ||
			body_stack[i]->type == TYPE_FOR)
		{
			doerr2("%s(%d) ERROR - Misplaced Exit While (line %d)\n", g_infname, yylineno, yylineno);
		}
	}
    DBG0("<do_bexitwhile\n");
    return (Node *) bexit;
}

Node *do_bexitfunction()
{
    Bexitfunction *bexitfunction = bexitfunction_new();
    DBG0(">do_bexitfunction\n");
//    if (body_stack[body_stack_n]->type != TYPE_FUNCTION)
//       doerr2("%s(%d) ERROR - Misplaced Exit Function (line %d)\n", g_infname, yylineno, yylineno);
    DBG0(">do_bexitfunction\n");
    return (Node *) bexitfunction;
}

void push(node)
	Node *node;
{
	body_stack[++body_stack_n] = node;
}

Node *pop(type)
     int type;
{
	Node *node;

	node = body_stack[body_stack_n--];
	if (body_stack_n < 0)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Too many END/NEXT statements \n", g_infname, yylineno);
		exit(1);
	}
	if (node->type != type)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Mismatched END/NEXT statements \n", g_infname, yylineno);
		printf("                Found statement %s\n", node_types[node->type]);
		exit(1);
	}
	return node;
}

Node *pop2(type1, type2)
     int type1;
     int type2;
{
	Node *node;

	node = body_stack[body_stack_n--];
	if (body_stack_n < 0)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Too many END/NEXT statements \n", g_infname, yylineno);
		exit(1);
	}
	if (node->type != type1 && node->type != type2)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Mismatched END/NEXT statements \n", g_infname, yylineno);
		printf("                Found statement %s\n", node_types[node->type]);
		exit(1);
	}
	return node;
}

Node *pop3(type1, type2, type3)
     int type1;
     int type2;
     int type3;
{
	Node *node;

	node = body_stack[body_stack_n--];
	if (body_stack_n < 0)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Too many END/NEXT statements \n", g_infname, yylineno);
		exit(1);
	}
	if (node->type != type1 && node->type != type2 && node->type != type3)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Mismatched END/NEXT statements \n", g_infname, yylineno);
		printf("                Found statement %s\n", node_types[node->type]);
		exit(1);
	}
	return node;
}

Node *do_bprintno(fileno, list)
     Bexpr *fileno;
     Node *list;
{
    Bprintno *bprintno = bprintno_new();
    DBG0(">do_bprintno\n");
    bprintno->addchild(bprintno, fileno);
    if (list) bprintno->addchild(bprintno, list);
    DBG0("<do_bprintno\n");
    return (Node *) bprintno;
}

Node *do_bprint(list)
     Node *list;
{
    Bprint *bprint = bprint_new();
DBG0(">do_bprint\n");
    if (list) bprint->addchild(bprint, list);
DBG0("<do_bprint\n");
    return (Node *) bprint;
}

Node *do_bsprint(Node *var, Node *list)
{
    Bsprint *bsprint = bsprint_new();
	DBG0(">do_bsprint\n");
	bsprint->addchild(bsprint, var);
    bsprint->addchild(bsprint, list);
	DBG0("<do_bsprint\n");
    return (Node *) bsprint;
}

Node *do_btokenize(Node *var, Node *tokens, Node *list)
{
    Btokenize *btokenize = btokenize_new();
	DBG0(">do_btokenize\n");
	btokenize->addchild(btokenize, var);
	btokenize->addchild(btokenize, tokens);
    btokenize->addchild(btokenize, list);
	DBG0("<do_btokenize\n");
    return (Node *) btokenize;
}

Node *do_bprintxy(x,y,list)
     Bexpr *x;
     Bexpr *y;
     Node *list;
{
    Bprintxy *bprintxy = bprintxy_new();
    DBG0(">do_bprintxy\n");
    bprintxy->addchild(bprintxy, x);
    bprintxy->addchild(bprintxy, y);
    bprintxy->addchild(bprintxy, list);
    DBG0("<do_bprintxy\n");
    return (Node *) bprintxy;
}

Node *do_list(expr1, expr2)
     Node *expr1;
     Node *expr2;
{
	if (expr1->type == TYPE_LIST)
	{
		expr1->addchild(expr1, expr2);
		return expr1;
	}
	else
	{
		Blist *blist = blist_new();
		blist->addchild(blist, expr1);
		blist->addchild(blist, expr2);
		return (Node *) blist;
	}
}


Node *do_paramlist(expr1, expr2)
     Node *expr1;
     Node *expr2;
{
	if (expr1->type == TYPE_LIST)
	{
		expr1->addchild(expr1, expr2);
		return expr1;
	}
	else
	{
		Blist *blist = blist_new();
		blist->addchild(blist, expr1);
		blist->addchild(blist, expr2);
		return (Node *) blist;
	}
}

Node *do_param(name, datatype, dimension, passed_by, initial_value)
     char *name;
     int datatype;
     int dimension;
     int passed_by;
     Bexpr *initial_value;
{
  Bparam *bparam = bparam_new();
  strcpy(bparam->name, name);
  bparam->datatype = datatype;
  bparam->dimension = dimension;
  bparam->passed_by = passed_by;
  if (initial_value)
    bparam->addchild(bparam, initial_value);
  return (Node *) bparam;
}

Bexpr *do_funccall(name, paramlist)
     char *name;
     Blist *paramlist;
{
    Bfunccall *bfunccall = bfunccall_new();
    Bfunction *bfunction = (Bfunction *) find_function_name(name);
    DBG0(">do_bfunccall\n");
    if (bfunction == NULL)
    {
		bfunction = bfunction_new();
		strcpy(bfunction->name, name);
		bprogram->addchild(bprogram, bfunction);
		bfunction->datatype = DATATYPE_INT;
	}

    bfunccall->bfunction = bfunction;
	bfunccall->datatype = bfunction->datatype;
    if (paramlist) bfunccall->addchild(bfunccall, paramlist);
    DBG0("<do_bfunccall\n");
    return (Bexpr *) do_bexpr((Bterm *)bfunccall);
}

Node *do_funclist(expr1, expr2)
     Node *expr1;
     Node *expr2;
{
	if (expr1->type == TYPE_LIST)
	{
		expr1->addchild(expr1, expr2);
		return expr1;
	}
	else
	{
		Blist *blist = blist_new();
		blist->addchild(blist, expr1);
		blist->addchild(blist, expr2);
		return (Node *) blist;
	}
}

Node *do_input(prompt, term)
     Bexpr *prompt;
     Bterm *term;
{
    Binput *binput;
    DBG0(">do_input\n");

    if (term->literal) 
	doerr2("%s(%d) ERROR -lineno %d : Cannot use literal for INPUT statement", g_infname, yylineno, yylineno);
    if (prompt && prompt->datatype != DATATYPE_CHAR) 
    {
       doerr2("%s(%d) ERROR - lineno %d : Cannot use non-string for INPUT prompt (datatype=%s)", 
		      g_infname, yylineno, yylineno, data_type[prompt->datatype]);
    }
    binput = binput_new();
    binput->addchild(binput, term);
    if (prompt)
       binput->addchild(binput, prompt);
    DBG0("<do_input\n");
    return (Node *)binput;
}

Node *do_inputxy(x, y, prompt, term)
	 Bexpr *x;
	 Bexpr *y;
     Bexpr *prompt;
     Bterm *term;
{
    Binputxy *binputxy;
    DBG0(">do_input\n");

    if (term->literal) 
	doerr2("%s(%d) ERROR -lineno %d : Cannot use literal for INPUTXY statement", g_infname, yylineno, yylineno);
    if (prompt && prompt->datatype != DATATYPE_CHAR) 
    {
       doerr2("%s(%d) ERROR - lineno %d : Cannot use non-string for INPUTXY prompt (datatype=%s)", 
		      g_infname, yylineno, yylineno, data_type[prompt->datatype]);
    }
    binputxy = binputxy_new();
    binputxy->addchild(binputxy, x);
    binputxy->addchild(binputxy, y);
    binputxy->addchild(binputxy, term);
    if (prompt)
       binputxy->addchild(binputxy, prompt);
    DBG0("<do_input\n");
    return (Node *)binputxy;
}

Node *do_char(exp)
    Bexpr *exp;
{
    Bchar *bchar = bchar_new();
    DBG0(">do_char\n");
    if (exp) bchar->addchild(bchar, exp);
    DBG0("<do_char\n");
    return (Node *) bchar;
}

Node *do_math(name, exp, type)
     char *name;
     Bexpr *exp;
	 int type;
{
    Bmath *bmath = bmath_new(name);
    DBG0(">do_math\n");
    bmath->addchild(bmath, exp);
    bmath->datatype = type;
    DBG0("<do_math\n");
    return (Node *) bmath;
}

Node *do_math2(name, exp1, exp2, type)
     char *name;
     Bexpr *exp1;
     Bexpr *exp2;
	 int type;
{
    Bmath *bmath = bmath_new(name);
    DBG0(">do_math2\n");
    bmath->addchild(bmath, exp1);
    bmath->addchild(bmath, exp2);
    bmath->datatype = type;
    DBG0("<do_math2\n");
    return (Node *) bmath;
}

Node *do_open(exp1, mode, exp2)
     Bexpr *exp1; /* filename */
     int mode;
     Bexpr *exp2; /* filenumber */
{
    Bopen *bopen = bopen_new();
    DBG0(">do_open\n");
    bopen->addchild(bopen, exp1);
    bopen->addchild(bopen, exp2);
    bopen->mode = mode;
    DBG0("<do_open\n");
    return (Node *) bopen;
}

Node *do_bscore(exp)
     Bexpr *exp;
{
    Bscore *bscore = bscore_new();
    DBG0(">do_bscore\n");

    if (exp)
       bscore->addchild(bscore, exp);
    DBG0("<do_score\n");
    return (Node *) bscore;
}

Node *do_put(exp1,exp2, name)
     Bexpr *exp1; /* filenumber */
     Bexpr *exp2; /* filepos - optional */
     Bterm *name; /* variable name */
{
    Bput *bput = bput_new();
    DBG0(">do_put\n");
    bput->addchild(bput, exp1);

    if (exp2)
    {
        bput->addchild(bput, exp2);
    }
    else /* empty file pos - replace with empty expression */
    {
	exp2 = bexpr_new();
        bput->addchild(bput, exp2);
    }

    if (name)
    {
       bput->addchild(bput, name);
    }
    else /* empty variable name - replace with emptye expression */
    {
       name = (Bterm *) bexpr_new();
       bput->addchild(bput, name);
    }

    DBG0("<do_put\n");
    return (Node *) bput;
}

Node *do_get(exp1,exp2, name)
     Bexpr *exp1; /* filenumber */
     Bexpr *exp2; /* filepos - optional */
     Bterm *name; /* variable name */
{
    Bget *bget = bget_new();
    DBG0(">do_get\n");
    bget->addchild(bget, exp1);

    if (exp2)
    {
        bget->addchild(bget, exp2);
    }
    else /* empty file pos - replace with empty expression */
    {
	exp2 = bexpr_new();
        bget->addchild(bget, exp2);
    }

    if (name)
    {
       bget->addchild(bget, name);
    }
    else /* empty variable name - replace with emptye expression */
    {
       name = (Bterm *) bexpr_new();
       bget->addchild(bget, name);
    }

    DBG0("<do_get\n");
    return (Node *) bget;
}

Node *do_mid(dest, src, start, len)
     Bterm *dest;
     Bexpr *src;
     Bexpr *start;
     Bexpr *len;
{
    Bmid *bmid = bmid_new();

    DBG0(">do_mid\n");
    bmid->addchild(bmid, dest);
    bmid->addchild(bmid, src);
    bmid->addchild(bmid, start);
    if (len) bmid->addchild(bmid, len);
    DBG0("<do_mid\n");
    return (Node *) bmid;
}

Node *do_binline(code)
     char *code;
{
	Binline *binline = binline_new();
    DBG0(">do_inline\n");
	binline->line = strdup(&code[7]);
    DBG0("<do_inline\n");
	return (Node *) binline;
}

Node *do_boutline(code)
     char *code;
{
	Boutline *boutline = boutline_new();
    DBG0(">do_outline\n");
	boutline->line = strdup(&code[8]);
    DBG0("<do_outline\n");
	return (Node *) boutline;
}

Node *do_bgoto(label)
     char *label;
{
	Bgoto *bgoto = bgoto_new(label);
    DBG0(">do_bgoto\n");
    DBG0("<do_bgoto\n");
	return (Node *) bgoto;
}

Node *do_blabel(label)
     char *label;
{
	Blabel *blabel = blabel_new(label);
    DBG0(">do_blabel\n");
    DBG0("<do_blabel\n");
	return (Node *) blabel;
}

Node *do_btype(name)
	char *name;
{
	Btype *btype = btype_new(name);
	DBG0(">do_btype\n");
	DBG0("<do_btype\n");
	return (Node *) btype;
}

Node *do_btype2(var, expr, datatype, typename)
	char *var;
	Node *expr;
	int datatype;
	char *typename;
{
  Bdim *bdim = bdim_new();
  Btype *btype;

  DBG0(">do_btype2\n");

  strcpy(bdim->name, var);
  bdim->datatype = datatype;
  bdim->dimension = 0;
  if (expr) bdim->addchild(bdim, expr);
  if (typename)
  {
	  bdim->btype = (Btype *)find_type_name(typename);
	  if (bdim->btype == NULL)
	  {
	      doerr2("%s(%d) ERROR - user defined type '%s' is unknown", g_infname, yylineno, typename );
	  }
  }

  btype = (Btype *)body_stack[body_stack_n];
  btype->addchild(btype, bdim);
//btype->dump(btype);  
  DBG0("<do_btype2\n");

  return (Node *)NULL;
}

Node *do_bsprite_get(Bexpr *n, Node *x, Node *y, Node *z, Node *mode, Node *w, Node *h)
{
	Bsprite_get *bsprite_get = bsprite_get_new();
	DBG0(">do_bsprite_get\n");
	bsprite_get->addchild(bsprite_get, n);
	bsprite_get->addchild(bsprite_get, x);
	bsprite_get->addchild(bsprite_get, y);
	bsprite_get->addchild(bsprite_get, z);
	bsprite_get->addchild(bsprite_get, mode);
	bsprite_get->addchild(bsprite_get, w);
	bsprite_get->addchild(bsprite_get, h);
	DBG0("<do_bsprite_get\n");
	return (Node *) bsprite_get;
}

Node *do_bredraw(Bexpr *exp)
{
    Bterm *bterm;
	Bredraw *bredraw = bredraw_new();
	DBG0(">do_bredraw\n");
	if (exp == (Bexpr *) -2)
	{
		bterm = (Bterm *)do_bterm("-2", DATATYPE_INT, 1, 0);
		bredraw->addchild(bredraw, bterm);
	}
	else if (exp == (Bexpr *)-1 || exp == NULL)
	{
		// null child //
	}
	else if (exp)
	{
		bredraw->addchild(bredraw, exp);
	}
	DBG0("<do_bredraw\n");
	return (Node *) bredraw;
}

Node *do_bcommand(char *command_name, ...)
{
    Bcommand *bcommand = bcommand_new(command_name);
	Node *node = NULL;
	va_list marker;

    DBG0(">do_bcommand(%s)\n", command_name);
	va_start( marker, command_name );     /* Initialize variable arguments. */
	node = va_arg( marker, Node *);
	while( node )
	{
		bcommand->addchild(bcommand, node);
		node = va_arg( marker, Node *);
	}
	va_end(marker);
	return (Node *)bcommand;
}

Node *do_bmusic(int opn, int channel, Bexpr *bexp)
{
	Bmusic *bmusic = bmusic_new();
	DBG0(">do_bmusic\n");
	bmusic->opn = opn;
	bmusic->channel = channel;
	if (bexp) bmusic->addchild(bmusic, bexp);
	DBG0("<do_bmusic\n");
	return (Node *) bmusic;
}

Node *do_bongosub(exp, list)
	Bexpr *exp;
     Node *list;
{
    Bongosub *bongosub = bongosub_new();
	DBG0(">do_bongosub\n");
	bongosub->addchild(bongosub, exp);
    bongosub->addchild(bongosub, list);
	DBG0("<do_bongosub\n");
    return (Node *) bongosub;
}


Node *do_bongoto(exp, list)
	Bexpr *exp;
     Node *list;
{
    Bongoto *bongoto = bongoto_new();
	DBG0(">do_bongoto\n");
	bongoto->addchild(bongoto, exp);
    bongoto->addchild(bongoto, list);
	DBG0("<do_bongoto\n");
    return (Node *) bongoto;
}


Node *do_varterm(char *name)
{
	Bterm *bterm = bterm_new(name);
	return (Node *)bterm;
}

Node *do_bmenu(varname, list)
     char *varname;
     Node *list;
{
    Bmenu *bmenu = bmenu_new(varname);
    DBG0(">do_bmenu\n");
    if (list) bmenu->addchild(bmenu, list);
    DBG0("<do_bmenu\n");
    return (Node *) bmenu;
}

Node *do_bmenuxy(x, y, varname, list)
	 Bexpr *x;
	 Bexpr *y;
     char *varname;
     Node *list;
{
    Bmenuxy *bmenuxy = bmenuxy_new(varname);
    DBG0(">do_bmenuxy\n");
	bmenuxy->addchild(bmenuxy, x);
	bmenuxy->addchild(bmenuxy, y);
    if (list) bmenuxy->addchild(bmenuxy, list);
    DBG0("<do_bmenuxy\n");
    return (Node *) bmenuxy;
}

Node *do_bexitprogram()
{
    Bexitprogram *bexitprogram = bexitprogram_new();
    DBG0(">do_bexitprogram\n");
    DBG0("<do_bexitprogram\n");
    return (Node *) bexitprogram;
}

char *uppercase(char *s)
{
	char *x = s;
	while(*s)
	{
		if (islower(*s)) *s=toupper(*s);
		s++;
	}
	return x;
}

char *lowercase(char *s)
{
	char *x = s;
	while(*s)
	{
		if (isupper(*s)) *s=tolower(*s);
		s++;
	}
	return x;
}

void update_lineno(char *filename, char *lineno)
{
	strcpy(g_infname, &filename[1]);
	yylineno = atoi(lineno);
}
