
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
  ID_MenuBibleStudyWhy,
  ID_MenuBibleStudyHow,
  ID_MenuBibleStudyGrow,
  ID_MenuShowStartPage,

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
  ID_ToolDropDownRange
};

/** General Controls */
enum {
  ID_BookTree = 200,
  ID_BookViewer1
};

/** Tool Bar IDs */
enum {
  ID_BookViewToolBar = 300
};

#endif
