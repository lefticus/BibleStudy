
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef DROPDOWNCTRL_H
#define DROPDOWNCTRL_H

#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/calctrl.h>
#include <wx/treectrl.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <sword/swmodule.h>

enum bsDropDownMode {
  bsCalendar = 1,
  bsTree = 2,
  bsBible = 4
};

/**
 * @author Jason Turner
 */
class DropDownCtrl : public wxDialog
{
private:
  bsDropDownMode m_Mode;

  wxTreeCtrl * m_Tree;
  wxCalendarCtrl *m_Calendar;
  wxComboBox *m_BookCB;
  wxComboBox *m_ChapterCB;
  wxComboBox *m_VerseCB;
  wxStaticText *m_BookLabel;
  wxStaticText *m_ChapterLabel;
  wxStaticText *m_VerseLabel;
  wxButton *m_Button;
  wxButton *m_Cancel;

  void UpdateBookCB();
  void UpdateVerseCB();
  void UpdateChapterCB();

  char m_LastBook;
  int m_LastChapter;
  int m_LastVerse;

  wxString m_Key;

  sword::SWModule *m_Module;

public:
  DropDownCtrl(wxWindow * parent, sword::SWModule *, bsDropDownMode mode);
  ~DropDownCtrl();

  wxTreeCtrl *GetTree();
  wxCalendarCtrl *GetCalendar();

  void UpdateCBs(wxCommandEvent &event);
  void OnKeyDown(wxKeyEvent &event);

  bool Validate() { return true; }
  bool TransferDataFromWindow();

  wxString GetKey() { return m_Key; }
  
  DECLARE_EVENT_TABLE()
};

#endif
