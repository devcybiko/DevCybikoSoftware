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
#ifndef _BUILD_H_
#define _BUILD_H_

#define MAX_PATH_LEN 256
#define MAX_FILE_LEN 64
#define MAX_TYPE_LEN 16
#define MAX_COPYRIGHT_LEN 64

#define MAX_LIST 256

typedef struct list {
	void *node[MAX_LIST];
} List;

typedef struct build {
	char path[MAX_PATH_LEN];
	char name[MAX_FILE_LEN];
	char author[MAX_FILE_LEN];
	char version[MAX_FILE_LEN];
	char cyos[MAX_FILE_LEN];
	char output[MAX_FILE_LEN];
	char type[MAX_TYPE_LEN];
	char icon[MAX_FILE_LEN];
	char icon_0[MAX_FILE_LEN];
	char icon_1[MAX_FILE_LEN];
	char copyright[MAX_COPYRIGHT_LEN];
	char splash_image[MAX_FILE_LEN];
	int  sdk;
	List source;
	List help;
	List splash_text;
	List pics;
	List d3sprites;
	List music;
	List files;
	List objects;
	List tex;
	List environment;
	int keep;
} Build;

#endif