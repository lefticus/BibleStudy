#if defined(__GNUG__) && !defined(__APPLE__)
	#pragma interface "biblestudy.h"
#endif

#ifndef _BIBLESTUDY_H_

	#define _BIBLESTUDY_H_


	#ifdef HAVE_CONFIG_H
		#include <config.h>
	#endif

// 	#include <stdio.h>
// 	#include <stdlib.h>
// 
// 	#include <wx/wx.h>
// 
// 	#include <sword/swmodule.h>
// 	#include <sword/swmgr.h>
// 	#include <sword/plainhtml.h>
// 	#include <sword/versekey.h>


	#define APPTITLE wxT("BibleStudy Software")


	/* Resource IDs */

	/** Menu Item IDs */
	enum
	{
		ID_MenuExit = 1,
		ID_MenuAbout,
		ID_MenuSplitVertically,
		ID_MenuSplitHorizontally,
		ID_MenuRemoveSplit,
		ID_MenuNewTab,
		ID_MenuCloseTab,
		ID_MenuShowHideBookTree,
		ID_MenuNewWindow,
		ID_MenuDetachTab,
		ID_MenuCloseOtherTabs,
		ID_MenuDuplicateTab,
		ID_MenuCloseWindow,
		ID_MenuBibleStudyWhy,
		ID_MenuBibleStudyHow,
		ID_MenuBibleStudyGrow,

		/* Must remain last */
		ID_MenuTopBookOption
	};

	/** Tool bar button IDs */
	enum
	{
		ID_ToolShowHideBookTree = 100,
		ID_ToolLookupKey,
		ID_ToolTextKey,
		ID_ToolSearchKey,
		ID_ToolListKey,
		ID_ToolNewTab,
		ID_ToolRemoveTab,
		ID_ToolForward,
		ID_ToolBackward,
		ID_ToolDropDownRange
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
