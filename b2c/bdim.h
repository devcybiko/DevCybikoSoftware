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
#ifndef _BDIM_H_
#define _BDIM_H_

#include "node.h"
#include "btype.h"

enum {
  BDIM_BY_VAL,
  BDIM_BY_REF};

#define class_bdim \
class_node \
void (*b2c2)(); \
char name[32]; \
int datatype; \
int dimension; \
int passed_by; \
Btype *btype; //if datatype = TYPE_TYPE

class {
  class_bdim
} Bdim;

extern Bdim *bdim_new();
extern void bdim_init(/*Node *this*/);
extern void bdim_b2c(/*Node *this*/);
#endif
