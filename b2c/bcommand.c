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
#include "bcommand.h"

void bcommand_b2c();

Bcommand *bcommand_new(char *command_name) {
  Bcommand *this = CALLOC(1, Bcommand);
  DBG0(">bcommand_new\n");

  bcommand_init(this, command_name);

  DBG0("<bcommand_new\n");
  return this;
}

void bcommand_init(Bcommand *this, char *command_name)
{
  DBG0(">bcommand_init\n");
  node_init(this);

  this->type = TYPE_COMMAND;
  this->b2c = bcommand_b2c;
  strcpy(this->command_name, command_name);

  DBG0("<bcommand_init\n");
}

void bcommand_b2c(Bcommand *this)
{
  Node *n;

  DBG0(">bcommand_b2c(%s)\n", this->command_name);
  fprintf(outfile, "%s(", this->command_name);
  for(n=this->child; n; n=n->next)
    {
      n->b2c(n);
      if (n->next) fprintf(outfile, ",");
    }
  fprintf(outfile, ")");
  DBG0("<bwrap_b2c\n");
}

#ifdef COMMENT
void bcommand_b2c(this)
     Bcommand *this;
{
  Node *n;

  DBG0(">bcommand_b2c\n");
  fprintf(outfile, "%s(", this->command_name);
  n = this->child;
  n->b2c(n);
  n=n->next;
  fprintf(outfile, ",");
  n->b2c(n);
  n=n->next;
  fprintf(outfile, ",");
  if (n) 
  {
	  n->b2c(n);
	  fprintf(outfile, ",");
	  n->next->b2c(n->next);
  }
  else 
  {
	  fprintf(outfile, "NULL");
	  fprintf(outfile, ",0");
  }
  fprintf(outfile, ")");
  DBG0("<bcommand_b2c\n");
}
#endif