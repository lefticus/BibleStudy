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
	#pragma implementation "DropDownEventHandler.h"
#endif

#include "DropDownEventHandler.h"
#include <wx/calctrl.h>
#include <wx/treectrl.h>
#include <wx/log.h>

BEGIN_EVENT_TABLE(DropDownEventHandler, wxEvtHandler)
	EVT_SET_FOCUS(DropDownEventHandler::OnSetFocus)
	EVT_KILL_FOCUS(DropDownEventHandler::OnKillFocus)
	EVT_TREE_ITEM_ACTIVATED(-1, DropDownEventHandler::OnItemActivated)
	EVT_CALENDAR(-1, DropDownEventHandler::OnDateSelected)
	EVT_MOVE(DropDownEventHandler::OnMove)
	EVT_TOOL(-1, DropDownEventHandler::OnVerseSelected)
END_EVENT_TABLE()

DropDownEventHandler::DropDownEventHandler()
{
}


DropDownEventHandler::~DropDownEventHandler()
{
}

void DropDownEventHandler::OnSetFocus(wxFocusEvent &event)
{
	wxLogTrace(wxTRACE_Messages, wxT("DropDownEventHandler::OnSetFocus called"));

	m_parent->DropDownGotFocus();
}

void DropDownEventHandler::OnKillFocus(wxFocusEvent &event)
{
	//m_parent->DropDownLostFocus();
}

void DropDownEventHandler::OnItemActivated(wxTreeEvent &event)
{
	m_parent->DropDownItemActivated(event);
}

void DropDownEventHandler::OnDateSelected(wxCalendarEvent &event)
{
	m_parent->DropDownDateSelected(event);
}

void DropDownEventHandler::SetParent(BookViewToolBar *nparent)
{
	m_parent = nparent;
}

void DropDownEventHandler::OnMove(wxMoveEvent &event)
{
	//event.Handled();
}

void DropDownEventHandler::OnVerseSelected(wxCommandEvent &event)
{
	m_parent->DropDownVerseSelected(event);
}
