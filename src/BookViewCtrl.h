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
	#pragma interface "BookViewCtrl.h"
#endif

#ifndef _BOOKVIEWCTRL_H_
	
	#define _BOOKVIEWCTRL_H_

	#include "biblestudy.h"
	#include <wx/notebook.h>
	#include <wx/html/htmlwin.h>
	#include <wx/fontdlg.h>
	#include <wx/image.h>
	#include <string>
	#include "BookModule.h"
	
	class BookViewCtrl;
	
	#include "BookViewEventHandler.h"
	
	using namespace sword;
	using namespace std;

	BEGIN_DECLARE_EVENT_TYPES()
		DECLARE_EVENT_TYPE(bsEVT_CHILD_SET_FOCUS, 1)
	END_DECLARE_EVENT_TYPES()

	#define EVT_CHILD_SET_FOCUS(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_CHILD_SET_FOCUS, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
	
	
	/**
	* Tabbed viewing of book modules
	* 
	**/
	class BookViewCtrl : public wxNotebook
	{
	private:
		BookViewEventHandler *m_CustEventHandler;
	
	public:
		BookViewCtrl(wxWindow *parent, int id, const wxPoint pos, const wxSize size);
		~BookViewCtrl();
		
		int AddTab();
		void CloseTab();
		void CloseOtherTabs();
		void DuplicateTab();
		void DuplicateTab(BookModule *);
		
		/**
		 * Sets the module for the active tab
		 */
		void OpenInCurrentTab(SWModule *);
		void OpenInCurrentTab(BookModule *);
		void OpenInCurrentTab(wxString html);

		void OpenInNewTab(SWModule *);
		void OpenInNewTab(BookModule *);
		void AddToCurrentTab(SWModule *);
		void AddToCurrentTab(BookModule *);
		
		void LookupKey(wxString key);
		void ChildGotFocus();
		void PostChildSetFocus();
		void OnSetFocus(wxEvent &event);
		void OnNotebookPageChanged(wxEvent &event);
		
		void SetIcon();
		
		BookModule *GetActiveBookModule();
		
		DECLARE_EVENT_TABLE()
	};

#endif
