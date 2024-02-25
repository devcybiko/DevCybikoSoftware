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
#include "bmath.h"

extern void bmath_b2c();
extern void bmath_debug();

Bmath *bmath_new(name) 
     char *name;
{
  Bmath *this = CALLOC(1, Bmath);
  DBG0(">bmath_new\n");

  bmath_init(this, name);

  DBG0("<bmath_new\n");
  return this;
}

void bmath_init(this, name)
     Bmath *this;
     char *name;
{
  DBG0(">bmath_init\n");
  bexpr_init(this);

  strcpy(this->name, name);
  this->type = TYPE_MATH;
  this->b2c = bmath_b2c;
  this->debug = bmath_debug;
  DBG0("<bmath_init\n");
}

void bmath_debug(this)
     Bmath *this;
{
  printf("%d bmath: %s\n", this->type, this->name);
}

void bmath_b2c(this)
     Bmath *this;
{
  Node *n;
  DBG0(">bmath_b2c\n");
  
  if (SAME(this->name, "sqrt"))
	  fprintf(outfile, "fixed_sqrt(");
  else if (SAME(this->name, "sin"))
	  fprintf(outfile, "fixed_sin(");
  else if (SAME(this->name, "cos"))
	  fprintf(outfile, "fixed_cos(");
  else if (SAME(this->name, "tan"))
	  fprintf(outfile, "fixed_tan(");
  else if (SAME(this->name, "inv"))
	  fprintf(outfile, "fixed_reciprocal(");
  else
	  fprintf(outfile, "_%s(", this->name);

  for(n=this->child; n; n=n->next)
    {
      n->b2c(n);
      if (n->next) fprintf(outfile, ",");
    }
  fprintf(outfile, ")");
  DBG0("<bmath_b2c\n");
}

