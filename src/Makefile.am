RESCOMP=@RESCOMP@

if USE_WINDOWS
RESOURCE_FILES = biblestudy_resource.o
WINDOWS_LINKFLAGS = --Wl,--subsystem,windows -mwindows
endif

biblestudy_resource.o: biblestudy.rc
	$(RESCOMP) -i $(srcdir)/biblestudy.rc -o biblestudy_resource.o \
	--include-dir $(srcdir) @RC_WX_INCLUDES@ \
	--define __WIN32__ --define __WIN95__ --define __GNUWIN32__

AM_CXXFLAGS = `wx-config --cxxflags ` -Wall -D_WX_WIN

bin_PROGRAMS = biblestudy
biblestudy_SOURCES = biblestudy.cpp dirtraversersimple.cpp BookViewCtrl.cpp BookViewSplitterCtrl.cpp BookTreeCtrl.cpp BibleStudyMainFrame.cpp BibleStudyApp.cpp BookModule.cpp SwordTools.cpp BookViewToolBar.cpp BibleStudyLanguages.cpp BookViewEventHandler.cpp DropDownEventHandler.cpp BibleStudyWizard.cpp BookViewHtml.cpp HTMLToolTip.cpp DropDownCtrl.cpp BookList.cpp PrefsDialog.cpp ReadingPlannerToolBar.cpp ReadingPlanWizard.cpp bsmarkupfiltmgr.cpp bsosishtmlhref.cpp bsgbfhtmlhref.cpp bsthmlhtmlhref.cpp bsurl.cpp


# set the include path found by configure
#INCLUDES = $(all_includes) -I/usr/include/sword -I/usr/local/include/sword

# the library search path.
biblestudy_LDFLAGS = $(WINDOWS_LINKFLAGS) `wx-config --libs @WX_LIBS_ARGS@` -D_WX_WIN


