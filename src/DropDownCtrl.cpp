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
	#pragma implementation "DropDownCtrl.h"
#endif


#include "DropDownCtrl.h"
#include <wx/combobox.h>
#include <versekey.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/log.h>

BEGIN_EVENT_TABLE(DropDownCtrl, wxMiniFrame)
	EVT_TEXT(-1, DropDownCtrl::UpdateCBs)
	EVT_BUTTON(-1, DropDownCtrl::OnButtonPress)
	EVT_KEY_DOWN(DropDownCtrl::OnKeyDown)
END_EVENT_TABLE()
DropDownCtrl::DropDownCtrl(wxWindow *parent, SWModule *module, bsDropDownMode mode) : wxMiniFrame(parent, -1, wxT("Select An Option"), wxDefaultPosition, wxDefaultSize, wxCLOSE_BOX|wxSTAY_ON_TOP)
{
	m_Mode = mode;

	m_Calendar = NULL;
	m_Tree = NULL;
	m_BookCB = NULL;
	m_ChapterCB = NULL;
	m_VerseCB = NULL;

	m_LastChapter = 0;
	m_LastVerse = 0;
	m_LastBook = 0;

	m_Module = module;

	switch(m_Mode) {
	case bsCalendar:
		m_Calendar = new wxCalendarCtrl(this, -1, wxDateTime::Now(), wxDefaultPosition, wxDefaultSize, wxCAL_SEQUENTIAL_MONTH_SELECTION|wxCAL_NO_YEAR_CHANGE|wxCAL_SHOW_SURROUNDING_WEEKS|wxCAL_SUNDAY_FIRST|wxCAL_SHOW_HOLIDAYS);
		//m_Calendar->PushEventHandler(this);
		SetClientSize(m_Calendar->GetSize());
		m_Calendar->Move(GetClientAreaOrigin());
		break;
	case bsTree:
		m_Tree = new wxTreeCtrl(this, -1, wxDefaultPosition, wxSize(200,100), wxTR_NO_BUTTONS|wxTR_HIDE_ROOT|wxTR_LINES_AT_ROOT);
		//m_Tree->PushEventHandler(this);
		SetClientSize(m_Tree->GetSize());
		m_Tree->Move(GetClientAreaOrigin());
		break;
	case bsBible:
		SetClientSize(wxSize(305, 50));
		m_BookCB = new wxComboBox(this, -1, wxT(""), wxPoint(GetClientAreaOrigin().x+2, GetClientAreaOrigin().y+2), wxSize( 150, wxDefaultSize.GetHeight()), 0, NULL, wxCB_READONLY);
		m_ChapterCB = new wxComboBox(this, -1, wxT(""), wxPoint(m_BookCB->GetPosition().x+m_BookCB->GetSize().GetWidth()+2, m_BookCB->GetPosition().y), wxSize(73,wxDefaultSize.GetHeight()), 0, NULL, wxCB_READONLY);
		m_VerseCB = new wxComboBox(this, -1, wxT(""), wxPoint(m_ChapterCB->GetPosition().x+m_ChapterCB->GetSize().GetWidth()+2, m_ChapterCB->GetPosition().y), wxSize(73,wxDefaultSize.GetHeight()), 0, NULL, wxCB_READONLY);
		m_Button = new wxButton(this, -1, wxT("Select"), wxPoint(m_BookCB->GetPosition().x, m_VerseCB->GetPosition().y+m_VerseCB->GetSize().GetHeight()+2), wxDefaultSize, 0, wxDefaultValidator, wxT("Select"));

		/*
		m_BookCB->PushEventHandler(this);
		m_ChapterCB->PushEventHandler(this);
		m_VerseCB->PushEventHandler(this);
		m_Button->PushEventHandler(this);
		*/
		SetClientSize(wxSize(m_VerseCB->GetPosition().x+m_VerseCB->GetSize().GetWidth()+4, m_Button->GetPosition().y+m_Button->GetSize().GetHeight()+4));

		UpdateBookCB();
		UpdateChapterCB();
		UpdateVerseCB();

		break;
	}
}


DropDownCtrl::~DropDownCtrl()
{
}

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

	while (!vk.Error()) {
		m_BookCB->Append(wxString(vk.getBookName(), wxConvUTF8));
		vk.Book(vk.Book()+1);
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

	while (vk.Book() == book && !vk.Error()) {
		m_ChapterCB->Append(wxString::Format(wxT("%i"), vk.Chapter()));
		vk.Chapter(vk.Chapter()+1);
	}
}

void DropDownCtrl::UpdateVerseCB()
{
	int chapter;
	char book;
	wxBusyCursor busy;

	wxLogDebug(wxT("DropDownCtrl::UpdateVerseCB called"));
	VerseKey vk(m_BookCB->GetStringSelection().Append(wxT(" ") + m_ChapterCB->GetStringSelection()).mb_str());
	chapter = vk.Chapter();
	book = vk.Book();

	m_VerseCB->Clear();

	while (vk.Chapter() == chapter && vk.Book() == book && !vk.Error()) {
		m_VerseCB->Append(wxString::Format(wxT("%i"), vk.Verse()));
		vk.Verse(vk.Verse()+1);
	}

	wxLogDebug(wxT("DropDownCtrl::UpdateVerseCB exiting"));
}

void DropDownCtrl::UpdateCBs(wxCommandEvent &event)
{

	wxLogDebug(wxT("DropDownCtrl::UpdateCBs called"));
	if (event.GetEventObject() == m_BookCB) {
		if (m_BookCB->GetSelection() != m_LastBook) {
			UpdateChapterCB();
			UpdateVerseCB();
		}

		m_LastBook = m_BookCB->GetSelection();

	} else if (event.GetEventObject() == m_ChapterCB) {
		if (m_ChapterCB->GetSelection() != m_LastChapter)
			UpdateVerseCB();

		m_LastChapter = m_ChapterCB->GetSelection();
	}

}

void DropDownCtrl::OnButtonPress(wxCommandEvent &event)
{
	wxCommandEvent eventCustom(wxEVT_COMMAND_TOOL_CLICKED);
	eventCustom.SetEventObject(event.GetEventObject());
	eventCustom.SetString(m_BookCB->GetStringSelection() + wxT(" ") + m_ChapterCB->GetStringSelection() + wxT(":") + m_VerseCB->GetStringSelection());

	wxLogDebug(wxT("Event String: ") + eventCustom.GetString());

	if (GetPreviousHandler())
		GetPreviousHandler()->ProcessEvent(eventCustom);
}

void DropDownCtrl::OnKeyDown(wxKeyEvent &event)
{
	wxLogDebug(wxT("DropDownCtrl::OnKeyDown called"));
	if (event.GetKeyCode() == WXK_ESCAPE) {
		wxFrame::Show(false);
	} else {
		event.Skip();
	}
}
