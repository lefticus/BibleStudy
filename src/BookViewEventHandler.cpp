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
	#pragma implementation "BookViewEventHandler.h"
#endif

#include "BookViewEventHandler.h"

BEGIN_EVENT_TABLE(BookViewEventHandler, wxEvtHandler)
	EVT_SET_FOCUS(BookViewEventHandler::OnSetFocus)
END_EVENT_TABLE()

BookViewEventHandler::BookViewEventHandler()
{
}


BookViewEventHandler::~BookViewEventHandler()
{
}

void BookViewEventHandler::OnSetFocus(wxFocusEvent &event)
{
	wxLogTrace(wxTRACE_Messages, "BookViewEventHandler::OnSetFocus called");

	m_parent->ChildGotFocus();
}

void BookViewEventHandler::SetParent(BookViewCtrl *nparent)
{
	m_parent = nparent;
}
