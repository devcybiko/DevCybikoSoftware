/**
  * The TCPKIT framework is a set of programs and libraries
  * that allow a set of Cybiko computers to communicate on
  * the internet.
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
#include "email.h"
#include "jed.h"
#include "listform.h"
#include "pop3.h"

Jed *listForm;
static Jed_item *listItem;
static 	Jed_item *ji;

void listForm_create() {
	char tmp[64];
	int x = 0;
	int y = 0;

	jed_open(&listForm, ptr_main_module, mini_normal_font);
	sprintf(tmp, "%d Messages", 0);
	jed_text_new(&ji, listForm, 0, y, 160, 16, tmp, cool_bold_font);
	y+=16;
	jed_list_new(&ji, listForm, x, y, 160, 80, 1000, mini_bold_font);
}

int listForm_main() {
	Jed_item *ji;
	int returnEvent = EXIT_APPLICATION;

	pop3_list();
	//
	// display form
	//
	jed_main(listForm, &ji, 0);

	if (ji != (Jed_item *)NULL) {
	} else {
		returnEvent = EXIT_APPLICATION;
	}
	return returnEvent;
}

void listForm_destroy() {
	jed_close(listForm);
}