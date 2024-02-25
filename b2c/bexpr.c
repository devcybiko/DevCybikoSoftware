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
#include "node.h"
#include "bexpr.h"
#include "bop.h"

extern void bexpr_b2c();
extern void bexpr_debug();

Bexpr *bexpr_new() {
  Bexpr *this = CALLOC(1, Bexpr);
  DBG0(">bexpr_new\n");

  bexpr_init(this);

  DBG0("<bexpr_new\n");
  return this;
}

void bexpr_init(this)
     Bexpr *this;
{
  DBG0(">bexpr_init\n");
  node_init(this);

  this->type = TYPE_EXPR;
  this->b2c = bexpr_b2c;
  this->debug = bexpr_debug;
  DBG0("<bexpr_init\n");
}

void bexpr_b2c(this)
     Bexpr *this;
{
  Node *n;
  Bop *op=(Bop *)this->parent;
  DBG0(">bexpr_b2c\n");
  
  for(n=this->child; n; n=n->next)
  {
	  Bexpr *expr = (Bexpr *)n;
	  // TYPE_LIST is a total hack to prevent coercion in print & sprint
//	  if (op->type != TYPE_LIST && op->type != TYPE_PARAM && op->type != TYPE_FUNCCALL &&
	  if (op->type == TYPE_OP &&
		  op->datatype == DATATYPE_DOUBLE && expr->datatype != DATATYPE_DOUBLE)
	  {
		  fprintf(outfile, "fixed_from_int(");
		  expr->b2c(expr);
		  fprintf(outfile, ")");
	  }
	  // TYPE_LIST is a total hack to prevent coercion in print & sprint
//	  else if (op->type != TYPE_LIST && op->type != TYPE_PARAM && op->type != TYPE_FUNCCALL &&
	  else if (op->type == TYPE_OP &&
				expr->datatype == DATATYPE_DOUBLE && op->datatype != DATATYPE_DOUBLE)
	  {
		  fprintf(outfile, "fixed_to_int(");
		  expr->b2c(expr);
		  fprintf(outfile, ")");
	  }
	  else
	  {
		  expr->b2c(expr);
	  }
  }
  DBG0("<bexpr_b2c\n");
}

void bexpr_debug(this)
     Bexpr *this;
{
  printf("%d: bexpr type=%s dim=%d\n", 
	  this->type, 
	  data_type[this->datatype],
	  this->dimension);
}
