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
#include "bterm.h"
#include "bop.h"

extern void bterm_debug();
extern void bterm_b2c();

Bterm *bterm_new(name) 
     char *name;
{
  Bterm *this = CALLOC(1, Bterm);
  DBG0(">bterm_new\n");

  bterm_init(this, name);

  DBG0("<bterm_new\n");
  return this;
}

void bterm_init(this, name)
     Bterm *this;
     char *name;
{
  DBG0(">bterm_init\n");
  bexpr_init(this);

  this->type = TYPE_TERM;
  this->b2c = bterm_b2c;
  this->debug = bterm_debug;

  this->name = strdup(name);

  DBG0("<bterm_init\n");
}

void bterm_b2c(this)
     Bterm *this;
{
  Node *n;

  DBG0(">bterm_b2c\n");
  if (this->dim)
  {
	if (this->dim->type == TYPE_PARAM)
	{
		if (this->dim->passed_by == BDIM_BY_REF)
			fprintf(outfile, "(*%s)", this->name);
		else
			fprintf(outfile, "%s", this->name);
	}
	else
		fprintf(outfile, "%s", this->name);
  }
  else
  {
	  if (this->datatype == DATATYPE_CHAR && this->literal && this->dimension==0)
	  {
		  fprintf(outfile, "'%c'", this->name[0]);
	  }
	  else if (this->datatype == DATATYPE_DOUBLE && this->literal && this->dimension==0)
	  {
			fprintf(outfile, "fixed_from_string(\"%s\")", this->name);
	  }
	  else
	  {
		  fprintf(outfile, "%s", this->name);
	  }
/*	  else
	  {
		  Bop *op = (Bop *) this->parent;
		  printf("op->datatype=%s(%d)\n", data_type[op->datatype], op->datatype);
		  printf("this->datatype=%s(%d)\n", data_type[this->datatype], this->datatype);
		  if (this->datatype == DATATYPE_DOUBLE && op->datatype != DATATYPE_DOUBLE)
		  {
			  fprintf(outfile, "fixed_to_int(%s)", this->name);
		  }
		  else if (this->datatype != DATATYPE_DOUBLE && op->datatype == DATATYPE_DOUBLE)
		  {
			  switch(this->datatype) {
			  case DATATYPE_INT:
				  fprintf(outfile, "fixed_from_int(%s)", this->name);
				  break;
			  case DATATYPE_CHAR:
				  fprintf(outfile, "fixed_from_char(%s)", this->name);
				  break;
			  default:
				  doerr2("Unexpected Datatype Conversion type=%d\n", this->datatype);
				  break;
			  }
		  }
		  else
		  {
			fprintf(outfile, "%s", this->name);
		  }
	  }
*/
  }
  for(n=this->child; n; n=n->next)
    {
	  if (n->type == TYPE_EXPR || n->type == TYPE_OP)
	  {
		fprintf(outfile, "[");
		n->b2c(n);
		fprintf(outfile, "]");
	  }
	  else if (n->type == TYPE_LIST)
	  {
		fprintf(outfile, "[");
		n->child->b2c(n->child);
		fprintf(outfile, "]");
		fprintf(outfile, "[");
		n->last->b2c(n->last);
		fprintf(outfile, "]");
	  }
	  else if (n->type == TYPE_TERM)
	  {
		  fprintf(outfile, ".");
		  n->b2c(n);
	  }
    }
  DBG0("<bterm_b2c\n");
}

void bterm_debug(this)
     Bterm *this;
{
  printf("%d: bterm '%s' type=%s dim=%d\n", 
	  this->type, 
	  this->name, 
	  data_type[this->datatype],
	  this->dimension);
}

