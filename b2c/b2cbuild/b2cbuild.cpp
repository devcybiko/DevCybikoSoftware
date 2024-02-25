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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <stdarg.h>

//#ifndef MAIN
//#include "stdafx.h"
//#endif //MAIN

#ifndef MAIN
#include <setjmp.h>
extern jmp_buf MainFrm_mark;
#endif

#include "b2cbuild.h"

#define MAX_INFILE 10
int current=0;
FILE *infile[MAX_INFILE];
FILE *outfile;
int lineno[MAX_INFILE];
char filename[MAX_INFILE][MAX_FILE_LEN];
char inrec[256];
int delete_files=1;
int sdk_version=2;

Build build;

int cy3d_dl_needed = 0;

void error_out(char *fmt, ...)
{
	char buf[256];
    va_list vl;

    va_start( vl, fmt );
	vsprintf(buf, fmt, vl);
	va_end(vl);
#ifdef MAIN
	printf("%s", buf);
#else
	AfxMessageBox(buf);
#endif //MAIN
}

void error_exit(int n)
{
#ifdef MAIN
	exit(n);
#else
	longjmp(MainFrm_mark, -1);
#endif
}

char *basename(char *name)
{
	static char s[MAX_FILE_LEN];
	char *t;

	strcpy(s, name);
	t = strrchr(s, '.');
	if (t) *t = 0;
	return s;
}

FILE *bld_open(char *s)
{
	FILE *outfile = fopen(s, "w");
	if (outfile == NULL)
	{
		error_out("ERROR %s(%d) - could not open %s for write\n", filename[current], lineno[current], s);
		error_exit(1);
	}
	return outfile;
}

char *trim(char *s)
{
	char *t;

	for(t=s; *t && isspace(*t);)
	{
		strcpy(t, &t[1]);
	}
	while(isspace(s[strlen(s)-1]))
		s[strlen(s)-1] = 0;
	return s;
}

char *trim2(char *s)
{
	trim(s);
	strtok(s, "]");
	return s;
}

int blankline(char *s)
{
	char *t;
	for(t=s; *t && isspace(*t); t++) ;
	if (*t) return 0;
	return 1;
}

void path()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		if (build.path[0] == 0)
		{
			strcat(build.path, inrec);
		}
		else
		{
			strcat(build.path, ";");
			strcat(build.path, inrec);
		}
	}
}

void option()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		if (strcmp(inrec, "keep")==0) 
		{
			build.keep = 1;
			delete_files=0;
		}
	}
}

void name()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.name, inrec);
	}
}

void author()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.author, inrec);
	}
}

void version()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.version, inrec);
	}
}

void cyos()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.cyos, inrec);
	}
}

void output()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.output, inrec);
	}
}

void copyright()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.copyright, inrec);
	}
}

void icon()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.icon, inrec);
	}
}

void icon0()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.icon_0, inrec);
	}
}

void icon1()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.icon_1, inrec);
	}
}

void splash_image()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		strcpy(build.splash_image, inrec);
	}
}

void type()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		if (strcmp(inrec, "game") == 0 ||
			strcmp(inrec, "root") == 0 ||
			strcmp(inrec, "app") == 0)
		{
			strcpy(build.type, inrec);
		}
		else
		{
			error_out("ERROR %s(%d) - unknown apptype \"%s\"\n", filename[current], lineno[current], inrec);
			error_exit(1);
		}
	}
}

void music()
{
	int musline=0;
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		build.music.node[musline++]=strdup(inrec);
		if (musline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for music exceeded(%d)\n", filename[current], lineno[current], musline);
			error_exit(1);
		}
		build.music.node[musline] = 0;
	}
}

void files()
{
	int filesline=0;
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		build.files.node[filesline++]=strdup(inrec);
		if (filesline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for files exceeded(%d)\n", filename[current], lineno[current], filesline);
			error_exit(1);
		}
		build.files.node[filesline] = 0;
	}
}

void objects()
{
	int filesline=0;
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		build.objects.node[filesline++]=strdup(inrec);
		if (filesline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for objects exceeded(%d)\n", filename[current], lineno[current], filesline);
			error_exit(1);
		}
		build.objects.node[filesline] = 0;
	}
}

void pics()
{
	int picline=0;
	int i;
	List *list;

	for(i=0; build.pics.node[i]; i++);
	if (i == MAX_LIST)
	{
		error_out("ERROR %s(%d) - max number pics exceeded(%d)\n", filename[current], lineno[current], i);
		error_exit(1);
	}

	list = (List *) calloc(1, sizeof(List));
	build.pics.node[i] = list;;
	list->node[picline++] = trim2(strdup(&inrec[5]));
	(list->node[0]);
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		list->node[picline++]=strdup(inrec);
		if (picline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for pic exceeded(%d)\n", filename[current], lineno[current], picline);
			error_exit(1);
		}
		list->node[picline] = 0;
	}
}

void d3sprite()
{
	int spriteline=0;
	int i;
	List *list;

	for(i=0; build.d3sprites.node[i]; i++);
	if (i == MAX_LIST)
	{
		error_out("ERROR %s(%d) - max number 3dspites exceeded(%d)\n", filename[current], lineno[current], i);
		error_exit(1);
	}

	build.d3sprites.node[i] = (List *) calloc(1, sizeof(List));
	list = (List *)build.d3sprites.node[i];
	list->node[spriteline++] = trim2(strdup(&inrec[10]));
	(list->node[0]);
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		list->node[spriteline++]=strdup(inrec);
		if (spriteline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for 3dsprite exceeded(%d)\n", filename[current], lineno[current], spriteline);
			error_exit(1);
		}
		list->node[spriteline] = 0;
	}
}

void help()
{
	int helpline=0;
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		build.help.node[helpline++]=strdup(inrec);
		if (helpline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for help exceeded(%d)\n", filename[current], lineno[current], helpline);
			error_exit(1);
		}
		build.help.node[helpline] = 0;
	}
}

int is_ext(char *s, char *ext)
{
	char *t;

	t = strrchr(s, '.');
	if (0==strcmp(t, ext))
		return 1;
	return 0;
}

void source()
{
	int sourceline=0;
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		if (!(is_ext(inrec, ".b2c") || is_ext(inrec, ".c")))
		{
			error_out("ERROR %s(%d) - Illegal file type for source (.b2c or .c only)\n", 
				filename[current], lineno[current]);
			error_exit(1);
		}
		build.source.node[sourceline++]=strdup(inrec);
		if (sourceline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for source exceeded(%d)\n", filename[current], lineno[current], sourceline);
			error_exit(1);
		}
		build.source.node[sourceline] = 0;
	}
}

void tex()
{
	static int texline=0;
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		cy3d_dl_needed = 1;
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		build.tex.node[texline++]=strdup(inrec);
		if (texline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for 3dtex exceeded(%d)\n", filename[current], lineno[current], texline);
			error_exit(1);
		}
		build.tex.node[texline] = 0;
	}
}

void sdk()
{
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		sdk_version = atoi(inrec);
		build.sdk = sdk_version;
	}
}

void splash_text()
{
	int textline=0;
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
		trim(inrec);
		build.splash_text.node[textline++]=strdup(inrec);
		if (textline == MAX_LIST)
		{
			error_out("ERROR %s(%d) - max number lines for splash.text exceeded(%d)\n", filename[current], lineno[current], textline);
			error_exit(1);
		}
		build.splash_text.node[textline] = 0;
	}
}

void environment()
{
	int envno=0;

	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (inrec[0] == '[') break;
//		trim(inrec);
		build.environment.node[envno++]=strdup(inrec); 
	}
}

void dump_build()
{
	int i;
	printf("path='%s'\n", build.path);
	printf("name='%s'\n", build.name);
	printf("author='%s'\n", build.author);
	printf("version='%s'\n", build.version);
	printf("source='%s'\n", build.source);
	printf("output='%s'\n", build.output);
	printf("type='%s'\n", build.type);
	printf("copyright='%s'\n", build.copyright);
	printf("icon='%s'\n", build.icon);
	printf("splash.image='%s'\n", build.splash_image);
	printf("help=\n");
	for(i=0; build.help.node[i]; i++)
		printf("    %s\n", build.help.node[i]);
	printf("splash.text=\n");
	for(i=0; build.splash_text.node[i]; i++)
		printf("    %s\n", build.splash_text.node[i]);
	printf("music=\n");
	for(i=0; build.music.node[i]; i++)
		printf("    %s\n", build.music.node[i]);
	printf("files=\n");
	for(i=0; build.files.node[i]; i++)
		printf("    %s\n", build.files.node[i]);
	printf("pics=\n");
	for(i=0; build.pics.node[i]; i++)
	{
		List *list;
		int j;
		list = (List *)build.pics.node[i];
		printf("    %s\n", list->node[0]);
		for(j=1; list->node[j]; j++)
			printf("        %s\n", list->node[j]);
	}
	printf("pics=\n");
	for(i=0; build.d3sprites.node[i]; i++)
	{
		List *list;
		int j;
		list = (List *)build.d3sprites.node[i];
		printf("    %s\n", list->node[0]);
		for(j=1; list->node[j]; j++)
			printf("        %s\n", list->node[j]);
	}
}

void create_root_inf()
{
	outfile = bld_open("root.inf");
	fprintf(outfile, "%s\n", build.type);
	fprintf(outfile, "%s\n", build.name);
	fprintf(outfile, "\n");
	fprintf(outfile, "\n");
	fprintf(outfile, "\n");
	fprintf(outfile, "\n");
	fprintf(outfile, "%s\n", build.name);
	fprintf(outfile, "%s\n", build.version); //version
	if (sdk_version > 2)
	{
		if (build.cyos[0] == 0)
			fprintf(outfile, "1.5.1\n"); //cyos version
		else
			fprintf(outfile, "%s\n", build.cyos);
	}
	else
	{
		if (build.cyos[0] == 0)
			fprintf(outfile, "1.3.57\n");
		else
			fprintf(outfile, "%s\n", build.cyos);
	}
	fprintf(outfile, "%s\n", build.copyright);

	fclose(outfile);
}

void create_score_inf()
{
	char data[200];

	memset(data, 0, 200);
	outfile = bld_open("score.inf");
	fwrite(data, 200, 1, outfile);

	fclose(outfile);
}

void create_help()
{
	int i;

	outfile = bld_open("0.help");
	for(i=0; build.help.node[i]; i++)
		fprintf(outfile, "%s\n", build.help.node[i]);

	fclose(outfile);
}

void create_root_spl()
{
	int i;

	outfile = bld_open("root.spl");
	fprintf(outfile, "%s\n", build.name);
	fprintf(outfile, "Version %s\n", build.version);
	fprintf(outfile, "%s\n", build.author);
	fprintf(outfile, "%s\n", build.copyright);
	fprintf(outfile, "\n");
	for(i=0; build.splash_text.node[i]; i++)
		fprintf(outfile, "%s\n", build.splash_text.node[i]);

	fclose(outfile);
}

void create_filer_list()
{
	int i;

	outfile = bld_open("filer.list");
	fprintf(outfile, "+0.help\n");
	fprintf(outfile, "+root.inf\n");
	fprintf(outfile, "+root.spl\n");
	fprintf(outfile, "+root.ico\n");
	if (sdk_version > 2)
	{
		fprintf(outfile, "+0.ico\n");
		fprintf(outfile, "+1.ico\n");
	}
	if (build.splash_image[0])
		fprintf(outfile, "+intro.pic\n");

	for(i=0; build.pics.node[i]; i++)
	{
		List *list;
		list = (List *)build.pics.node[i];
		fprintf(outfile, "+%s\n", list->node[0]);
	}

	for(i=0; build.d3sprites.node[i]; i++)
	{
		List *list;
		list = (List *)build.d3sprites.node[i];
		fprintf(outfile, "+%s\n", list->node[0]);
	}

	for(i=0; build.music.node[i]; i++)
		fprintf(outfile, "+%s\n", build.music.node[i]);

	for(i=0; build.files.node[i]; i++)
		fprintf(outfile, "+%s\n", build.files.node[i]);

	for(i=0; build.tex.node[i]; i++)
	{
		FILE *x;
		char texfile[MAX_FILE_LEN];
		sprintf(texfile, "%s.tex", basename((char *)build.tex.node[i]));
		if (x=fopen(texfile, "r"))
		{
			fprintf(outfile, "+%s\n", texfile);
			fclose(x);
		}
		sprintf(texfile, "%s.tex1", basename((char *)build.tex.node[i]));
		if (x=fopen(texfile, "r"))
		{
			fprintf(outfile, "+%s\n", texfile);
			fclose(x);
		}
		sprintf(texfile, "%s.tex2", basename((char *)build.tex.node[i]));
		if (x=fopen(texfile, "r"))
		{
			fprintf(outfile, "+%s\n", texfile);
			fclose(x);
		}
	}
	if (cy3d_dl_needed)
	{
		FILE *xxx;
		char cy3d[MAX_FILE_LEN];
		sprintf(cy3d, "%s\\lib\\cy3d.dl", getenv("CYBIKO_SDK"));
		if (xxx=fopen(cy3d, "rb"))
		{
			fclose(xxx);
			fprintf(outfile, "-%s\n", cy3d);
		}
		else
		{
			sprintf(cy3d, "%s\\lib\\dl\\cy3d.dl", getenv("CYBIKO_SDK"));
			if (xxx=fopen(cy3d, "rb"))
			{
				fclose(xxx);
				fprintf(outfile, "-%s\n", cy3d);
			}
			else
			{
				error_out("ERROR Opening %s\n", cy3d);
				error_exit(1);
			}
		}
	}
	fprintf(outfile, "-score.inf\n");

	fclose(outfile);
}

void errorlevel()
{
	fprintf(outfile, "if errorlevel 1 goto end\n");
}

void ifexist(char *name)
{
	if (delete_files)
		fprintf(outfile, "if exist %s del %s\n", name, name);
	else
		fprintf(outfile, "rem if exist %s del %s\n", name, name);
}

void compile_tex()
{
	int i;
	char texbase[MAX_FILE_LEN];

	outfile = bld_open("_maketex.bat");
	fprintf(outfile, "@echo off\n");
	for (i=0; build.tex.node[i]; i++)
	{
		strcpy(texbase, basename((char *)build.tex.node[i]));
		fprintf(outfile, "bmp2spr %s %s\n",
			texbase,
			build.tex.node[i]);
		errorlevel();
		fprintf(outfile, "%s\\bin\\b2csplit %s.spr\n", 
			build.path,
			texbase);
		errorlevel();
	}
	fprintf(outfile, ":end\n");
	fclose(outfile);
	system("_maketex.bat");
}

void compile_source()
{
	char base[MAX_FILE_LEN];
	char picbase[MAX_FILE_LEN];
	char tmpfile[MAX_FILE_LEN];
	int i, j;
	
	outfile = bld_open("_make.bat");
	fprintf(outfile, "@echo off\n");
	fprintf(outfile, "set CC=vcc\n");
	for(i=0; build.environment.node[i]; i++)
	{
		if (strncmp((char *)build.environment.node[i], "PATH=", 5)==0)
			fprintf(outfile, "PATH %s\n", &(((char *)build.environment.node[i])[5]));
		else
			fprintf(outfile, "set %s\n", build.environment.node[i]);
	}
	for(i=0; build.source.node[i]; i++)
	{
		strcpy(base,basename((char *)build.source.node[i]));

		if (is_ext((char *)build.source.node[i], ".b2c"))
		{
			fprintf(outfile, "%s\\bin\\b2cpp %s > %s.tmp\n", 
				build.path,
				build.source.node[i],
				base);
			errorlevel();
			fprintf(outfile, "%s\\bin\\b2c %s.tmp\n",
				build.path,
				base);
			errorlevel();
		}
		fprintf(outfile, "%%CC%% -I%s\\inc -o %s.o %s.c\n", build.path, base, base);
		errorlevel();
	}

	if (sdk_version > 2)
	{
		fprintf(outfile, "%%CC%% -o bytecode.bin %s\\bin\\b2xuser.o", build.path);
	}
	else
	{
		fprintf(outfile, "%%CC%% -o bytecode.bin %s\\bin\\b2cuser.o", build.path);
	}
	for (i=0; build.source.node[i]; i++)
	{
		strcpy(base, basename((char *)build.source.node[i]));
		fprintf(outfile, " %s.o", base);
	}
	for (i=0; build.objects.node[i]; i++)
	{
		fprintf(outfile, " %s", build.objects.node[i]);
	}
	fprintf(outfile, "\n");
	errorlevel();

	if (build.splash_image[0] != 0)
	{
		fprintf(outfile, "2pic intro.pic %s\n", build.splash_image);
		errorlevel();
	}

	if (build.icon[0] != 0)
	{
		fprintf(outfile, "2pic root.ico %s\n", build.icon);
		errorlevel();
	}
	else
	{
		fprintf(outfile, "2pic root.ico %s\\inc\\b2c.bmp\n", build.path);
		errorlevel();
	}

	if (build.icon_0[0] != 0)
	{
		fprintf(outfile, "2pic 0.ico %s\n", build.icon_0);
		errorlevel();
	}
	else if (sdk_version > 2)
	{
		fprintf(outfile, "2pic 0.ico %s\\inc\\0.bmp\n", build.path);
		errorlevel();
	}

	if (build.icon_1[0] != 0)
	{
		fprintf(outfile, "2pic 1.ico %s\n", build.icon_1);
		errorlevel();
	}
	else if (sdk_version > 2)
	{
		fprintf(outfile, "2pic 1.ico %s\\inc\\1.bmp\n", build.path);
		errorlevel();
	}

	for (i=0; build.pics.node[i]; i++)
	{
		List *list = (List *)build.pics.node[i];
		char picfile[MAX_FILE_LEN];
		FILE *listfile;

		strcpy(picbase, basename((char *)list->node[0]));
		sprintf(picfile, "_%s.list", picbase);
		listfile = bld_open(picfile);
		for (j=1; list->node[j]; j++)
		{
			fprintf(listfile, "%s\n", list->node[j]);
		}
		fclose(listfile);

		fprintf(outfile, "2pic %s @%s\n",
			list->node[0],
			picfile);
		errorlevel();
	}

	for (i=0; build.d3sprites.node[i]; i++)
	{
		List *list = (List *)build.d3sprites.node[i];
		char spritefile[MAX_FILE_LEN];

		strcpy(spritefile, basename((char *)list->node[0]));
		fprintf(outfile, "bmp2spr %s ", spritefile);
		for (j=1; list->node[j]; j++)
		{
			fprintf(outfile, "%s ", list->node[j]);
		}
		fprintf(outfile, "\n");
		errorlevel();
	}

	if (build.output[0]==0)
		sprintf(build.output, "%s.app", base);

	if (sdk_version > 2)
	{
		fprintf(outfile, "filer a %s @filer.list bytecode.bin \"%%CYBIKO_SDK%%\\lib\\cybiko\\main.e\"\n",
			build.output);
		errorlevel();
	}
	else
	{
		fprintf(outfile, "filer a %s @filer.list bytecode.bin \"%%CYBIKO_SDK%%\\lib\\main.e\"\n",
			build.output);
		errorlevel();
	}

	fprintf(outfile, ":end\n");

	ifexist("root.inf");
	ifexist("root.spl");
	ifexist("filer.list");
	ifexist("0.help");
	ifexist("score.inf");
	ifexist("root.ico");
	ifexist("0.ico");
	ifexist("1.ico");
	for(i=0; build.source.node[i]; i++)
	{
		strcpy(base, basename((char *)build.source.node[i]));
		if (is_ext((char *)build.source.node[i], ".b2c"))
		{
			sprintf(tmpfile, "%s.tmp", base);
			ifexist(tmpfile);
			sprintf(tmpfile, "%s.c", base);
			ifexist(tmpfile);
		}
		sprintf(tmpfile, "%s.o", base);
		ifexist(tmpfile);
	}
	ifexist("bytecode.bin");
	ifexist("_maketex.bat");
	if (build.splash_image[0])
		ifexist("intro.pic");
	for (i=0; build.pics.node[i]; i++)
	{
		List *list = (List *)build.pics.node[i];
		char picfile[MAX_FILE_LEN];
		strcpy(picbase, basename((char *)list->node[0]));
		sprintf(picfile, "_%s.list", picbase);
		ifexist(picfile);
		ifexist((char *)list->node[0]);
	}
	for (i=0; build.d3sprites.node[i]; i++)
	{
		List *list = (List *)build.d3sprites.node[i];
		ifexist((char *)list->node[0]);
	}
	for (i=0; build.tex.node[i]; i++)
	{
		char texfile[MAX_FILE_LEN];
		char texbase[MAX_FILE_LEN];
		strcpy(texbase, basename((char *)build.tex.node[i]));
		sprintf(texfile, "%s.tex", texbase);
		ifexist(texfile);
		sprintf(texfile, "%s.tex1", texbase);
		ifexist(texfile);
		sprintf(texfile, "%s.tex2", texbase);
		ifexist(texfile);
		sprintf(texfile, "%s.spr", texbase);
		ifexist(texfile);
	}	
	fclose(outfile);

	system("_make.bat");
}

int isa_b2c_file(char *s)
{
	char *dot;

	dot = strrchr(s, '.');
	if (dot && strcmp(dot, ".b2c")==0) return 1;
	return 0;
}

void do_everything(char *fname)
{
	infile[current] = fopen(fname, "r");
	if (infile[current] == NULL) 
	{
		error_out("ERROR Opening %s\n", fname);
		error_exit(1);
	}

	strcpy(filename[current], fname);
	while(fgets(inrec, sizeof(inrec), infile[current]))
	{
		lineno[current]++;
		strtok(inrec, "\n\r");
Again:
		if (inrec[0] == '#') continue;
		else if (blankline(inrec)) continue;
		else if (strncmp(inrec, "[path]", 6)==0) path();
		else if (strncmp(inrec, "[name]", 6)==0) name();
		else if (strncmp(inrec, "[author]", 8)==0) author();
		else if (strncmp(inrec, "[version]", 9)==0) version();
		else if (strncmp(inrec, "[cyos]", 6)==0) cyos();
		else if (strncmp(inrec, "[source]", 8)==0) source();
		else if (strncmp(inrec, "[type]", 6)==0) type();
		else if (strncmp(inrec, "[copyright]", 11)==0) copyright();
		else if (strncmp(inrec, "[help]", 6)==0) help();
		else if (strncmp(inrec, "[icon]", 6)==0) icon();
		else if (strncmp(inrec, "[icon0]", 6)==0) icon0();
		else if (strncmp(inrec, "[icon1]", 6)==0) icon1();
		else if (strncmp(inrec, "[splash.text]", 13)==0) splash_text();
		else if (strncmp(inrec, "[splash.image]", 13)==0) splash_image();
		else if (strncmp(inrec, "[music]", 7)==0) music();
		else if (strncmp(inrec, "[files]", 7)==0) files();
		else if (strncmp(inrec, "[objects]", 9)==0) objects();
		else if (strncmp(inrec, "[option]", 8)==0) option();
		else if (strncmp(inrec, "[pic=", 5)==0) pics();
		else if (strncmp(inrec, "[3dsprite=", 10)==0) d3sprite();
		else if (strncmp(inrec, "[3dtex]", 7)==0) tex();
		else if (strncmp(inrec, "[sdk]", 5)==0) sdk();
		else if (strncmp(inrec, "[environment]", 13)==0) environment();
		else if (strncmp(inrec, "[output]", 8)==0) output();
		else if (strncmp(inrec, "[include=", 9)==0)
		{
			char file[MAX_FILE_LEN];
			strcpy(file, &inrec[9]);
			strtok(file, "]");
			current++;
			do_everything(file);
			current--;
			inrec[0]=0;
		}
		else
		{
			error_out("ERROR %s(%d) - unknown command \"%s\"\n", filename[current], lineno[current], inrec);
			error_exit(1);
		}
		if (!feof(infile[current]))
			goto Again;
	}
}

#ifdef MAIN
int main(int argc, char **argv)
{
	if (argc == 1)
	{
		error_out("Usage: %s file.bld", argv[0]);
		error_exit(0);
	}
	if (isa_b2c_file(argv[1]))
	{
		build.source.node[0] = strdup(argv[1]);
		goto Process;
	}

	do_everything(argv[1]);

Process:
	//dump_build();

	if (build.path[0] == 0)
	{
		strcpy(build.path, ".");
	}
	if (build.source.node[0] == 0)
	{
		error_out("ERROR %s(%d) - missing [source] file\n", filename[current], lineno[current]);
		error_exit(1);
	}
	if (build.name[0] == 0)
	{
		strcpy(build.name, basename((char *)build.source.node[0]));
	}
	if (build.type[0] == 0)
	{
		strcpy(build.type, "game");
	}
	if (build.version[0] == 0)
	{
		strcpy(build.version, "1.0.0");
	}
	if (build.copyright[0] == 0)
	{
		time_t ltime;
		struct tm *today;
		time(&ltime);
		today = localtime(&ltime);
		strftime(build.copyright, sizeof(build.copyright), "(C) Copyright %Y", today);
	}
	create_root_inf();
	create_help();
	create_root_spl();
	create_score_inf();
	compile_tex();
	create_filer_list();
	compile_source();

	if (delete_files)
	{
		system("del _make.bat");
	}
	return 0;
}
#endif //MAIN
