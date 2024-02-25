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
#include "bwhile.h"
#include "bterm.h"
#include "bexpr.h"
#include "bbody.h"
#include "bop.h"

extern int _escape_;

void bwhile_b2c();

Bwhile *bwhile_new() {
  Bwhile *this = CALLOC(1, Bwhile);
  DBG0(">bwhile_new\n");

  bwhile_init(this);

  DBG0("<bwhile_new\n");
  return this;
}

void bwhile_init(this)
     Bwhile *this;
{
  DBG0(">bwhile_init\n");

  node_init(this);

  this->type = TYPE_WHILE;
  this->b2c = bwhile_b2c;

  DBG0("<bwhile_init\n");
}

void bwhile_b2c(this)
     Bwhile *this;
{
  Bexpr *bexpr;
  Bbody *body;

  DBG0(">bwhile_b2c\n");
  bexpr = (Bexpr *) this->child;
  body = (Bbody *) this->child->next;

  fprintf(outfile, "while(");
  bexpr->b2c(bexpr);
  fprintf(outfile, ") {\n");
  if (_escape_) fprintf(outfile, "_escape(0);\n");
  
  for(; body; body=(Bbody *)body->next)
    body->b2c(body);

  fprintf(outfile, "}\n");  

  DBG0("<bwhile_b2c\n");
}
