

#ifndef __FILELISTFORM_H__
#define __FILELISTFORM_H__

////////////////////////////////////////////////////////////
//be sure to #include CyWin.h prior to including this file//
////////////////////////////////////////////////////////////

#include "MenuForm.h"

//FileListForm function(returns item selected, or -1 if cancelled using <Esc>
int FileListForm(
	char* title,				//(in)title of the form
	char* filter,				//(in)filter for file list
	char* filename,				//(out)filename selected
	struct cWinApp* ptr_win_app	//(in)application pointer(main_module.m_process)
);

#endif
