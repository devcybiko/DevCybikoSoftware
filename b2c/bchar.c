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
#include "bchar.h"

void bchar_b2c();

Bchar *bchar_new() {
  Bchar *this = CALLOC(1, Bchar);
  DBG0(">bchar_new\n");

  bchar_init(this);

  DBG0("<bchar_new\n");
  return this;
}

void bchar_init(this)
     Bchar *this;
{
  DBG0(">bchar_init\n");
  node_init(this);

  this->type = TYPE_CHAR;
  this->b2c = bchar_b2c;

  DBG0("<bchar_init\n");
}

void bchar_b2c(this)
     Bchar *this;
{
  DBG0(">bchar_b2c\n");
  fprintf(outfile, "_char(");
  if (this->child)
	  this->child->b2c(this->child);
  else
	  fprintf(outfile, "0");
  fprintf(outfile, ")");
  DBG0("<bchar_b2c\n");
}
