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
	#pragma implementation "BookViewSplitterCtrl.h"
#endif

#include <wx/log.h>
#include "BookViewSplitterCtrl.h"
#include "BookViewHtml.h"

#if USE_GENERIC_SPLITTERWINDOW
BEGIN_EVENT_TABLE(BookViewSplitterCtrl, wxGenericSplitterWindow)
#else
BEGIN_EVENT_TABLE(BookViewSplitterCtrl, wxSplitterWindow)
#endif
	EVT_CHILD_SET_FOCUS(-1, BookViewSplitterCtrl::OnNewActiveChild)
	EVT_SPLITTER_UNSPLIT(-1, BookViewSplitterCtrl::OnUnSplit)
	EVT_LINK_CLICKED(BookViewSplitterCtrl::OnLinkClicked)
	EVT_LINK_HOVER(BookViewSplitterCtrl::OnLinkHover)
END_EVENT_TABLE()

DEFINE_EVENT_TYPE(bsEVT_ACTIVE_MODULE_CHANGE)
DEFINE_EVENT_TYPE(bsEVT_BOOK_TREE_CHANGE)
DEFINE_EVENT_TYPE(bsEVT_SHOW_BIBLESTUDY)


BookViewSplitterCtrl::BookViewSplitterCtrl(wxWindow *parent, SwordTools *nswordtools, const wxPoint pos, const wxSize size) : wxSplitterWindow(parent, -1, pos, size, wxSP_3D|wxSP_LIVE_UPDATE, wxT("splitterWindow"))
{
	SetMinimumPaneSize(50);

	m_SwordTools = nswordtools;
	m_TopLevelSplit = new wxSplitterWindow(this, -1, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_PERMIT_UNSPLIT);
	m_FirstChildSplit = new wxSplitterWindow(m_TopLevelSplit, -1, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_PERMIT_UNSPLIT);
	m_SecondChildSplit = new wxSplitterWindow(m_TopLevelSplit, -1, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_PERMIT_UNSPLIT);


	m_TopLevelSplit->SetMinimumPaneSize(50);
	m_FirstChildSplit->SetMinimumPaneSize(50);
	m_SecondChildSplit->SetMinimumPaneSize(50);

	m_SecondChildSplit->Show(false);
	m_TopLevelSplit->Initialize(m_FirstChildSplit);


	BookViewCtrl *bookview = new BookViewCtrl(m_FirstChildSplit, -1, wxDefaultPosition, wxDefaultSize);
	m_LastFocus = bookview;
	m_FirstChildSplit->Initialize(bookview);

	m_LastSashPosition = 150;

	m_BookTree = new BookTreeCtrl(this, ID_BookTree, wxDefaultPosition, wxDefaultSize);
	m_BookTree->SetSwordTools(m_SwordTools);
	bookview->AddTab();

	m_BookTree->RefreshBookList(true);

	ShowHideBookTree();
}


BookViewSplitterCtrl::~BookViewSplitterCtrl()
{
}


bool BookViewSplitterCtrl::ShowHideBookTree()
{
	if (IsSplit()) {
		m_LastSashPosition = GetSashPosition();
		Unsplit(m_BookTree);
	} else {
		wxSplitterWindow::SplitVertically(m_BookTree, m_TopLevelSplit, m_LastSashPosition);
		m_BookTree->Show(true);
	}
	
	wxCommandEvent eventCustom(bsEVT_BOOK_TREE_CHANGE);
	eventCustom.SetEventObject(this);
	eventCustom.SetInt(IsSplit());
	ProcessEvent(eventCustom);

	return IsSplit();	
}


void BookViewSplitterCtrl::CloseTab()
{
	GetActiveBookViewCtrl()->CloseTab();
}

void BookViewSplitterCtrl::AddTab()
{
	GetActiveBookViewCtrl()->AddTab();
}

void BookViewSplitterCtrl::OpenInCurrentTab(SWModule *mod)
{
	GetActiveBookViewCtrl()->OpenInCurrentTab(mod);

//	wxCommandEvent eventCustom(bsEVT_ACTIVE_MODULE_CHANGE);
//	eventCustom.SetEventObject(this);
//	eventCustom.SetClientData(GetActiveBookViewCtrl()->GetActiveBookModule());
//	ProcessEvent(eventCustom);
}

void BookViewSplitterCtrl::AddToCurrentTab(SWModule *mod)
{
	GetActiveBookViewCtrl()->AddToCurrentTab(mod);

}

void BookViewSplitterCtrl::AddToCurrentTab(BookModule *mod)
{
	GetActiveBookViewCtrl()->AddToCurrentTab(mod);
}


void BookViewSplitterCtrl::OpenInNewTab(SWModule *mod)
{


	GetActiveBookViewCtrl()->OpenInNewTab(mod);
}

void BookViewSplitterCtrl::OpenInCurrentTab(BookModule *mod)
{
	GetActiveBookViewCtrl()->OpenInCurrentTab(mod);
}

void BookViewSplitterCtrl::OpenInNewTab(BookModule *mod)
{
	GetActiveBookViewCtrl()->OpenInNewTab(mod);
}

void BookViewSplitterCtrl::LookupKey(wxString key)
{
	GetActiveBookViewCtrl()->LookupKey(key);
}

void BookViewSplitterCtrl::BrowseKey(wxString key)
{
	GetActiveBookViewCtrl()->BrowseKey(key);
}

void BookViewSplitterCtrl::BrowseForward()
{
	GetActiveBookViewCtrl()->BrowseForward();
}

void BookViewSplitterCtrl::BrowseBackward()
{
	GetActiveBookViewCtrl()->BrowseBackward();
}


void BookViewSplitterCtrl::Search(wxString range, wxString search, int searchtype)
{
	GetActiveBookViewCtrl()->Search(range, search, searchtype);
}

void BookViewSplitterCtrl::OnNewActiveChild(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BookViewSplitterCtrl::OnNewActiveChild called"));
	if (!wxString(wxT("wxNotebook")).CompareTo(event.GetEventObject()->GetClassInfo()->GetClassName())) {
		m_LastFocus = (BookViewCtrl *)event.GetEventObject();
	}

	event.Skip();

	wxCommandEvent eventCustom(bsEVT_ACTIVE_MODULE_CHANGE);
	eventCustom.SetEventObject(this);
	eventCustom.SetClientData(((BookViewCtrl *)(event.GetEventObject()))->GetActiveBookModule());
	ProcessEvent(eventCustom);
}

void BookViewSplitterCtrl::OnLinkClicked(wxCommandEvent& event)
{
	wxString target;
	
	if (event.GetString().StartsWith(wxT("biblestudy://"), &target)) {
		wxCommandEvent eventCustom(bsEVT_SHOW_BIBLESTUDY);
		eventCustom.SetEventObject(this);
		eventCustom.SetString(target);
		ProcessEvent(eventCustom);
	}
}

BookViewCtrl *BookViewSplitterCtrl::GetActiveBookViewCtrl()
{
	return m_LastFocus;
}


void BookViewSplitterCtrl::SplitHorizontally()
{
	wxSplitterWindow *nparent;

	if (m_TopLevelSplit->IsSplit()) {
		nparent = (wxSplitterWindow *)GetActiveBookViewCtrl()->GetParent();
		if (nparent->IsSplit()) {
			//Nothing to do.
		} else {
			BookViewCtrl *bookview = new BookViewCtrl(nparent, -1, wxDefaultPosition, wxDefaultSize);
			bookview->AddTab();
			m_LastFocus = bookview;
			nparent->SplitHorizontally(nparent->GetWindow1(), bookview);
		}
	} else {
		BookViewCtrl *bookview;
		if (m_FirstChildSplit->IsShown()) {


			bookview = new BookViewCtrl(m_SecondChildSplit, -1, wxDefaultPosition, wxDefaultSize);
			bookview->AddTab();
			m_SecondChildSplit->Initialize(bookview);
			m_SecondChildSplit->Show(true);
			bookview->Show(true);
			m_TopLevelSplit->SplitHorizontally(m_FirstChildSplit, m_SecondChildSplit);
		} else {
			m_FirstChildSplit->Show(true);
			bookview = new BookViewCtrl(m_FirstChildSplit, -1, wxDefaultPosition, wxDefaultSize);
			bookview->AddTab();
			m_FirstChildSplit->Initialize(bookview);
			m_FirstChildSplit->Show(true);
			m_TopLevelSplit->SplitHorizontally(m_SecondChildSplit, m_FirstChildSplit);

		}

		m_LastFocus = bookview;
	}
}


void BookViewSplitterCtrl::SplitVertically()
{
	wxSplitterWindow *nparent;

	if (m_TopLevelSplit->IsSplit()) {
		nparent = (wxSplitterWindow *)GetActiveBookViewCtrl()->GetParent();
		if (nparent->IsSplit()) {
			//Nothing to do.
		} else {
			BookViewCtrl *bookview = new BookViewCtrl(nparent, -1, wxDefaultPosition, wxDefaultSize);
			bookview->AddTab();
			m_LastFocus = bookview;
			nparent->SplitVertically(nparent->GetWindow1(), bookview);
		}
	} else {
		BookViewCtrl *bookview;
		if (m_FirstChildSplit->IsShown()) {


			bookview = new BookViewCtrl(m_SecondChildSplit, -1, wxDefaultPosition, wxDefaultSize);
			bookview->AddTab();
			m_SecondChildSplit->Initialize(bookview);
			m_SecondChildSplit->Show(true);
			bookview->Show(true);
			m_TopLevelSplit->SplitVertically(m_FirstChildSplit, m_SecondChildSplit);
		} else {
			m_FirstChildSplit->Show(true);
			bookview = new BookViewCtrl(m_FirstChildSplit, -1, wxDefaultPosition, wxDefaultSize);
			bookview->AddTab();
			m_FirstChildSplit->Initialize(bookview);
			m_FirstChildSplit->Show(true);
			m_TopLevelSplit->SplitVertically(m_SecondChildSplit, m_FirstChildSplit);

		}
		
		m_LastFocus = bookview;
	}
}

void BookViewSplitterCtrl::RemoveActiveView()
{
	wxSplitterWindow *parent;
	wxWindow *childToRemove;
	
	parent = (wxSplitterWindow *)m_LastFocus->GetParent();
	
	if (parent->IsSplit()) {
		childToRemove = m_LastFocus;
	} else {
		childToRemove = parent;
		parent = (wxSplitterWindow *)parent->GetParent();
	}
	
	if (parent->IsSplit()) {
		parent->Unsplit(childToRemove);
	}
}

void BookViewSplitterCtrl::OnUnSplit(wxSplitterEvent &event)
{
	wxWindow *windowBeingRemoved;
	BookViewCtrl *bookViewBeingRemoved;
	wxSplitterWindow *splitBeingRemoved;

	windowBeingRemoved = event.GetWindowBeingRemoved();

	if (windowBeingRemoved == m_FirstChildSplit 
		|| windowBeingRemoved == m_SecondChildSplit) {
		
		splitBeingRemoved = (wxSplitterWindow *)windowBeingRemoved;
		
		bookViewBeingRemoved = (BookViewCtrl *)splitBeingRemoved->GetWindow1();
		if (bookViewBeingRemoved)
			bookViewBeingRemoved->Destroy();

		bookViewBeingRemoved = (BookViewCtrl *)splitBeingRemoved->GetWindow2();
		if (bookViewBeingRemoved)
			bookViewBeingRemoved->Destroy();
			
	} else if (windowBeingRemoved != m_BookTree) {
		windowBeingRemoved->Destroy();
	}

	((wxSplitterWindow *)event.GetEventObject())->GetWindow1()->SetFocus();
}

void BookViewSplitterCtrl::CloseOtherTabs()
{
	m_LastFocus->CloseOtherTabs();
}

void BookViewSplitterCtrl::DuplicateTab()
{
	m_LastFocus->DuplicateTab();
}

BookModule* BookViewSplitterCtrl::GetActiveBookModule()
{
	return m_LastFocus->GetActiveBookModule();
}


void BookViewSplitterCtrl::OpenInCurrentTab(wxString html)
{
	m_LastFocus->OpenInCurrentTab(html);
}

void BookViewSplitterCtrl::OnLinkHover(wxCommandEvent &event)
{
	BookViewHtml *html = (BookViewHtml *)event.GetEventObject();
	wxString key;
	BookModule *book = NULL;

	if (!event.GetString().StartsWith(wxT("biblestudy://"))) {
		book = m_SwordTools->GetModuleFromLink(event.GetString(), 
			GetActiveBookViewCtrl()->GetActiveBookModule());
		key = m_SwordTools->GetKeyFromLink(event.GetString());


		if (book) {
			html->SetHTMLToolTip(book->LookupKey(key, wxT(""), 0, true));
			delete book;
		} else {
			html->SetHTMLToolTip(wxT(""));
		}
	} else {
		html->SetHTMLToolTip(wxT(""));
	}
}
