/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#if defined(__GNUG__) && !defined(__APPLE__)
	#pragma interface "BookViewSplitterCtrl.h"
#endif


#ifndef _BOOKVIEWSPLITTERCTRL_H_
	#define _BOOKVIEWSPLITTERCTRL_H_


	#include "BookTreeCtrl.h"
	#include "BookViewCtrl.h"

	#include "SwordTools.h"
	#include <wx/splitter.h>



	BEGIN_DECLARE_EVENT_TYPES()
		DECLARE_EVENT_TYPE(bsEVT_ACTIVE_MODULE_CHANGE, 1)
		DECLARE_EVENT_TYPE(bsEVT_BOOK_TREE_CHANGE, 1)
		DECLARE_EVENT_TYPE(bsEVT_SHOW_BIBLESTUDY, 1)
	END_DECLARE_EVENT_TYPES()

	#define EVT_ACTIVE_MODULE_CHANGE(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_ACTIVE_MODULE_CHANGE, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
	#define EVT_BOOK_TREE_CHANGE(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_BOOK_TREE_CHANGE, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
	#define EVT_SHOW_BIBLESTUDY(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_SHOW_BIBLESTUDY, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

	/**
	*
	* Jason Turner
	**/
	class BookViewSplitterCtrl : public wxSplitterWindow
	{

	private:
		BookTreeCtrl *m_BookTree;
		int m_LastSashPosition;
		SwordTools *m_SwordTools;
		BookViewCtrl *m_LastFocus;

		wxSplitterWindow *m_TopLevelSplit, *m_FirstChildSplit, *m_SecondChildSplit;

		BookViewCtrl *GetActiveBookViewCtrl();


	public:
		BookViewSplitterCtrl();
		~BookViewSplitterCtrl();
		BookViewSplitterCtrl(wxWindow *parent, SwordTools *, const wxPoint pos, const wxSize size);

		bool ShowHideBookTree();

		void CloseTab();
		void AddTab();
		void CloseOtherTabs();
		void DuplicateTab();

		void OpenInCurrentTab(SWModule *);
		void OpenInCurrentTab(wxString html);
		void OpenInNewTab(SWModule *);
		void OpenInNewTab(BookModule *);
		void OpenInCurrentTab(BookModule *);
		void AddToCurrentTab(SWModule *);
		void AddToCurrentTab(BookModule *);

		void LookupKey(wxString key);
		void Search(wxString range, wxString search, int searchtype);
		void BrowseKey(wxString key);
		void BrowseForward();
		void BrowseBackward();

		void RemoveActiveView();

		void OnNewActiveChild(wxCommandEvent& event);
		void OnFocusGot(wxEvent& event);
		void OnLinkClicked(wxCommandEvent& event);
		void OnLinkHover(wxCommandEvent& event);

		void SplitHorizontally();
		void SplitVertically();

		void OnUnSplit(wxSplitterEvent &event);

		BookModule* GetActiveBookModule();
		DECLARE_EVENT_TABLE()
	};


#endif
