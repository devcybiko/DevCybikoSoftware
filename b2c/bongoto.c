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
#include "bongoto.h"
#include "bexpr.h"
#include "bterm.h"

void bongoto_b2c();

Bongoto *bongoto_new() {
  Bongoto *this = CALLOC(1, Bongoto);
  DBG0(">bongoto_new\n");

  bongoto_init(this);

  DBG0("<bongoto_new\n");
  return this;
}

void bongoto_init(this)
     Bongoto *this;
{
  DBG0(">bongoto_init\n");

  node_init(this);

  this->type = TYPE_ONGOTO;
  this->b2c = bongoto_b2c;
  this->fileio = FALSE;

  DBG0("<bongoto_init\n");
}

void bongoto_b2c(this)
Bongoto *this;
{
	Node *n;
	Node *start;
	Bexpr *exp;
	Bterm *term;
	int i;

	DBG0(">bongoto_b2c\n");
	fprintf(outfile, "switch(");

	exp = (Bexpr *) this->child;
	exp->b2c(exp);
	fprintf(outfile, ") {\n");
	start = exp->next;
	if (start && start->type == TYPE_LIST) start=start->child;
	for(i=1, n=start; n; n=n->next)
	{
		fprintf(outfile, "case %d: ", i++);
		term = (Bterm *) n;
		if (term->name[0] != 0)
		{
			fprintf(outfile, "goto ");
			n->b2c(n);
			fprintf(outfile, ";\n");
		}
		else 
		{
			fprintf(outfile, "break;\n");
		}
	}
	fprintf(outfile, "}\n");
	DBG0("<bongoto_b2c\n");
}

