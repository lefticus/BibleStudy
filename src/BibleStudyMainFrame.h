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
	#pragma interface "BibleStudyMainFrame.h"
#endif

#ifndef _BIBLESTUDYMAINFRAME_H_
#define _BIBLESTUDYMAINFRAME_H_


	#include "SwordTools.h"
	#include "BookViewToolBar.h"
	#include "BookViewSplitterCtrl.h"

	BEGIN_DECLARE_EVENT_TYPES()
		DECLARE_EVENT_TYPE(bsEVT_EXIT_APP, 1)
	END_DECLARE_EVENT_TYPES()

	#define EVT_EXIT_APP(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_EXIT_APP, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),


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
		wxToolBar *m_LookupToolBar;
		
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

		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnCloseWindow(wxCommandEvent& event);
		
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
		void OnOptionChange(wxMenuEvent& event);
		void OnNewWindow(wxMenuEvent& event);

		void OnLoadKey(wxCommandEvent& event);
		void OnSearch(wxCommandEvent& event);
		void OnBrowseKey(wxCommandEvent& event);
		void OnBrowseBackward(wxCommandEvent& event);
		void OnBrowseForward(wxCommandEvent& event);

		void OnOpenInNewTab(wxCommandEvent &event);
		void OnOpenInNewWindow(wxCommandEvent &event);
		void OnOpenInCurrentTab(wxCommandEvent &event);
		void OnAddToCurrentTab(wxCommandEvent &event);

		void OnShowStartPage(wxMenuEvent& event);

		void OnActiveModuleChange(wxCommandEvent &event);
		void OnBookTreeChange(wxCommandEvent &event);

		void DisplayModule(SWModule *module);
		void DisplayModule(BookModule *module);

		void OnShowHowBecomeChristian();
		void OnShowWhyBecomeChristian();
		void OnShowHowGrowSpiritually();
		void OnShowBibleStudy(wxCommandEvent &event);

		void ShowStartPage();

		wxString BibleStudies();
		wxString Heading();
		wxString DevotionalOfTheDay();
		wxString ProverbOfTheDay();
		wxString SearchBox();

		DECLARE_EVENT_TABLE()
	};

#endif
