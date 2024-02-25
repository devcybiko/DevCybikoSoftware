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
#include "bpaper.h"

void bpaper_b2c();

Bpaper *bpaper_new() {
  Bpaper *this = CALLOC(1, Bpaper);
  DBG0(">bpaper_new\n");

  bpaper_init(this);

  DBG0("<bpaper_new\n");
  return this;
}

void bpaper_init(this)
     Bpaper *this;
{
  DBG0(">bpaper_init\n");
  node_init(this);

  this->type = TYPE_PAPER;
  this->b2c = bpaper_b2c;

  DBG0("<bpaper_init\n");
}

void bpaper_b2c(this)
     Bpaper *this;
{
  Node *n;

  DBG0(">bpaper_b2c\n");
  fprintf(outfile, "_paper(");
  for(n=this->child; n; n=n->next)
    {
      n->b2c(n);
      if (n->next) fprintf(outfile, ",");
    }
  fprintf(outfile, ")");
  DBG0("<bpaper_b2c\n");
}
