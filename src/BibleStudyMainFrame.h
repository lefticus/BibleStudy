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
		BookViewSplitterCtrl *m_WindowSplit;
		//BookViewCtrl *m_BookViewer1;
		//BookTreeCtrl *m_BookTree;
		SwordTools *m_SwordTools;
		BookViewToolBar *m_ToolBar;
		
		
		void SetupSplitterWindows();
		void UpdateToolbars(BookModule *);
		BibleStudyMainFrame *OpenNewWindow();
		
	public:
		BibleStudyMainFrame();
		~BibleStudyMainFrame(); 
		
		BibleStudyMainFrame(SwordTools *, const wxString& title, const wxPoint& pos, const wxSize& size);
		
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		
		void OnSplitHorizontally(wxCommandEvent& event);
		void OnSplitVertically(wxCommandEvent& event);
		void OnRemoveSplit(wxCommandEvent& event);
		
		void OnNewTab(wxCommandEvent& event);
		void OnRemoveTab(wxCommandEvent& event);
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
		
		DECLARE_EVENT_TABLE()
		
	};

#endif
