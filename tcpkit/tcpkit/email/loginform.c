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
#include "loginform.h"
#include "pop3.h"

Jed *loginForm;
static Jed_item *hostnameString;
static Jed_item *usernameString;
static Jed_item *passwordString;
static Jed_item *loginButton;
static 	Jed_item *ji;

void loginForm_create() {
	char tmp[64];
	int x = 0;
	int y = 0;

	jed_open(&loginForm, ptr_main_module, mini_normal_font);
	sprintf(tmp, "Email Version %s", VERSION);
	jed_text_new(&ji, loginForm, 0, y, 160, 16, tmp, cool_bold_font);
	y+=16;
	jed_text_new(&ji, loginForm, x, y, 60, 12, "Hostname:", mini_bold_font);
	y+=16;
	jed_text_new(&ji, loginForm, x, y, 60, 12, "Username:", mini_bold_font);
	y+=16;
	jed_text_new(&ji, loginForm, x, y, 60, 12, "Password:", mini_bold_font);

	x=60;
	y=16;
	jed_string_new(&hostnameString, loginForm, x, y, 80, 14, 64, "alcorgrp.com", NULL);
	y+=16;
	jed_string_new(&usernameString, loginForm, x, y, 80, 14, 64, "", NULL);
	y+=16;
	jed_string_new(&passwordString, loginForm, x, y, 80, 14, 64, "", NULL);
	y+=16;
	
	jed_button_new(&loginButton, loginForm, 56, 76, 48, 16, "Login", cool_bold_font);
}

int loginForm_main() {
	Jed_item *ji;
	char *hostname;
	char *username;
	char *password;
	int returnEvent = EXIT_APPLICATION;

	//
	// display form
	//
	jed_main(loginForm, &ji, 0);

	if (ji != (Jed_item *)NULL) {
		hostname = jed_get_value(hostnameString);
		username = jed_get_value(usernameString);
		password = jed_get_value(passwordString);

		pop3_open(hostname, username, password);
		returnEvent = SHOW_LOGIN_FORM;
	} else {
		returnEvent = EXIT_APPLICATION;
	}
	return returnEvent;
}

void loginForm_destroy() {
	jed_close(loginForm);
}