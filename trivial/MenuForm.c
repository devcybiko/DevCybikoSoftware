#ifndef __MENUFORM_C__
#define __MENUFORM_C__

#include "MenuForm.h"

int SimpleMenuForm(
		char* title,				//(in)title of the menu
		char** ItemList,			//(in)list of items (array of char*, with last item being "")
		int x,						//(in) x coordinate of upperleft
		int y,						//(in) y coordinate of upperleft
		int width,					//(in) width of form
		int height,					//(in) height of form
		bool round,					//(in) TRUE=rounded, FALSE=rectangular
		struct cWinApp* ptr_win_app	//(in)application pointer(main_module.m_process)
)
{
	//custom form (pointer only to save stack)
	struct cCustomForm* pCustomForm;
	//rectangle (pointer only)
	struct rect_t* pRect;
	//list(ptr)
	struct cList* pList;
	//item(ptr)
	struct cItem* pItem;
	//index
	int index;
	//return value
	int Result;
	//message pointer
	struct Message* pMsg;

	//allocate
	pCustomForm=(struct cCustomForm*)malloc(sizeof(struct cCustomForm));

	//set up rectangle
	pRect=(struct rect_t*)malloc(sizeof(struct rect_t));
	rect_set(pRect,x,y,width,height);

	//construct
	cCustomForm_ctor(pCustomForm,pRect,title,round,ptr_win_app);

	//allocate the list
	pList=(struct cList*)malloc(sizeof(struct cList));

	//construct the list
	cList_ctor(pList,width-6);

	//add items
	index=0;
	while(strlen(ItemList[index])>0)
	{
		//allocate a new item
		pItem=(struct cItem*)malloc(sizeof(struct cItem));
		//construct item
		cItem_ctor(pItem,width-6,ItemList[index],FALSE,NULL,NULL);
		//add item
		cList_AddItem(pList,pItem);
		//increment index
		index++;
	}

	//add the list to the form
	cCustomForm_AddObj(pCustomForm,pList,0,0);

	//set the modal result to none
	pCustomForm->ModalResult=mrNone;

	//message loop
	while(pCustomForm->ModalResult==mrNone)
	{
		//show form
		cCustomForm_Show(pCustomForm);

		//get a message
		pMsg=cWinApp_get_message(ptr_win_app,0,1,MSG_USER);

		switch(pMsg->msgid)
		{
		case MSG_QUIT:
		case MSG_SHUTUP:
			{
				//return a -2
				Result=-2;
				//change the modal result
				pCustomForm->ModalResult=mrQuit;
			}break;
		case MSG_KEYDOWN:
			{
				//check for esc
				if(Message_get_key_param(pMsg)->scancode==KEY_ESC)
				{
					//result of -1
					Result=-1;
					//change modalresult
					pCustomForm->ModalResult=mrCancel;
					break;
				}
				//check for enter
				if(Message_get_key_param(pMsg)->scancode==KEY_ENTER)
				{
					//result of selected item
					Result=cList_Sel(pList);
					//change modalresult
					pCustomForm->ModalResult=mrOk;
					break;
				}
			}
		default:
			//default processing
			cCustomForm_proc(pCustomForm,pMsg);
		}

		//delete the message
		Message_delete(pMsg);
	}

	//hide form
	cCustomForm_Hide(pCustomForm);

	//clear out the list
	while(cList_GetCount(pList)>0)
	{
		//grab first item
		pItem=cList_get_by_index(pList,0);
		//remove item
		cList_RemObj(pList,pItem);
		//destroy item
		cItem_dtor(pItem,FREE_MEMORY);
	}

	//remove list from form
	cCustomForm_RemObj(pCustomForm,pList);

	//destroy list
	cList_dtor(pList,FREE_MEMORY);

	//destroy form
	cCustomForm_dtor(pCustomForm,FREE_MEMORY);

	//destroy rect
	free(pRect);

	//return the result
	return(Result);
}


#endif