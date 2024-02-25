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
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int return_code = 0;

char *skip_blanks(char *rec)
{
	while(isspace(*rec)) rec++;
	return rec;
}

int preprocess(char *infname)
{
	char *s;
	char inrec[256];
	FILE *infile;
	int lineno=0;

	if (infname)
	{
		printf("@%s 1\n", infname);
		infile = fopen(infname, "r");
		if (!infile) 
		{
			fprintf(stderr, "ERROR: Could not open %s\n", infname);
			printf("/* ERROR Openning %s\n", infname);
			return_code = 1;
			return return_code;
		}
	}
	else
	{
		infile = stdin;
		infname="stdin";
	}
	while(fgets(inrec, sizeof(inrec), infile))
	{
		lineno++;
		s = skip_blanks(inrec);
		if (_strnicmp(s, "include", 7) == 0)
		{
			s = strtok(inrec, "\""); // include
			s = strtok(NULL, "\"\n\r"); //filename
			if (!s || preprocess(s))
			{
				fprintf(stderr, "ERROR %s:%d\n", infname, lineno);
				return_code = 1;
				return 1;
			}
			else
			{
				printf("@%s %d\n", infname, lineno);
			}
		}
		else
		{
			printf("%s", inrec);
			if (inrec[strlen(inrec)-1] != '\n')
				printf("\n");
		}
	}
	return 0;
}

main(int argc, char **argv)
{
	if (argc < 2)
	{
		preprocess(NULL);
	}
	else
	{
		preprocess(argv[1]);
	}

	return return_code;
}