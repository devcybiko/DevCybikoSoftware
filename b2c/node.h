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
#ifndef _NODE_H_
#define _NODE_H_

#define class typedef struct
#define class_node \
  struct node *parent; \
  struct node *child; \
  struct node *last; \
  struct node *next; \
  struct node *prev; \
  int type; \
\
  void (*destroy)(); \
  void (*addchild)(); \
  void (*remchild)(); \
  int (*parse)(); \
  void (*b2c)(); \
  void (*dump)(); \
  void (*debug)();

class node {
    class_node
} Node;

extern Node *node_new();
extern void node_init(/*Node *this */);
extern void node_uninit(/*Node *this */);
extern void node_destroy(/*Node *this */);
#endif
