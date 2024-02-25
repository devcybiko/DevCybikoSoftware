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
#include "bparam.h"
#include "bterm.h"

extern void bparam_debug();
extern void bparam_b2c();
extern void bparam_proto();

Bparam *bparam_new() {
  Bparam *this = CALLOC(1, Bparam);
  DBG0(">bparam_new\n");

  bparam_init(this);

  DBG0("<bparam_new\n");
  return this;
}

void bparam_init(this)
     Bparam *this;
{
  DBG0(">bparam_init\n");

  node_init(this);

  this->type = TYPE_PARAM;
  this->b2c = bparam_b2c;
  this->debug = bparam_debug;
  this->proto = bparam_proto;
  DBG0("<bparam_init\n");
}

void bparam_b2c(this)
     Bparam *this;
{
  DBG0(">bparam_b2c\n");

  if (this->passed_by == BDIM_BY_VAL && this->dimension == 0)
    {
      fprintf(outfile, "%s %s;\n", data_type[this->datatype], this->name);
    }
  else 
    {
      fprintf(outfile, "%s *%s;\n", data_type[this->datatype], this->name);
    }
  DBG0("<bparam_b2c\n");
}

void bparam_proto(this)
     Bparam *this;
{
  DBG0(">bparam_b2c\n");

  if (this->passed_by == BDIM_BY_VAL && this->dimension == 0)
    {
      fprintf(outfile, "%s %s", data_type[this->datatype], this->name);
    }
  else 
    {
      fprintf(outfile, "%s *%s", data_type[this->datatype], this->name);
    }
  DBG0("<bparam_b2c\n");
}

void bparam_debug(this)
     Bparam *this;
{
  printf("%d: bparam '%s' type=%s", 
	 this->type, 
	 this->name, 
	 data_type[this->datatype]);
  if (this->passed_by == BDIM_BY_REF) printf(" ByRef\n");
  else printf(" ByValue\n");
}
