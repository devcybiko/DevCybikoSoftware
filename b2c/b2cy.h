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
typedef union {
  char *string;
  int num;
  int mode;
  Bexpr *expr;
  Node *node;
  Bterm *term;
} YYSTYPE;
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


extern YYSTYPE yylval;
