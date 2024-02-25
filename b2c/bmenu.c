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
#include "bmenu.h"

extern void bmenu_debug();
extern void bmenu_b2c();

Bmenu *bmenu_new(name) 
     char *name;
{
  Bmenu *this = CALLOC(1, Bmenu);
  DBG0(">bmenu_new\n");

  bmenu_init(this, name);

  DBG0("<bmenu_new\n");
  return this;
}

void bmenu_init(this, name)
     Bmenu *this;
     char *name;
{
  DBG0(">bmenu_init\n");
  node_init(this);

  this->type = TYPE_MENU;
  this->b2c = bmenu_b2c;

  this->name = strdup(name);

  DBG0("<bmenu_init\n");
}

void bmenu_b2c(this)
Bmenu *this;
{
	Node *n;
	Node *start;

	DBG0(">menu_b2c\n");
	fprintf(outfile, "_menu(1000, 1000, &%s", this->name);
	start = this->child;
	if (start && start->type == TYPE_LIST) start=start->child;
	for(n=start; n; n=n->next)
	{
		fprintf(outfile, ",");	
		n->b2c(n);	
	}	
	fprintf(outfile, ",NULL)");	
	DBG0("<menu_b2c\n");
}

