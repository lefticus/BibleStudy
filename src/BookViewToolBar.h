
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BOOKVIEWTOOLBAR_H_
#define _BOOKVIEWTOOLBAR_H_

#include <wx/toolbar.h>
#include <wx/combobox.h>
#include <wx/treectrl.h>
#include <wx/calctrl.h>

#include "DropDownCtrl.h"

const wxEventType bsEVT_LOAD_KEY = 5404;
const wxEventType bsEVT_SEARCH = 5405;
const wxEventType bsEVT_BROWSE_KEY = 5406;
const wxEventType bsEVT_BROWSE_BACKWARD = 5407;
const wxEventType bsEVT_BROWSE_FORWARD = 5408;


#define EVT_LOAD_KEY(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_LOAD_KEY, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

#define EVT_BROWSE_KEY(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_BROWSE_KEY, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

#define EVT_SEARCH(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_SEARCH, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

#define EVT_BROWSE_BACKWARD(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_BROWSE_BACKWARD, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

#define EVT_BROWSE_FORWARD(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_BROWSE_FORWARD, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

/**
 * Toolbar with inputs for searching in a Module.
 *
 **/
class BookViewToolBar: public wxToolBar
{
private:
  wxTextCtrl *m_LookupKey;
  wxComboBox *m_DropDownRange;
  DropDownCtrl *m_SubFrame;
  void AddRanges();

public:
  BookViewToolBar(wxWindow * parent, wxWindowID id, long style);
  ~BookViewToolBar();

  wxString GetLookupKey() const;
  void SetLookupKey(const wxString&);

  void SetDropDownFrame(DropDownCtrl* subframe);
  void SetTypeDescription(const wxString &);
  void EnableNavigation(bool);

  void OnLookupKey(wxCommandEvent & event);
  void OnListKey(wxCommandEvent & event);
  void OnSearch(wxCommandEvent & event);
  void OnBrowseForward(wxCommandEvent & event);
  void OnBrowseBackward(wxCommandEvent & event);

  wxString GetRange();

  DECLARE_EVENT_TABLE()
};

#endif
