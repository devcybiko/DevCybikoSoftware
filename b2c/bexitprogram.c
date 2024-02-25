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
#include "bexitprogram.h"

extern void bexitprogram_debug();
extern void bexitprogram_b2c();

Bexitprogram *bexitprogram_new() 
{
  Bexitprogram *this = CALLOC(1, Bexitprogram);
  DBG0(">bexitprogram_new\n");

  bexitprogram_init(this);

  DBG0("<bexitprogram_new\n");
  return this;
}

void bexitprogram_init(this)
     Bexitprogram *this;
{
  DBG0(">bexitprogram_init\n");
  node_init(this);

  this->type = TYPE_EXITPROGRAM;
  this->b2c = bexitprogram_b2c;

  DBG0("<bexitprogram_init\n");
}

void bexitprogram_b2c(this)
Bexitprogram *this;
{
	DBG0(">EXITPROGRAM_b2c\n");
	fprintf(outfile, "_exit_basic(0)");
	DBG0("<EXITPROGRAM_b2c\n");
}

