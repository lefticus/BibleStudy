bin_PROGRAMS = biblestudy
biblestudy_SOURCES = biblestudy.cpp biblestudy.h BibleStudyApp.cpp BibleStudyApp.h BibleStudyMainFrame.cpp BibleStudyMainFrame.h BookModule.cpp BookModule.h BookTreeCtrl.cpp BookTreeCtrl.h BookViewCtrl.cpp BookViewCtrl.h BookViewSplitterCtrl.cpp BookViewSplitterCtrl.h SwordTools.cpp SwordTools.h TestSword.cpp TestSword.h BookViewToolBar.h BookViewToolBar.cpp BibleStudyLanguages.h BibleStudyLanguages.cpp

# set the include path found by configure
INCLUDES = -I/usr/include/sword $(all_includes)

# the library search path.
biblestudy_LDFLAGS = $(all_libraries) `wx-config --libs`
biblestudy_DEPENDENCIES = 
biblestudy_LDADD = -lsword
AM_CFLAGS = 
AM_CXXFLAGS = -ggdb `wx-config --cxxflags`
AM_FFLAGS = 
SUBDIRS = 
