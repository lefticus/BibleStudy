/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BookViewToolBar.h"

#include "../icons/addtab.xpm"
#include "../icons/removetab.xpm"
#include "../icons/booktree.xpm"
#include "../icons/lookup.xpm"

DEFINE_EVENT_TYPE(bsEVT_LOAD_KEY)


BEGIN_EVENT_TABLE(BookViewToolBar, wxToolBar)
	EVT_BUTTON(ID_ToolDropDownBtn, BookViewToolBar::OnShowDropDown)
	EVT_TOOL(ID_ToolLookupKey, BookViewToolBar::OnLookupKey)
	
END_EVENT_TABLE()



BookViewToolBar::BookViewToolBar(wxWindow *parent, wxWindowID id, long style) : wxToolBar(parent, id, wxDefaultPosition, wxDefaultSize, style, wxPanelNameStr)
{
	AddTool(ID_ToolShowHideBookTree, wxT("Book List"), wxBitmap(booktree_xpm), wxT("Show/Hide Book List"), wxITEM_CHECK);
	AddSeparator();
	AddTool(ID_ToolNewTab, wxT("Add Tab"), wxBitmap(addtab_xpm), wxT("Add a New Tab"), wxITEM_NORMAL);
	AddTool(ID_ToolRemoveTab, wxT("Remove Tab"), wxBitmap(removetab_xpm), wxT("Removes the Active Tab"), wxITEM_NORMAL);
	AddSeparator();
	m_LookupKey = new wxTextCtrl(this, ID_ToolTextKey);
	AddControl(m_LookupKey);
	AddTool(ID_ToolLookupKey, wxT("Lookup"), wxBitmap(lookup_xpm), wxT("Lookup Key"), wxITEM_NORMAL);
	AddSeparator();
	m_DropDownKey = new wxTextCtrl(this, ID_ToolDropDownKey, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	AddControl(m_DropDownKey);
	m_DropDownBtn = new wxButton(this, ID_ToolDropDownBtn, wxT("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	AddControl(m_DropDownBtn);
	
	Realize();
	
	m_DropDownKey->Show(false);
	m_DropDownBtn->Show(false);
	
	m_SubFrame = NULL;
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
		m_DropDownKey->Show(true);
		m_DropDownBtn->Show(true);
		DropDownEventHandler *m_EventHandler = new DropDownEventHandler();
		m_EventHandler->SetParent(this);
		subframe->PushEventHandler(m_EventHandler);
	} else {
		m_DropDownKey->Show(false);
		m_DropDownBtn->Show(false);
	}
}

void BookViewToolBar::OnShowDropDown(wxEvent &event)
{
	wxPoint toolbarpos, windowpos, pos, clientareapos;
/*	wxSize toolsize, firsttextboxsize, secondtextboxsize;
	int sepsize;
	
	toolbarpos = this->GetPosition();
	windowpos = this->GetParent()->GetPosition();
	clientareapos = this->GetParent()->GetClientAreaOrigin();
	
	toolsize = this->GetToolSize();
	firsttextboxsize = m_LookupKey->GetSize();
	secondtextboxsize = m_DropDownKey->GetSize();
	sepsize = GetToolSeparation();
	
	int menubar, borderwidth, titlebar;
	//borderwidth = wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_X);
	//menubar = wxSystemSettings::GetMetric(wxSYS_MENU_Y);
	//titlebar = wxSystemSettings::GetMetric(wxSYS_CAPTION_Y);
	
	wxLogDebug(wxT("TextBox pos: %i, %i  size: %i, %i"), pos.x, pos.y, size.GetWidth(), size.GetHeight()), 
	
	//pos.x = windowpos.x + toolsize.GetWidth() * 3 + sepsize * 3 + firsttextboxsize.GetWidth() + secondtextboxsize.GetWidth();
	toolbarpos.x = 0;
	toolbarpos.y = 0;
	toolbarpos = GetParent()->ClientToScreen(toolbarpos);
	
	pos.x = toolbarpos.x + toolsize.GetWidth() * 3 ; //+ sepsize * 3 ;
	
	pos.y = toolbarpos.y; //+ (toolsize.GetHeight()-secondtextboxsize.GetHeight())/2;
	//pos.y = windowpos.y;*/
	
	if (m_SubFrame) {
		pos = wxGetMousePosition();
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

	m_DropDownKey->SetValue(tree->GetItemText(item));
	
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
}

void BookViewToolBar::DropDownDateSelected(wxCalendarEvent &event)
{
	m_SubFrame->Show(false);
	wxDateTime date = event.GetDate();
	
	wxString key;
	
	
	key = key.Format(wxT("%02i.%02i"), date.GetMonth()+1, date.GetDay());
	wxLogDebug(wxT("Date Selected: ") + key);
	
	m_DropDownKey->SetValue(wxString::Format(wxT("%i "), date.GetDay()) + wxDateTime::GetMonthName(date.GetMonth()));
	
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

