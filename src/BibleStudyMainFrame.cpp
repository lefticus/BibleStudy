/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BibleStudyMainFrame.h"

/** Register event handlers */
BEGIN_EVENT_TABLE(BibleStudyMainFrame, wxFrame)
	EVT_MENU(ID_MenuQuit, BibleStudyMainFrame::OnQuit)
	EVT_MENU(ID_MenuAbout, BibleStudyMainFrame::OnAbout)
	
	EVT_MENU(ID_MenuSplitVertically, BibleStudyMainFrame::OnSplitVertically)
	EVT_MENU(ID_MenuSplitHorizontally, BibleStudyMainFrame::OnSplitHorizontally)
	EVT_MENU(ID_MenuRemoveSplit, BibleStudyMainFrame::OnRemoveSplit)
	
	EVT_MENU(ID_MenuNewTab, BibleStudyMainFrame::OnNewTab)
	EVT_MENU(ID_MenuRemoveTab, BibleStudyMainFrame::OnRemoveTab)
	EVT_MENU(ID_MenuShowHideBookTree, BibleStudyMainFrame::OnShowHideBookTree)
	EVT_MENU(ID_MenuNewWindow, BibleStudyMainFrame::OnNewWindow)

	EVT_MENU_RANGE(ID_MenuTopBookOption, ID_MenuTopBookOption+50, BibleStudyMainFrame::OnOptionChange)

	EVT_TOOL(ID_ToolShowHideBookTree, BibleStudyMainFrame::OnShowHideBookTree)
	EVT_TOOL(ID_ToolLookupKey, BibleStudyMainFrame::OnLookupKey)
	EVT_TOOL(ID_ToolNewTab, BibleStudyMainFrame::OnNewTab)
	EVT_TOOL(ID_ToolRemoveTab, BibleStudyMainFrame::OnRemoveTab)
	
	EVT_OPEN_IN_CURRENT_TAB(-1, BibleStudyMainFrame::OnOpenInCurrentTab)
	EVT_OPEN_IN_NEW_TAB(-1, BibleStudyMainFrame::OnOpenInNewTab)
	EVT_OPEN_IN_NEW_WINDOW(-1, BibleStudyMainFrame::OnOpenInNewWindow)
	
	EVT_ACTIVE_MODULE_CHANGE(-1, BibleStudyMainFrame::OnActiveModuleChange)
	EVT_BOOK_TREE_CHANGE(-1, BibleStudyMainFrame::OnBookTreeChange)
END_EVENT_TABLE() 

BibleStudyMainFrame::BibleStudyMainFrame()
{
}

BibleStudyMainFrame::~BibleStudyMainFrame()
{
}

BibleStudyMainFrame::BibleStudyMainFrame(SwordTools *newSwordTools, const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{

	m_SwordTools = newSwordTools;

	wxMenu *menuFile = new wxMenu();
	wxMenu *menuHelp = new wxMenu();
	wxMenu *menuWindow = new wxMenu();
	wxMenu *menuOptions = new wxMenu();
		
	menuFile->Append( ID_MenuNewWindow, wxT("&New Window"));
	menuFile->AppendSeparator();
	menuFile->Append( ID_MenuQuit, wxT("E&xit") );
	
	menuHelp->Append( ID_MenuAbout, wxT("&About BibleStudy") );
		
	menuWindow->Append( ID_MenuShowHideBookTree, wxT("Show/Hide Book List") );
	menuWindow->AppendSeparator();
	menuWindow->Append( ID_MenuSplitVertically, wxT("Split View &Left/Right") );
	menuWindow->Append( ID_MenuSplitHorizontally, wxT("Split View &Top/Bottom") );
	menuWindow->Append( ID_MenuRemoveSplit, wxT("&Remove Active View") );
	menuWindow->AppendSeparator();
	menuWindow->Append( ID_MenuNewTab, wxT("&New Tab"));
	menuWindow->Append( ID_MenuRemoveTab, wxT("Close Current Tab"));
	
	OptionsList optlist;
	optlist = m_SwordTools->GetSwordManager()->getGlobalOptions();
	
	OptionsList::iterator it;
	int id = ID_MenuTopBookOption;
	for (it = optlist.begin(); it != optlist.end(); it++) {
		menuOptions->AppendCheckItem(id, wxString(it->c_str(), wxConvUTF8), wxString(m_SwordTools->GetSwordManager()->getGlobalOptionTip(it->c_str()), wxConvUTF8)); 
		if (!strcmp(m_SwordTools->GetSwordManager()->getGlobalOption(it->c_str()), "On")) {
			menuOptions->Check(id, true);
		} else {
			menuOptions->Check(id, false);
		}
		
		id++;
	}
	
	
	
	wxMenuBar *menuBar = new wxMenuBar(wxMB_DOCKABLE);
	menuBar->Append( menuFile, wxT("&File") );
	menuBar->Append( menuOptions, wxT("&Options") );
	menuBar->Append( menuWindow, wxT("&Window") );
	menuBar->Append( menuHelp, wxT("&Help") );
	
	
	
	SetMenuBar( menuBar );

	CreateStatusBar();
	SetStatusText( wxT("Welcome to BibleStudy!") );
	
	
	//wxToolBar *toolbar = CreateToolBar(wxTB_DOCKABLE|wxTB_TEXT|wxTB_NOICONS);
	
	//toolbar->ToggleTool(ID_ToolShowHideBookTree, true);
	//SetToolBar(toolbar);
	
	m_ToolBar = new BookViewToolBar(this, ID_BookViewToolBar, wxTB_HORIZONTAL|wxTB_TEXT|wxTB_NOICONS|wxTB_DOCKABLE| wxNO_BORDER);
	//AddChild(lookup);
	SetToolBar(m_ToolBar);
	
	SetupSplitterWindows();
	
}

void BibleStudyMainFrame::OnOptionChange(wxMenuEvent& event)
{
	if (GetMenuBar()->IsChecked(event.GetId())) {
		m_SwordTools->GetSwordManager()->setGlobalOption(GetMenuBar()->GetLabel(event.GetId()).mb_str(), "On");
	} else {
		m_SwordTools->GetSwordManager()->setGlobalOption(GetMenuBar()->GetLabel(event.GetId()).mb_str(), "Off");
	}
}


void BibleStudyMainFrame::OnActiveModuleChange(wxCommandEvent& event)
{
	UpdateToolbars((BookModule *)event.GetClientData());
}

void BibleStudyMainFrame::UpdateToolbars(BookModule *bm)
{
	

	if (bm) {
		m_ToolBar->SetLookupKey(bm->GetLastLookupKey());
	} else {
		m_ToolBar->SetLookupKey(wxT(""));
	}

}

void BibleStudyMainFrame::OnLookupKey(wxCommandEvent& event)
{
	m_WindowSplit->LookupKey( m_ToolBar->GetLookupKey() );
}

void BibleStudyMainFrame::SetupSplitterWindows()
{	
	m_WindowSplit = new BookViewSplitterCtrl(this, m_SwordTools, wxDefaultPosition, wxDefaultSize);
	
	//sp_toplevel->SplitHorizontally(sp_firstchild, sp_secondchild, 0);
}

void BibleStudyMainFrame::OnNewTab(wxCommandEvent& event)
{
	m_WindowSplit->AddTab();
}

void BibleStudyMainFrame::OnRemoveTab(wxCommandEvent& event)
{
	m_WindowSplit->RemoveTab();
}


void BibleStudyMainFrame::OnShowHideBookTree(wxCommandEvent& event)
{
	m_WindowSplit->ShowHideBookTree();
}

void BibleStudyMainFrame::OnBookTreeChange(wxCommandEvent& event)
{
	GetToolBar()->ToggleTool(ID_ToolShowHideBookTree, event.GetInt());
}

void BibleStudyMainFrame::OnQuit(wxCommandEvent& event)
{
	Close(TRUE);
}

void BibleStudyMainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(wxT("This is BibleStudy bible software.\nMany thanks to the Sword project.\n\nLicensed under the GPL."), wxT("About BibleStudy"), wxOK | wxICON_INFORMATION, this);

}

void BibleStudyMainFrame::OnNewWindow(wxMenuEvent& event)
{
	OpenNewWindow();
}

BibleStudyMainFrame *BibleStudyMainFrame::OpenNewWindow()
{
	BibleStudyMainFrame *frame = new BibleStudyMainFrame(m_SwordTools, APPTITLE, wxPoint(50,50), wxSize(450,340));
	frame->Show(TRUE);
	return frame;
	//SetTopWindow(frame);
}

void BibleStudyMainFrame::OnOpenInNewTab(wxCommandEvent &event)
{
	m_WindowSplit->OpenInNewTab((SWModule *)event.GetClientData());
}

void BibleStudyMainFrame::OnOpenInNewWindow(wxCommandEvent &event)
{
	OpenNewWindow()->DisplayModule((SWModule *)event.GetClientData());
}

void BibleStudyMainFrame::OnOpenInCurrentTab(wxCommandEvent &event)
{
	m_WindowSplit->OpenInCurrentTab((SWModule *)event.GetClientData());
}

void BibleStudyMainFrame::DisplayModule(SWModule *module)
{
	m_WindowSplit->OpenInCurrentTab(module);
}


void BibleStudyMainFrame::OnSplitVertically(wxCommandEvent& event)
{
	m_WindowSplit->SplitVertically();
}

void BibleStudyMainFrame::OnSplitHorizontally(wxCommandEvent& event)
{
	m_WindowSplit->SplitHorizontally();
}

void BibleStudyMainFrame::OnRemoveSplit(wxCommandEvent& event)
{
}
