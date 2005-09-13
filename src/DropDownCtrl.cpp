
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <DropDownCtrl.h>

#include <sword/versekey.h>

#include <wx/textctrl.h>
#include <wx/log.h>
#include <wx/intl.h>

using namespace sword;

BEGIN_EVENT_TABLE(DropDownCtrl, wxDialog)
EVT_TEXT(-1, DropDownCtrl::UpdateCBs)
EVT_KEY_DOWN(DropDownCtrl::OnKeyDown)
END_EVENT_TABLE()

DropDownCtrl::DropDownCtrl(wxWindow *parent, SWModule *module,
                           bsDropDownMode mode)
    : wxDialog(parent, -1, wxT("Select An Option"),
                  wxDefaultPosition, wxDefaultSize, wxCAPTION 
		  | wxCLIP_CHILDREN | wxSTAY_ON_TOP),
    m_Mode(mode), m_Tree(NULL), m_Calendar(NULL), m_BookCB(NULL),
    m_ChapterCB(NULL), m_VerseCB(NULL), m_LastBook(0),
    m_LastChapter(0), m_LastVerse(0), m_Module(module)
{
  switch (m_Mode)
  {
  case bsCalendar:
    m_Calendar =
      new wxCalendarCtrl(this, -1, wxDateTime::Now(), wxDefaultPosition,
                         wxDefaultSize,
                         wxCAL_SEQUENTIAL_MONTH_SELECTION | wxCAL_NO_YEAR_CHANGE
                         | wxCAL_SHOW_SURROUNDING_WEEKS | wxCAL_SUNDAY_FIRST |
                         wxCAL_SHOW_HOLIDAYS);
    // m_Calendar->PushEventHandler(this);
    
    SetClientSize(m_Calendar->GetSize());
    m_Calendar->Move(GetClientAreaOrigin());
    
    m_Cancel =
      new wxButton(this, wxID_CANCEL, _("Cancel"),
                   wxDefaultPosition, wxDefaultSize,
                   0, wxDefaultValidator, _("Cancel"));
    
    if (m_Cancel->GetSize().GetWidth() * 2 + 6 > GetClientSize().GetWidth()) {
      SetClientSize(m_Cancel->GetSize().GetWidth() * 2 + 6, 
		      GetClientSize().GetHeight());
    }


    m_Cancel->Move(GetClientSize().GetWidth()
		    - (m_Cancel->GetSize().GetWidth() + 2), 
		   GetClientSize().GetHeight() + 2);
    
    m_Button =
      new wxButton(this, wxID_OK, _("OK"),
                   wxDefaultPosition, wxDefaultSize,
                   0, wxDefaultValidator, _("OK"));

    m_Button->Move(m_Cancel->GetRect().GetLeft()
		    - m_Cancel->GetSize().GetWidth() - 2, 
		    m_Cancel->GetPosition().y);
    
    SetClientSize(GetClientSize().GetWidth(), 
		    GetClientSize().GetHeight() 
		    + m_Button->GetSize().GetHeight() + 4);
    m_Calendar->Move((GetClientSize().GetWidth() - m_Calendar->GetSize().GetWidth()) / 2, 0);
    break;
  case bsTree:
    m_Tree =
      new wxTreeCtrl(this, -1, wxDefaultPosition, wxSize(305, 200),
                     wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS
		                      | wxTR_FULL_ROW_HIGHLIGHT | wxTR_SINGLE);
    // m_Tree->PushEventHandler(this);
    SetClientSize(m_Tree->GetSize());
    m_Tree->Move(GetClientAreaOrigin());
    
    m_Cancel =
      new wxButton(this, wxID_CANCEL, _("Cancel"),
                   wxDefaultPosition, wxDefaultSize,
                   0, wxDefaultValidator, _("Cancel"));

    m_Cancel->Move(GetClientSize().GetWidth()
		    - (m_Cancel->GetSize().GetWidth() + 2), 
		    m_Tree->GetSize().GetHeight() + 2);
    
    m_Button =
      new wxButton(this, wxID_OK, _("OK"),
                   wxDefaultPosition, wxDefaultSize,
                   0, wxDefaultValidator, _("OK"));

    m_Button->Move(m_Cancel->GetRect().GetLeft()
		    - m_Cancel->GetSize().GetWidth() - 2, 
		    m_Cancel->GetPosition().y);
    SetClientSize(GetClientSize().GetWidth(), 
		    GetClientSize().GetHeight() 
		    + m_Button->GetSize().GetHeight() + 4);
    break;
  case bsBible:
    SetClientSize(wxSize(305, 70));
    m_BookLabel = new wxStaticText(this, -1, _("Book:"),
                                   wxPoint(GetClientAreaOrigin().x + 2,
                                           GetClientAreaOrigin().y + 2),
                                   wxSize(150, wxDefaultSize.GetHeight()),
                                   0);

    m_ChapterLabel = new wxStaticText(this, -1, _("Chapter:"),
                                      wxPoint(m_BookLabel->GetPosition().x +
                                              m_BookLabel->GetSize().GetWidth() + 2,
                                              m_BookLabel->GetPosition().y),
                                      wxSize(73, wxDefaultSize.GetHeight()),
                                      0);

    m_VerseLabel = new wxStaticText(this, -1, _("Verse:"),
                                    wxPoint(m_ChapterLabel->GetPosition().x +
                                            m_ChapterLabel->GetSize().GetWidth() + 2,
                                            m_ChapterLabel->GetPosition().y),
                                    wxSize(m_ChapterLabel->GetSize().GetWidth(),
                                           wxDefaultSize.GetHeight()),
                                    0);
    m_BookCB =
      new wxComboBox(this, -1, wxT(""),
                     wxPoint(m_BookLabel->GetPosition().x,
                             m_BookLabel->GetSize().GetHeight() +
                             m_BookLabel->GetPosition().y + 2),
                     wxSize(m_BookLabel->GetSize().GetWidth(),
                            wxDefaultSize.GetHeight()),
                     0, NULL, wxCB_READONLY);
    m_ChapterCB =
      new wxComboBox(this, -1, wxT(""),
                     wxPoint(m_ChapterLabel->GetPosition().x,
                             m_BookCB->GetPosition().y),
                     wxSize(m_ChapterLabel->GetSize().GetWidth(),
                            wxDefaultSize.GetHeight()),
                     0, NULL, wxCB_READONLY);
    m_VerseCB =
      new wxComboBox(this, -1, wxT(""),
                     wxPoint(m_VerseLabel->GetPosition().x,
                             m_ChapterCB->GetPosition().y),
                     wxSize(m_VerseLabel->GetSize().GetWidth(),
                            wxDefaultSize.GetHeight()),
                     0, NULL, wxCB_READONLY);
    m_Cancel =
      new wxButton(this, wxID_CANCEL, _("Cancel"),
                   wxDefaultPosition, wxDefaultSize,
                   0, wxDefaultValidator, _("Cancel"));

    m_Cancel->Move(m_VerseCB->GetRect().GetRight()
		    - m_Cancel->GetSize().GetWidth(), 
		    m_VerseCB->GetPosition().y +
		    m_VerseCB->GetSize().GetHeight() + 2);
    
    m_Button =
      new wxButton(this, wxID_OK, _("OK"),
                   wxDefaultPosition, wxDefaultSize,
                   0, wxDefaultValidator, _("OK"));

    m_Button->Move(m_Cancel->GetRect().GetLeft()
		    - m_Cancel->GetSize().GetWidth() - 2, 
		    m_Cancel->GetPosition().y);
    /*
       * m_BookCB->PushEventHandler(this);
       * m_ChapterCB->PushEventHandler(this);
       * m_VerseCB->PushEventHandler(this);
       * m_Button->PushEventHandler(this); 
    */
    SetClientSize(wxSize
                  (m_VerseLabel->GetPosition().x +
                   m_VerseLabel->GetSize().GetWidth() + 4,
                   m_Button->GetPosition().y + m_Button->GetSize().GetHeight() +
                   4));

    UpdateBookCB();
    UpdateChapterCB();
    UpdateVerseCB();

    m_VerseCB->SetSelection(0,0);
    m_BookCB->SetSelection(0,0);
    m_ChapterCB->SetSelection(0,0);

    break;
  }
}

DropDownCtrl::~DropDownCtrl()
{}

wxTreeCtrl *DropDownCtrl::GetTree()
{
  return m_Tree;
}

void DropDownCtrl::UpdateBookCB()
{
  wxBusyCursor busy;

  wxLogDebug(wxT("DropDownCtrl::UpdateBookCB called"));
  VerseKey vk("gen 1:1");

  m_BookCB->Clear();

  while (!vk.Error())
  {
    m_BookCB->Append(wxString(vk.getBookName(), wxConvUTF8));
    vk.Book(vk.Book() + 1);
  }
}

void DropDownCtrl::UpdateChapterCB()
{
  char book;

  wxBusyCursor busy;

  wxLogDebug(wxT("DropDownCtrl::UpdateChapterCB called"));
  VerseKey vk(m_BookCB->GetStringSelection().mb_str());

  book = vk.Book();

  m_ChapterCB->Clear();

  while (vk.Book() == book && !vk.Error())
  {
    m_ChapterCB->Append(wxString::Format(wxT("%i"), vk.Chapter()));
    vk.Chapter(vk.Chapter() + 1);
  }
}

void DropDownCtrl::UpdateVerseCB()
{
  int chapter;
  char book;

  wxBusyCursor busy;

  wxLogDebug(wxT("DropDownCtrl::UpdateVerseCB called"));
  VerseKey vk(m_BookCB-> GetStringSelection().
              Append(wxT(" ") + m_ChapterCB->GetStringSelection()). mb_str());
  chapter = vk.Chapter();
  book = vk.Book();

  m_VerseCB->Clear();

  while (vk.Chapter() == chapter && vk.Book() == book && !vk.Error())
  {
    m_VerseCB->Append(wxString::Format(wxT("%i"), vk.Verse()));
    vk.Verse(vk.Verse() + 1);
  }

  wxLogDebug(wxT("DropDownCtrl::UpdateVerseCB exiting"));
}

void DropDownCtrl::UpdateCBs(wxCommandEvent & event)
{

  wxLogDebug(wxT("DropDownCtrl::UpdateCBs called"));
  if (event.GetEventObject() == m_BookCB)
  {
    if (m_BookCB->GetSelection() != m_LastBook)
    {
      UpdateChapterCB();
      UpdateVerseCB();
    }

    m_LastBook = m_BookCB->GetSelection();

  }
  else if (event.GetEventObject() == m_ChapterCB)
  {
    if (m_ChapterCB->GetSelection() != m_LastChapter)
      UpdateVerseCB();

    m_LastChapter = m_ChapterCB->GetSelection();
  }

}


bool DropDownCtrl::TransferDataFromWindow()
{
  if (m_Mode == bsBible) {
    m_Key = m_BookCB->GetStringSelection() + wxT(" ") +
                        m_ChapterCB->GetStringSelection() /* + wxT(":") +
                        m_VerseCB->GetStringSelection() */;
  } else if (m_Mode == bsCalendar) {
    wxDateTime date = m_Calendar->GetDate();
    wxString key;
    m_Key = key.Format(wxT("%02i.%02i"), date.GetMonth() + 1, date.GetDay());
  } else if (m_Mode == bsTree) {

    wxTreeItemId item = m_Tree->GetSelection();
    wxTreeItemId parent;
    wxString key;
    bool cont;

    key = wxT("/") + m_Tree->GetItemText(item);

    cont = true;

    while (cont)
    {
      item = m_Tree->GetItemParent(item);
      parent = m_Tree->GetItemParent(item);

      if (parent)
      {
        key = wxT("/") + m_Tree->GetItemText(item) + key;
      }
      else
      {
        cont = false;
      }
    }

    m_Key = key;
  }
  
  return true;
}

void DropDownCtrl::OnKeyDown(wxKeyEvent & event)
{
  wxLogDebug(wxT("DropDownCtrl::OnKeyDown called"));
  if (event.GetKeyCode() == WXK_ESCAPE)
  {
    wxDialog::Show(false);
  }
  else
  {
    event.Skip();
  }
}
