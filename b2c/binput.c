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
#include "binput.h"
#include "bexpr.h"
#include "bterm.h"

void binput_b2c();

Binput *binput_new() {
  Binput *this = CALLOC(1, Binput);
  DBG0(">binput_new\n");

  binput_init(this);

  DBG0("<binput_new\n");
  return this;
}

void binput_init(this)
     Binput *this;
{
  DBG0(">binput_init\n");
  node_init(this);

  this->type = TYPE_INPUT;
  this->b2c = binput_b2c;

  DBG0("<binput_init\n");
}

void binput_b2c(this)
Binput *this;
{
	Bterm *var = (Bterm *) this->child;
	
	DBG0(">binput_b2c\n");
	
	switch(var->datatype) {
    case DATATYPE_CHAR: 
		if (var->dim->child) /* array of char */
		{
			if (var->child) /* subscripted string char */
				fprintf(outfile, "_input_char(&");
			else
				fprintf(outfile, "_input_string(");
		}
		else
			fprintf(outfile, "_input_char(&");
		break;
    case DATATYPE_INT: fprintf(outfile, "_input_int(&"); break;
    case DATATYPE_LONG: fprintf(outfile, "_input_long(&"); break;
    case DATATYPE_DOUBLE: fprintf(outfile, "_input_fixed(&"); break;
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
	DBG0("<binput_b2c\n");
}
