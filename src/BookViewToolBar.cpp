/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifdef __GNUG__
	#pragma implementation "BookViewToolBar.h"
#endif


#include "BookViewToolBar.h"
#include "DropDownEventHandler.h"
#include "biblestudy.h"

#include <wx/bitmap.h>
#include <wx/utils.h>
#include <wx/textctrl.h>
#include <wx/frame.h>
#include <wx/combobox.h>
#include <wx/log.h>
#include <wx/artprov.h>

#include "../icons/addtab.xpm"
#include "../icons/removetab.xpm"
#include "../icons/booktree.xpm"
#include "../icons/lookup.xpm"
#include "../icons/search.xpm"
#include "../icons/list.xpm"

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



BookViewToolBar::BookViewToolBar(wxWindow *parent, wxWindowID id, long style) : wxToolBar(parent, id, wxDefaultPosition, wxDefaultSize, style, wxPanelNameStr)
{
	SetToolBitmapSize(wxSize(22,22));
	SetToolSeparation(5);

	AddTool(ID_ToolShowHideBookTree, wxT("Book List"), wxBitmap(booktree_xpm), wxT("Show/Hide Book List"), wxITEM_CHECK);
	AddSeparator();
	AddTool(ID_ToolNewTab, wxT("Add Tab"), wxBitmap(addtab_xpm), wxT("Add a New Tab"), wxITEM_NORMAL);
	AddTool(ID_ToolRemoveTab, wxT("Remove Tab"), wxBitmap(removetab_xpm), wxT("Removes the Active Tab"), wxITEM_NORMAL);
	AddSeparator();
	m_LookupKey = new wxTextCtrl(this, ID_ToolTextKey);
	m_LookupKey->SetSize((int)(m_LookupKey->GetSize().GetWidth()*1.5), m_LookupKey->GetSize().GetHeight());
	AddControl(m_LookupKey);
	AddTool(ID_ToolListKey, wxT("List"), wxBitmap(list_xpm), wxT("List Keys"), wxITEM_NORMAL);
	AddTool(ID_ToolLookupKey, wxT("Lookup"), wxBitmap(lookup_xpm), wxT("Lookup Key"), wxITEM_NORMAL);

	m_DropDownRange = new wxComboBox(this, ID_ToolDropDownRange, wxT(""), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	m_DropDownRange->SetSize((int)(m_DropDownRange->GetSize().GetWidth()*1.75), m_DropDownRange->GetSize().GetHeight());
	AddRanges();

	AddControl(m_DropDownRange);
	AddTool(ID_ToolSearchKey, wxT("Search"), wxBitmap(search_xpm), wxT("Search"), wxITEM_NORMAL);

	AddTool(ID_ToolBackward, wxT("Backward"),wxArtProvider::GetIcon(wxART_GO_BACK, wxART_OTHER, wxSize(22,22)), wxT("Backward"), wxITEM_NORMAL);
	AddTool(ID_ToolForward, wxT("Forward"),wxArtProvider::GetIcon(wxART_GO_FORWARD, wxART_OTHER, wxSize(22,22)), wxT("Forward"), wxITEM_NORMAL);

	Realize();

	EnableTool(ID_ToolListKey, false);
//	m_DropDownKey->Enable(false);
//	m_DropDownBtn->Enable(false);

	m_SubFrame = NULL;
}

wxString *BookViewToolBar::GetRange()
{
	return (wxString *)(m_DropDownRange->GetClientData(m_DropDownRange->GetSelection()));
}

void BookViewToolBar::AddRanges()
{
	m_DropDownRange->Append(wxT("Current Verses"), new wxString(wxT(""), wxConvUTF8));

	m_DropDownRange->Append(wxT("Old Testament"), new wxString(wxT("Gen-Mal"), wxConvUTF8));
	m_DropDownRange->Append(wxT("Mosaic Law"), new wxString(wxT("Gen-Deut"), wxConvUTF8));
	m_DropDownRange->Append(wxT("OT History"), new wxString(wxT("Josh-Esther"), wxConvUTF8));
	m_DropDownRange->Append(wxT("Books of Wisdom"), new wxString(wxT("Job-Song"), wxConvUTF8));
	m_DropDownRange->Append(wxT("Major Prophets"), new wxString(wxT("Is-Dan"), wxConvUTF8));
	m_DropDownRange->Append(wxT("Minor Prophets"), new wxString(wxT("Hos-Mal"), wxConvUTF8));
	m_DropDownRange->Append(wxT("Megillot"), new wxString(wxT("Ruth, Esther, Ecc, Song, Lam"), wxConvUTF8));

	m_DropDownRange->Append(wxT("New Testament"), new wxString(wxT("Mat-Rev"), wxConvUTF8));
	m_DropDownRange->Append(wxT("Gospels"), new wxString(wxT("Mat-John"), wxConvUTF8));
	m_DropDownRange->Append(wxT("NT History"), new wxString(wxT("Mat-Acts"), wxConvUTF8));
	m_DropDownRange->Append(wxT("Paul's Letters"), new wxString(wxT("Ro-Phil"), wxConvUTF8));
	m_DropDownRange->Append(wxT("Other Letters"), new wxString(wxT("Heb-Rev"), wxConvUTF8));
	m_DropDownRange->Append(wxT("All Letters"), new wxString(wxT("Ro-Rev"), wxConvUTF8));

	m_DropDownRange->Append(wxT("No Restrictions"), new wxString(wxT("Gen-Rev"), wxConvUTF8));

	m_DropDownRange->SetSelection(0);
}

BookViewToolBar::~BookViewToolBar()
{
}

wxString BookViewToolBar::GetLookupKey()
{
	return m_LookupKey->GetValue();
}

void BookViewToolBar::SetLookupKey(wxString newKey)
{
	m_LookupKey->SetValue(newKey);
}

void BookViewToolBar::SetDropDownFrame(wxFrame *subframe)
{
	if (m_SubFrame) {
		m_SubFrame->PopEventHandler();
	}

	m_SubFrame = subframe;
	if (m_SubFrame) {
		EnableTool(ID_ToolListKey, true);
//		m_DropDownKey->Enable(true);
//		m_DropDownBtn->Enable(true);
		DropDownEventHandler *m_EventHandler = new DropDownEventHandler();
		m_EventHandler->SetParent(this);
		subframe->PushEventHandler(m_EventHandler);
	} else {
		EnableTool(ID_ToolListKey, false);
//		m_DropDownKey->Enable(false);
//		m_DropDownBtn->Enable(false);
	}
}


void BookViewToolBar::OnListKey(wxEvent &event)
{
	wxPoint pos;


	pos = GetParent()->ClientToScreen(wxPoint(0,0));
	pos.x = pos.x + GetToolSize().GetWidth() * 3 + GetToolSeparation() * 2 + GetMargins().GetWidth();

	
	if (m_SubFrame) {
		
		m_SubFrame->Move(pos.x, pos.y);
		m_SubFrame->Show(true);
	}
}

void BookViewToolBar::OnShowDropDown(wxEvent &event)
{
	wxPoint pos;

	
	pos = GetParent()->ClientToScreen(wxPoint(0,0));
	pos.x = pos.x + GetToolSize().GetWidth() * 4 + GetToolSeparation() * 3 + m_LookupKey->GetSize().GetWidth() + GetMargins().GetWidth();


	if (m_SubFrame) {
		
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

void BookViewToolBar::DropDownItemActivated(wxTreeEvent &event)
{
	wxTreeCtrl *tree = (wxTreeCtrl *)event.GetEventObject();
	wxTreeItemId item = event.GetItem();
	wxTreeItemId parent;
	wxString key;

	bool cont;
	
	m_SubFrame->Show(false);



	key = wxT("/") + tree->GetItemText(item);
	
	cont = true;

	while (cont) {
		item = tree->GetItemParent(item);
		parent = tree->GetItemParent(item);
		
		if (parent) {
			key = wxT("/") + tree->GetItemText(item) + key;
		} else {
			cont = false;
		}
	}

	wxCommandEvent eventCustom(bsEVT_LOAD_KEY);
	eventCustom.SetEventObject(this);
	eventCustom.SetString(key);
	ProcessEvent(eventCustom);

	m_LookupKey->SetValue(key);
}

void BookViewToolBar::DropDownDateSelected(wxCalendarEvent &event)
{
	m_SubFrame->Show(false);
	wxDateTime date = event.GetDate();

	wxString key;


	key = key.Format(wxT("%02i.%02i"), date.GetMonth()+1, date.GetDay());
	wxLogDebug(wxT("Date Selected: ") + key);

	m_LookupKey->SetValue(key);

	wxCommandEvent eventCustom(bsEVT_LOAD_KEY);
	eventCustom.SetEventObject(this);
	eventCustom.SetString(key);
	ProcessEvent(eventCustom);
}

void BookViewToolBar::OnLookupKey(wxEvent &event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BookViewToolBar::OnLookupKey called"));

	wxCommandEvent eventCustom(bsEVT_LOAD_KEY);
	eventCustom.SetEventObject(this);
	eventCustom.SetString(m_LookupKey->GetValue());
	ProcessEvent(eventCustom);
}

void BookViewToolBar::OnSearch(wxEvent &event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BookViewToolBar::OnSearch called"));

	wxCommandEvent eventCustom(bsEVT_SEARCH);
	eventCustom.SetEventObject(this);
	eventCustom.SetString(m_LookupKey->GetValue());
	ProcessEvent(eventCustom);
}

void BookViewToolBar::OnBrowseBackward(wxEvent &event)
{
	wxCommandEvent eventCustom(bsEVT_BROWSE_BACKWARD);
	eventCustom.SetEventObject(this);
	ProcessEvent(eventCustom);
}

void BookViewToolBar::OnBrowseForward(wxEvent &event)
{
	wxCommandEvent eventCustom(bsEVT_BROWSE_FORWARD);
	eventCustom.SetEventObject(this);
	ProcessEvent(eventCustom);
}

void BookViewToolBar::DropDownVerseSelected(wxCommandEvent &event)
{
	m_SubFrame->Show(false);

	wxLogTrace(wxTRACE_Messages, wxT("BookViewToolBar::OnLookupKey called"));
	wxLogDebug(wxT("EventString:") + event.GetString());
	wxCommandEvent eventCustom(bsEVT_BROWSE_KEY);
	eventCustom.SetEventObject(this);
	eventCustom.SetString(event.GetString());
	ProcessEvent(eventCustom);

}
