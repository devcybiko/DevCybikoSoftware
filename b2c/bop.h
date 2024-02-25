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
#ifndef _BOP_H_
#define _BOP_H_

#include "bexpr.h"

#define class_bop \
    class_bexpr \
    int op; 

class bop {
  class_bop
} Bop;

extern Bop *bop_new(/* int operation */);
extern void bop_init(/*Node *this*/);
extern void bop_b2c();

enum {
  OP_AND,
  OP_OR,
  OP_NEQ,
  OP_LEQ,
  OP_GEQ,
  OP_GREATER,
  OP_EQ,
  OP_LESSER,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_LPAREN,
  OP_RPAREN,
  OP_LBRACKET,
  OP_RBRACKET,
  OP_COMMA,
  OP_POUNDSIGN,

  OP_EQEQ,
  OP_UNARY_MINUS,
  OP_UNARY_PLUS,
  OP_NOT,
  OP_MOD,
  MAX_OP};

#endif
