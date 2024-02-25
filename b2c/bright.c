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
#include "bright.h"

void bright_b2c();

Bright *bright_new() {
  Bright *this = CALLOC(1, Bright);
  DBG0(">bright_new\n");

  bright_init(this);

  DBG0("<bright_new\n");
  return this;
}

void bright_init(this)
     Bright *this;
{
  DBG0(">bright_init\n");
  bexpr_init(this);

  this->type = TYPE_RIGHT;
  this->b2c = bright_b2c;

  DBG0("<bright_init\n");
}

void bright_b2c(this)
     Bright *this;
{
  Node *dest;
  Node *src;
  Node *len;

  DBG0(">bright_b2c\n");
  fprintf(outfile, "_right(");
  dest = this->child;
  src = dest->next;
  len = src->next;

  dest->b2c(dest);
  fprintf(outfile, ",");
  src->b2c(src);
  fprintf(outfile, ",");
  len->b2c(len);
  fprintf(outfile, ")");
  DBG0("<bright_b2c\n");
}
