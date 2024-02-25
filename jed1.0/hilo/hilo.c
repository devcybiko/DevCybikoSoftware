//
// Jed Hello World
// (C) Copyright 2001
// The Alcor Group, Inc.
// Author: Gregory L. Smith
//

#include "../jed.h"

long main(int argc, char* argv[], bool start)
{
  struct module_t main_module;
  Jed *form;
  Jed_item *label1;
  Jed_item *label2;
  Jed_item *higher, *lower, *thatsit;
  Jed_item *ji;
  Jed_item *console;

  int number = random(100)+1;
  int hi = 101;
  int lo = 0;
  int x;
  char s[32];

  init_module(&main_module);

  jed_open(&form, &main_module, NULL);

  jed_button_new(&higher,  form, 0,   84, 40, 16, "Higher", mini_bold_font);
  jed_button_new(&lower,   form, 60,  84, 40, 16, "Lower", mini_bold_font);
  jed_button_new(&thatsit, form, 124, 84, 40, 16, "YES!", mini_bold_font);

  jed_text_new(&label1, form, 0, 0, 160, 14, "I will guess your number", cool_bold_font);
  jed_text_new(&label2, form, 0, 14, 160, 14, "From 1 - 100", NULL);
  jed_console_new(&console, form, 0, 28, 160, 56, 100, NULL);

  while(1)
  {
      x = (hi+lo)/2;
      sprintf(s, "Is it %d?", x);
      jed_console_add_text(console, s);
      jed_main(form, &ji, 0);
      if (ji == higher)
        lo = x;
      else if (ji == lower)
        hi = x;
      else if (ji== NULL || ji == thatsit)
      {
        break;
      }
  }
  jed_close(form);
 
  return 0;
}

//
// user-suppliend message handler
//
Jed_rc jed_process_message(Jed *jed, struct Message *message)
{
    //
    // do nothing to message
    // instruct jed_main to do default thing
    //
    return 0;
}
 

