//
// File List Form by Ernest Pazera
//
// BubbleSort added by Gregory Smith
// 10/8/2001
//

#ifndef __FILELISTFORM_C__
#define __FILELISTFORM_C__

#include "Cywin.h"
#include "FileListForm.h"

struct namesize
{
    char *s;
    long size;
};

struct cItem* cItem_CreateFromNamesize(struct namesize *namesizep);

static struct namesize *namesizep = 0;
static int n = 0;

static void bubblesort(struct namesize *namesizep, int n)
{
    int i, j;
    struct namesize tmp;

    for(i=0; i<(n-1); i++)
    {
        for (j=i+1; j<n; j++)
        {
            if (strcmp(namesizep[i].s, namesizep[j].s)>0)
            {
                tmp = namesizep[i];
                namesizep[i] = namesizep[j];
                namesizep[j] = tmp;
            }
        }
    }
}

static void add_namesize(struct namesize **namesizepp, int *n, char *s, long size)
{
    struct namesize *tmp;

    if (*namesizepp)
    {
        tmp = *namesizepp;
        (*n)++;
        *namesizepp = malloc((*n)*sizeof(struct namesize));
        memcpy(*namesizepp, tmp, ((*n)-1)*sizeof(struct namesize));
        free(tmp);
    }
    else
    {
        *n=1;
        *namesizepp = malloc((*n)*sizeof(struct namesize));
    }
    (*namesizepp)[(*n)-1].s = strdup(s);
    (*namesizepp)[(*n)-1].size = size;
}

static void free_namesize(struct namesize *namesizep, int n)
{
        int i;

        for (i=0; i<n; i++)
        {
                free(namesizep[i].s);
        }
        free(namesizep);
}

int FileListForm(
	char* title,				//(in)title of the form
	char* filter,				//(in)filter for file list
	char* filename,				//(out)filename selected
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
	//return value
	int Result;
	//message pointer
	struct Message* pMsg;
	//file finder
	struct FileFind* pFileFind;
	//file information
	struct File* pFile;
        int i;

	//trun on the hourglass
	set_hourglass(TRUE);

	//allocate
	pCustomForm=(struct cCustomForm*)malloc(sizeof(struct cCustomForm));

	//set up rectangle
	pRect=(struct rect_t*)malloc(sizeof(struct rect_t));
	rect_set(pRect,-2,-2,164,104);

	//construct
	cCustomForm_ctor(pCustomForm,pRect,title,FALSE,ptr_win_app);

	//allocate the list
	pList=(struct cList*)malloc(sizeof(struct cList));

	//construct the list
	cList_ctor(pList,158);

	//allocate file finder
	pFileFind=(struct FileFind*)malloc(sizeof(struct FileFind));

	//allocate file
	pFile=(struct File*)malloc(sizeof(struct File));

	//start finding files
	FileFind_ctor(pFileFind,pFile,filter);

	//add items
    n=0;
	while(FileFind_has_more_elements(pFileFind))//continue until no more elements
	{
        //find next element
        if(FileFind_next_element(pFileFind))
        {
                //create item
                add_namesize(&namesizep, &n, pFileFind->fileinfo->name, pFileFind->fileinfo->size);
        }
    }
    // sort the namesize
    bubblesort(namesizep, n);

    //add items to list
    for(i=0; i<n; i++)
	{
        pItem=cItem_CreateFromNamesize(&namesizep[i]);
        cList_AddItem(pList,pItem);
	}

	//destroy fileinfo
	File_dtor(pFile,FREE_MEMORY);

	//destroy filefind
	FileFind_dtor(pFileFind,FREE_MEMORY);

	//add the list to the form
	cCustomForm_AddObj(pCustomForm,pList,0,0);

	//set the modal result to none
	pCustomForm->ModalResult=mrNone;

	//turn the hourglass off
	set_hourglass(FALSE);

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
					//get item
                    pItem=cList_get_by_index(pList,Result);
					//copy name to filename
                    strcpy(filename,cItem_GetTitle(pItem));
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

    // free the namesize structure
    free_namesize(namesizep, n);

	//return the result
	return(Result);
}

struct cItem* cItem_CreateFromNamesize(struct namesize *namesizep)
{
	//temp
	char temp[10];
	//item pointer
	struct cItem* pItem;
	//allocate item
	pItem=(struct cItem*)malloc(sizeof(struct cItem));
	//fill out size
    sprintf(temp,"%u,%uk",namesizep->size/1024,(namesizep->size%1024)*10/1024);
	//construct item
    cItem_ctor(pItem,158,namesizep->s,FALSE,temp,NULL);
	//return the new item
	return(pItem);
}


#endif
