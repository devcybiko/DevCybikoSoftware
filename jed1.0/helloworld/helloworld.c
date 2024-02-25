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
  Jed *hello_form;
  Jed_item *label1;
  Jed_item *label2;
  Jed_item *button1;
  Jed_item *ji;

  init_module(&main_module);

  //
  // open the jed main form with the default font
  //
  jed_open(&hello_form, &main_module, NULL);

  //
  // create the OK button with cool_bold_font
  //
  jed_button_new(&button1, hello_form, 64, 46, 32, 32, "Ok", cool_bold_font);

  //
  // Hello World in cool bold font
  //
  jed_text_new(&label1, hello_form, 0, 23, 160, 14, "Hello World", cool_bold_font);

  //
  // press enter
  //
  jed_text_new(&label2, hello_form, 0, 88, 160, 14, "(press enter to continue)", NULL);

  //
  // display form
  //
  jed_main(hello_form, &ji, 0);

  //
  // destroy form
  //
  jed_close(hello_form);

  //
  // exit
  //
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
 

