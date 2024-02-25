/**
  * The JED project is a library that offers a simple
  * GUI for the Cybiko Handheld Computer for Teens
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
  *///  Step1.c
//
//  Interface tutorial step 1.
//

#include "CyWin.h"
#include "alcor.h"
#include "jed.h"

#define DEBUG 1
#ifdef DEBUG
#define DBG cprintf
#else
#define DBG
#endif

///////////////////////////////////////////////////////
//           Main function of the                    //
//            sample application.                    //
///////////////////////////////////////////////////////

char g_s[64];
Jed_item *around, *console;
int update_the_around_list = TRUE;

long main(int argc, char* argv[], bool start)
{
  struct module_t main_module;
  Jed *main_form;
  Jed_item *label1;
  Jed_item *button1, *button2;
  Jed_item *button3, *button4;
  Jed_item *ji;
  Jed_item *string1, *string2;
  Jed_item *list;
  int i;
  char *s;

  DBG("Starting program\n");
  init_module(&main_module);

  DBG("Jed Open Called\n");
  jed_open(&main_form, &main_module, NULL);

  DBG("Jed string new Called\n");
  jed_string_new(&string1, main_form, 0, 74, 160, 12, 80, "A*Chat Welcome", NULL);

  DBG("Jed Button New Called\n");
  jed_button_new(&button1, main_form, 0, 88, 35, 12, "Button1", NULL);
  DBG("Jed Button New Called\n");
  jed_button_new(&button2, main_form, 40, 88, 35, 12, "Button2", NULL);
  DBG("Jed Button New Called\n");
  jed_button_new(&button3, main_form, 80, 88, 35, 12, "Button3", NULL);
  DBG("Jed Button New Called\n");
  jed_button_new(&button4, main_form, 120, 88, 35, 12, "Button4", NULL);

  DBG("Jed Console New Called\n");
  jed_console_new(&console, main_form, 30, 0, 130, 72, 100, cool_bold_font);

  DBG("Jed List New Called\n");
  jed_list_new(&list, main_form, 0, 0, 29, 72, 32, NULL);

  for (i=0; i<=finder.howmany_around; i++)
  {
    DBG("Jed list add item Called\n");
    jed_list_add_item(list, finder.cf[i].cf_fk.f_nick);
  }
  while(1)
  {
      jed_main(main_form, &ji, 1000);
      if (ji)
      {
          s = jed_get_value(ji);
          sprintf(g_s, "%s", s);
          jed_console_add_text(console, g_s);
          if (ji == string1) jed_string_set_value(ji, "");
      }
      else
      {
          TRACE("main loop ended with ESC");
          break;
      }
  }
  jed_close(main_form);
  return 0;
}

Jed_rc jed_process_message(Jed *jed, struct Message *message)
{
    static int i=0;

    sprintf(g_s, "foo %d", i++);
    jed_console_add_text(console, g_s);
    jed_repaint_item(console, TRUE);
    return 0;
}
 
