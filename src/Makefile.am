RESCOMP=@RESCOMP@

if USE_WINDOWS
RESOURCE_FILES = biblestudy_resource.o
WINDOWS_LINKFLAGS = --Wl,--subsystem,windows -mwindows
endif

biblestudy_resource.o: biblestudy.rc
	$(RESCOMP) -i $(srcdir)/biblestudy.rc -o biblestudy_resource.o \
	--include-dir $(srcdir) @RC_WX_INCLUDES@ \
	--define __WIN32__ --define __WIN95__ --define __GNUWIN32__


bin_PROGRAMS = biblestudy
biblestudy_SOURCES = biblestudy.cpp biblestudy.h BibleStudyApp.cpp BibleStudyApp.h BibleStudyMainFrame.cpp BibleStudyMainFrame.h BookModule.cpp BookModule.h BookTreeCtrl.cpp BookTreeCtrl.h BookViewCtrl.cpp BookViewCtrl.h BookViewSplitterCtrl.cpp BookViewSplitterCtrl.h SwordTools.cpp SwordTools.h BookViewToolBar.h BookViewToolBar.cpp BibleStudyLanguages.h BibleStudyLanguages.cpp BookViewEventHandler.h BookViewEventHandler.cpp DropDownEventHandler.h DropDownEventHandler.cpp BibleStudyWizard.h BibleStudyWizard.cpp BookViewHtml.h BookViewHtml.cpp HTMLToolTip.h HTMLToolTip.cpp DropDownCtrl.h DropDownCtrl.cpp




# set the include path found by configure
INCLUDES = -I/usr/local/include/sword -I/usr/include/sword $(all_includes)

# the library search path.
biblestudy_LDFLAGS = $(all_libraries) $(WINDOWS_LINKFLAGS) `wx-config --libs`
biblestudy_LDADD = $(RESOURCE_FILES) -lsword 


AM_CFLAGS =
AM_CXXFLAGS = `wx-config --cxxflags` -Wall
AM_FFLAGS =
SUBDIRS =
