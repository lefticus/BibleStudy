# Microsoft Developer Studio Project File - Name="biblestudy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=biblestudy - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "biblestudy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "biblestudy.mak" CFG="biblestudy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "biblestudy - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "biblestudy - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "biblestudy - Win32 Release"

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
# ADD CPP /nologo /MD /W4 /GX /O2 /I "$(WXWIN)/lib/msw" /I "$(WXWIN)/include" /I "$(WXWIN)/contrib/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_WINDOWS" /D WINVER=0x400 /D "_MT" /D wxUSE_GUI=1 /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /i "$(WXWIN)/include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib wsock32.lib zlib.lib regex.lib png.lib jpeg.lib tiff.lib wxmsw.lib wxxrc.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(WXWIN)/lib" /libpath:"$(WXWIN)/contrib/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "biblestudy - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /Gm /GX /Zi /Od /I "$(WXWIN)/lib/mswud" /I "$(WXWIN)/include" /I "$(WXWIN)/contrib/include" /I "../../sword/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_LIB" /D "REGEX_MALLOC" /D "_WINDOWS" /D WINVER=0x400 /D "_MT" /D wxUSE_GUI=1 /D "__WXDEBUG__" /D WXDEBUG=1 /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /i "$(WXWIN)/include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib wsock32.lib zlibd.lib regexd.lib pngd.lib jpegd.lib tiffd.lib wxmswd.lib libswordvc6d.lib /nologo /subsystem:windows /debug /machine:I386 /out:"./biblestudyd.exe" /pdbtype:sept /libpath:"$(WXWIN)/lib" /libpath:"$(WXWIN)/contrib/lib" /libpath:"../../sword/lib" /libpath:"../../icu-sword/lib" /verbose:lib
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "biblestudy - Win32 Release"
# Name "biblestudy - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\biblestudy.cpp
# End Source File
# Begin Source File

SOURCE=.\biblestudy.rc
# End Source File
# Begin Source File

SOURCE=..\src\BibleStudyApp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BibleStudyLanguages.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BibleStudyMainFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BibleStudyWizard.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BookModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BookTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BookViewCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BookViewEventHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BookViewHtml.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BookViewSplitterCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\BookViewToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\DropDownCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\DropDownEventHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\HTMLToolTip.cpp
# End Source File
# Begin Source File

SOURCE=..\src\SwordTools.cpp
# End Source File
# Begin Source File

SOURCE=..\src\TestSword.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\biblestudy.h
# End Source File
# Begin Source File

SOURCE=..\src\BibleStudyApp.h
# End Source File
# Begin Source File

SOURCE=..\src\BibleStudyLanguages.h
# End Source File
# Begin Source File

SOURCE=..\src\BibleStudyMainFrame.h
# End Source File
# Begin Source File

SOURCE=..\src\BibleStudyWizard.h
# End Source File
# Begin Source File

SOURCE=..\src\BookModule.h
# End Source File
# Begin Source File

SOURCE=..\src\BookTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=..\src\BookViewCtrl.h
# End Source File
# Begin Source File

SOURCE=..\src\BookViewEventHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\BookViewHtml.h
# End Source File
# Begin Source File

SOURCE=..\src\BookViewSplitterCtrl.h
# End Source File
# Begin Source File

SOURCE=..\src\BookViewToolBar.h
# End Source File
# Begin Source File

SOURCE=..\src\DropDownCtrl.h
# End Source File
# Begin Source File

SOURCE=..\src\DropDownEventHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\HTMLToolTip.h
# End Source File
# Begin Source File

SOURCE=..\src\SwordTools.h
# End Source File
# Begin Source File

SOURCE=..\src\TestSword.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\biblestudy.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\blank.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\bullseye.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\cdrom.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\computer.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\drive.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\file1.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\floppy.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\folder1.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\folder2.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\hand.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\magnif1.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\noentry.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\pbrush.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\pencil.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\pntleft.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\pntright.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\query.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\removble.ico
# End Source File
# Begin Source File

SOURCE=.\wx\msw\rightarr.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\roller.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\size.cur
# End Source File
# Begin Source File

SOURCE=.\wx\msw\watch1.cur
# End Source File
# End Group
# Begin Source File

SOURCE=..\icons\addtab.xpm
# End Source File
# Begin Source File

SOURCE=..\icons\book.xpm
# End Source File
# Begin Source File

SOURCE=..\icons\booktree.xpm
# End Source File
# Begin Source File

SOURCE=..\icons\closedfolder.xpm
# End Source File
# Begin Source File

SOURCE=..\icons\lookup.xpm
# End Source File
# Begin Source File

SOURCE=.\makefile
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\makefile.gtk
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\makefile.mtf
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\icons\openfolder.xpm
# End Source File
# Begin Source File

SOURCE=..\icons\removetab.xpm
# End Source File
# End Target
# End Project
