# Microsoft Developer Studio Project File - Name="IcqLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=IcqLib - Win32 BC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "icqlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "icqlib.mak" CFG="IcqLib - Win32 BC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IcqLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "IcqLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "IcqLib - Win32 BC" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IcqLib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "BYTE_ORDER_LITTLE_ENDIAN" /D "_MSVC_" /D __STDC__=1 /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "IcqLib - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "BYTE_ORDER_LITTLE_ENDIAN" /D "_MSVC_" /D __STDC__=1 /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "IcqLib - Win32 BC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "IcqLib___Win32_BC"
# PROP BASE Intermediate_Dir "IcqLib___Win32_BC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "IcqLib___Win32_BC"
# PROP Intermediate_Dir "IcqLib___Win32_BC"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "BYTE_ORDER_LITTLE_ENDIAN" /D "_MSVC_" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "BYTE_ORDER_LITTLE_ENDIAN" /D "_MSVC_" /D __STDC__=1 /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "IcqLib - Win32 Release"
# Name "IcqLib - Win32 Debug"
# Name "IcqLib - Win32 BC"
# Begin Group "Sources"

# PROP Default_Filter "*.c"
# Begin Source File

SOURCE=.\chatsession.c
# End Source File
# Begin Source File

SOURCE=.\contacts.c
# End Source File
# Begin Source File

SOURCE=.\cyrillic.c
# End Source File
# Begin Source File

SOURCE=.\eventhandle.c
# End Source File
# Begin Source File

SOURCE=.\filesession.c
# End Source File
# Begin Source File

SOURCE=.\icqbyteorder.c
# End Source File
# Begin Source File

SOURCE=.\icqevent.c
# End Source File
# Begin Source File

SOURCE=.\icqlib.c
# End Source File
# Begin Source File

SOURCE=.\icqpacket.c
# End Source File
# Begin Source File

SOURCE=.\list.c
# End Source File
# Begin Source File

SOURCE=.\proxy.c
# End Source File
# Begin Source File

SOURCE=.\queue.c
# End Source File
# Begin Source File

SOURCE=.\socketmanager.c
# End Source File
# Begin Source File

SOURCE=.\stdpackets.c
# End Source File
# Begin Source File

SOURCE=.\tcp.c
# End Source File
# Begin Source File

SOURCE=.\tcpchathandle.c
# End Source File
# Begin Source File

SOURCE=.\tcpfilehandle.c
# End Source File
# Begin Source File

SOURCE=.\tcphandle.c
# End Source File
# Begin Source File

SOURCE=.\tcplink.c
# End Source File
# Begin Source File

SOURCE=.\timeout.c
# End Source File
# Begin Source File

SOURCE=.\udp.c
# End Source File
# Begin Source File

SOURCE=.\udphandle.c
# End Source File
# Begin Source File

SOURCE=.\util.c
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\chatsession.h
# End Source File
# Begin Source File

SOURCE=.\contacts.h
# End Source File
# Begin Source File

SOURCE=.\eventhandle.h
# End Source File
# Begin Source File

SOURCE=.\filesession.h
# End Source File
# Begin Source File

SOURCE=.\icq.h
# End Source File
# Begin Source File

SOURCE=.\icqbyteorder.h
# End Source File
# Begin Source File

SOURCE=.\icqevent.h
# End Source File
# Begin Source File

SOURCE=.\icqlib.h
# End Source File
# Begin Source File

SOURCE=.\icqpacket.h
# End Source File
# Begin Source File

SOURCE=.\icqtypes.h
# End Source File
# Begin Source File

SOURCE=.\list.h
# End Source File
# Begin Source File

SOURCE=.\queue.h
# End Source File
# Begin Source File

SOURCE=.\socketmanager.h
# End Source File
# Begin Source File

SOURCE=.\stdpackets.h
# End Source File
# Begin Source File

SOURCE=.\tcp.h
# End Source File
# Begin Source File

SOURCE=.\tcplink.h
# End Source File
# Begin Source File

SOURCE=.\timeout.h
# End Source File
# Begin Source File

SOURCE=.\udp.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# End Group
# End Target
# End Project
