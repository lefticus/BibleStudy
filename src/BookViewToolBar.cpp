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


BookViewToolBar::BookViewToolBar(wxWindow *parent, wxWindowID id, long style) : wxToolBar(parent, id, wxDefaultPosition, wxDefaultSize, style, wxPanelNameStr)
{
	AddTool(ID_ToolShowHideBookTree, wxT("Book List"), wxNullBitmap, wxT("Show/Hide Book List"), wxITEM_CHECK);
	AddSeparator();
	AddTool(ID_ToolNewTab, wxT("Add Tab"), wxNullBitmap, wxT("Add a New Tab"), wxITEM_NORMAL);
	AddTool(ID_ToolRemoveTab, wxT("Remove Tab"), wxNullBitmap, wxT("Removes the Active Tab"), wxITEM_NORMAL);
	AddSeparator();
	m_LookupKey = new wxTextCtrl(this, ID_ToolTextKey);
	AddControl(m_LookupKey);
	AddTool(ID_ToolLookupKey, wxT("Lookup"), wxNullBitmap, wxT("Lookup Key"), wxITEM_NORMAL);
	

	Realize();
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
