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
#include "bput.h"
#include "bterm.h"

void bput_b2c();

Bput *bput_new() {
  Bput *this = CALLOC(1, Bput);
  DBG0(">bput_new\n");

  bput_init(this);

  DBG0("<bput_new\n");
  return this;
}

void bput_init(this)
     Bput *this;
{
  DBG0(">bput_init\n");
  node_init(this);

  this->type = TYPE_PUT;
  this->b2c = bput_b2c;

  DBG0("<bput_init\n");
}

void bput_b2c(this)
     Bput *this;
{
  Node *n;
  Bterm *bterm;

  DBG0(">bput_b2c\n");
  fprintf(outfile, "_put(");
  n = this->child;
  n->b2c(this->child); /** filenumber **/

  fprintf(outfile, ",");

  n=n->next;
  if (n->type == TYPE_EXPR && n->child == NULL)
    fprintf(outfile, "-1");
  else
    n->b2c(n); /** file position */

  fprintf(outfile, ",");

  n=n->next;
  if (n->type == TYPE_EXPR && n->child == NULL)
    {
      fprintf(outfile, "-1,-1");
    }
  else
    {    
      fprintf(outfile, "&");
      n->b2c(n); /** variable to print **/

      fprintf(outfile, ",");
      
      bterm = (Bterm *) n;
      
      if (bterm->dim->child && bterm->child == NULL)
	  {
		bterm->dim->child->b2c(bterm->dim->child);
		fprintf(outfile, "*");
	  }
      
      
    switch(bterm->datatype) 
	{
	case DATATYPE_CHAR : fprintf(outfile, "sizeof(char)"); break;
	case DATATYPE_INT : fprintf(outfile, "sizeof(short)"); break;
	case DATATYPE_LONG : fprintf(outfile, "sizeof(long)"); break;
	case DATATYPE_DOUBLE : fprintf(outfile, "sizeof(fixed)"); break;
	default: doerr2("%s(%d) ERROR - Cannot put '%s' - invalid data type\n", g_infname, 0, bterm->name); break;
	}
    }

  fprintf(outfile, ")");
  DBG0("<bput_b2c\n");
}
