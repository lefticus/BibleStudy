
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

#include <biblestudy.h>

BEGIN_DECLARE_EVENT_TYPES()
  DECLARE_EVENT_TYPE(bsEVT_EXIT_APP, 1)
END_DECLARE_EVENT_TYPES()

#define EVT_EXIT_APP(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_EXIT_APP, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

class SwordTools;
class BookViewToolBar;
class BookViewSplitterCtrl;
class BookModule;

/**
 * Main window of BibleStudy
 *
 **/
class BibleStudyMainFrame:public wxFrame {
public:
  ~BibleStudyMainFrame();

  BibleStudyMainFrame(SwordTools *, const wxString &title,
                      const wxPoint &pos, const wxSize &size);

  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnCloseWindow(wxCommandEvent &event);

  void OnSplitHorizontally(wxCommandEvent &event);
  void OnSplitVertically(wxCommandEvent &event);
  void OnRemoveActiveView(wxCommandEvent &event);

  void OnNewTab(wxCommandEvent &event);
  void OnCloseTab(wxCommandEvent &event);
  void OnDetachTab(wxCommandEvent &event);
  void OnDuplicateTab(wxCommandEvent &event);
  void OnCloseOtherTabs(wxCommandEvent &event);
  void OnShowHideBookTree(wxCommandEvent &event);
  void OnTreeItemActivated(wxCommandEvent &event);
  void OnOptionChange(wxCommandEvent &event);
  void OnNewWindow(wxCommandEvent &event);

  void OnLoadKey(wxCommandEvent &event);
  void OnSearch(wxCommandEvent &event);
  void OnBrowseKey(wxCommandEvent &event);
  void OnBrowseBackward(wxCommandEvent &event);
  void OnBrowseForward(wxCommandEvent &event);

  void OnOpenInNewTab(wxCommandEvent &event);
  void OnOpenInNewWindow(wxCommandEvent &event);
  void OnOpenInCurrentTab(wxCommandEvent &event);
  void OnAddToCurrentTab(wxCommandEvent &event);

  void OnShowStartPage(wxCommandEvent &event);

  void OnActiveModuleChange(wxCommandEvent &event);
  void OnBookTreeChange(wxCommandEvent &event);

  void DisplayModule(sword::SWModule *module);
  void DisplayModule(BookModule *module);

  void OnShowHowBecomeChristian(wxCommandEvent &event);
  void OnShowWhyBecomeChristian(wxCommandEvent &event);
  void OnShowHowGrowSpiritually(wxCommandEvent &event);
  void OnShowBibleStudy(wxCommandEvent &event);

  void ShowStartPage();

  wxString BibleStudies() const;
  wxString Heading() const;
  wxString DevotionalOfTheDay() const;
  wxString ProverbOfTheDay() const;
  wxString SearchBox() const;

private:
  /** Reference to the main split that seperates treeview from books */
  BookViewSplitterCtrl * m_WindowSplit;

  /** Reference to global SwordTools */
  SwordTools *m_SwordTools;

  /** Reference to MainFrame toolbar */
  BookViewToolBar *m_ToolBar;
  wxToolBar *m_LookupToolBar;

  /** Initial setup of splitters, called by constructor */
  void SetupSplitterWindows();

  /** Update the toolbars to represent the currently viewed tab */
  void UpdateToolbars(BookModule *);

  /** Create a new window */
  BibleStudyMainFrame *OpenNewWindow();


  DECLARE_EVENT_TABLE()
};

#endif
