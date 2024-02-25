

#ifndef __MENUFORM_H__
#define __MENUFORM_H__

////////////////////////////////////////////////////////////
//be sure to #include CyWin.h prior to including this file//
////////////////////////////////////////////////////////////

//this result is given if an MSG_QUIT or MSG_SHUTUP message is received
#define MENUFORM_QUIT	-2
//this result is given if ESC is pressed
#define MENUFORM_CANCEL	-1


//SimpleMenuForm function(returns item selected, or -1 if cancelled using <Esc>
int SimpleMenuForm(
	char* title,				//(in)title of the menu
	char** ItemList,			//(in)list of items (array of char*, with last item being "")
	int x,						//(in) x coordinate of upperleft
	int y,						//(in) y coordinate of upperleft
	int width,					//(in) width of form
	int height,					//(in) height of form
	bool round,					//(in) TRUE=rounded, FALSE=rectangular
	struct cWinApp* ptr_win_app	//(in)application pointer(main_module.m_process)
);

#endif
