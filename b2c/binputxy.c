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
#include "binputxy.h"
#include "bexpr.h"
#include "bterm.h"

void binputxy_b2c();

Binputxy *binputxy_new() {
  Binputxy *this = CALLOC(1, Binputxy);
  DBG0(">binputxy_new\n");

  binputxy_init(this);

  DBG0("<binputxy_new\n");
  return this;
}

void binputxy_init(this)
     Binputxy *this;
{
  DBG0(">binputxy_init\n");
  node_init(this);

  this->type = TYPE_INPUTXY;
  this->b2c = binputxy_b2c;

  DBG0("<binputxy_init\n");
}

void binputxy_b2c(this)
Binputxy *this;
{
	Bterm *x = (Bterm *) this->child;
	Bterm *y = (Bterm *) x->next;
	Bterm *var = (Bterm *) y->next;

	DBG0(">binputxy_b2c\n");
	
	switch(var->datatype) {
    case DATATYPE_CHAR: 
		if (var->dim->child) /* array of char */
		{
			if (var->child) /* subscripted string char */
			{
				fprintf(outfile, "_inputxy_char(");
				x->b2c(x);
				fprintf(outfile, ",");
				y->b2c(y);
				fprintf(outfile, ",&");
			}
			else
			{
				fprintf(outfile, "_inputxy_string(");
				x->b2c(x);
				fprintf(outfile, ",");
				y->b2c(y);
				fprintf(outfile, ",");
			}
		}
		else
		{
				fprintf(outfile, "_inputxy_char(");
				x->b2c(x);
				fprintf(outfile, ",");
				y->b2c(y);
				fprintf(outfile, ",&");
		}
		break;
    case DATATYPE_INT: 
		fprintf(outfile, "_inputxy_int("); 
		x->b2c(x);
		fprintf(outfile, ",");
		y->b2c(y);
		fprintf(outfile, ",&");
		break;
    case DATATYPE_LONG:
		fprintf(outfile, "_inputxy_long("); 
		x->b2c(x);
		fprintf(outfile, ",");
		y->b2c(y);
		fprintf(outfile, ",&");
		break;
    case DATATYPE_DOUBLE:
		fprintf(outfile, "_inputxy_fixed(");
		x->b2c(x);
		fprintf(outfile, ",");
		y->b2c(y);
		fprintf(outfile, ",&");
		break;
	}
	var->b2c(var);  /* var name */
	fprintf(outfile, ",");

	if (var->datatype == DATATYPE_CHAR)
	{
		if (var->dim->child) /* array of char */
		{
			if (var->child) /* subscripted string char */
				fprintf(outfile, "1,");
			else
			{
				var->dim->child->b2c(var->dim->child);
				fprintf(outfile, ",");
			}
		}
	}
	if (var->next) var->next->b2c(var->next);  /* prompt */
	else fprintf(outfile, "NULL");
	fprintf(outfile, ")");
	DBG0("<binputxy_b2c\n");
}
