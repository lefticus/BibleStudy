
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BIBLESTUDY_H_
#define _BIBLESTUDY_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define APPTITLE wxT("BibleStudy")

/* Resource IDs */

/** Menu Item IDs */
enum {
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
		ID_MenuReadingPlannerWiz,
		ID_MenuBibleStudyWhy,
		ID_MenuBibleStudyHow,
		ID_MenuBibleStudyGrow,
		ID_MenuShowStartPage,
		ID_MenuShowReadingPlanPage,
		ID_MenuShowHideRPToolBar,
		ID_MenuPrefs,

		/* Must remain last */
		ID_MenuTopBookOption
};

/** Tool bar button IDs */
enum {
		ID_ToolShowHideBookTree = 100,
		ID_ToolLookupKey,
		ID_ToolTextKey,
		ID_ToolSearchKey,
		ID_ToolListKey,
		ID_ToolNewTab,
		ID_ToolRemoveTab,
		ID_ToolForward,
		ID_ToolBackward,
		ID_ToolDropDownRange,

		ID_ToolCalendar,
		ID_ToolPrev,
		ID_ToolNext,
		ID_ComboPlans,
		ID_CheckDone,
		ID_GaugeDone
};

/** General Controls */
enum {
		ID_BookTree = 200,
		ID_BookViewer1
};

/** Tool Bar IDs */
enum {
		ID_BookViewToolBar = 300,
		ID_ReadingPlannerToolBar
	};
	
/** BookList IDs */
enum
{
	ID_PopSelectAll =	400,
	ID_PopDeselectAll,
	ID_PopInvertSel,
	ID_PopSelectOTLaw,
	ID_PopSelectOTHistory,
	ID_PopSelectOTPsalms,
	ID_PopSelectOTProphets,
	ID_PopSelectNTGospels,
	ID_PopSelectNTHistory,
	ID_PopSelectNTEpistles,
	ID_BookList_OT,
	ID_BookList_NT
};

/** Calendar Wizard Page IDs */
enum
{
	ID_CalendarCtrlStart = 500,
	ID_CalendarCtrlEnd,
	ID_CheckCtrlSun,
	ID_CheckCtrlMon,
	ID_CheckCtrlTue,
	ID_CheckCtrlWed,
	ID_CheckCtrlThu,
	ID_CheckCtrlFri,
	ID_CheckCtrlSat,
	ID_TextCtrlTotal,
	ID_EditPlanName
};

/** ReadingPlanner ToolBar subframe */
enum
{
		ID_DateFrame = 600,
		ID_DateCalendar,
		ID_DateDone,
		ID_DateToday
};

/** PrefsDialog */
enum
{
	ID_BrowseInstall = 700,
	ID_BrowseBackup,
	ID_DetectPalm,
	ID_RadioChoice
};

enum
{
	ID_RPWizard = 800
};

#endif
