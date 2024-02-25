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
#include "bfunction.h"
#include "bterm.h"
#include "bexpr.h"
#include "bbody.h"
#include "bop.h"
#include "blist.h"
#include "bparam.h"
#include "bdim.h"
#include "bexitfunction.h"

int bexitfunction_level = 0;

void bexitfunction_init();
void bexitfunction_b2c();

Bexitfunction *bexitfunction_new(name) 
     char *name;
{
  Bexitfunction *this = CALLOC(1, Bexitfunction);
  DBG0(">bexitfunction_new\n");
  bexitfunction_init(this, name);
  DBG0("<bexitfunction_new\n");
  return this;
}

void bexitfunction_init(this, name)
     Bexitfunction *this;
     char *name;
{
  DBG0(">bexitfunction_init\n");

  node_init(this);

  this->type = TYPE_EXIT;
  this->b2c = bexitfunction_b2c;

  DBG0("<bexitfunction_init\n");
}

void bexitfunction_uninit(this)
     Bexitfunction *this;
{
  DBG0(">bexitfunction_uninit\n");

  node_uninit(this);

  DBG0("<bexitfunction_uninit\n");
}

void bexitfunction_b2c(this)
     Bexitfunction *this;
{
	Bfunction *bfunction;
  DBG0(">bexitfunction_b2c\n");

  for(bfunction = (Bfunction *)this->parent;
	  bfunction;
	  bfunction = (Bfunction *)bfunction->parent)
	  {
		  if (bfunction->type == TYPE_FUNCTION) 
				break;
	  }
  if (bfunction == NULL) doerr2("%s(%d) ERROR - Exit Function outside a function", g_infname, 0);
  if (bfunction->datatype == DATATYPE_VOID) //subroutine
	  fprintf(outfile, "return;\n");
  else 
	  fprintf(outfile, "return _%s;\n", bfunction->name);

  DBG0("<bexitfunction_b2c\n");
}

