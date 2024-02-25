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
#include "bprogram.h"
#include "bfunction.h"
#include "bdim.h"
#include "time.h"

int bprogram_level = 0;
extern int c_coords;
extern int n_sprites;
extern int n_3dsprites;
extern int n_rooms;
extern int _show_;
extern int _onmessage_defined_;
extern int _show_main_;
extern int _escape_;
extern int _help_;
extern int _multitask_;

void bprogram_init();
void bprogram_b2c();

Bprogram *bprogram_new(name) 
     char *name;
{
  Bprogram *this = CALLOC(1, Bprogram);
  DBG0(">bprogram_new\n");
  bprogram_init(this, name);
  DBG0("<bprogram_new\n");
  return this;
}

void bprogram_init(this, name)
     Bprogram *this;
     char *name;
{
  DBG0(">bprogram_init\n");

  node_init(this);

  this->type = TYPE_PROGRAM;
  this->b2c = bprogram_b2c;

  strcpy(this->name, name);

  DBG0("<bprogram_init\n");
}

void bprogram_uninit(this)
     Bprogram *this;
{
  DBG0(">bprogram_uninit\n");

  node_uninit(this);

  DBG0("<bprogram_uninit\n");
}

void bprogram_b2c(this)
     Bprogram *this;
{
  Node *n;
  time_t now;

  DBG0(">bprogram_b2c\n");

  now = time(0);
  fprintf(outfile, "/***************************************************\n");
  fprintf(outfile, "/* Program translated by b2c Version %s\n", VERSION);
  fprintf(outfile, "/* b2c (C) Copyright 2001 The Alcor Group, Inc\n");
  fprintf(outfile, "/* Written by Greg Smith\n");
  fprintf(outfile, "/*\n");
  fprintf(outfile, "/* Program %s converted %s", this->name, ctime(&now));
  fprintf(outfile, "/****************************************************/\n");
  fprintf(outfile, "#include \"b2cuser.h\"\n");

  if (_show_main_)
  {
	fprintf(outfile, "int _true=1;\n");
	fprintf(outfile, "int _true_=1;\n");
	fprintf(outfile, "int _false_=0;\n");
	fprintf(outfile, "int _c_coords=%d;\n", c_coords);
	fprintf(outfile, "int _n_sprites=%d;\n", n_sprites);
	fprintf(outfile, "int _n_3dsprites=%d;\n", n_3dsprites);
	fprintf(outfile, "int _n_rooms=%d;\n", n_rooms);
	fprintf(outfile, "int error=0;\n");
	fprintf(outfile, "int _show_=%d;\n", _show_);
	fprintf(outfile, "int b2c_decimals=2;\n");
	fprintf(outfile, "int _escape_=1;\n");
	fprintf(outfile, "int _help_=1;\n");
	fprintf(outfile, "int _multitask_=%d;\n", _multitask_);
  }
  else
  {
	fprintf(outfile, "extern int _true;\n");
	fprintf(outfile, "extern int _true_;\n");
	fprintf(outfile, "extern int _false_;\n");
	fprintf(outfile, "extern int _c_coords;\n");
	fprintf(outfile, "extern int _n_sprites;\n");
	fprintf(outfile, "extern int _n_3dsprites;\n");
	fprintf(outfile, "extern int _n_rooms;\n");
	fprintf(outfile, "extern int error;\n");
	fprintf(outfile, "extern int _show_;\n");
	fprintf(outfile, "extern int b2c_decimals;\n");
	fprintf(outfile, "extern int _escape_;\n");
	fprintf(outfile, "extern int _help_;\n");
	fprintf(outfile, "extern int _multitask_;\n");
  }

  if (_show_main_ && (_onmessage_defined_ == 0)) 
  {
	  fprintf(outfile, "void onmessage(long cyid, int msgno, char *buffer)\n");
	  fprintf(outfile, "{}\n");
  }

  for(n=this->child; n; n=n->next)
    {
      if (n->type == TYPE_DIM || 
		  n->type == TYPE_TYPE || 
		  n->type == TYPE_OUTLINE)
	  {
		n->b2c(n);
	  }
    }

  for(n=this->child; n; n=n->next)
    {
      if (n->type == TYPE_FUNCTION)
		((Bfunction *)n)->proto(n);
    }

  for(n=this->child; n; n=n->next)
    {
      if (n->type == TYPE_FUNCTION)
		n->b2c(n);
    }

  if (_show_main_)
  {
	  fprintf(outfile, "main() {\n");
	  fprintf(outfile, "TRACE(\"Created by B2C Version %s\");\n", VERSION);
	  fprintf(outfile, "_init_b2c();\n");
	  fprintf(outfile, "_escape_=%d;\n", _escape_);
	  fprintf(outfile, "_help_=%d;\n", _help_);
	  fprintf(outfile, "_multitask_=%d;\n", _multitask_);

	  for(n=this->child; n; n=n->next)
		{
		  if (n->type == TYPE_DIM)
			{
			  Bdim *bdim = (Bdim *) n;
			  bdim->b2c2(n);
			}
			  else if (n->type == TYPE_FUNCTION ||
				  n->type == TYPE_TYPE ||
				  n->type == TYPE_OUTLINE)
			{
			  /** do nothing **/
			}
			else
			{
			  n->b2c(n);
			}
		}
	  fprintf(outfile, "_destroy_b2c();\n");
	  fprintf(outfile, "return 0;\n");
	  fprintf(outfile, "}\n");
  }
  DBG0("<bprogram_b2c\n");
}

