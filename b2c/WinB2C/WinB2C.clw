; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWinB2CApp
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WinB2C.h"
LastPage=0

ClassCount=8
Class1=CWinB2CApp
Class2=CWinB2CDoc
Class3=CWinB2CView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_WINB2CTYPE
Resource3=IDR_WINB2CTYPE_CNTR_IP
Class5=CChildFrame
Class6=CAboutDlg
Class7=CBuildTree
Class8=CMyTreeCtrl
Resource4=IDR_MAINFRAME
Resource5=IDD_BUILDTREE_DIALOG

[CLS:CWinB2CApp]
Type=0
HeaderFile=WinB2C.h
ImplementationFile=WinB2C.cpp
Filter=N
LastObject=CWinB2CApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CWinB2CDoc]
Type=0
HeaderFile=WinB2CDoc.h
ImplementationFile=WinB2CDoc.cpp
Filter=N
LastObject=CWinB2CDoc

[CLS:CWinB2CView]
Type=0
HeaderFile=WinB2CView.h
ImplementationFile=WinB2CView.cpp
Filter=C
LastObject=CWinB2CView
BaseClass=CRichEditView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=WinB2C.cpp
ImplementationFile=WinB2C.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_PROJECT_VIEW
Command9=ID_PROJECT_NEW
Command10=ID_PROJECT_OPEN
Command11=ID_PROJECT_SAVE
Command12=ID_PROJECT_SAVEAS
Command13=ID_PROJECT_CLOSE
Command14=ID_PROJECT_VIEW
Command15=ID_APP_ABOUT
CommandCount=15

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_WINB2CTYPE]
Type=1
Class=CWinB2CView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_PASTE_SPECIAL
Command16=ID_EDIT_SELECT_ALL
Command17=ID_EDIT_FIND
Command18=ID_EDIT_REPEAT
Command19=ID_EDIT_REPLACE
Command20=ID_OLE_INSERT_NEW
Command21=ID_OLE_EDIT_LINKS
Command22=ID_OLE_EDIT_PROPERTIES
Command23=ID_OLE_VERB_FIRST
Command24=ID_VIEW_TOOLBAR
Command25=ID_VIEW_STATUS_BAR
Command26=IDD_PROJECT_VIEW
Command27=ID_VIEW_FUNCTIONS
Command28=ID_PROJECT_NEW
Command29=ID_PROJECT_OPEN
Command30=ID_PROJECT_SAVE
Command31=ID_PROJECT_SAVEAS
Command32=ID_PROJECT_CLOSE
Command33=ID_PROJECT_VIEW
Command34=ID_WINDOW_NEW
Command35=ID_WINDOW_CASCADE
Command36=ID_WINDOW_TILE_HORZ
Command37=ID_WINDOW_ARRANGE
Command38=ID_APP_ABOUT
CommandCount=38

[MNU:IDR_WINB2CTYPE_CNTR_IP]
Type=1
Class=CWinB2CView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_WINDOW_NEW
Command12=ID_WINDOW_CASCADE
Command13=ID_WINDOW_TILE_HORZ
Command14=ID_WINDOW_ARRANGE
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_SELECT_ALL
Command10=ID_EDIT_FIND
Command11=ID_EDIT_REPEAT
Command12=ID_EDIT_REPLACE
Command13=ID_OLE_EDIT_PROPERTIES
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_NEXT_PANE
Command19=ID_PREV_PANE
Command20=ID_CANCEL_EDIT_CNTR
CommandCount=20

[ACL:IDR_WINB2CTYPE_CNTR_IP]
Type=1
Class=CWinB2CView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[DLG:IDD_BUILDTREE_DIALOG]
Type=1
Class=CBuildTree
ControlCount=28
Control1=IDC_PROJECT_BUILDTREE,SysTreeView32,1350635551
Control2=IDC_PROJECT_AUTHOR,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_PROJECT_COPYRIGHT,edit,1350631552
Control5=IDC_STATIC,static,1342308354
Control6=IDC_PROJECT_CYOSVERSION,edit,1350631552
Control7=IDC_STATIC,static,1342308354
Control8=IDC_PROJECT_NAME,edit,1350631552
Control9=IDC_STATIC,static,1342308354
Control10=IDC_PROJECT_OUTPUT,edit,1350631552
Control11=IDC_STATIC,static,1342308354
Control12=IDC_PROJECT_KEEP,button,1342242851
Control13=IDC_PROJECT_PATH_BUTTON,button,1342242816
Control14=IDC_PROJECT_APPTYPE,combobox,1344340226
Control15=IDC_PROJECT_SDK20,button,1342308393
Control16=IDC_PROJECT_SDK30,button,1342308393
Control17=IDC_PROJECT_VERSION,edit,1350631552
Control18=IDC_STATIC,static,1342308354
Control19=IDC_STATIC,button,1342177287
Control20=IDC_PROJECT_HELP_TEXT,edit,1352728580
Control21=IDC_STATIC,button,1342177287
Control22=IDC_PROJECT_SPLASH_TEXT,edit,1352728580
Control23=IDC_STATIC,static,1342308354
Control24=IDC_STATIC,button,1342177287
Control25=IDC_STATIC,button,1342177287
Control26=IDC_PROJECT_PATH,edit,1350631552
Control27=IDC_PROJECT_ENVIRONMENT,edit,1352728580
Control28=IDC_STATIC,button,1342177287

[CLS:CBuildTree]
Type=0
HeaderFile=BuildTree.h
ImplementationFile=BuildTree.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CBuildTree

[CLS:CMyTreeCtrl]
Type=0
HeaderFile=mytreectrl.h
ImplementationFile=mytreectrl.cpp
BaseClass=CTreeCtrl
LastObject=CMyTreeCtrl

