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


#include "../icons/book.xpm"
#include "../icons/bible.xpm"
#include "../icons/lexicon.xpm"
#include "../icons/commentary.xpm"
#include "../icons/devotional.xpm"

enum {
	ID_BIBLICAL_TEXT_ICON = 0,
	ID_LEXICON_ICON,
	ID_COMMENTARY_ICON,
	ID_BOOK_ICON,
	ID_DEVOTIONAL_ICON
};


DEFINE_EVENT_TYPE(bsEVT_CHILD_SET_FOCUS)


BEGIN_EVENT_TABLE(BookViewCtrl, wxNotebook)
	EVT_SET_FOCUS(BookViewCtrl::OnSetFocus)
	EVT_NOTEBOOK_PAGE_CHANGED(-1, BookViewCtrl::OnNotebookPageChanged)
	
END_EVENT_TABLE()


BookViewCtrl::~BookViewCtrl()
{
}

BookViewCtrl::BookViewCtrl(wxWindow *parent, int id, const wxPoint pos, const wxSize size) : wxNotebook(parent, id, pos, size, wxSIMPLE_BORDER, wxT("notebook"))
{

	int imgsize = 16;
	
	wxImageList *images = new wxImageList(imgsize, imgsize, TRUE);
	wxIcon icons[5];
	icons[ID_BIBLICAL_TEXT_ICON] = wxIcon(bible_xpm);
	icons[ID_LEXICON_ICON] = wxIcon(lexicon_xpm);
	icons[ID_COMMENTARY_ICON] = wxIcon(commentary_xpm);
	icons[ID_BOOK_ICON] = wxIcon(book_xpm);
	icons[ID_DEVOTIONAL_ICON] = wxIcon(devotional_xpm);
	
	int sizeOrig = icons[0].GetWidth();
	
	for ( size_t i = 0; i < WXSIZEOF(icons); i++ ) {
		if (imgsize == sizeOrig ) {
			images->Add(icons[i]);
		} else {
			images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(imgsize,imgsize)));
		}
	}
	
	AssignImageList(images);



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

	#if wxMAJOR_VERSION == 2 && wxMINOR_VERSION > 4
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
	wxHtmlWindow *html;
	BookModule *bookmod;
	wxString key;
	bool performsearch;
	html = (wxHtmlWindow *)GetPage(GetSelection())->GetChildren().GetFirst()->GetData();
	SetPageText(GetSelection(), wxString(newModule->Name(), wxConvUTF8));
	
	bookmod = (BookModule *)html->GetClientData();
	if (bookmod) {
		key = bookmod->GetLastLookupKey();
		
		performsearch = !strcmp(bookmod->GetModule()->Type(), newModule->Type());
	
		delete bookmod;
	}
	
	bookmod = new BookModule(newModule);
	html->SetClientData(bookmod);
	
	if (!performsearch && !strcmp(newModule->Type(), "Daily Devotional")) {
		key = wxString::Format(wxT("%02i.%02i"), wxDateTime::Today().GetMonth() + 1, wxDateTime::Today().GetDay());
		performsearch = true;
	}
	
	if (performsearch)
		LookupKey(key);
	else
		LookupKey(wxT(""));
		
	SetIcon();
}

void BookViewCtrl::SetIcon()
{
	BookModule *bookmod = GetActiveBookModule();
	SWModule *module = bookmod->GetModule();
	
	if (!strcmp(module->Type(), "Biblical Texts")) {
		SetPageImage(GetSelection(), ID_BIBLICAL_TEXT_ICON);
	} else if (!strcmp(module->Type(), "Lexicons / Dictionaries") ||
				!strcmp(module->Type(), "Glossaries")) {
		SetPageImage(GetSelection(), ID_LEXICON_ICON);
	} else if (!strcmp(module->Type(), "Commentaries")) {
		SetPageImage(GetSelection(), ID_COMMENTARY_ICON);
	} else if (!strcmp(module->Type(), "Daily Devotional")) {
		SetPageImage(GetSelection(), ID_DEVOTIONAL_ICON);
	} else {
		SetPageImage(GetSelection(), ID_BOOK_ICON);
	}
	

}


void BookViewCtrl::OpenInNewTab(SWModule *newModule)
{
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
