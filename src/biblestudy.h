#ifndef _BIBLESTUDY_H_

	#define _BIBLESTUDY_H_

	#ifdef HAVE_CONFIG_H
	#include <config.h>
	#endif

	#include <stdio.h>
	#include <stdlib.h>

	#include <wx/wx.h>

	#include <sword/swmodule.h>
	#include <sword/swmgr.h>
	#include <sword/plainhtml.h>
	#include <versekey.h>
	
	
	#define APPTITLE wxT("BibleStudy Software")
	
	
	/* Resource IDs */
	
	/** Menu Item IDs */
	enum
	{
		ID_MenuQuit = 1,
		ID_MenuAbout,
		ID_MenuSplitVertically,
		ID_MenuSplitHorizontally,
		ID_MenuRemoveSplit,
		ID_MenuNewTab,
		ID_MenuRemoveTab,
		ID_MenuShowHideBookTree,
		ID_MenuTopBookOption,
		ID_MenuNewWindow
	};
	
	/** Tool bar button IDs */
	enum
	{
		ID_ToolShowHideBookTree = 100,
		ID_ToolLookupKey,
		ID_ToolTextKey,
		ID_ToolNewTab,
		ID_ToolRemoveTab
	};
 
	/** General Controls */
	enum
	{
		ID_BookTree = 200,
		ID_BookViewer1
	};
	
	/** Tool Bar IDs */
	enum
	{
		ID_BookViewToolBar = 300
	};
	
#endif
