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

#include "../icons/splitleftright.xpm"

/** Register event handlers */
BEGIN_EVENT_TABLE(BibleStudyMainFrame, wxFrame)
	EVT_MENU(ID_MenuExit, BibleStudyMainFrame::OnExit)
	EVT_MENU(ID_MenuAbout, BibleStudyMainFrame::OnAbout)
	
	EVT_MENU(ID_MenuSplitVertically, BibleStudyMainFrame::OnSplitVertically)
	EVT_MENU(ID_MenuSplitHorizontally, BibleStudyMainFrame::OnSplitHorizontally)
	EVT_MENU(ID_MenuRemoveSplit, BibleStudyMainFrame::OnRemoveActiveView)
	
	EVT_MENU(ID_MenuNewTab, BibleStudyMainFrame::OnNewTab)
	EVT_MENU(ID_MenuCloseTab, BibleStudyMainFrame::OnCloseTab)
	EVT_MENU(ID_MenuShowHideBookTree, BibleStudyMainFrame::OnShowHideBookTree)
	EVT_MENU(ID_MenuNewWindow, BibleStudyMainFrame::OnNewWindow)
	EVT_MENU(ID_MenuCloseWindow, BibleStudyMainFrame::OnCloseWindow)
	
	EVT_MENU(ID_MenuCloseOtherTabs, BibleStudyMainFrame::OnCloseOtherTabs)
	EVT_MENU(ID_MenuDetachTab, BibleStudyMainFrame::OnDetachTab)
	EVT_MENU(ID_MenuDuplicateTab, BibleStudyMainFrame::OnDuplicateTab)

	EVT_MENU(ID_MenuBibleStudyHow, BibleStudyMainFrame::OnShowHowBecomeChristian)
	EVT_MENU(ID_MenuBibleStudyWhy, BibleStudyMainFrame::OnShowWhyBecomeChristian)
	EVT_MENU(ID_MenuBibleStudyGrow, BibleStudyMainFrame::OnShowHowGrowSpiritually)

	
	EVT_MENU_RANGE(ID_MenuTopBookOption, ID_MenuTopBookOption+50, BibleStudyMainFrame::OnOptionChange)

	EVT_TOOL(ID_ToolShowHideBookTree, BibleStudyMainFrame::OnShowHideBookTree)
	//EVT_TOOL(ID_ToolLookupKey, BibleStudyMainFrame::OnLookupKey)
	EVT_TOOL(ID_ToolNewTab, BibleStudyMainFrame::OnNewTab)
	EVT_TOOL(ID_ToolRemoveTab, BibleStudyMainFrame::OnCloseTab)
		
	EVT_OPEN_IN_CURRENT_TAB(-1, BibleStudyMainFrame::OnOpenInCurrentTab)
	EVT_OPEN_IN_NEW_TAB(-1, BibleStudyMainFrame::OnOpenInNewTab)
	EVT_OPEN_IN_NEW_WINDOW(-1, BibleStudyMainFrame::OnOpenInNewWindow)
	
	EVT_ACTIVE_MODULE_CHANGE(-1, BibleStudyMainFrame::OnActiveModuleChange)
	EVT_BOOK_TREE_CHANGE(-1, BibleStudyMainFrame::OnBookTreeChange)
	
	EVT_LOAD_KEY(BibleStudyMainFrame::OnLoadKey)
END_EVENT_TABLE() 


BibleStudyMainFrame::~BibleStudyMainFrame()
{
}

BibleStudyMainFrame::BibleStudyMainFrame(SwordTools *newSwordTools, const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame((wxFrame *)NULL, -1, title, pos, size, wxDEFAULT_FRAME_STYLE,wxT("BibleStudyWindow"))
{

	m_SwordTools = newSwordTools;

	wxMenu *menuFile = new wxMenu();
	wxMenu *menuHelp = new wxMenu();
	wxMenu *menuBibleStudies = new wxMenu();
	wxMenu *menuWindow = new wxMenu();
	wxMenu *menuOptions = new wxMenu();
		
	menuFile->Append( ID_MenuNewWindow, wxT("&New Window") );
	menuFile->Append( ID_MenuCloseWindow, wxT("&Close Window") );
	menuFile->AppendSeparator();
	menuFile->Append( ID_MenuExit, wxT("E&xit") );
	
	menuHelp->Append( ID_MenuAbout, wxT("&About BibleStudy") );
		
	menuWindow->Append( ID_MenuShowHideBookTree, wxT("Show/Hide Book List") );
	menuWindow->AppendSeparator();
	
	//wxMenuItem *menuItemSplitLeftRight = new wxMenuItem(menuWindow, ID_MenuSplitVertically, wxT("Split View &Left/Right"));
	//menuItemSplitLeftRight->SetBitmap(wxBitmap(splitleftright_xpm) );
	//menuWindow->Append( menuItemSplitLeftRight );
	
	menuWindow->Append( ID_MenuSplitVertically, wxT("Split View &Left/Right") );
	
	menuWindow->Append( ID_MenuSplitHorizontally, wxT("Split View &Top/Bottom") );
	menuWindow->Append( ID_MenuRemoveSplit, wxT("&Remove Active View") );
	menuWindow->AppendSeparator();
	menuWindow->Append( ID_MenuNewTab, wxT("&New Tab") );
	menuWindow->Append( ID_MenuCloseTab, wxT("Close Tab") );
	menuWindow->Append( ID_MenuCloseOtherTabs, wxT("Close Other Tabs") );
	menuWindow->Append( ID_MenuDetachTab, wxT("Detach Tab") );
	menuWindow->Append( ID_MenuDuplicateTab, wxT("Duplicate Tab") );
	
	OptionsList optlist;
	optlist = m_SwordTools->GetSwordManager()->getGlobalOptions();
	
	/* Add global options reported by SwordManager */
	OptionsList::iterator it;
	int id = ID_MenuTopBookOption;
	for (it = optlist.begin(); it != optlist.end(); it++) {
		menuOptions->AppendCheckItem(id, wxString(it->c_str(), wxConvUTF8), wxString(m_SwordTools->GetSwordManager()->getGlobalOptionTip(it->c_str()), wxConvUTF8)); 
		/* If global option is on, check the menu item */
		if (!strcmp(m_SwordTools->GetSwordManager()->getGlobalOption(it->c_str()), "On")) {
			menuOptions->Check(id, true);
		} else {
			menuOptions->Check(id, false);
		}
		
		id++;
	}

	menuBibleStudies->Append(ID_MenuBibleStudyWhy, wxT("Why Should I Become a Christian?"));	
	menuBibleStudies->Append(ID_MenuBibleStudyHow, wxT("How Can I Become a Christian?"));
	menuBibleStudies->Append(ID_MenuBibleStudyGrow, wxT("How Can I Grow as a Christian?"));
	
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append( menuFile, wxT("&File") );
	menuBar->Append( menuBibleStudies, wxT("&Bible Studies") );
	menuBar->Append( menuOptions, wxT("&Options") );
	menuBar->Append( menuWindow, wxT("&Window") );
	menuBar->Append( menuHelp, wxT("&Help") );
	
	
	
	SetMenuBar( menuBar );

	CreateStatusBar();
	SetStatusText( wxT("Welcome to BibleStudy!") );
		
	m_ToolBar = new BookViewToolBar(this, ID_BookViewToolBar, wxTB_HORIZONTAL|wxTB_FLAT);
	SetToolBar(m_ToolBar);
	
	SetupSplitterWindows();
}


void BibleStudyMainFrame::OnShowWhyBecomeChristian()
{
	SWModule *mod = NULL;
	mod = m_SwordTools->GetModule("MKJV");

	BibleStudyWizard *wiz = new BibleStudyWizard(this, -1, wxT("Why Should I Become a Christian?"));
	
	wiz->AddPage(NULL, wxT("Why Should You Become A Christian?"), wxT(""));
	wiz->AddPage(mod, wxT("John 3:16"), wxT("jn 3:16"));
	wiz->AddPage(mod, wxT("John 3:20"), wxT("jn 3:20"));
	wiz->AddPage(mod, wxT("John 3:22"), wxT("jn 3:22"));
	
//	BibleStudyWizardPage::Chain(p1, p2);
//	BibleStudyWizardPage::Chain(p2, p3);
	
	//wiz->SetSize(p1->GetBestSize());
	wiz->RunWizard();
}


void BibleStudyMainFrame::OnShowHowBecomeChristian()
{
	SWModule *mod = NULL;
	mod = m_SwordTools->GetModule("MKJV");

	BibleStudyWizard *wiz = new BibleStudyWizard(this, -1, wxT("How Can I Become a Christian?"));
	
	wiz->AddPage(mod, wxT("John 3:16"), wxT("jn 3:16"));
	wiz->AddPage(mod, wxT("John 3:20"), wxT("jn 3:20"));
	wiz->AddPage(mod, wxT("John 3:22"), wxT("jn 3:22"));
	
//	BibleStudyWizardPage::Chain(p1, p2);
//	BibleStudyWizardPage::Chain(p2, p3);
	
	//wiz->SetSize(p1->GetBestSize());
	wiz->RunWizard();
}


void BibleStudyMainFrame::OnShowHowGrowSpiritually()
{
	SWModule *mod = NULL;
	mod = m_SwordTools->GetModule("MKJV");

	BibleStudyWizard *wiz = new BibleStudyWizard(this, -1, wxT("How Can I Grow as a Christian?"));
	
	wiz->AddPage(mod, wxT("John 3:16"), wxT("jn 3:16"));
	wiz->AddPage(mod, wxT("John 3:20"), wxT("jn 3:20"));
	wiz->AddPage(mod, wxT("John 3:22"), wxT("jn 3:22"));
	
//	BibleStudyWizardPage::Chain(p1, p2);
//	BibleStudyWizardPage::Chain(p2, p3);
	
	//wiz->SetSize(p1->GetBestSize());
	wiz->RunWizard();
}

/**
 * Called when an option menu item is changed
 */
void BibleStudyMainFrame::OnOptionChange(wxMenuEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnOptionChange called"));
	if (GetMenuBar()->IsChecked(event.GetId())) {
		m_SwordTools->GetSwordManager()->setGlobalOption(GetMenuBar()->GetLabel(event.GetId()).mb_str(), "On");
	} else {
		m_SwordTools->GetSwordManager()->setGlobalOption(GetMenuBar()->GetLabel(event.GetId()).mb_str(), "Off");
	}
}


void BibleStudyMainFrame::OnActiveModuleChange(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnActiveModuleChange called"));
	UpdateToolbars((BookModule *)event.GetClientData());
}

void BibleStudyMainFrame::UpdateToolbars(BookModule *bm)
{
	if (bm) {
		m_ToolBar->SetLookupKey(bm->GetLastLookupKey());
		m_ToolBar->SetDropDownFrame(bm->GetControl(this));
	} else {
		m_ToolBar->SetLookupKey(wxT(""));
	}

	
}

void BibleStudyMainFrame::OnLoadKey(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnLookupKey called"));
	m_WindowSplit->LookupKey( event.GetString() );
}

void BibleStudyMainFrame::SetupSplitterWindows()
{	
	m_WindowSplit = new BookViewSplitterCtrl(this, m_SwordTools, wxDefaultPosition, wxDefaultSize);
}

void BibleStudyMainFrame::OnNewTab(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnNewTab called"));
	m_WindowSplit->AddTab();
}

void BibleStudyMainFrame::OnCloseTab(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnCloseTab called"));
	m_WindowSplit->CloseTab();
}


void BibleStudyMainFrame::OnShowHideBookTree(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnShowHideBookTree called"));
	m_WindowSplit->ShowHideBookTree();
}

/**
 * Called when BookTree is hid/unhid
 */
void BibleStudyMainFrame::OnBookTreeChange(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnBookTreeChange called"));
	GetToolBar()->ToggleTool(ID_ToolShowHideBookTree, event.GetInt());
}

void BibleStudyMainFrame::OnExit(wxCommandEvent& event)
{
//	ShowSampleWizard();
/*	
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnExit called"));
	wxWindow *window;
		
	window = FindWindowByName(wxT("BibleStudyWindow"));
	
	while (window) {
		window->Close();
		window = FindWindowByName(wxT("BibleStudyWindow"));
	}
*/
}

void BibleStudyMainFrame::OnCloseWindow(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnCloseWindow called"));
	Close(TRUE);
}


void BibleStudyMainFrame::OnAbout(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnAbout called"));
	wxMessageBox(wxT("This is BibleStudy bible software.\nMany thanks to the Sword project.\n\nLicensed under the GPL."), wxT("About BibleStudy"), wxOK | wxICON_INFORMATION, this);
}

void BibleStudyMainFrame::OnNewWindow(wxMenuEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnNewWindow called"));
	OpenNewWindow();
}

BibleStudyMainFrame *BibleStudyMainFrame::OpenNewWindow()
{
	BibleStudyMainFrame *frame = new BibleStudyMainFrame(m_SwordTools, APPTITLE, wxPoint(50,50), wxSize(450,340));
	frame->Show(TRUE);
	return frame;
}

void BibleStudyMainFrame::OnOpenInNewTab(wxCommandEvent &event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnOpenInNewTab called"));
	m_WindowSplit->OpenInNewTab((SWModule *)event.GetClientData());
}

void BibleStudyMainFrame::OnOpenInNewWindow(wxCommandEvent &event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnOpenInNewWindow called"));
	OpenNewWindow()->DisplayModule((SWModule *)event.GetClientData());
}

void BibleStudyMainFrame::OnOpenInCurrentTab(wxCommandEvent &event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnOpenInCurrentTab called"));
	m_WindowSplit->OpenInCurrentTab((SWModule *)event.GetClientData());
}

void BibleStudyMainFrame::DisplayModule(SWModule *module)
{
	m_WindowSplit->OpenInCurrentTab(module);
}

void BibleStudyMainFrame::DisplayModule(BookModule *module)
{
	m_WindowSplit->OpenInCurrentTab(module);
}

void BibleStudyMainFrame::OnSplitVertically(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnSplitVertically called"));
	m_WindowSplit->SplitVertically();
}

void BibleStudyMainFrame::OnSplitHorizontally(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnSplitHorizontally called"));
	m_WindowSplit->SplitHorizontally();
}

void BibleStudyMainFrame::OnRemoveActiveView(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnRemoveActiveView called"));
	m_WindowSplit->RemoveActiveView();
}

void BibleStudyMainFrame::OnCloseOtherTabs(wxMenuEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnCloseOtherTabs called"));
	m_WindowSplit->CloseOtherTabs();
}

/**
 * Called when a detach tab menu is called
 * @todo Make this call request the split to detach a tab, which fires back an
 *       event with the BookModule in question
 */
void BibleStudyMainFrame::OnDetachTab(wxMenuEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnDetachTab called"));
	OpenNewWindow()->DisplayModule(m_WindowSplit->GetActiveBookModule());
	m_WindowSplit->CloseTab();
}


void BibleStudyMainFrame::OnDuplicateTab(wxMenuEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnDuplicateTab called"));
	m_WindowSplit->DuplicateTab();
}
