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
#include "binline.h"

void binline_b2c();

Binline *binline_new() {
  Binline *this = CALLOC(1, Binline);
  DBG0(">binline_new\n");

  binline_init(this);

  DBG0("<binline_new\n");
  return this;
}

void binline_init(this)
     Binline *this;
{
  DBG0(">binline_init\n");
  node_init(this);

  this->type = TYPE_INLINE;
  this->b2c = binline_b2c;

  DBG0("<binline_init\n");
}

void binline_b2c(this)
     Binline *this;
{
  DBG0(">binline_b2c\n");

  fprintf(outfile, "/**/%s", this->line);

  DBG0("<binline_b2c\n");
}
