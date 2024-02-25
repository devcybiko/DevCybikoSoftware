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
#include "bprint.h"
#include "bexpr.h"
#include "bterm.h"

void bprint_b2c();

Bprint *bprint_new() {
  Bprint *this = CALLOC(1, Bprint);
  DBG0(">bprint_new\n");

  bprint_init(this);

  DBG0("<bprint_new\n");
  return this;
}

void bprint_init(this)
     Bprint *this;
{
  DBG0(">bprint_init\n");

  node_init(this);

  this->type = TYPE_PRINT;
  this->b2c = bprint_b2c;
  this->fileio = FALSE;

  DBG0("<bprint_init\n");
}

void bprint_b2c(this)
Bprint *this;
{
	Node *n;
	Bterm *bterm;
	Node *start;

	DBG0(">bprint_b2c\n");
	fprintf(outfile, "_print(\"");
	start = this->child;
	if (start && start->type == TYPE_LIST) start=start->child;
	for(n=start; n; n=n->next)
	{
      if (n->type != TYPE_EXPR && n->type != TYPE_TERM && n->type != TYPE_OP)
		doerr2("%s(%d) ERROR - Internal Error in Print - Expected expression got %s", g_infname, 0, node_types[n->type]);
      bterm = (Bterm *) n->child; /* could be term or op */
      if (bterm->datatype == DATATYPE_CHAR && bterm->dimension==1) 
	    fprintf(outfile, "%%s");
	  else if (bterm->datatype == DATATYPE_CHAR && bterm->dimension==0)
	    fprintf(outfile, "%%c");
      else if (bterm->datatype == DATATYPE_INT && bterm->dimension==0)
		fprintf(outfile, "%%d");
      else if (bterm->datatype == DATATYPE_LONG && bterm->dimension==0)
		fprintf(outfile, "%%ld");
      else if (bterm->datatype == DATATYPE_DOUBLE && bterm->dimension==0)
		fprintf(outfile, "%%s");
      else 
		doerr2("%s(%d) ERROR - Internal Error in Print - Illegal Datatype = %d[%d]\n", g_infname, 0, bterm->datatype, bterm->dimension);
    }
	fprintf(outfile, "\"");
	for(n=start; n; n=n->next)
	{
		Bterm *bterm = (Bterm *) n;
		fprintf(outfile, ",");	
		if (bterm->datatype == DATATYPE_DOUBLE)
			fprintf(outfile, "fixed_print(");
		n->b2c(n);
		if (bterm->datatype == DATATYPE_DOUBLE)
			fprintf(outfile, ",b2c_decimals)");
	}
	fprintf(outfile, ")");	
	DBG0("<bprint_b2c\n");
}

