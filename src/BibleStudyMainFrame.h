/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BIBLESTUDYMAINFRAME_H_
#define _BIBLESTUDYMAINFRAME_H_

	#include "biblestudy.h"
	#include <wx/splitter.h>
	#include <wx/notebook.h>
	#include <wx/treectrl.h>
	#include "SwordTools.h"
	#include "BookTreeCtrl.h"
	#include "BookViewSplitterCtrl.h"
	#include "BookViewCtrl.h"
	#include "BookViewToolBar.h"

	/**
	* Main window of BibleStudy
	* 
	**/
	class BibleStudyMainFrame: public wxFrame
	{

	private:
		/** Reference to the main split that seperates treeview from books */
		BookViewSplitterCtrl *m_WindowSplit;
		
		/** Reference to globabl SwordTools */
		SwordTools *m_SwordTools;
		
		/** Reference to MainFrame toolbar */
		BookViewToolBar *m_ToolBar;
		
		/** Initial setup of splitters, called by constructor */
		void SetupSplitterWindows();
		
		/** Update the toolbars to represent the currently viewed tab */
		void UpdateToolbars(BookModule *);
		
		/** Create a new window */
		BibleStudyMainFrame *OpenNewWindow();
		
	public:
		~BibleStudyMainFrame(); 
		
		/** Default constructor */
		BibleStudyMainFrame(SwordTools *, const wxString& title, const wxPoint& pos, const wxSize& size);
		
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		
		void OnSplitHorizontally(wxCommandEvent& event);
		void OnSplitVertically(wxCommandEvent& event);
		void OnRemoveActiveView(wxCommandEvent& event);
		
		void OnNewTab(wxCommandEvent& event);
		void OnCloseTab(wxCommandEvent& event);
		void OnDetachTab(wxMenuEvent& event);
		void OnDuplicateTab(wxMenuEvent& event);
		void OnCloseOtherTabs(wxMenuEvent& event);
		void OnShowHideBookTree(wxCommandEvent& event);
		void OnTreeItemActivated(wxCommandEvent& event);
		void OnLookupKey(wxCommandEvent& event);
		void OnOptionChange(wxMenuEvent& event);
		void OnNewWindow(wxMenuEvent& event);
		
		void OnOpenInNewTab(wxCommandEvent &event);
		void OnOpenInNewWindow(wxCommandEvent &event);
		void OnOpenInCurrentTab(wxCommandEvent &event);
		
		void OnActiveModuleChange(wxCommandEvent &event);
		void OnBookTreeChange(wxCommandEvent &event);
		
		void DisplayModule(SWModule *module);
		void DisplayModule(BookModule *module);
		
		DECLARE_EVENT_TABLE()
	};

#endif
