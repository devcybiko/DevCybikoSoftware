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
//
// POP3 Email
// (C) Copyright 2003
// The Alcor Group, Inc.
// Author: Gregory L. Smith
//

#include "email.h"
#include "jed.h"
#include "loginform.h"
#include "..\tcplib.h"

struct module_t main_module;
struct module_t *ptr_main_module;
long tcpqueue=0;

long main(int argc, char* argv[], bool start)
{
	int formEvent = SHOW_LOGIN_FORM;

	ptr_main_module = &main_module;
	init_module(ptr_main_module);

	tcp_init(&main_module);

	loginForm_create();

	while(formEvent != EXIT_APPLICATION) {
		switch (formEvent) {
		case SHOW_LOGIN_FORM: formEvent = loginForm_main(); break;
		case SHOW_LIST_FORM: formEvent = listForm_main(); break;
		default: formEvent = EXIT_APPLICATION; break;
		}
	}

	loginForm_destroy();
	listForm_destroy();

	if (tcpqueue) tcp_close(tcpqueue);
	return 0;
}

//
// user-suppliend message handler
//
Jed_rc jed_process_message(Jed *jed, struct Message *message)
{

	tcp_process_message(message);
    return 0;
}
 

