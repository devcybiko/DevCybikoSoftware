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
#include <stdlib.h>

#define SAME(a,b) (0==strcmp(a,b))
#define SEPS "<> /:"
char inrec[1024];
FILE *infile;
FILE *index;

void extract_page()
{
	char *s;
	char buf[1024];
	FILE *outfile;

	strcpy(buf, inrec);
	for(s=strtok(&buf[8], SEPS);
		s;
		s=strtok(NULL, SEPS))
	{
		if SAME(s, "B") continue;
		s = strtok(s, "(");
		printf("%s\n", s);

		fprintf(index, "<LI> <OBJECT type=\"text/sitemap\">\n");
		fprintf(index, "<param name=\"Name\" value=\"%s\"> ", s);
		strcat(s, ".htm");
		outfile = fopen(s, "w");
		fprintf(index, "<param name=\"Local\" value=\"%s\">\n", s);
		fprintf(index, "</OBJECT>\n");

		fprintf(outfile, "<B>%s", inrec);
		while(fgets(inrec, sizeof(inrec), infile))
		{
			if (strncmp(inrec, "<P>Topic", 8)==0) break;
			fprintf(outfile, "%s", inrec);
		}
		fclose(outfile);
		break;
	}
}

main(int argc, char **argv)
{

	infile = fopen(argv[1], "r");
	if (!infile)
	{
		printf("Could not open %s\n", argv[1]);
		exit(0);
	}

	index = fopen("b2c.hhk", "w");
	fprintf(index, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n");
	fprintf(index, "<HTML>\n");
	fprintf(index, "<HEAD>\n");
	fprintf(index, "<meta name=\"GENERATOR\" content=\"Microsoft&reg; HTML Help Workshop 4.1\">\n");
	fprintf(index, "<!-- Sitemap 1.0 -->\n");
	fprintf(index, "</HEAD><BODY>\n");
	fprintf(index, "<UL>\n");

	while(fgets(inrec, sizeof(inrec), infile))
	{
		while (strncmp(inrec, "<P>Topic", 8)==0)
			extract_page();

	}
	fprintf(index, "</UL>\n");
	fprintf(index, "</BODY></HTML>\n");
	fclose(index);

}
