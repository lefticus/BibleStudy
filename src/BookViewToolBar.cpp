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
	

	Realize();
}

void BookViewToolBar::SetupIcons()
{
	/*
	int size = 32;
	
	wxImageList *images = new wxImageList(size, size, TRUE);
	wxIcon icons[5];
	icons[0] = wxIcon(addtab);
	
	int sizeOrig = icons[0].GetWidth();
	
	for ( size_t i = 0; i < WXSIZEOF(icons); i++ ) {
		if (size == sizeOrig ) {
			images->Add(icons[i]);
		} else {
			images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size,size)));
		}
	}
	
	AssignImageList(images);
	*/
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
