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
#include "bongosub.h"
#include "bexpr.h"
#include "bterm.h"

void bongosub_b2c();

Bongosub *bongosub_new() {
  Bongosub *this = CALLOC(1, Bongosub);
  DBG0(">bongosub_new\n");

  bongosub_init(this);

  DBG0("<bongosub_new\n");
  return this;
}

void bongosub_init(this)
     Bongosub *this;
{
  DBG0(">bongosub_init\n");

  node_init(this);

  this->type = TYPE_ONGOSUB;
  this->b2c = bongosub_b2c;
  this->fileio = FALSE;

  DBG0("<bongosub_init\n");
}

void bongosub_b2c(this)
Bongosub *this;
{
	Node *n;
	Node *start;
	Bexpr *exp;
	int i;

	DBG0(">bongosub_b2c\n");
	fprintf(outfile, "switch(");

	exp = (Bexpr *) this->child;
	exp->b2c(exp);
	fprintf(outfile, ") {\n");
	start = exp->next;
	if (start && start->type == TYPE_LIST) start=start->child;
	for(i=1, n=start; n; n=n->next)
	{
		fprintf(outfile, "case %d: ", i++);
		n->b2c(n);
		fprintf(outfile, "; break;\n");
	}
	fprintf(outfile, "}\n");
	DBG0("<bongosub_b2c\n");
}

