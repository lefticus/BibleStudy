/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BookViewSplitterCtrl.h"

#if USE_GENERIC_SPLITTERWINDOW
BEGIN_EVENT_TABLE(BookViewSplitterCtrl, wxGenericSplitterWindow)
#else
BEGIN_EVENT_TABLE(BookViewSplitterCtrl, wxSplitterWindow)
#endif
	EVT_NOTEBOOK_PAGE_CHANGED(-1, BookViewSplitterCtrl::OnTabPageChange)
	EVT_KILL_FOCUS(BookViewSplitterCtrl::OnFocusLost)
END_EVENT_TABLE()

DEFINE_EVENT_TYPE(bsEVT_ACTIVE_MODULE_CHANGE)
DEFINE_EVENT_TYPE(bsEVT_BOOK_TREE_CHANGE)


BookViewSplitterCtrl::BookViewSplitterCtrl()
{
}

BookViewSplitterCtrl::BookViewSplitterCtrl(wxWindow *parent, SwordTools *nswordtools, const wxPoint pos, const wxSize size) : wxSplitterWindow(parent, -1, pos, size, wxSP_3D|wxSP_FULLSASH|wxSP_LIVE_UPDATE, wxT("splitterWindow"))
{
	SetMinimumPaneSize(50);
	
	m_SwordTools = nswordtools;
	m_TopLevelSplit = new wxSplitterWindow(this, -1);
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
	
	m_LastSashPosition = 100;
	
	m_BookTree = new BookTreeCtrl(this, ID_BookTree, wxDefaultPosition, wxDefaultSize);
	m_BookTree->SetSwordTools(m_SwordTools);
	//m_BookViewer1 = new BookViewCtrl(this, ID_BookViewer1, wxDefaultPosition, wxDefaultSize);
	bookview->AddTab();
	
	m_BookTree->RefreshBookList();

	ShowHideBookTree();
}


BookViewSplitterCtrl::~BookViewSplitterCtrl()
{
}

/*
void BookViewSplitterCtrl::SetChildren(BookTreeCtrl *newTree, BookViewCtrl *newNotebook)
{
	m_Tree = newTree;
	m_Notebook = newNotebook;
	SplitVertically(m_Tree, m_Notebook, 100);
}
*/

bool BookViewSplitterCtrl::ShowHideBookTree()
{
	if (IsSplit()) {
		//tr_books->Show(false);
		m_LastSashPosition = GetSashPosition();
		Unsplit(m_BookTree);
		//Initialize(nb_firstchild);
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


void BookViewSplitterCtrl::RemoveTab()
{
	GetActiveBookViewCtrl()->RemoveTab();
}

void BookViewSplitterCtrl::AddTab()
{
	GetActiveBookViewCtrl()->AddTab();
}

void BookViewSplitterCtrl::OpenInCurrentTab(SWModule *mod)
{
	GetActiveBookViewCtrl()->OpenInCurrentTab(mod);
	
	wxCommandEvent eventCustom(bsEVT_ACTIVE_MODULE_CHANGE);
	eventCustom.SetEventObject(this);
	eventCustom.SetClientData(GetActiveBookViewCtrl()->GetActiveBookModule());
	ProcessEvent(eventCustom);
}

void BookViewSplitterCtrl::OpenInNewTab(SWModule *mod)
{
	GetActiveBookViewCtrl()->OpenInNewTab(mod);

	wxCommandEvent eventCustom(bsEVT_ACTIVE_MODULE_CHANGE);
	eventCustom.SetEventObject(this);
	eventCustom.SetClientData(GetActiveBookViewCtrl()->GetActiveBookModule());
	ProcessEvent(eventCustom);

}

void BookViewSplitterCtrl::LookupKey(wxString key)
{
	GetActiveBookViewCtrl()->LookupKey(key);
}

void BookViewSplitterCtrl::OnTabPageChange(wxNotebookEvent& event)
{
	wxCommandEvent eventCustom(bsEVT_ACTIVE_MODULE_CHANGE);
	eventCustom.SetEventObject(this);
	eventCustom.SetClientData(((BookViewCtrl *)(event.GetEventObject()))->GetActiveBookModule());
	ProcessEvent(eventCustom);
}

BookViewCtrl *BookViewSplitterCtrl::GetActiveBookViewCtrl()
{
	printf("Current Focus Class Name: %s\n", (const char *)wxString(FindFocus()->GetClassInfo()->GetClassName(), wxConvUTF8).mb_str());
	if (FindFocus()) {
		if (!wxString(wxT("BookViewCtrl")).CompareTo(FindFocus()->GetClassInfo()->GetClassName())) {
			m_LastFocus = (BookViewCtrl *)FindFocus();
			return (BookViewCtrl *)FindFocus();
		} else {
			return m_LastFocus;
		}
	} else {
		return m_LastFocus;
	}
}

void BookViewSplitterCtrl::OnFocusLost(wxFocusEvent &event)
{
	printf("Focus Lost Class Name: %s\n", (const char *)wxString(event.GetEventObject()->GetClassInfo()->GetClassName(), wxConvUTF8).mb_str());
	if (!wxString(wxT("BookViewCtrl")).CompareTo(event.GetEventObject()->GetClassInfo()->GetClassName())) {
		printf("FocusLost\n");
		m_LastFocus = (BookViewCtrl *)event.GetEventObject();
	}
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
