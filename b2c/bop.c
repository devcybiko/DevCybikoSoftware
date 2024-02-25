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
#include "bop.h"
#include "bterm.h"

//#define DBG0 printf

extern void bop_debug();

char *op_strings[] = {
  "and",
  "or",
  "<>",
  "<=",
  ">=",
  ">",
  "=",
  "<",
  "+",
  "-",
  "*",
  "/",
  "(",
  ")",
  "[",
  "]",
  ",",
  "#",
  "==",
  "-",
  "+",
  "!",
  "%",
  0};

Bop *bop_new(operation) 
     int operation;
{
  Bop *this = CALLOC(1, Bop);
  DBG0(">bop_new\n");

  bop_init(this, operation);

  DBG0("<bop_new\n");
  return this;
}

void bop_init(this, op)
     Bop *this;
     int op;
{
  DBG0(">bop_init\n");

  bexpr_init(this);

  this->type = TYPE_OP;
  this->op = op;

  this->b2c = bop_b2c;
  this->debug = bop_debug;

  DBG0("<bop_init\n");
}

static void string_op(Bop *this, Bterm *left, Bterm *right)
{
	DBG0(">string_op\n");
	DBG0("%08x %08x %08x\n", this, left, right);
  switch(this->op) {
  case OP_NEQ:
	  fprintf(outfile, "(0!=strcmp(");
	  left->b2c(left);
	  fprintf(outfile, ",");
	  right->b2c(right);
	  fprintf(outfile, "))");
	  break;
  case OP_LEQ:
	  fprintf(outfile, "(0<=strcmp(");
	  left->b2c(left);
	  fprintf(outfile, ",");
	  right->b2c(right);
	  fprintf(outfile, "))");
	  break;
  case OP_GEQ:
	  fprintf(outfile, "(0>=strcmp(");
	  left->b2c(left);
	  fprintf(outfile, ",");
	  right->b2c(right);
	  fprintf(outfile, "))");
	  break;
  case OP_GREATER:
	  fprintf(outfile, "(0>strcmp(");
	  left->b2c(left);
	  fprintf(outfile, ",");
	  right->b2c(right);
	  fprintf(outfile, "))");
	  break;
  case OP_EQEQ:
	  fprintf(outfile, "(0==strcmp(");
	  left->b2c(left);
	  fprintf(outfile, ",");
	  right->b2c(right);
	  fprintf(outfile, "))");
	  break;
  case OP_LESSER:
	  fprintf(outfile, "(0<strcmp(");
	  left->b2c(left);
	  fprintf(outfile, ",");
	  right->b2c(right);
	  fprintf(outfile, "))");
	  break;
  case OP_EQ: 
	  fprintf(outfile, "strcpy(");
	  left->b2c(left);
	  fprintf(outfile, ",");
	  right->b2c(right);
	  fprintf(outfile, ")");
	  break;
  default: doerr2("%s(%d) ERROR - Internal error - illegal string op %d", g_infname, 0, this->op); break;
  }
}

void bop_b2c(this)
     Bop *this;
{
  Bterm *left, *right;
  DBG0(">bop_b2c\n");

  left = (Bterm *) this->child;
  right = (Bterm *) this->last;

  DBG0("%08x %08x %08x\n", this, left, right);

  switch(this->op) {
  case OP_NOT: break;
  case OP_UNARY_MINUS: break;
  case OP_UNARY_PLUS: break;
  case OP_AND: break;
  case OP_OR:  break;
  case OP_NEQ: break;
  case OP_LEQ: break;
  case OP_GEQ: break;
  case OP_GREATER: break;
  case OP_EQEQ: break;
  case OP_LESSER: break;
  case OP_ADD: break;
  case OP_SUB: break;
  case OP_MUL:
	  if (this->datatype == DATATYPE_DOUBLE)
		fprintf(outfile, "fixed_multiply(");
	  break;
  case OP_DIV: 
	  if (this->datatype == DATATYPE_DOUBLE)
		  fprintf(outfile, "fixed_divide(");
	  break;
  case OP_MOD: break;
  case OP_EQ: break;
  case OP_LPAREN: break;
  case OP_LBRACKET: break;
  default: 
	  this->dump(this);
	  doerr2("%s(%d) ERROR - Internal error - illegal op1 %d", g_infname, 0, this->op);
	  break;
  }

  /* Print left child - but not for unary operators or strings*/
  if (left != right)
  {
	  if ((left->datatype == DATATYPE_CHAR) && (left->dimension==1))// string
	  {
		  /* string */
		  string_op(this, left, right);
		  goto EARLY_EXIT;
	  }
	  else
	  {
		  if (left->type == TYPE_EXPR)
		  {
			  left->b2c(left);
		  }
		  else if (left->datatype == DATATYPE_DOUBLE && this->datatype != DATATYPE_DOUBLE)
		  {
			  fprintf(outfile, "fixed_to_int(");
			  left->b2c(left);
			  fprintf(outfile, ")");
		  }
		  else if (left->datatype != DATATYPE_DOUBLE && this->datatype == DATATYPE_DOUBLE)
		  {
			  fprintf(outfile, "fixed_from_int(");
			  left->b2c(left);
			  fprintf(outfile, ")");
		  }
		  else
		  {
			  left->b2c(left);
		  }
	  }
  }

  switch(this->op) {
  case OP_NOT: fprintf(outfile, "!"); break;
  case OP_UNARY_MINUS: fprintf(outfile, "-"); break;
  case OP_UNARY_PLUS: fprintf(outfile, "+"); break;
  case OP_AND: fprintf(outfile, "&&"); break;
  case OP_OR:  fprintf(outfile, "||"); break;
  case OP_NEQ: fprintf(outfile, "!="); break;
  case OP_LEQ: fprintf(outfile, "<="); break;
  case OP_GEQ: fprintf(outfile, ">="); break;
  case OP_GREATER: fprintf(outfile, ">"); break;
  case OP_EQEQ: fprintf(outfile, "=="); break;
  case OP_LESSER: fprintf(outfile, "<"); break;
  case OP_ADD: fprintf(outfile, "+"); break;
  case OP_SUB: fprintf(outfile, "-"); break;
  case OP_MUL: 
	  if (this->datatype != DATATYPE_DOUBLE)
		  fprintf(outfile, "*");
	  else
		  fprintf(outfile, ",");
	  break;
  case OP_DIV: 
	  if (this->datatype != DATATYPE_DOUBLE)
		  fprintf(outfile, "/");
	  else
		  fprintf(outfile, ",");
	  break;
  case OP_MOD: fprintf(outfile, "%%"); break;
  case OP_EQ: fprintf(outfile, "="); break;
  case OP_LPAREN: fprintf(outfile, "("); break;
  case OP_LBRACKET: fprintf(outfile, "["); break;
  default: doerr2("%s(%d) ERROR - Internal error - illegal op2 %d", g_infname, 0, this->op); break;
  }

  if (right->type == TYPE_EXPR)
  {
	  right->b2c(right);
  }
  else if (right->datatype == DATATYPE_DOUBLE && this->datatype != DATATYPE_DOUBLE)
  {
	  fprintf(outfile, "fixed_to_int(");
	  right->b2c(right);
	  fprintf(outfile, ")");
  }
  else if (right->datatype != DATATYPE_DOUBLE && this->datatype == DATATYPE_DOUBLE)
  {
	  fprintf(outfile, "fixed_from_int(");
	  right->b2c(left);
	  fprintf(outfile, ")");
  }
  else
  {
	  right->b2c(right);
  }

  switch(this->op) {
  case OP_NOT: break;
  case OP_UNARY_MINUS: break;
  case OP_UNARY_PLUS: break;
  case OP_AND: break;
  case OP_OR:  break;
  case OP_NEQ: break;
  case OP_LEQ: break;
  case OP_GEQ: break;
  case OP_GREATER: break;
  case OP_EQEQ: break;
  case OP_LESSER: break;
  case OP_ADD: break;
  case OP_SUB: break;
  case OP_MUL:
	  if (this->datatype == DATATYPE_DOUBLE)
		fprintf(outfile, ")");
	  break;
  case OP_DIV: 
	  if (this->datatype == DATATYPE_DOUBLE)
		  fprintf(outfile, ")");
	  break;
  case OP_MOD: break;
  case OP_EQ: break;
  case OP_LPAREN: 
    fprintf(outfile, ")");
	break;
  case OP_LBRACKET:
    fprintf(outfile, "]");
	break;
  default: doerr2("%s(%d) ERROR - Internal error - illegal op3 %d", g_infname, 0, this->op); break;
  }

EARLY_EXIT:
  DBG0("<bop_b2c\n");
}

void bop_debug(this)
     Bop *this;
{
  printf("%d: bop '%s' this->datatype=%s\n", this->type, op_strings[this->op], data_type[this->datatype]);
}
