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
#include "bdim.h"
#include "bterm.h"

extern int bdim_parse();
extern void bdim_debug();
extern void bdim_b2c2();

Bdim *bdim_new() {
  Bdim *this = CALLOC(1, Bdim);
  DBG0(">bdim_new\n");

  bdim_init(this);

  DBG0("<bdim_new\n");
  return this;
}

void bdim_init(this)
     Bdim *this;
{
  DBG0(">bdim_init\n");

  node_init(this);

  this->type = TYPE_DIM;
  this->b2c = bdim_b2c;
  this->b2c2 = bdim_b2c2;
  this->debug = bdim_debug;

  DBG0("<bdim_init\n");
}

void bdim_b2c(this)
Bdim *this;
{
	DBG0(">bdim_b2c\n");
	fprintf(outfile, "%s ", data_type[this->datatype]);
	if (this->btype) fprintf(outfile, "%s ", this->btype->name);  //user type definition

	if (this->child)
    {
		/** literal defined array **/
		Bexpr *bexpr = (Bexpr *) this->child;
		if (bexpr->type == TYPE_EXPR)
		{
			if (bexpr->literal)
			{
				fprintf(outfile, "%s", this->name);
				fprintf(outfile, "[");
				bexpr->b2c(bexpr);
				fprintf(outfile, "]");
				//fprintf(outfile, ";\nshort __%s=", this->name);
				//this->child->b2c(this->child);
			}
			else
			{
				/** dynamically allocated array **/
				//fprintf(outfile, " *%s=0", this->name);
				fprintf(outfile, " *%s=0;\n", this->name);
				fprintf(outfile, "short __%s", this->name);
			}
		}
		/** doubly dimensioned array - literals only! **/
		else if (bexpr->type == TYPE_LIST)
		{
			bexpr = (Bexpr *)bexpr->child;
			fprintf(outfile, "%s", this->name);
			fprintf(outfile, "[");
			bexpr->b2c(bexpr);
			fprintf(outfile, "]");

			bexpr = (Bexpr *)bexpr->next;
			fprintf(outfile, "[");
			bexpr->b2c(bexpr);
			fprintf(outfile, "]");
		}
    }
	else
    {
		/** scalar **/
		fprintf(outfile, " %s", this->name);
    }
	
	fprintf(outfile, ";\n");
	DBG0("<bdim_b2c\n");
}

void bdim_b2c2(this)
Bdim *this;
{
	DBG0(">bdim_b2c2\n");
	
	if (this->child)
    {
		/** expression-defined array **/
		Bexpr *bexpr = (Bexpr *) this->child;
		
		if (bexpr->type == TYPE_EXPR && !bexpr->literal)
		{
			/** dynamically allocated array **/
			fprintf(outfile, " if (%s==0) {%s=(%s *)calloc(", 
				this->name, this->name, data_type[this->datatype]);
			bexpr->b2c(bexpr);
			fprintf(outfile, ", sizeof(%s))", data_type[this->datatype]);
//			fprintf(outfile, ", sizeof(%s)); __%s=", data_type[this->datatype], this->name);
//			bexpr->b2c(bexpr);
			fprintf(outfile, ";}\n");
		}
    }
	
	DBG0("<bdim_b2c2\n");
}

void bdim_debug(this)
     Bdim *this;
{
  printf("%d: bdim '%s' type=%s, dim=%d\n", 
	  this->type, 
	  this->name, 
	  data_type[this->datatype],
	  this->dimension);
}
