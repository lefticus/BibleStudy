/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "DropDownEventHandler.h"

BEGIN_EVENT_TABLE(DropDownEventHandler, wxEvtHandler)
	EVT_SET_FOCUS(DropDownEventHandler::OnSetFocus)
	EVT_KILL_FOCUS(DropDownEventHandler::OnKillFocus)
	EVT_TREE_ITEM_ACTIVATED(-1, DropDownEventHandler::OnItemActivated)
	EVT_CALENDAR(-1, DropDownEventHandler::OnDateSelected)
END_EVENT_TABLE()

DropDownEventHandler::DropDownEventHandler()
{
}


DropDownEventHandler::~DropDownEventHandler()
{
}

void DropDownEventHandler::OnSetFocus(wxFocusEvent &event)
{
	wxLogTrace(wxTRACE_Messages, "DropDownEventHandler::OnSetFocus called");

	m_parent->DropDownGotFocus();
}

void DropDownEventHandler::OnKillFocus(wxFocusEvent &event)
{
	m_parent->DropDownLostFocus();
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
