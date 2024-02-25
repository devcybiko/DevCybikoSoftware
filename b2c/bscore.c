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
#include "bscore.h"

void bscore_b2c();

Bscore *bscore_new() {
  Bscore *this = CALLOC(1, Bscore);
  DBG0(">bscore_new\n");

  bscore_init(this);

  DBG0("<bscore_new\n");
  return this;
}

void bscore_init(this)
     Bscore *this;
{
  DBG0(">bscore_init\n");
  node_init(this);

  this->type = TYPE_SCORE;
  this->b2c = bscore_b2c;

  DBG0("<bscore_init\n");
}

void bscore_b2c(this)
     Bscore *this;
{
  DBG0(">bscore_b2c\n");
  if (this->child)
  {
	fprintf(outfile, "_update_high_scores(");
    this->child->b2c(this->child);
	fprintf(outfile, ")");
  }
  else
  {
    fprintf(outfile, "_show_high_scores()");
  }
  DBG0("<bscore_b2c\n");
}
