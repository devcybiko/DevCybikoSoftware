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
#include "bgoto.h"

extern void bgoto_debug();
extern void bgoto_b2c();

Bgoto *bgoto_new(name) 
     char *name;
{
  Bgoto *this = CALLOC(1, Bgoto);
  DBG0(">bgoto_new\n");

  bgoto_init(this, name);

  DBG0("<bgoto_new\n");
  return this;
}

void bgoto_init(this, name)
     Bgoto *this;
     char *name;
{
  DBG0(">bgoto_init\n");
  bexpr_init(this);

  this->type = TYPE_GOTO;
  this->b2c = bgoto_b2c;
  this->debug = bgoto_debug;

  this->name = strdup(name);

  DBG0("<bgoto_init\n");
}

void bgoto_b2c(this)
     Bgoto *this;
{
  DBG0(">bgoto_b2c\n");
  fprintf(outfile, "goto %s", this->name);
  DBG0("<bgoto_b2c\n");
}

void bgoto_debug(this)
     Bgoto *this;
{
  printf("%d: bgoto '%s' type=%s\n", this->type, this->name, data_type[this->datatype]);
}
