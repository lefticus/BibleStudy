
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
#include <wx/intl.h>

#include "../icons/addtab.xpm"
#include "../icons/removetab.xpm"
#include "../icons/booktree.xpm"
#include "../icons/lookup.xpm"
#include "../icons/search.xpm"
#include "../icons/list.xpm"
#include "../icons/forward.xpm"
#include "../icons/back.xpm"


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

  AddTool(ID_ToolShowHideBookTree, _("Book List"), wxBitmap(booktree_xpm),
          wxNullBitmap, wxITEM_CHECK, _("Show/Hide Book List"),
          _("Show or hide the list of books that are on the left side of the window."));
  AddSeparator();

  AddTool(ID_ToolNewTab, _("Add Tab"), wxBitmap(addtab_xpm),
          wxNullBitmap, wxITEM_NORMAL, _("Add a New Tab"),
          _("Add a new tab in the current view."));

  AddTool(ID_ToolRemoveTab, _("Remove Tab"), wxBitmap(removetab_xpm),
          wxNullBitmap, wxITEM_NORMAL, _("Remove Current Tab"),
          _("Remove the currently selected tab."));

  AddSeparator();

  AddTool(ID_ToolListKey, _("Select Entry"), wxBitmap(list_xpm),
          wxNullBitmap, wxITEM_NORMAL, _("Select Entry"),
          _("Select a section, chapter or date in the currently opened book."));

  AddSeparator();

  m_LookupKey = new wxTextCtrl(this, ID_ToolTextKey);
  m_LookupKey->SetSize(200, m_LookupKey->GetSize().GetHeight());
  AddControl(m_LookupKey);

  AddTool(ID_ToolLookupKey, _("Lookup"), wxBitmap(lookup_xpm),
          wxNullBitmap, wxITEM_NORMAL, _("Lookup Entry"),
          _("Lookup the section, word or reference currently entered on the toolbar."));

//  m_DropDownRange =
//    new wxComboBox(this, ID_ToolDropDownRange, wxT(""), wxDefaultPosition,
//                   wxSize(200, -1), 0, NULL, wxCB_READONLY);
//  AddRanges();

//  AddControl(m_DropDownRange);
//  AddTool(ID_ToolSearchKey, _("Search"), wxBitmap(search_xpm),
//          wxNullBitmap, wxITEM_NORMAL, _("Search Entry"),
//          _("Search for the words currently entered on the toolbar."));

  AddTool(ID_ToolBackward, _("Backward"), wxBitmap(back_xpm),
          wxNullBitmap, wxITEM_NORMAL, _("Go Backward"),
          _("Browse backward in the current book."));

  AddTool(ID_ToolForward, _("Forward"), wxBitmap(forward_xpm),
          wxNullBitmap, wxITEM_NORMAL, _("Go Forward"),
          _("Browse forward in the current book."));

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
  m_DropDownRange->Append(_("Old Testament"),
                          new wxString(wxT("Gen-Mal"), wxConvUTF8));
  m_DropDownRange->Append(_("Law"),
                          new wxString(wxT("Gen-Deut"), wxConvUTF8));
  m_DropDownRange->Append(_("OT History"),
                          new wxString(wxT("Josh-Esther"), wxConvUTF8));
  m_DropDownRange->Append(_("Books of Wisdom"),
                          new wxString(wxT("Job-Song"), wxConvUTF8));
  m_DropDownRange->Append(_("Prophets"),
                          new wxString(wxT("Is-Mal"), wxConvUTF8));
//  m_DropDownRange->Append(_("Major Prophets"),
//                          new wxString(wxT("Is-Dan"), wxConvUTF8));
//  m_DropDownRange->Append(_("Minor Prophets"),
//                          new wxString(wxT("Hos-Mal"), wxConvUTF8));
//  m_DropDownRange->Append(_("Megillot"),
//                          new wxString(wxT("Ruth, Esther, Ecc, Song, Lam"),
//                                       wxConvUTF8));

  m_DropDownRange->Append(_("New Testament"),
                          new wxString(wxT("Mat-Rev"), wxConvUTF8));
  m_DropDownRange->Append(_("Gospels"),
                          new wxString(wxT("Mat-John"), wxConvUTF8));
  m_DropDownRange->Append(_("NT History"),
                          new wxString(wxT("Mat-Acts"), wxConvUTF8));
  m_DropDownRange->Append(_("Paul's Letters"),
                          new wxString(wxT("Ro-Phil"), wxConvUTF8));
  m_DropDownRange->Append(_("Other Letters"),
                          new wxString(wxT("Heb-Rev"), wxConvUTF8));
  m_DropDownRange->Append(_("All Letters"),
                          new wxString(wxT("Ro-Rev"), wxConvUTF8));

  m_DropDownRange->Append(_("No Restrictions"),
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

void BookViewToolBar::SetTypeDescription(const wxString &typeDesc)
{
  SetToolShortHelp(ID_ToolListKey, _("Select ") + typeDesc);
  FindById(ID_ToolListKey)->SetLabel(_("Select ") + typeDesc);
  UpdateWindowUI(wxUPDATE_UI_RECURSE);
//  Realize();
  Refresh();
}

void BookViewToolBar::EnableNavigation(bool enable) 
{
  EnableTool(ID_ToolBackward, enable);
  EnableTool(ID_ToolForward, enable);
  Refresh();
}

void BookViewToolBar::SetDropDownFrame(DropDownCtrl *subframe)
{
  if (m_SubFrame != subframe)
  {
    if (m_SubFrame)
    {
      wxEvtHandler *handler;

      if (m_SubFrame->GetPreviousHandler() != NULL)
      {
        wxLogDebug(wxT("BookViewToolBar::SetDropDownFrame Popping Event Handler"));
        handler = m_SubFrame->PopEventHandler(FALSE);
        wxLogDebug(wxT("BookViewToolBar::SetDropDownFrame Event Handler Popped"));
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

  Refresh();
}

void BookViewToolBar::OnListKey(wxCommandEvent & event)
{

  if (m_SubFrame)
  {
    ToggleTool(ID_ToolListKey, true);
    m_SubFrame->CentreOnParent();
      
    if (m_SubFrame->ShowModal() == wxID_OK) {
      wxCommandEvent eventCustom(bsEVT_LOAD_KEY);

      eventCustom.SetEventObject(this);
      eventCustom.SetString(m_SubFrame->GetKey());
      ProcessEvent(eventCustom);

      m_LookupKey->SetValue(m_SubFrame->GetKey());
    }
    ToggleTool(ID_ToolListKey, false); 
  }
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


