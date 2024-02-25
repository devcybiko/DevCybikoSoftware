# Microsoft Developer Studio Project File - Name="b2c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=b2c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "b2c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "b2c.mak" CFG="b2c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "b2c - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "b2c - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "b2c - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "b2c - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "b2c - Win32 Release"
# Name "b2c - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\b2c.h
# End Source File
# Begin Source File

SOURCE=.\b2cy.h
# End Source File
# Begin Source File

SOURCE=.\b3dcollision.h
# End Source File
# Begin Source File

SOURCE=.\b3dget.h
# End Source File
# Begin Source File

SOURCE=.\b3dmove.h
# End Source File
# Begin Source File

SOURCE=.\b3dredraw.h
# End Source File
# Begin Source File

SOURCE=.\b3drmove.h
# End Source File
# Begin Source File

SOURCE=.\b3droom.h
# End Source File
# Begin Source File

SOURCE=.\b3dsprite.h
# End Source File
# Begin Source File

SOURCE=.\b3dwall.h
# End Source File
# Begin Source File

SOURCE=.\bbeep.h
# End Source File
# Begin Source File

SOURCE=.\bbody.h
# End Source File
# Begin Source File

SOURCE=.\bchar.h
# End Source File
# Begin Source File

SOURCE=.\bcircfill.h
# End Source File
# Begin Source File

SOURCE=.\bcircle.h
# End Source File
# Begin Source File

SOURCE=.\bclose.h
# End Source File
# Begin Source File

SOURCE=.\bcls.h
# End Source File
# Begin Source File

SOURCE=.\bcollision.h
# End Source File
# Begin Source File

SOURCE=.\bdialog.h
# End Source File
# Begin Source File

SOURCE=.\bdim.h
# End Source File
# Begin Source File

SOURCE=.\belse.h
# End Source File
# Begin Source File

SOURCE=.\belseif.h
# End Source File
# Begin Source File

SOURCE=.\beof.h
# End Source File
# Begin Source File

SOURCE=.\bexists.h
# End Source File
# Begin Source File

SOURCE=.\bexit.h
# End Source File
# Begin Source File

SOURCE=.\bexitfunction.h
# End Source File
# Begin Source File

SOURCE=.\bexitprogram.h
# End Source File
# Begin Source File

SOURCE=.\bexpr.h
# End Source File
# Begin Source File

SOURCE=.\bfilelist.h
# End Source File
# Begin Source File

SOURCE=.\bfindfile.h
# End Source File
# Begin Source File

SOURCE=.\bfont.h
# End Source File
# Begin Source File

SOURCE=.\bfor.h
# End Source File
# Begin Source File

SOURCE=.\bfunccall.h
# End Source File
# Begin Source File

SOURCE=.\bfunction.h
# End Source File
# Begin Source File

SOURCE=.\bget.h
# End Source File
# Begin Source File

SOURCE=.\bgetchar.h
# End Source File
# Begin Source File

SOURCE=.\bgetkey.h
# End Source File
# Begin Source File

SOURCE=.\bgoto.h
# End Source File
# Begin Source File

SOURCE=.\bif.h
# End Source File
# Begin Source File

SOURCE=.\bink.h
# End Source File
# Begin Source File

SOURCE=.\binline.h
# End Source File
# Begin Source File

SOURCE=.\binput.h
# End Source File
# Begin Source File

SOURCE=.\binputxy.h
# End Source File
# Begin Source File

SOURCE=.\bkey.h
# End Source File
# Begin Source File

SOURCE=.\bkeyclick.h
# End Source File
# Begin Source File

SOURCE=.\blabel.h
# End Source File
# Begin Source File

SOURCE=.\blen.h
# End Source File
# Begin Source File

SOURCE=.\bline.h
# End Source File
# Begin Source File

SOURCE=.\blist.h
# End Source File
# Begin Source File

SOURCE=.\bload.h
# End Source File
# Begin Source File

SOURCE=.\bmath.h
# End Source File
# Begin Source File

SOURCE=.\bmenu.h
# End Source File
# Begin Source File

SOURCE=.\bmenuxy.h
# End Source File
# Begin Source File

SOURCE=.\bmid.h
# End Source File
# Begin Source File

SOURCE=.\bmove.h
# End Source File
# Begin Source File

SOURCE=.\bmusic.h
# End Source File
# Begin Source File

SOURCE=.\bnextfile.h
# End Source File
# Begin Source File

SOURCE=.\bongosub.h
# End Source File
# Begin Source File

SOURCE=.\bongoto.h
# End Source File
# Begin Source File

SOURCE=.\bop.h
# End Source File
# Begin Source File

SOURCE=.\bopen.h
# End Source File
# Begin Source File

SOURCE=.\boutline.h
# End Source File
# Begin Source File

SOURCE=.\bpage.h
# End Source File
# Begin Source File

SOURCE=.\bpagecopy.h
# End Source File
# Begin Source File

SOURCE=.\bpaper.h
# End Source File
# Begin Source File

SOURCE=.\bparam.h
# End Source File
# Begin Source File

SOURCE=.\bpoint.h
# End Source File
# Begin Source File

SOURCE=.\bprint.h
# End Source File
# Begin Source File

SOURCE=.\bprintno.h
# End Source File
# Begin Source File

SOURCE=.\bprintxy.h
# End Source File
# Begin Source File

SOURCE=.\bprogram.h
# End Source File
# Begin Source File

SOURCE=.\bput.h
# End Source File
# Begin Source File

SOURCE=.\brect.h
# End Source File
# Begin Source File

SOURCE=.\brectfill.h
# End Source File
# Begin Source File

SOURCE=.\bredraw.h
# End Source File
# Begin Source File

SOURCE=.\bremove.h
# End Source File
# Begin Source File

SOURCE=.\brename.h
# End Source File
# Begin Source File

SOURCE=.\bright.h
# End Source File
# Begin Source File

SOURCE=.\bscore.h
# End Source File
# Begin Source File

SOURCE=.\bsendmessage.h
# End Source File
# Begin Source File

SOURCE=.\bsprint.h
# End Source File
# Begin Source File

SOURCE=.\bsprite.h
# End Source File
# Begin Source File

SOURCE=.\bsprite_get.h
# End Source File
# Begin Source File

SOURCE=.\bstatement.h
# End Source File
# Begin Source File

SOURCE=.\bterm.h
# End Source File
# Begin Source File

SOURCE=.\bthen.h
# End Source File
# Begin Source File

SOURCE=.\btocyid.h
# End Source File
# Begin Source File

SOURCE=.\btokenize.h
# End Source File
# Begin Source File

SOURCE=.\btouser.h
# End Source File
# Begin Source File

SOURCE=.\btype.h
# End Source File
# Begin Source File

SOURCE=.\busermenu.h
# End Source File
# Begin Source File

SOURCE=.\bvibrate.h
# End Source File
# Begin Source File

SOURCE=.\bwait.h
# End Source File
# Begin Source File

SOURCE=.\bwhile.h
# End Source File
# Begin Source File

SOURCE=.\bwrap.h
# End Source File
# Begin Source File

SOURCE=.\node.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\b2c.c
# End Source File
# Begin Source File

SOURCE=.\b2cl.c

!IF  "$(CFG)" == "b2c - Win32 Release"

!ELSEIF  "$(CFG)" == "b2c - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\b2cy.c
# End Source File
# Begin Source File

SOURCE=.\b3dcollision.c
# End Source File
# Begin Source File

SOURCE=.\b3dget.c
# End Source File
# Begin Source File

SOURCE=.\b3dmove.c
# End Source File
# Begin Source File

SOURCE=.\b3dredraw.c
# End Source File
# Begin Source File

SOURCE=.\b3drmove.c
# End Source File
# Begin Source File

SOURCE=.\b3droom.c
# End Source File
# Begin Source File

SOURCE=.\b3dsprite.c
# End Source File
# Begin Source File

SOURCE=.\b3dwall.c
# End Source File
# Begin Source File

SOURCE=.\bbeep.c
# End Source File
# Begin Source File

SOURCE=.\bbody.c
# End Source File
# Begin Source File

SOURCE=.\bchar.c
# End Source File
# Begin Source File

SOURCE=.\bcircfill.c
# End Source File
# Begin Source File

SOURCE=.\bcircle.c
# End Source File
# Begin Source File

SOURCE=.\bclose.c
# End Source File
# Begin Source File

SOURCE=.\bcls.c
# End Source File
# Begin Source File

SOURCE=.\bcollision.c
# End Source File
# Begin Source File

SOURCE=.\bdialog.c
# End Source File
# Begin Source File

SOURCE=.\bdim.c
# End Source File
# Begin Source File

SOURCE=.\belse.c
# End Source File
# Begin Source File

SOURCE=.\belseif.c
# End Source File
# Begin Source File

SOURCE=.\beof.c
# End Source File
# Begin Source File

SOURCE=.\bexists.c
# End Source File
# Begin Source File

SOURCE=.\bexit.c
# End Source File
# Begin Source File

SOURCE=.\bexitfunction.c
# End Source File
# Begin Source File

SOURCE=.\bexitprogram.c
# End Source File
# Begin Source File

SOURCE=.\bexpr.c
# End Source File
# Begin Source File

SOURCE=.\bfilelist.c
# End Source File
# Begin Source File

SOURCE=.\bfindfile.c
# End Source File
# Begin Source File

SOURCE=.\bfont.c
# End Source File
# Begin Source File

SOURCE=.\bfor.c
# End Source File
# Begin Source File

SOURCE=.\bfunccall.c
# End Source File
# Begin Source File

SOURCE=.\bfunction.c
# End Source File
# Begin Source File

SOURCE=.\bget.c
# End Source File
# Begin Source File

SOURCE=.\bgetchar.c
# End Source File
# Begin Source File

SOURCE=.\bgetkey.c
# End Source File
# Begin Source File

SOURCE=.\bgoto.c
# End Source File
# Begin Source File

SOURCE=.\bif.c
# End Source File
# Begin Source File

SOURCE=.\bink.c
# End Source File
# Begin Source File

SOURCE=.\binline.c
# End Source File
# Begin Source File

SOURCE=.\binput.c
# End Source File
# Begin Source File

SOURCE=.\binputxy.c
# End Source File
# Begin Source File

SOURCE=.\bkey.c
# End Source File
# Begin Source File

SOURCE=.\bkeyclick.c
# End Source File
# Begin Source File

SOURCE=.\blabel.c
# End Source File
# Begin Source File

SOURCE=.\blen.c
# End Source File
# Begin Source File

SOURCE=.\bline.c
# End Source File
# Begin Source File

SOURCE=.\blist.c
# End Source File
# Begin Source File

SOURCE=.\bload.c
# End Source File
# Begin Source File

SOURCE=.\bmath.c
# End Source File
# Begin Source File

SOURCE=.\bmenu.c
# End Source File
# Begin Source File

SOURCE=.\bmenuxy.c
# End Source File
# Begin Source File

SOURCE=.\bmid.c
# End Source File
# Begin Source File

SOURCE=.\bmove.c
# End Source File
# Begin Source File

SOURCE=.\bmusic.c
# End Source File
# Begin Source File

SOURCE=.\bnextfile.c
# End Source File
# Begin Source File

SOURCE=.\bongosub.c
# End Source File
# Begin Source File

SOURCE=.\bongoto.c
# End Source File
# Begin Source File

SOURCE=.\bop.c
# End Source File
# Begin Source File

SOURCE=.\bopen.c
# End Source File
# Begin Source File

SOURCE=.\boutline.c
# End Source File
# Begin Source File

SOURCE=.\bpage.c
# End Source File
# Begin Source File

SOURCE=.\bpagecopy.c
# End Source File
# Begin Source File

SOURCE=.\bpaper.c
# End Source File
# Begin Source File

SOURCE=.\bparam.c
# End Source File
# Begin Source File

SOURCE=.\bpoint.c
# End Source File
# Begin Source File

SOURCE=.\bprint.c
# End Source File
# Begin Source File

SOURCE=.\bprintno.c
# End Source File
# Begin Source File

SOURCE=.\bprintxy.c
# End Source File
# Begin Source File

SOURCE=.\bprogram.c
# End Source File
# Begin Source File

SOURCE=.\bput.c
# End Source File
# Begin Source File

SOURCE=.\brect.c
# End Source File
# Begin Source File

SOURCE=.\brectfill.c
# End Source File
# Begin Source File

SOURCE=.\bredraw.c
# End Source File
# Begin Source File

SOURCE=.\bremove.c
# End Source File
# Begin Source File

SOURCE=.\brename.c
# End Source File
# Begin Source File

SOURCE=.\bright.c
# End Source File
# Begin Source File

SOURCE=.\bscore.c
# End Source File
# Begin Source File

SOURCE=.\bsendmessage.c
# End Source File
# Begin Source File

SOURCE=.\bsprint.c
# End Source File
# Begin Source File

SOURCE=.\bsprite.c
# End Source File
# Begin Source File

SOURCE=.\bsprite_get.c
# End Source File
# Begin Source File

SOURCE=.\bstatement.c
# End Source File
# Begin Source File

SOURCE=.\bterm.c
# End Source File
# Begin Source File

SOURCE=.\bthen.c
# End Source File
# Begin Source File

SOURCE=.\btocyid.c
# End Source File
# Begin Source File

SOURCE=.\btokenize.c
# End Source File
# Begin Source File

SOURCE=.\btouser.c
# End Source File
# Begin Source File

SOURCE=.\btype.c
# End Source File
# Begin Source File

SOURCE=.\busermenu.c
# End Source File
# Begin Source File

SOURCE=.\bvibrate.c
# End Source File
# Begin Source File

SOURCE=.\bwait.c
# End Source File
# Begin Source File

SOURCE=.\bwhile.c
# End Source File
# Begin Source File

SOURCE=.\bwrap.c
# End Source File
# Begin Source File

SOURCE=.\node.c
# End Source File
# Begin Source File

SOURCE=.\yywrap.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\b2cl.l

!IF  "$(CFG)" == "b2c - Win32 Release"

USERDEP__B2CL_="b2cy.h"	
# Begin Custom Build
InputPath=.\b2cl.l

"b2cl.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -i b2cl.l 
	copy lex.yy.c b2cl.c 
	del lex.yy.c 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "b2c - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\b2cl.l

"b2cl.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -ob2cl.c b2cl.l

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\b2cy.y

!IF  "$(CFG)" == "b2c - Win32 Release"

# Begin Custom Build
InputPath=.\b2cy.y

BuildCmds= \
	bison b2cy.y -o b2cy.c -d

"b2cy.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"b2cy.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "b2c - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\b2cy.y

"b2cy.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bison -d b2cy.y -o b2cy.c

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
