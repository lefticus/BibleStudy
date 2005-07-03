
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <BookViewToolBar.h>
#include <biblestudy.h>
#include <DropDownEventHandler.h>

#include <wx/toolbar.h>
#include <wx/event.h>
#include <wx/textctrl.h>
#include <wx/frame.h>
#include <wx/log.h>

#include "../icons/addtab.xpm"
#include "../icons/removetab.xpm"
#include "../icons/booktree.xpm"
#include "../icons/lookup.xpm"
#include "../icons/search.xpm"
#include "../icons/list.xpm"
#include "../icons/forward.xpm"
#include "../icons/back.xpm"

DEFINE_EVENT_TYPE(bsEVT_LOAD_KEY)
DEFINE_EVENT_TYPE(bsEVT_BROWSE_KEY)
DEFINE_EVENT_TYPE(bsEVT_SEARCH)
DEFINE_EVENT_TYPE(bsEVT_BROWSE_FORWARD)
DEFINE_EVENT_TYPE(bsEVT_BROWSE_BACKWARD)

BEGIN_EVENT_TABLE(BookViewToolBar, wxToolBar)
EVT_TOOL(ID_ToolLookupKey, BookViewToolBar::OnLookupKey)
EVT_TOOL(ID_ToolListKey, BookViewToolBar::OnListKey)
EVT_TOOL(ID_ToolSearchKey, BookViewToolBar::OnSearch)
EVT_TOOL(ID_ToolBackward, BookViewToolBar::OnBrowseBackward)
EVT_TOOL(ID_ToolForward, BookViewToolBar::OnBrowseForward)
END_EVENT_TABLE()


BookViewToolBar::BookViewToolBar(wxWindow * parent, wxWindowID id, long style)
    : wxToolBar(parent, id, wxDefaultPosition, wxDefaultSize,
                style, wxPanelNameStr)
{
  SetToolBitmapSize(wxSize(22, 22));
  SetToolSeparation(5);

  AddTool(ID_ToolShowHideBookTree, wxT("Book List"), wxBitmap(booktree_xpm),
          wxNullBitmap, wxITEM_CHECK, wxT("Show/Hide Book List"),
          wxT("Show or hide the list of books that are on the left side of the window."));
  AddSeparator();

  AddTool(ID_ToolNewTab, wxT("Add Tab"), wxBitmap(addtab_xpm),
          wxNullBitmap, wxITEM_NORMAL, wxT("Add a New Tab"),
          wxT("Add a new tab in the current view."));

  AddTool(ID_ToolRemoveTab, wxT("Remove Tab"), wxBitmap(removetab_xpm),
          wxNullBitmap, wxITEM_NORMAL, wxT("Remove Current Tab"),
          wxT("Remove the currently selected tab."));

  AddSeparator();

  m_LookupKey = new wxTextCtrl(this, ID_ToolTextKey);
  m_LookupKey->SetSize((int) (m_LookupKey->GetSize().GetWidth() * 1.5),
                       m_LookupKey->GetSize().GetHeight());
  AddControl(m_LookupKey);
  AddTool(ID_ToolListKey, wxT("Sections"), wxBitmap(list_xpm),
          wxNullBitmap, wxITEM_NORMAL, wxT("List Sections"),
          wxT("List all sections, chapters or words in the currently opened book."));

  AddTool(ID_ToolLookupKey, wxT("Lookup"), wxBitmap(lookup_xpm),
          wxNullBitmap, wxITEM_NORMAL, wxT("Lookup Entry"),
          wxT("Lookup the section, word or reference currently entered on the toolbar."));

  m_DropDownRange =
    new wxComboBox(this, ID_ToolDropDownRange, wxT(""), wxDefaultPosition,
                   wxDefaultSize, 0, NULL, wxCB_READONLY);
  m_DropDownRange->SetSize((int) (m_DropDownRange->GetSize().GetWidth() * 1.75),
                           m_DropDownRange->GetSize().GetHeight());
  AddRanges();

  AddControl(m_DropDownRange);
  AddTool(ID_ToolSearchKey, wxT("Search"), wxBitmap(search_xpm),
          wxNullBitmap, wxITEM_NORMAL, wxT("Search Entry"),
          wxT("Search for the words currently entered on the toolbar."));

  AddTool(ID_ToolBackward, wxT("Backward"), wxBitmap(back_xpm),
          wxNullBitmap, wxITEM_NORMAL, wxT("Go Backward"),
          wxT("Browse backward in the current book."));

  AddTool(ID_ToolForward, wxT("Forward"), wxBitmap(forward_xpm),
          wxNullBitmap, wxITEM_NORMAL, wxT("Go Forward"),
          wxT("Browse forward in the current book."));

  Realize();

  EnableTool(ID_ToolListKey, false);

  m_SubFrame = NULL;
}

wxString BookViewToolBar::GetRange()
{
  return *((wxString *) (m_DropDownRange->
                         GetClientData(m_DropDownRange->GetSelection())));
}

void BookViewToolBar::AddRanges()
{
  m_DropDownRange->Append(wxT("Old Testament"),
                          new wxString(wxT("Gen-Mal"), wxConvUTF8));
  m_DropDownRange->Append(wxT("Mosaic Law"),
                          new wxString(wxT("Gen-Deut"), wxConvUTF8));
  m_DropDownRange->Append(wxT("OT History"),
                          new wxString(wxT("Josh-Esther"), wxConvUTF8));
  m_DropDownRange->Append(wxT("Books of Wisdom"),
                          new wxString(wxT("Job-Song"), wxConvUTF8));
  m_DropDownRange->Append(wxT("Major Prophets"),
                          new wxString(wxT("Is-Dan"), wxConvUTF8));
  m_DropDownRange->Append(wxT("Minor Prophets"),
                          new wxString(wxT("Hos-Mal"), wxConvUTF8));
  m_DropDownRange->Append(wxT("Megillot"),
                          new wxString(wxT("Ruth, Esther, Ecc, Song, Lam"),
                                       wxConvUTF8));

  m_DropDownRange->Append(wxT("New Testament"),
                          new wxString(wxT("Mat-Rev"), wxConvUTF8));
  m_DropDownRange->Append(wxT("Gospels"),
                          new wxString(wxT("Mat-John"), wxConvUTF8));
  m_DropDownRange->Append(wxT("NT History"),
                          new wxString(wxT("Mat-Acts"), wxConvUTF8));
  m_DropDownRange->Append(wxT("Paul's Letters"),
                          new wxString(wxT("Ro-Phil"), wxConvUTF8));
  m_DropDownRange->Append(wxT("Other Letters"),
                          new wxString(wxT("Heb-Rev"), wxConvUTF8));
  m_DropDownRange->Append(wxT("All Letters"),
                          new wxString(wxT("Ro-Rev"), wxConvUTF8));

  m_DropDownRange->Append(wxT("No Restrictions"),
                          new wxString(wxT(""), wxConvUTF8));

  m_DropDownRange->SetSelection(13);
}

BookViewToolBar::~BookViewToolBar()
{}

wxString BookViewToolBar::GetLookupKey() const
{
  return m_LookupKey->GetValue();
}

void BookViewToolBar::SetLookupKey(const wxString &newKey)
{
  m_LookupKey->SetValue(newKey);
}

void BookViewToolBar::SetDropDownFrame(wxFrame *subframe)
{
  if (m_SubFrame != subframe)
  {
    if (m_SubFrame)
    {
      wxEvtHandler *handler;

      if (m_SubFrame->GetPreviousHandler() != NULL)
      {
        wxLogDebug(wxT
                   ("BookViewToolBar::SetDropDownFrame Popping Event Handler"));
        handler = m_SubFrame->PopEventHandler(FALSE);
        wxLogDebug(wxT
                   ("BookViewToolBar::SetDropDownFrame Event Handler Popped"));
      }

    }

    if (subframe)
    {
      EnableTool(ID_ToolListKey, true);
      DropDownEventHandler *m_EventHandler = new DropDownEventHandler();

      m_EventHandler->SetParent(this);
      wxLogDebug(wxT("BookViewToolBar::SetDropDownFrame Adding event Handler"));
      subframe->PushEventHandler(m_EventHandler);

    }
    else
    {
      EnableTool(ID_ToolListKey, false);
    }

    m_SubFrame = subframe;
  }
}

void BookViewToolBar::OnListKey(wxCommandEvent & event)
{
  wxPoint pos;

  pos = GetParent()->ClientToScreen(wxPoint(0, 0));
  pos.x =
    pos.x + GetToolSize().GetWidth() * 3 + GetToolSeparation() * 2 +
    GetMargins().GetWidth();

  if (m_SubFrame)
  {
    if (m_SubFrame->IsShown())
    {
      m_SubFrame->Show(false);
    }
    else
    {
      m_SubFrame->Move(pos.x, pos.y);
      m_SubFrame->Show(true);
    }
  }
}

void BookViewToolBar::OnShowDropDown(wxCommandEvent & event)
{
  wxPoint pos;

  pos = GetParent()->ClientToScreen(wxPoint(0, 0));
  pos.x =
    pos.x + GetToolSize().GetWidth() * 4 + GetToolSeparation() * 3 +
    m_LookupKey->GetSize().GetWidth() + GetMargins().GetWidth();

  if (m_SubFrame)
  {

    m_SubFrame->Move(pos.x, pos.y);
    m_SubFrame->Show(true);
  }

}

void BookViewToolBar::DropDownGotFocus()
{
}

void BookViewToolBar::DropDownLostFocus()
{
  m_SubFrame->Show(false);
}

void BookViewToolBar::DropDownItemActivated(wxTreeEvent & event)
{
  wxTreeCtrl *tree = (wxTreeCtrl *) event.GetEventObject();

  wxTreeItemId item = event.GetItem();
  wxTreeItemId parent;
  wxString key;

  bool cont;

  m_SubFrame->Show(false);

  key = wxT("/") + tree->GetItemText(item);

  cont = true;

  while (cont)
  {
    item = tree->GetItemParent(item);
    parent = tree->GetItemParent(item);

    if (parent)
    {
      key = wxT("/") + tree->GetItemText(item) + key;
    }
    else
    {
      cont = false;
    }
  }

  wxCommandEvent eventCustom(bsEVT_LOAD_KEY);

  eventCustom.SetEventObject(this);
  eventCustom.SetString(key);
  ProcessEvent(eventCustom);

  m_LookupKey->SetValue(key);
}

void BookViewToolBar::DropDownDateSelected(wxCalendarEvent & event)
{
  m_SubFrame->Show(false);
  wxDateTime date = event.GetDate();

  wxString key;

  key = key.Format(wxT("%02i.%02i"), date.GetMonth() + 1, date.GetDay());
  wxLogDebug(wxT("Date Selected: ") + key);

  m_LookupKey->SetValue(key);

  wxCommandEvent eventCustom(bsEVT_LOAD_KEY);

  eventCustom.SetEventObject(this);
  eventCustom.SetString(key);
  ProcessEvent(eventCustom);
}

void BookViewToolBar::OnLookupKey(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages, wxT("BookViewToolBar::OnLookupKey called"));

  wxCommandEvent eventCustom(bsEVT_LOAD_KEY);

  eventCustom.SetEventObject(this);
  eventCustom.SetString(m_LookupKey->GetValue());
  ProcessEvent(eventCustom);
}

void BookViewToolBar::OnSearch(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages, wxT("BookViewToolBar::OnSearch called"));

  wxCommandEvent eventCustom(bsEVT_SEARCH);

  eventCustom.SetEventObject(this);
  eventCustom.SetString(m_LookupKey->GetValue());
  ProcessEvent(eventCustom);
}

void BookViewToolBar::OnBrowseBackward(wxCommandEvent & event)
{
  wxCommandEvent eventCustom(bsEVT_BROWSE_BACKWARD);

  eventCustom.SetEventObject(this);
  ProcessEvent(eventCustom);
}

void BookViewToolBar::OnBrowseForward(wxCommandEvent & event)
{
  wxCommandEvent eventCustom(bsEVT_BROWSE_FORWARD);

  eventCustom.SetEventObject(this);
  ProcessEvent(eventCustom);
}

void BookViewToolBar::DropDownVerseSelected(wxCommandEvent & event)
{
  m_SubFrame->Show(false);

  wxLogTrace(wxTRACE_Messages, wxT("BookViewToolBar::OnLookupKey called"));
  wxLogDebug(wxT("EventString:") + event.GetString());
  wxCommandEvent eventCustom(bsEVT_BROWSE_KEY);

  eventCustom.SetEventObject(this);
  eventCustom.SetString(event.GetString());
  ProcessEvent(eventCustom);

}
