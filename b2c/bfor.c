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
#include "bfor.h"
#include "bterm.h"
#include "bexpr.h"
#include "bbody.h"
#include "bop.h"

extern int _escape_;

//#define DBG0 printf

void bfor_b2c();

Bfor *bfor_new() {
  Bfor *this = CALLOC(1, Bfor);
  DBG0(">bfor_new\n");

  bfor_init(this);

  DBG0("<bfor_new\n");
  return this;
}

void bfor_init(this)
     Bfor *this;
{
  DBG0(">bfor_init\n");

  node_init(this);

  this->type = TYPE_FOR;
  this->b2c = bfor_b2c;

  DBG0("<bfor_init\n");
}

static int loop_counter=0;
void bfor_b2c(this)
Bfor *this;
{
	Bterm *counter;
	Bexpr *from;
	Bexpr *to;
	Bexpr *step;
	Bbody *body;
	
	//this->dump(this);

	loop_counter++;
	DBG0(">bfor_b2c\n");
	counter = (Bterm *)this->child;
	DBG0("...1\n");
	from = (Bexpr *) counter->next;
	DBG0("...2\n");
	to = (Bexpr *) from->next;
	DBG0("...3\n");
	step = (Bexpr *) to->next;
	DBG0("...4 step=%08x\n", step);
	if (step && (step->type == TYPE_EXPR || step->type == TYPE_OP))
    {
		DBG0("...5\n");
		body = (Bbody *) step->next;
    }
	else
    {
		DBG0("...6\n");
		body = (Bbody *) step;
		step = NULL;
    }
	
	DBG0("...7\n");
	
	counter->b2c(counter);
	fprintf(outfile, "=");
	from->b2c(from);
	fprintf(outfile, ";\n");
	
	fprintf(outfile, "while(_true) {\n");
	fprintf(outfile, "int _incr%02d = ", loop_counter);
	if (step) step->b2c(step);
	else fprintf(outfile, "1");
	
	DBG0("...8\n");
	fprintf(outfile, ";\n");
	if (_escape_) fprintf(outfile, "_escape(0);\n");
	fprintf(outfile, "if (_incr%02d<0 && ", loop_counter);
	counter->b2c(counter);
	
	DBG0("...9\n");
	fprintf(outfile, "<");
	to->b2c(to);
	
	DBG0("...10\n");
	fprintf(outfile, ") break;\n");
	fprintf(outfile, "if (_incr%02d>0 && ", loop_counter);
	counter->b2c(counter);
	
	DBG0("...11\n");
	fprintf(outfile, ">");
	to->b2c(to);
	
	DBG0("...12\n");
	fprintf(outfile, ") break;\n");
	
	for(; body; body = (Bbody *) body->next)
	{
		DBG0("...13\n");
		body->b2c(body);
	}
	DBG0("...14\n");
	fprintf(outfile, "_incr%02d=", loop_counter);
	
	if (step) step->b2c(step);
	else fprintf(outfile, "1");
	DBG0("...15\n");
	
	fprintf(outfile, ";\n");
	counter->b2c(counter);
	
	DBG0("...16\n");
	fprintf(outfile, "+=_incr%02d;\n", loop_counter);
	fprintf(outfile, "}\n");  

	loop_counter--;
	DBG0("<bfor_b2c\n");
}
