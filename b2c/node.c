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

int node_level = 0;

void node_remchild();
void node_dump();
void node_debug();
void node_addchild();
void node_b2c();

Node *node_new() {
  Node *this = CALLOC(1, Node);
  DBG0(">node_new\n");
  node_init(this);
  DBG0("<node_new\n");
  return this;
}

void node_init(this)
     Node *this;
{
  DBG0(">node_init\n");

  this->destroy = node_destroy;
  this->addchild = node_addchild;
  this->remchild = node_remchild;
  this->b2c = node_b2c;
  this->dump = node_dump;
  this->debug = node_debug;

  DBG0("<node_init\n");
}

void node_uninit(this)
     Node *this;
{
  DBG0(">node_uninit\n");
  DBG0("<node_uninit\n");
}

void node_destroy(this)
     Node *this;
{
  Node *n;
  DBG0(">node_destroy\n");
  for(n=this->child; n; n=n->next)
    n->destroy(n);
  node_uninit(this);
  free(this);
  DBG0("<node_destroy\n");
}

void node_remchild(this)
     Node *this;
{
  DBG0(">node_remchild this=%08x parent=%08x\n", this, this->parent);
  if (this->prev) this->prev->next = this->next;
  if (this->next) this->next->prev = this->prev;
  if (this->parent)
    {
      if (this->parent->last == this) this->parent->last = this->prev;
      if (this->parent->child== this) this->parent->child= this->next;
    }
  this->parent = NULL;
  this->next = NULL;
  this->prev = NULL;
  DBG0("<node_remchild\n");
}

void node_addchild(this, child)
     Node *this;
     Node *child;
{
  DBG0(">node_addchild\n");
  child->parent = this;
  child->prev = this->last;
  child->next = NULL;
  if (this->last) 
    {
      this->last->next = child;
    }
  else
    {
      this->child = child;
    }
  this->last = child;
  DBG0("<node_addchild\n");
}

void node_b2c(this)
     Node *this;
{
  DBG0(">node_b2c\n");
  DBG0("<node_b2c\n");
}

node_tab()
{
  int i;
  for(i=0; i<node_level; i++)
    printf(" | ");
}

void node_dump(this)
     Node *this;
{
  Node *n;

  node_tab();
  node_level++;
  this->debug(this);
  for(n=this->child; n; n=n->next)
    n->dump(n);
  node_level--;
}

void node_debug(this)
     Node *this;
{
  printf("%d: %s\n", this->type, node_types[this->type]);
}
