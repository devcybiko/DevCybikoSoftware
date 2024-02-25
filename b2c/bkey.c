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
#include "bkey.h"

void bkey_b2c();

Bkey *bkey_new() {
  Bkey *this = CALLOC(1, Bkey);
  DBG0(">bkey_new\n");

  bkey_init(this);

  DBG0("<bkey_new\n");
  return this;
}

void bkey_init(this)
     Bkey *this;
{
  DBG0(">bkey_init\n");
  node_init(this);

  this->type = TYPE_KEY;
  this->b2c = bkey_b2c;

  DBG0("<bkey_init\n");
}

void bkey_b2c(this)
     Bkey *this;
{
  DBG0(">bkey_b2c\n");
  fprintf(outfile, "_key(");
  if (this->child)
	  this->child->b2c(this->child);
  else
	  fprintf(outfile, "0");
  fprintf(outfile, ")");
  DBG0("<bkey_b2c\n");
}
