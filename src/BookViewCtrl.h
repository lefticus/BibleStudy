
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _BOOKVIEWCTRL_H_
#define _BOOKVIEWCTRL_H_

class BookModule;

#include <BookViewEventHandler.h>

#include <wx/notebook.h>

#include <swmgr.h>

BEGIN_DECLARE_EVENT_TYPES()
  DECLARE_EVENT_TYPE(bsEVT_CHILD_SET_FOCUS, 1)
END_DECLARE_EVENT_TYPES()

#define EVT_CHILD_SET_FOCUS(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_CHILD_SET_FOCUS, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

/**
 * Tabbed viewing of book modules
 *
 **/
class BookViewCtrl:public wxNotebook {
private:
  BookViewEventHandler *m_CustEventHandler;

public:
  BookViewCtrl(wxWindow *parent, int id, const wxPoint pos,
               const wxSize size);
  ~BookViewCtrl();

  int AddTab();
  void CloseTab();
  void CloseOtherTabs();
  void DuplicateTab();
  void DuplicateTab(BookModule *);

  /**
   * Sets the module for the active tab
   */
  void OpenInCurrentTab(sword::SWModule *);
  void OpenInCurrentTab(BookModule *);
  void OpenInCurrentTab(const wxString &html);

  void OpenInNewTab(sword::SWModule *);
  void OpenInNewTab(BookModule *);
  void OpenInNewTab(const wxString &html);

  void AddToCurrentTab(sword::SWModule *);
  void AddToCurrentTab(BookModule *);

  void LookupKey(const wxString &key);
  void BrowseKey(const wxString &key);
  void Search(const wxString &range, const wxString &search, int searchtype);
  void BrowseForward();
  void BrowseBackward();

  void ChildGotFocus();
  void PostChildSetFocus(BookModule *bm = NULL);
  void OnSetFocus(wxFocusEvent &event);
  void OnLeftUp(wxMouseEvent &event);
  void OnNotebookPageChanged(wxNotebookEvent &event);
	void RefreshStartPages(const wxString html);

  void SetIcon();

  BookModule *GetActiveBookModule();
public:
	// This may seem silly since we can call GetPageCount but the problem is when 
	// we are in the midst of creating that first tab and the change page event 
	// is called and I want to get info from a tab that is not complete.
	bool m_firstTabCreated;
  DECLARE_EVENT_TABLE()
};

#endif
