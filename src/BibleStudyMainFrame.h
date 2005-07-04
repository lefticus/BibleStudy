
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _BIBLESTUDYMAINFRAME_H_
#define _BIBLESTUDYMAINFRAME_H_
#include <sword/swmodule.h>

#include <wx/event.h>
#include <wx/frame.h>
#include <wx/config.h>


#include "ReadingPlanWizard.h"

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(bsEVT_EXIT_APP, 1)
END_DECLARE_EVENT_TYPES()

#define EVT_EXIT_APP(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_EXIT_APP, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

class SwordTools;
class BookViewToolBar;
class ReadingPlannerToolBar;
class BookViewSplitterCtrl;
class BookModule;
class RPpdb;
struct dayRecord;
class PrefsDialog;

/**
 * Configuration data structure for BibleStudy Preference Storage
 *
 **/
struct BibleStudyConfig
{
  wxString m_PalmUserName;		// User name for the Palm Pilot desktop user.
  wxString m_PalmUserInstallPath;	// The installation path for the Palm Pilot user.
  wxString m_PalmUserBackupPath;	// The backup path for the Palm Pilot user.
  int m_PalmIntegration;		// True if user wants to use Palm Integration.
};
/**
 * Main window of BibleStudy
 *
 **/
class BibleStudyMainFrame:public wxFrame
{
public:
  void InstallCurrentPlan();
  void OnPlanChanged(wxCommandEvent & event);
  wxArrayString GetPlanNames();

  ~BibleStudyMainFrame();

  BibleStudyMainFrame(SwordTools *, const wxString &title,
                      const wxPoint &pos, const wxSize &size);

  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnCloseWindow(wxCommandEvent &event);
  void OnPrefs(wxCommandEvent & event);

  void OnCopy(wxCommandEvent &event);
  void OnSelectAll(wxCommandEvent &event);
  
  void OnSplitHorizontally(wxCommandEvent &event);
  void OnSplitVertically(wxCommandEvent &event);
  void OnRemoveActiveView(wxCommandEvent &event);

  void OnNewTab(wxCommandEvent &event);
  void OnCloseTab(wxCommandEvent &event);
  void OnDetachTab(wxCommandEvent &event);
  void OnDuplicateTab(wxCommandEvent &event);
  void OnCloseOtherTabs(wxCommandEvent &event);
  void OnShowHideBookTree(wxCommandEvent &event);
  void OnShowHidePlanBar(wxCommandEvent & event);
  void OnTreeItemActivated(wxCommandEvent &event);
  void OnOptionChange(wxCommandEvent &event);
  void OnNewWindow(wxCommandEvent &event);

  void OnLoadKey(wxCommandEvent &event);
  void OnSearch(wxCommandEvent &event);
  void OnBrowseKey(wxCommandEvent &event);
  void OnBrowseBackward(wxCommandEvent &event);
  void OnBrowseForward(wxCommandEvent &event);
  void OnNextDay(wxCommandEvent &event);
  void OnPrevDay(wxCommandEvent &event);
  void OnCheckDayDone(wxCommandEvent &event);

  void OnOpenInNewTab(wxCommandEvent &event);
  void OnOpenInNewWindow(wxCommandEvent &event);
  void OnOpenInCurrentTab(wxCommandEvent &event);
  void OnAddToCurrentTab(wxCommandEvent &event);

  void OnShowStartPage(wxCommandEvent &event);
  wxString BuildStartPage();

  void OnActiveModuleChange(wxCommandEvent &event);
  void OnBookTreeChange(wxCommandEvent &event);

  void DisplayModule(sword::SWModule *module);
  void DisplayModule(BookModule *module);

  void OnShowHowBecomeChristian(wxCommandEvent &event);
  void OnShowWhyBecomeChristian(wxCommandEvent &event);
  void OnShowHowGrowSpiritually(wxCommandEvent &event);
  void OnShowBibleStudy(wxCommandEvent &event);

  void OnShowReadingPlanPage(wxCommandEvent& event);
  void OnReadingPlannerWiz(wxCommandEvent& event);
  void ShowReadingPlan();
  wxString ReadingPlannerHeading();
  wxString InsertReadingPlan() const;
  wxString BuildStringAssignment(dayRecord* recP) const;
  wxString GetLinkString(wxString strBook, int chapter) const;
  void LayoutChildren();
  void UpdatePlanToolBar();
  void ShowHidePlanBar(bool show);
  wxDateTime GetPlanDate() {return m_PlanDate;}
  void SetPlanDate(const wxDateTime& date);

  void SaveConfig();
  void LoadConfig();

  void ShowStartPage();

  wxString BibleStudies() const;
  wxString Heading() const;
  wxString DevotionalOfTheDay() const;
  wxString ProverbOfTheDay() const;
  wxString SearchBox() const;

private:
  KJVBible rpBible;
  void OnSize(wxSizeEvent& event);

  /** Cross-platform config storage, uses native storage, either .conf or registry, etc. */
  BibleStudyConfig m_Config;

  /** Reference to the main split that seperates treeview from books */
  BookViewSplitterCtrl * m_WindowSplit;

  /** Reference to global SwordTools */
  SwordTools * m_SwordTools;

  /** Reference to MainFrame toolbar */
  BookViewToolBar *m_ToolBar;

  //wxToolBar *m_LookupToolBar;
  ReadingPlannerToolBar *m_PlanToolBar;

  /** Initial setup of splitters, called by constructor */
  void SetupSplitterWindows();

  /** The Current ReadingPlanner file **/
  RPpdb *m_pdbFile;

  /** Current Date for the ReadingPlaner **/
  wxDateTime m_PlanDate;

  /** Update the toolbars to represent the currently viewed tab */
  void UpdateToolbars(BookModule *);

  /** Create a new window */
  BibleStudyMainFrame *OpenNewWindow();

  /** Preferences Form Frame */
  PrefsDialog * m_PrefsDialog;
  DECLARE_EVENT_TABLE()
};

#endif
