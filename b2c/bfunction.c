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

void bfunction_b2c();
void bfunction_debug();
void bfunction_proto();

Bfunction *bfunction_new() 
{
	Bfunction *this = CALLOC(1, Bfunction);
	DBG0(">bfunction_new\n");
	
	bfunction_init(this);
	
	DBG0("<bfunction_new\n");
	return this;
}

void bfunction_init(this)
Bfunction *this;
{
	DBG0(">bfunction_init\n");
	
	node_init(this);
	
	this->type = TYPE_FUNCTION;
	this->b2c = bfunction_b2c;
	this->debug = bfunction_debug;
	this->proto = bfunction_proto;
	
	DBG0("<bfunction_init\n");
}

void bfunction_b2c(this)
Bfunction *this;
{
    Blist *params;
    Bbody *body;
    Bparam *n;
    
    DBG0(">bfunction_b2c\n");
    params = (Blist *) this->child;
	if (params == NULL)
	{
		doerr2("ERROR - function %s was called but never defined\n",
			this->name);
	}
    body = (Bbody *) this->child->next;
	if (body == NULL)
	{
		doerr2("ERROR - function %s has no body\n",
			this->name);
	}

	//printf("function->name=%s\n", this->name);

    fprintf(outfile, "%s %s(", data_type[this->datatype], this->name);
    if (params->type == TYPE_LIST)
	{
        for(n = (Bparam *) params->child; n; n= (Bparam *) n->next)
		{
			n->proto(n);
            if (n->next) fprintf(outfile, ", ");
		}
	}
    else
	{
        n = (Bparam *) params;
        n->proto(n);
	}
    fprintf(outfile, ")\n");
    
    fprintf(outfile, "{\n");
	if (this->datatype != DATATYPE_VOID)  /** Subroutine **/
		fprintf(outfile, "%s _%s=0;\n", data_type[this->datatype], this->name);

    for(n=(Bparam *) body; n; n=(Bparam *)n->next)
    {
      if (n->type == TYPE_DIM)
		n->b2c(n);
    }
    for(; body; body=(Bbody *)body->next)
	{
        if (body->type != TYPE_DIM)
			body->b2c(body);
	}
    
	if (this->datatype == DATATYPE_VOID) /** Subroutine **/
		fprintf(outfile,"return;\n");
	else
		fprintf(outfile, "return _%s;\n", this->name);

    fprintf(outfile, "}\n");  
    
    DBG0("<bfunction_b2c\n");
}

void bfunction_proto(this)
Bfunction *this;
{
    Blist *params;
    Bparam *n;
    
    DBG0(">bfunction_proto\n");
    params = (Blist *) this->child;

	//printf("function->name=%s\n", this->name);

    fprintf(outfile, "extern %s %s(", data_type[this->datatype], this->name);

	if (params == NULL)
	{
		fprintf(outfile, "void");
	}
	else if (params->type == TYPE_LIST)
	{
        for(n = (Bparam *) params->child; n; n=(Bparam *)n->next)
		{
            n->proto(n);
			if (n->next)
				fprintf(outfile, ", ");
		}
	}
    else
	{
        n = (Bparam *) params;
        n->proto(n);
	}
    
    fprintf(outfile, ");\n");
    DBG0("<bfunction_proto\n");
}

void bfunction_debug(this)
Bfunction *this;
{
	printf("%d: bfunction %s as %s\n", this->type, this->name, data_type[this->datatype]);
}
