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


DEFINE_EVENT_TYPE(bsEVT_CHILD_SET_FOCUS)


BEGIN_EVENT_TABLE(BookViewCtrl, wxNotebook)
	EVT_SET_FOCUS(BookViewCtrl::OnSetFocus)
	EVT_NOTEBOOK_PAGE_CHANGED(-1, BookViewCtrl::OnNotebookPageChanged)
END_EVENT_TABLE()

BookViewCtrl::BookViewCtrl()
{
}


BookViewCtrl::~BookViewCtrl()
{
}

BookViewCtrl::BookViewCtrl(wxWindow *parent, int id, const wxPoint pos, const wxSize size) : wxNotebook(parent, id, pos, size, wxSIMPLE_BORDER, wxT("notebook"))
{
	wxNotebookSizer *nbs = new wxNotebookSizer( this );
	m_CustEventHandler = new BookViewEventHandler();
	m_CustEventHandler->SetParent(this);
}

int BookViewCtrl::AddTab()
{
	wxNotebookPage *page;
	wxHtmlWindow *html;
	wxBoxSizer *panelsizer = new wxBoxSizer( wxVERTICAL );
	
	page = new wxPanel( this );
	html = new wxHtmlWindow( page, -1, wxDefaultPosition, wxDefaultSize, wxVSCROLL, wxT("htmlwindow"));
	
	BookViewEventHandler *neweventhandler;
	neweventhandler = new BookViewEventHandler();
	neweventhandler->SetParent(this);
	html->PushEventHandler(neweventhandler);

	#if wxMAJOR_VERSION ==2 && wxMINOR_VERSION > 4
		html->SetFonts(wxT("Arial"), wxT("Courier New"), 0); // crashes wx2.4
	#endif
	
	panelsizer->Add(html, 1, wxEXPAND);
	page->SetSizer(panelsizer);
	AddPage(page, wxT("*Empty*"));
	
	SetSelection(GetPageCount() - 1);
	
	return GetPageCount() - 1;
}

void BookViewCtrl::CloseTab()
{
	wxHtmlWindow *html;
	BookModule *mod;
	int page;

	html = (wxHtmlWindow *)GetPage(GetSelection())->GetChildren().GetFirst()->GetData();
	mod = (BookModule *)html->GetClientData();
	
	if (GetPageCount() > 1) {
		if (mod)
			delete mod;
		page = GetSelection();
		RemovePage(page);
		if (GetPageCount() > page) 
			SetSelection(page);
		else
			SetSelection(page-1);
	}
	
	PostChildSetFocus();
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
	
	if (mod)
		html->SetPage( mod->LookupKey( key ) );	
}

void BookViewCtrl::OpenInCurrentTab(BookModule *bm)
{
	OpenInCurrentTab(bm->GetModule());
	LookupKey(bm->GetLastLookupKey());
}

void BookViewCtrl::OpenInCurrentTab(SWModule *newModule)
{
	printf("BookView:Got Open in current tab event\n");
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
	printf("BookView:Got Open in new tab event\n");
	//AddTab();
	SetSelection(AddTab());
	OpenInCurrentTab(newModule);
}

void BookViewCtrl::OpenInNewTab(BookModule *bm)
{
	SetSelection(AddTab());
	OpenInCurrentTab(bm);
}

BookModule* BookViewCtrl::GetActiveBookModule()
{
	wxHtmlWindow *html;
	int page = (GetSelection() == -1) ? 0 : GetSelection();
	html = (wxHtmlWindow *)GetPage(page)->GetChildren().GetFirst()->GetData();
	return (BookModule *)html->GetClientData();
}

void BookViewCtrl::ChildGotFocus()
{	
	PostChildSetFocus();
}

void BookViewCtrl::PostChildSetFocus()
{
	wxCommandEvent eventCustom(bsEVT_CHILD_SET_FOCUS);
	eventCustom.SetEventObject(this);
	eventCustom.SetClientData(GetActiveBookModule());
	ProcessEvent(eventCustom);

}

void BookViewCtrl::OnNotebookPageChanged(wxEvent &event)
{
	event.Skip();
	Refresh();
	PostChildSetFocus();
}

void BookViewCtrl::OnSetFocus(wxEvent &event)
{
	event.Skip();
	PostChildSetFocus();
}

void BookViewCtrl::CloseOtherTabs()
{
	int curtab = GetSelection();
	int numbefore;
	int numafter;
	int i;
	
	numbefore = curtab;
	numafter = GetPageCount() - (curtab + 1);
	
	for (i = 0; i < numbefore; i++) {
		SetSelection(0);
		CloseTab();
	}
	
	for (i = 0; i < numafter; i++) {
		SetSelection(1);
		CloseTab();
	}
	
}

void BookViewCtrl::DuplicateTab()
{
	DuplicateTab(GetActiveBookModule());
}

void BookViewCtrl::DuplicateTab(BookModule *bm)
{
	int selection = GetSelection();
	
	OpenInNewTab(bm);
	
	SetSelection(selection);
}

