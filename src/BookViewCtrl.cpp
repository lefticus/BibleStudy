/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BookViewCtrl.h"


BookViewCtrl::BookViewCtrl()
{
}


BookViewCtrl::~BookViewCtrl()
{
}

BookViewCtrl::BookViewCtrl(wxWindow *parent, int id, const wxPoint pos, const wxSize size) : wxNotebook(parent, id, pos, size, wxSIMPLE_BORDER, wxT("notebook"))
{
	wxNotebookSizer *nbs = new wxNotebookSizer( this );
}

int BookViewCtrl::AddTab()
{
	wxNotebookPage *page;
	wxHtmlWindow *html;
	wxBoxSizer *panelsizer = new wxBoxSizer( wxVERTICAL );
	
	page = new wxPanel( this );
	html = new wxHtmlWindow( page, -1, wxDefaultPosition, wxDefaultSize, wxVSCROLL, wxT("htmlwindow"));
	//html->SetFonts("Shalohm", "Courier New", 0);
	panelsizer->Add(html, 1, wxEXPAND);
	page->SetSizer(panelsizer);
	AddPage(page, wxT("*Empty*"));
	
	return GetPageCount() - 1;
}

void BookViewCtrl::RemoveTab()
{
	wxHtmlWindow *html;
	BookModule *mod;

	html = (wxHtmlWindow *)GetPage(GetSelection())->GetChildren().GetFirst()->GetData();
	mod = (BookModule *)html->GetClientData();
	
	if (GetPageCount() > 1) {
		if (mod)
			delete mod;
		
		RemovePage(GetSelection());
	}
}


void BookViewCtrl::LookupKey(wxString key)
{
	wxHtmlWindow *html;
	BookModule *mod;
	VerseKey vk;
	wxString output;
	char book = 0;
	char numstr[10];
	int chapter = 0, verse = 0;
	
	output = wxT("<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'><body dir='rtl' lang='he'>");
	html = (wxHtmlWindow *)GetPage(GetSelection())->GetChildren().GetFirst()->GetData();
	mod = (BookModule *)html->GetClientData();
	html->SetPage( mod->LookupKey( key ) );	
}

void BookViewCtrl::OpenInCurrentTab(SWModule *newModule)
{
	wxHtmlWindow *html;
	BookModule *bookmod;
	wxString key;
	bool performsearch;
	html = (wxHtmlWindow *)GetPage(GetSelection())->GetChildren().GetFirst()->GetData();
	SetPageText(GetSelection(), wxString(newModule->Name(), wxConvUTF8));
	//newBookModule->SetKey("jn 3:16");
	//html->SetPage((const char *)(*newBookModule));
	bookmod = (BookModule *)html->GetClientData();
	if (bookmod) {
		key = bookmod->GetLastLookupKey();
		
		performsearch = !strcmp(bookmod->GetModule()->Type(), newModule->Type());
	
		delete bookmod;
	}
	
	bookmod = new BookModule(newModule);
	html->SetClientData(bookmod);
	
	if (performsearch)
		LookupKey(key);
	else
		LookupKey(wxT(""));
	//html->AppendToPage("hi");
}

void BookViewCtrl::OpenInNewTab(SWModule *newModule)
{
	SetSelection(AddTab());
	OpenInCurrentTab(newModule);
}


BookModule* BookViewCtrl::GetActiveBookModule()
{
	wxHtmlWindow *html;
	html = (wxHtmlWindow *)GetPage(GetSelection())->GetChildren().GetFirst()->GetData();
	return (BookModule *)html->GetClientData();
}
