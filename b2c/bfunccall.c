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
#include "bfunccall.h"

void bfunccall_b2c();
void bfunccall_debug();

Bfunccall *bfunccall_new() {
  Bfunccall *this = CALLOC(1, Bfunccall);
  DBG0(">bfunccall_new\n");

  bfunccall_init(this);

  DBG0("<bfunccall_new\n");
  return this;
}

void bfunccall_init(this)
     Bfunccall *this;
{
  DBG0(">bfunccall_init\n");
  node_init(this);

  this->type = TYPE_FUNCCALL;
  this->b2c = bfunccall_b2c;
  this->debug=bfunccall_debug;
  DBG0("<bfunccall_init\n");
}

void bfunccall_b2c(this)
     Bfunccall *this;
{
  Node *n;

  DBG0(">bfunccall_b2c\n");
  fprintf(outfile, "%s(", this->bfunction->name);
  if (this->child && this->child->type == TYPE_LIST) n = this->child;
  else n = (Node *) this;
					
  for(n=n->child; n; n=n->next)
    {
      n->b2c(n);
      if (n->next) fprintf(outfile, ",");
    }
  fprintf(outfile, ")");
  DBG0("<bfunccall_b2c\n");
}

void bfunccall_debug(Bfunccall *this)
{
  printf("%d: bfunccall datatype=%s\n", this->type, data_type[this->bfunction->datatype]);
}
