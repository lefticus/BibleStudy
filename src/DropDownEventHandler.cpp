
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <DropDownEventHandler.h>
#include <BookViewToolBar.h>

#include <wx/log.h>

BEGIN_EVENT_TABLE(DropDownEventHandler, wxEvtHandler)
EVT_MOVE(DropDownEventHandler::OnMove)
END_EVENT_TABLE()

DropDownEventHandler::DropDownEventHandler()
{}

DropDownEventHandler::~DropDownEventHandler()
{}



void DropDownEventHandler::SetParent(BookViewToolBar *nparent)
{
  m_parent = nparent;
}

void DropDownEventHandler::OnMove(wxMoveEvent &event)
{
  // event.Handled();
}


