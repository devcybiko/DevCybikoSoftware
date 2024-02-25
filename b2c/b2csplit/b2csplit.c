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

error(char *err, char *fname)
{
	printf("%s %s\n", err, fname);
	exit(1);
}

myread(char *buffer, int m, int n, FILE *infile)
{
	int i;
	for(i=0; i<m*n; i++)
	{
		buffer[i] = fgetc(infile);
	}
}

split(char *big, char *top, char *bot)
{
	int i=0;
	int j=0;
	int t=0;
	int b=0;
	for(i=0; i<256; i+=32)
	{
		for(j=0; j<16; j++)
		{
			top[t++] = big[i+j];
			bot[b++] = big[i+(15-j)+16];
		}
	}
}

main(int argc, char **argv)
{
	char infname[256];
	char outfname1[256];
	char outfname2[256];
	FILE *infile;
	FILE *outfile1;
	FILE *outfile2;
	char buffer[256];
	char top_buffer[128];
	char bottom_buffer[128];
	char *dot;

	strcpy(infname, argv[1]);
	dot = strrchr(argv[1], '.');
	if (strcmp(dot, ".tex")==0)
	{
		/* image will be inverted later */
		return 0;
	}
	else if (strcmp(dot, ".spr") != 0) 
	{
		printf("file is %s, not a .spr\n", dot);
		return 0;
	}

	dot = strtok(argv[1], ".");

	strcpy(outfname1, argv[1]);
	strcpy(outfname2, argv[1]);
	strcat(outfname1, ".tex1");
	strcat(outfname2, ".tex2");

	infile = fopen(infname, "rb");
	if (!infile) error("could not open", infname);

	outfile1 = fopen(outfname1, "wb");
	if (!outfile1) error("could not open", outfname1);

	outfile2 = fopen(outfname2, "wb");
	if (!outfile2) error("could not open", outfname2);

	myread(buffer, 256, 1, infile);
	split(buffer, top_buffer, bottom_buffer);
	fwrite(top_buffer, 128, 1, outfile1);
	fwrite(bottom_buffer, 128, 1, outfile2);

	fclose(infile);
	fclose(outfile1);
	fclose(outfile2);

	return 0;
}