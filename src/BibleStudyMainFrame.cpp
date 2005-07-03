
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <BibleStudyMainFrame.h>
#include <BookTreeCtrl.h>
#include <BookViewSplitterCtrl.h>
#include <BookViewToolBar.h>
#include <ReadingPlannerToolBar.h>
#include <PrefsDialog.h>
#include <SwordTools.h>
#include <BibleStudyWizard.h>
#include <BookModule.h>

#include <wx/log.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <libreadingplanner/SELStack.h>
#include <libreadingplanner/MultDays.h>
#include <libreadingplanner/RPpdb.h>

#include "../icons/biblestudy.xpm"

using namespace sword;

// #include "../icons/splitleftright.xpm"

/** Register event handlers */
BEGIN_EVENT_TABLE(BibleStudyMainFrame, wxFrame)
	EVT_SIZE(BibleStudyMainFrame::OnSize)

	EVT_MENU(ID_MenuExit, BibleStudyMainFrame::OnExit)
	EVT_MENU(ID_MenuAbout, BibleStudyMainFrame::OnAbout)
	EVT_MENU(ID_MenuSplitVertically, BibleStudyMainFrame::OnSplitVertically)
	EVT_MENU(ID_MenuSplitHorizontally, BibleStudyMainFrame::OnSplitHorizontally)
	EVT_MENU(ID_MenuRemoveSplit, BibleStudyMainFrame::OnRemoveActiveView)
	EVT_MENU(ID_MenuShowStartPage, BibleStudyMainFrame::OnShowStartPage)
	EVT_MENU(ID_MenuShowHideRPToolBar, BibleStudyMainFrame::OnShowHidePlanBar)

	EVT_MENU(ID_MenuNewTab, BibleStudyMainFrame::OnNewTab)
	EVT_MENU(ID_MenuCloseTab, BibleStudyMainFrame::OnCloseTab)
	EVT_MENU(ID_MenuShowHideBookTree, BibleStudyMainFrame::OnShowHideBookTree)
	EVT_MENU(ID_MenuNewWindow, BibleStudyMainFrame::OnNewWindow)
	EVT_MENU(ID_MenuCloseWindow, BibleStudyMainFrame::OnCloseWindow)
	EVT_MENU(ID_MenuReadingPlannerWiz, BibleStudyMainFrame::OnReadingPlannerWiz)

	EVT_MENU(ID_MenuCloseOtherTabs, BibleStudyMainFrame::OnCloseOtherTabs)
	EVT_MENU(ID_MenuDetachTab, BibleStudyMainFrame::OnDetachTab)
	EVT_MENU(ID_MenuDuplicateTab, BibleStudyMainFrame::OnDuplicateTab)
	EVT_MENU(ID_MenuBibleStudyHow, BibleStudyMainFrame::OnShowHowBecomeChristian)
	EVT_MENU(ID_MenuBibleStudyWhy, BibleStudyMainFrame::OnShowWhyBecomeChristian)
  EVT_MENU(ID_MenuBibleStudyGrow,
         BibleStudyMainFrame::OnShowHowGrowSpiritually) 
	EVT_MENU(ID_MenuPrefs, BibleStudyMainFrame::OnPrefs)

  EVT_MENU_RANGE(ID_MenuTopBookOption, ID_MenuTopBookOption + 50,
                 BibleStudyMainFrame::OnOptionChange)

	EVT_TOOL(ID_ToolShowHideBookTree, BibleStudyMainFrame::OnShowHideBookTree)
  // EVT_TOOL(ID_ToolLookupKey, BibleStudyMainFrame::OnLookupKey)
	EVT_TOOL(ID_ToolNewTab, BibleStudyMainFrame::OnNewTab)
	EVT_TOOL(ID_ToolRemoveTab, BibleStudyMainFrame::OnCloseTab)
	EVT_OPEN_IN_CURRENT_TAB(-1, BibleStudyMainFrame::OnOpenInCurrentTab)
	EVT_OPEN_IN_NEW_TAB(-1, BibleStudyMainFrame::OnOpenInNewTab)
	EVT_OPEN_IN_NEW_WINDOW(-1, BibleStudyMainFrame::OnOpenInNewWindow)
	EVT_ADD_TO_CURRENT_TAB(-1, BibleStudyMainFrame::OnAddToCurrentTab)
	EVT_ACTIVE_MODULE_CHANGE(-1, BibleStudyMainFrame::OnActiveModuleChange)
	EVT_BOOK_TREE_CHANGE(-1, BibleStudyMainFrame::OnBookTreeChange)
	EVT_SHOW_BIBLESTUDY(BibleStudyMainFrame::OnShowBibleStudy)
	EVT_LOAD_KEY(BibleStudyMainFrame::OnLoadKey)
	EVT_BROWSE_KEY(BibleStudyMainFrame::OnBrowseKey)
	EVT_BROWSE_BACKWARD(BibleStudyMainFrame::OnBrowseBackward)
	EVT_BROWSE_FORWARD(BibleStudyMainFrame::OnBrowseForward)
	EVT_SEARCH(BibleStudyMainFrame::OnSearch)
	EVT_BROWSE_NEXT_DAY(BibleStudyMainFrame::OnNextDay)
	EVT_BROWSE_PREV_DAY(BibleStudyMainFrame::OnPrevDay)
	EVT_CHECK_DONE(BibleStudyMainFrame::OnCheckDayDone)
	EVT_PLAN_CHANGED(BibleStudyMainFrame::OnPlanChanged)
END_EVENT_TABLE()

DEFINE_EVENT_TYPE(bsEVT_EXIT_APP)

BibleStudyMainFrame::~BibleStudyMainFrame()
{
	InstallCurrentPlan();
	if(m_pdbFile) delete m_pdbFile;
	SaveConfig();
}

BibleStudyMainFrame::BibleStudyMainFrame(SwordTools *newSwordTools, 
                                         const wxString & title, 
					 const wxPoint & pos, 
					 const wxSize & size):
    wxFrame((wxFrame *) NULL, -1, title, pos, size, wxDEFAULT_FRAME_STYLE,
            wxT("BibleStudyWindow")),
    m_SwordTools(newSwordTools)
{
	
	LoadConfig();

	m_PlanToolBar = NULL;
	m_WindowSplit = NULL;
	// Open and read an existing ReadingPlan.
	
	if(m_Config.m_PalmIntegration)
	{
		m_pdbFile = new RPpdb(m_Config.m_PalmUserBackupPath.mb_str());
	}else
	{
		wxString localPath = ::wxGetHomeDir();
		localPath += wxT("/.biblestudy");
		if(!wxFileName::DirExists(localPath))
			wxFileName::Mkdir(localPath);
		localPath += wxT("/readingplans");
		if(!wxFileName::DirExists(localPath))
			wxFileName::Mkdir(localPath);
		m_pdbFile = new RPpdb(localPath.mb_str());
	}
	// Set first plan name found as current plan.
	
	PDBNode* firstPlan = NULL;
	if(m_pdbFile->PDBGetNextDatabase(true, &firstPlan) == errNone)
		m_pdbFile->PDBOpenDatabase(firstPlan);


	m_PlanDate = wxDateTime::Today();

	wxWindowDisabler disableAll;

	wxMenu *menuFile = new wxMenu();
	wxMenu *menuHelp = new wxMenu();
	wxMenu *menuBibleStudies = new wxMenu();
	wxMenu *menuWindow = new wxMenu();
	wxMenu *menuOptions = new wxMenu();

	SetIcon(wxIcon(biblestudy_xpm));

	menuFile->Append(ID_MenuNewWindow, wxT("&New Window"));
	menuFile->Append(ID_MenuCloseWindow, wxT("&Close Window"));
	menuFile->AppendSeparator();
	menuFile->Append(ID_MenuReadingPlannerWiz, wxT("&ReadingPlanner Wizard..."));
	menuFile->AppendSeparator();
  menuFile->Append(ID_MenuExit, wxT("E&xit"));

  menuHelp->Append(ID_MenuAbout, wxT("&About BibleStudy"));

  menuWindow->Append(ID_MenuShowStartPage, wxT("Show Start Page"));
	menuWindow->Append(ID_MenuShowHideBookTree, wxT("Show/Hide Book List"));
	menuWindow->Append(ID_MenuShowHideRPToolBar, wxT("Show/Hide ReadingPlanner Toolbar"));
	menuWindow->AppendSeparator();

  menuWindow->Append(ID_MenuSplitVertically, wxT("Split View &Left/Right"));

  menuWindow->Append(ID_MenuSplitHorizontally, wxT("Split View &Top/Bottom"));
  menuWindow->Append(ID_MenuRemoveSplit, wxT("&Remove Active View"));
	menuWindow->AppendSeparator();
  menuWindow->Append(ID_MenuNewTab, wxT("&New Tab"));
  menuWindow->Append(ID_MenuCloseTab, wxT("Close Tab"));
  menuWindow->Append(ID_MenuCloseOtherTabs, wxT("Close Other Tabs"));
  menuWindow->Append(ID_MenuDetachTab, wxT("Detach Tab"));
  menuWindow->Append(ID_MenuDuplicateTab, wxT("Duplicate Tab"));

	StringList optlist;

	optlist = m_SwordTools->GetSwordManager()->getGlobalOptions();

  // unsigned char mychars[13];
  // mychars[0] = 68;
  // mychars[1] = 69;
  // mychars[2] = 226;
  // mychars[3] = 128;
  // mychars[4] = 156;
  // mychars[5] = 67;
  // mychars[6] = 46;
  // mychars[7] = 46;
  // mychars[8] = 46;
  // mychars[9] = 226;
  // mychars[10] = 128;
  // mychars[11] = 157;
  // mychars[12] = 0;
  // 
  // wxString leftquote = wxString((const char *)mychars, wxConvUTF8);
  // 
  // wxMessageBox(leftquote, wxT("Quote Test"), wxOK |
  // wxICON_INFORMATION, this);

  /*
   * Add global options reported by SwordManager 
   */
	StringList::iterator it;
	int id = ID_MenuTopBookOption;
	
	menuOptions->Append(ID_MenuPrefs, wxT("Preferences"));
	menuOptions->AppendSeparator();

	for (it = optlist.begin(); it != optlist.end(); it++) {
    menuOptions->AppendCheckItem(id, wxString(it->c_str(), wxConvUTF8),
                                 wxString(m_SwordTools->GetSwordManager()->
                                          getGlobalOptionTip(it->c_str()),
                                          wxConvUTF8));
    /*
     * If global option is on, check the menu item 
     */
    if (!strcmp
        (m_SwordTools->GetSwordManager()->getGlobalOption(it->c_str()), "On")) {
			menuOptions->Check(id, true);
		} else {
			menuOptions->Check(id, false);
		}

		id++;
	}

  // menuBibleStudies->Append(ID_MenuBibleStudyWhy, wxT("Why Should I
  // Become a Christian?"));
  menuBibleStudies->Append(ID_MenuBibleStudyHow,
                           wxT("How Can I Become a Christian?"));
  menuBibleStudies->Append(ID_MenuBibleStudyGrow,
                           wxT("How Can I Grow as a Christian?"));

	wxMenuBar *menuBar = new wxMenuBar();

  menuBar->Append(menuFile, wxT("&File"));
  menuBar->Append(menuBibleStudies, wxT("&Bible Studies"));
  menuBar->Append(menuOptions, wxT("&Options"));
  menuBar->Append(menuWindow, wxT("&Window"));
  menuBar->Append(menuHelp, wxT("&Help"));

  SetMenuBar(menuBar);

	CreateStatusBar();
  SetStatusText(wxT("Welcome to BibleStudy!"));

  m_ToolBar =
    new BookViewToolBar(this, ID_BookViewToolBar, wxTB_HORIZONTAL | 
                        wxTB_FLAT );
	SetToolBar(m_ToolBar);

	// Add the ReadingPlanner toolbar here.
  
  m_PlanToolBar =
    new ReadingPlannerToolBar(this, ID_ReadingPlannerToolBar, wxTB_HORIZONTAL | 
                       wxTB_FLAT );
	UpdatePlanToolBar();


	SetupSplitterWindows();
	LayoutChildren();
}

void BibleStudyMainFrame::UpdatePlanToolBar()
{
	if(m_PlanToolBar && m_pdbFile->DBIsOpen() && m_pdbFile->PDBGetLastError() == errNone)
	{
		int index = m_pdbFile->FindDayIndex((RPDate)(&m_PlanDate));
		int percent = 0;
		bool done = false;
		if(index >= 0)
		{
			percent = m_pdbFile->PercentDone();
			done =  m_pdbFile->PDBGetRecord(index)->pSel->m_bnDone;
			m_PlanToolBar->SetControlStates(percent,done, true);
		}
		else m_PlanToolBar->SetControlStates(m_pdbFile->PercentDone(), false, false);
	}
}
/*
 * note: this biblestudy is hardcoded into the .exe to make sure that it
 * can never be seperated from the application 
 */
void BibleStudyMainFrame::OnShowWhyBecomeChristian(wxCommandEvent &)
{
	SWModule *mod = NULL;

  mod = m_SwordTools->GetModule("KJV");
  wxWindowDisabler *disableAll = new wxWindowDisabler();

  BibleStudyWizard *wiz = new BibleStudyWizard(this, -1,
                                               wxT
                                               ("Why Should I Become a Christian?"));

  wiz->AddPage(NULL,
               wxT
               ("You are probably wondering why you are reading this right now.\n\nYou received this software because someone cares about you and what happens to you when you die.\n\nThe following pages will discuss where you stand with a Holy and Loving God. \n\nThe information contained here is based on the Christian Bible. If you have questions about the bible, and wonder why it should have any authority in your life I suggest that you look at this website:\nhttp://www.answersingenesis.org/home/area/faq/bible.asp"),
               wxT(""));
  wiz->AddPage(mod,
               wxT
               ("The bible teaches that everyone has sinned. What is sin? Sin is any thought or action that is not perfect. Have you ever done anything that you knew was wrong? Like being mean? Then you have sinned."),
               wxT("Ro 3:23"));
  wiz->AddPage(mod,
               wxT
               ("Because God is perfect, he can not live with sin, so, the \"wage of sin is death.\" Everyone dies someday, we all know that. Here the Bible is talking about eternal death, or eternal seperation from God."),
               wxT("Ro 6:23"));
  wiz->AddPage(mod,
               wxT
               ("Because of the sin of Adam, the first human, all now have the tendancy to sin. Thankfully, just as sin entered the world through one man, one Man can remove the sin of the world."),
               wxT("Ro 5:12"));
  wiz->AddPage(mod,
               wxT
               ("It is easy for us to be nice to someone who is nice to us, but God reached out to us while we weren't his friend and sent his son, Jesus to die for our sin."),
               wxT("Ro 5:8"));
  wiz->AddPage(mod,
               wxT
               ("If you accept the death of Jesus as the covering for your sin, you will not have to face eternal separation from God."),
               wxT("Ro 10:9-13"));
	delete disableAll;
	
	wiz->RunWizard();
	wiz->Destroy();
}

void BibleStudyMainFrame::OnShowHowBecomeChristian(wxCommandEvent &)
{
	SWModule *mod = NULL;

  mod = m_SwordTools->GetModule("KJV");

	wxWindowDisabler *disableAll = new wxWindowDisabler();	

  BibleStudyWizard *wiz = new BibleStudyWizard(this, -1,
                                               wxT
                                               ("How Can I Become a Christian?"));

  wiz->AddPage(NULL,
               wxT
               ("Becoming a Christian means loving Christ, serving His church, and wanting to spread His Love throughout the world."),
               wxT(""));
  wiz->AddPage(mod,
               wxT
               ("Recognize that God loves us but our sin has separated us from God, fram a live with eternal purpose, and from a healthy relationship with others."),
               wxT("ro 3:23"));
  wiz->AddPage(mod,
               wxT
               ("Realize you cannot do enough good to earn God's forgiveness from sin, nor can you find true fulfillment through your own efforts."),
               wxT("eph 2:8-9"));
  wiz->AddPage(mod,
               wxT
               ("Jesus Christ alone can provide forgiveness from eternal punishment for sin. He alone can free us from the present penalty of sin, our selfishness, which damages our relationships with others. He alone can take away the price of sin, our sense of emptiness, and give our lives meaning and purpose."),
               wxT("jn 14:6"));
  wiz->AddPage(mod,
               wxT
               ("Confess, believe, and repent in order to be saved from sin."),
               wxT("Ro 10:9; Acts 3:19"));
  wiz->AddPage(mod,
               wxT
               ("Follow Jesus by observing His teachings, participating in His church, and furthering His mission."),
               wxT("jn 12:26"));
  wiz->AddPage(mod,
               wxT
               ("If you have questions regarding the Christian Faith or if you are still investigating Christianity, please call 1-800-NEED-HIM"),
               wxT(""));
	
	delete disableAll;	

	wiz->RunWizard();
	wiz->Destroy();
}

void BibleStudyMainFrame::OnShowHowGrowSpiritually(wxCommandEvent &)
{
	SWModule *mod = NULL;

  mod = m_SwordTools->GetModule("KJV");
	wxWindowDisabler *disableAll = new wxWindowDisabler();	

  BibleStudyWizard *wiz = new BibleStudyWizard(this, -1,
                                               wxT
                                               ("How Can I Grow as a Christian?"));

  wiz->AddPage(mod,
               wxT
               ("Now that you have started your new life, you are probably asking yourself \"What do I do now?\"\n\nThe old habits and character traits that marked your life before Christ are passing away."),
               wxT("II Cor 5:17"));
  wiz->AddPage(mod,
               wxT
               ("Allow the Holy Spirit (God's Spirit) to work in and through you."),
               wxT("John 16:13; John 14:16"));
  wiz->AddPage(mod,
               wxT
               ("Read God's Word.\n\nAs much as we need daily food to nourish our physical bodies, we need spiritual nourishment."),
               wxT("Mat 14:16"));
  wiz->AddPage(mod,
               wxT
               ("Talk to God.\n\nNow that you belong to Him, do not hesitate to talk with Him daily."),
               wxT("I John 5:14"));
  wiz->AddPage(mod,
               wxT
               ("Get involved with God's people.\n\nYou are special and unique, created with gifts and talents that are needed in God's kingdom."),
               wxT("I Cor 12:14"));
  wiz->AddPage(mod,
               wxT
               ("Guard yourself against temptation.\n\nWe do have an enemy. He is called the Devil, Satan. Now that you have given your life over to God, he will come tempt you to change your ming. Guard yourself!"),
               wxT("James 4:7-8; I Peter 5:8-9"));
  wiz->AddPage(mod,
               wxT
               ("Rejoice!\n\nYou belong to God. You are His child and in His family! You will always be in His presence. Jesus is ocming back for all His children!"),
               wxT("Jn 14:3"));
	delete disableAll;

	wiz->RunWizard();
	wiz->Destroy();
}

/**
 * Called when an option menu item is changed
 */
void BibleStudyMainFrame::OnOptionChange(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnOptionChange called"));
	if (GetMenuBar()->IsChecked(event.GetId())) {
    if (GetMenuBar()->GetLabel(event.GetId()) != wxT("Transliteration")) {
      m_SwordTools->GetSwordManager()->setGlobalOption(GetMenuBar()->
                                                       GetLabel(event.GetId()).
                                                       mb_str(), "On");
    } else {
      m_SwordTools->GetSwordManager()->setGlobalOption(GetMenuBar()->
                                                       GetLabel(event.GetId()).
                                                       mb_str(), "ISO");
    }
	} else {
    m_SwordTools->GetSwordManager()->setGlobalOption(GetMenuBar()->
                                                     GetLabel(event.GetId()).
                                                     mb_str(), "Off");
	}
}

void BibleStudyMainFrame::OnActiveModuleChange(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnActiveModuleChange called"));
  UpdateToolbars((BookModule *) event.GetClientData());
}

void BibleStudyMainFrame::UpdateToolbars(BookModule * bm)
{
	if (bm) {
		if (bm->GetLastSearch() == wxT("")) {
			m_ToolBar->SetLookupKey(bm->GetLastLookupKey());
		} else {
			m_ToolBar->SetLookupKey(bm->GetLastSearch());
		}

		m_ToolBar->SetDropDownFrame(bm->GetControl(this));
		GetMenuBar()->Enable(ID_MenuDetachTab, true);
		GetMenuBar()->Enable(ID_MenuDuplicateTab, true);

	} else {
		GetMenuBar()->Enable(ID_MenuDetachTab, false);
		GetMenuBar()->Enable(ID_MenuDuplicateTab, false);
		m_ToolBar->SetLookupKey(wxT(""));
		m_ToolBar->SetDropDownFrame(NULL);
	}
}

void BibleStudyMainFrame::OnLoadKey(wxCommandEvent & event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnLookupKey called"));
  m_WindowSplit->LookupKey(event.GetString());
}

void BibleStudyMainFrame::OnBrowseKey(wxCommandEvent & event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnLookupKey called"));
	m_WindowSplit->BrowseKey(event.GetString());
	UpdateToolbars(m_WindowSplit->GetActiveBookModule());
}

void BibleStudyMainFrame::OnBrowseForward(wxCommandEvent & event)
{
	m_WindowSplit->BrowseForward();
	UpdateToolbars(m_WindowSplit->GetActiveBookModule());
}

void BibleStudyMainFrame::OnBrowseBackward(wxCommandEvent & event)
{
	m_WindowSplit->BrowseBackward();
	UpdateToolbars(m_WindowSplit->GetActiveBookModule());
}

void BibleStudyMainFrame::OnSearch(wxCommandEvent & event)
{
  m_WindowSplit->Search(*(m_ToolBar->GetRange()), event.GetString(), -2);
}

void BibleStudyMainFrame::OnNextDay(wxCommandEvent & event)
{
	m_PlanDate.Add(wxDateSpan(0,0,0,1));
	UpdatePlanToolBar();
	m_WindowSplit->RefreshStartPages(BuildStartPage());
}

void BibleStudyMainFrame::OnPrevDay(wxCommandEvent & event)
{
	m_PlanDate.Subtract(wxDateSpan(0,0,0,1));
	UpdatePlanToolBar();
	m_WindowSplit->RefreshStartPages(BuildStartPage());
}

void BibleStudyMainFrame::SetupSplitterWindows()
{
  m_WindowSplit =
    new BookViewSplitterCtrl(this, m_SwordTools, wxDefaultPosition,
                             wxDefaultSize);
}

void BibleStudyMainFrame::OnNewTab(wxCommandEvent & event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnNewTab called"));
	m_WindowSplit->AddTab();
}

void BibleStudyMainFrame::OnCloseTab(wxCommandEvent & event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnCloseTab called"));
	m_WindowSplit->CloseTab();
}

void BibleStudyMainFrame::OnShowHideBookTree(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnShowHideBookTree called"));
	m_WindowSplit->ShowHideBookTree();
}

/**
 * Called when BookTree is hid/unhid
 */
void BibleStudyMainFrame::OnBookTreeChange(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnBookTreeChange called"));
	GetToolBar()->ToggleTool(ID_ToolShowHideBookTree, event.GetInt());
}

void BibleStudyMainFrame::OnExit(wxCommandEvent & event)
{
	wxCommandEvent eventCustom(bsEVT_EXIT_APP);
	eventCustom.SetEventObject(this);
	ProcessEvent(eventCustom);
}

void BibleStudyMainFrame::OnCloseWindow(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnCloseWindow called"));
	Close(TRUE);
}

void BibleStudyMainFrame::OnShowBibleStudy(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnShowBibleStudy called"));

	if (event.GetString() == wxT("How_Can_I_Become_A_Christian")) {
		OnShowHowBecomeChristian(event);
	}

	if (event.GetString() == wxT("How_Can_I_Grow_As_A_Christian")) {
		OnShowHowGrowSpiritually(event);
	}

}

void BibleStudyMainFrame::OnAbout(wxCommandEvent & event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnAbout called"));
  wxMessageBox(wxT
               ("This is BibleStudy bible software.\nMany thanks to the Sword project. (www.crosswire.org/sword)\n\nAlso Thanks to Timothy Butler for the use of the icons.\n\nLicensed under the GPL (http://www.gnu.org/licenses/gpl.html).\nPlease distribute freely."),
               wxT("About BibleStudy"), wxOK | wxICON_INFORMATION, this);
}

void BibleStudyMainFrame::OnNewWindow(wxCommandEvent & event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnNewWindow called"));
	OpenNewWindow();
}

BibleStudyMainFrame *BibleStudyMainFrame::OpenNewWindow()
{
  BibleStudyMainFrame *frame =
    new BibleStudyMainFrame(m_SwordTools, APPTITLE, wxPoint(50, 50),
                            wxSize(450, 340));

	frame->Show(TRUE);
	return frame;
}

void BibleStudyMainFrame::OnOpenInNewTab(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnOpenInNewTab called"));
  m_WindowSplit->OpenInNewTab((SWModule *) event.GetClientData());
}

void BibleStudyMainFrame::OnOpenInNewWindow(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnOpenInNewWindow called"));
  OpenNewWindow()->DisplayModule((SWModule *) event.GetClientData());
}

void BibleStudyMainFrame::OnOpenInCurrentTab(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnOpenInCurrentTab called"));
  m_WindowSplit->OpenInCurrentTab((SWModule *) event.GetClientData());
}

void BibleStudyMainFrame::OnAddToCurrentTab(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnAddToCurrentTab called"));
  m_WindowSplit->AddToCurrentTab((SWModule *) event.GetClientData());
}

void BibleStudyMainFrame::DisplayModule(SWModule * module)
{
	m_WindowSplit->OpenInCurrentTab(module);
}

void BibleStudyMainFrame::DisplayModule(BookModule * module)
{
	m_WindowSplit->OpenInCurrentTab(module);
}

void BibleStudyMainFrame::OnSplitVertically(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnSplitVertically called"));
	m_WindowSplit->SplitVertically();
}

void BibleStudyMainFrame::OnSplitHorizontally(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnSplitHorizontally called"));
	m_WindowSplit->SplitHorizontally();
}

void BibleStudyMainFrame::OnRemoveActiveView(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnRemoveActiveView called"));
	m_WindowSplit->RemoveActiveView();
}

void BibleStudyMainFrame::OnCloseOtherTabs(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnCloseOtherTabs called"));
	m_WindowSplit->CloseOtherTabs();
}

/**
 * Called when a detach tab menu is called
 * @todo Make this call request the split to detach a tab, which fires back an
 *       event with the BookModule in question
 */
void BibleStudyMainFrame::OnDetachTab(wxCommandEvent & event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnDetachTab called"));
	wxWindowDisabler disableAll;

	OpenNewWindow()->DisplayModule(m_WindowSplit->GetActiveBookModule());
	m_WindowSplit->CloseTab();
}

void BibleStudyMainFrame::OnDuplicateTab(wxCommandEvent & event)
{
  wxLogTrace(wxTRACE_Messages,
             wxT("BibleStudyMainFrame::OnDuplicateTab called"));
	m_WindowSplit->DuplicateTab();
}

void BibleStudyMainFrame::OnShowStartPage(wxCommandEvent & event)
{
	ShowStartPage();
}

void BibleStudyMainFrame::OnShowReadingPlanPage(wxCommandEvent &event)
{
	ShowReadingPlan();
}

void BibleStudyMainFrame::ShowStartPage()
{
	wxString page = BuildStartPage();
	m_WindowSplit->OpenInCurrentTab(page);
}

wxString BibleStudyMainFrame::BuildStartPage()
{
	wxString page;

	page = wxT("<html><title>Start Page</title>");
	page += wxT("<table>");
  page +=
    wxT
    ("<tr><td bgcolor=#000000 colspan=2><table cellpadding=1 cellspacing=0 width='100%'><tr><td align=center bgcolor=#000099 border=1 width='100%'><font color=#FFFFFF>")
    + Heading() + wxT("</font></td></tr></table></td></tr>");
  page +=
    wxT("<tr><td valign=top>") + BibleStudies() +
    wxT("</td><td valign=top rowspan=2>");
	page += InsertReadingPlan();
	page += ProverbOfTheDay() +  wxT("</td></tr>");
	page += wxT("<tr><td valign=top>") + DevotionalOfTheDay() + wxT("</td></tr>");
	page += wxT("</table>");
	page += wxT("</html>");
	return page;
}

 /* 
	* Use this to open a new page showing only the ReadingPlan
	*/
void BibleStudyMainFrame::ShowReadingPlan()
{
	wxString page;
	wxDateTime today = wxDateTime::Today();

	page = wxT("<html><title>ReadingPlanner</title>");
	page += wxT("<table>");
	page += wxT("<tr><td bgcolor=#000000 colspan=2><table cellpadding=1 cellspacing=0 width='100%'><tr><td align=center bgcolor=#000099 border=1 width='100%'><font color=#FFFFFF>") + ReadingPlannerHeading() + wxT("</font></td></tr></table></td></tr>");
	page += wxT("<tr><td valign=top>");
	page += InsertReadingPlan();
	page += wxT("</td></tr>");
	page += wxT("</table>");
	page += wxT("</html>");

	wxLogDebug(page);

	m_WindowSplit->OpenInCurrentTab(page);
}
	/*
	 * Use this to insert a reading plan into any page.
	 */
wxString BibleStudyMainFrame::InsertReadingPlan() const
{
	char dbName[MAX_NAME_LEN + 4];
	wxString output;
	PDBErr lastErr = m_pdbFile->PDBGetLastError();
	if(!m_pdbFile->DBIsOpen() || lastErr != errNone)
		return output = wxT("Error Reading Plan File"); 
	m_pdbFile->PDBDatabaseInfo(dbName);
	m_pdbFile->StripName(dbName);
	int index = m_pdbFile->FindDayIndex((RPDate)(&m_PlanDate));
	output = wxT("<table cellpadding=1 cellspacing=0 width='100%'><tr><td align=center bgcolor=#215697><font color=#FFFFFF>ReadingPlan</font></td></tr>");
	output += wxT("<tr><td>");
	output += wxT("<b><i><font size=+1>") + wxString(dbName,wxConvUTF8) + wxT("</i></b>  - ");
	output += m_PlanDate.FormatDate() + wxT("</font><br>");
	if(index >= 0)
	{
		output += BuildStringAssignment(m_pdbFile->PDBGetRecord(index));
	}else output += wxT("Nothing Assigned for Today");
	output += wxT("</td></tr></table>");
	return output;
}

wxString BibleStudyMainFrame::ProverbOfTheDay() const
{
	wxString output;
	wxString key;
	wxDateTime today = wxDateTime::Today();
  BookModule web(m_SwordTools->GetModule("KJV"));

	key = wxT("prov ");
	key += wxString::Format(wxT("%i"), today.GetDay());

  output =
    wxT
    ("<table cellpadding=1 cellspacing=0><tr><td align=center bgcolor=#990000><font color=#FFFFFF>Proverb Of The Day</font></td></tr>");
	output += wxT("<tr><td>");
	output += web.LookupKey(key);
	output += wxT("</td></tr></table>");
	return output;
}

wxString BibleStudyMainFrame::BibleStudies() const
{
	wxString output;

  output =
    wxT
    ("<table cellpadding=1 cellspacing=0 width='100%'><tr><td align=center bgcolor=#990099><font color=#FFFFFF>Bible Studies</font></td></tr>");
  output +=
    wxT
    ("<tr><td><a href='biblestudy://How_Can_I_Become_A_Christian'>How Can I Become a Christian?</a></td></tr>");
  output +=
    wxT
    ("<tr><td><a href='biblestudy://How_Can_I_Grow_As_A_Christian'>How Can I Grow as a Christian?</a></td></tr>");
	output += wxT("</table>");
	return output;
}

wxString BibleStudyMainFrame::SearchBox() const
{
	wxString output;

  output =
    wxT
    ("<table cellpadding=1 cellspacing=0><tr><td align=center bgcolor=#FFAAFF>Search</td></tr>");
  output +=
    wxT
    ("<tr><td><form><input type=text><input type=submit value=Search></form></td></tr>");
	output += wxT("</table>");
	return output;
}

wxString BibleStudyMainFrame::DevotionalOfTheDay() const
{
	wxString output;
	wxDateTime today = wxDateTime::Today();
	BookModule sme(m_SwordTools->GetModule("SME"));
	wxString key;

  key =
    wxString::Format(wxT("%02i.%02i"), today.GetMonth() + 1, today.GetDay());

  output =
    wxT
    ("<table cellpadding=1 cellspacing=0><tr><td align=center bgcolor=#009900><font color=#FFFFFF>Daily Devotional</font></td></tr>");
	output += wxT("<tr><td>");
	output += sme.LookupKey(key);
	output += wxT("</td></tr></table>");
	return output;
}

wxString BibleStudyMainFrame::Heading() const
{
	wxString output;
	wxDateTime today = wxDateTime::Today();
	output = wxT("<b><font size=+1>Welcome To BibleStudy ") + today.FormatDate() + wxT("</font></b>");
	return output;
}

wxString BibleStudyMainFrame::ReadingPlannerHeading()
{
	wxString output;
	wxDateTime today = wxDateTime::Today();
	output = wxT("<b><font size=+1>ReadingPlanner for BibleStudy ") + today.FormatDate() + wxT("</font></b>");
	return output;
}

void BibleStudyMainFrame::OnReadingPlannerWiz(wxCommandEvent& event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BibleStudyMainFrame::OnReadingPlannerWiz called"));
	RPDate dateBegin, dateEnd;
	DAYFLAGS dayFlags;
	CSELStack SEL_List;
	CMultDays readingDays;
	char pathName[MAX_PATH_NAME];
	memset(pathName,0,MAX_PATH_NAME);
	if(m_Config.m_PalmIntegration)
		strcpy(pathName, m_Config.m_PalmUserBackupPath.mb_str());
	else
	{		
		wxString localPath = ::wxGetHomeDir();
		localPath += wxT("/.biblestudy/readingplans");
		strcpy(pathName, localPath.mb_str());
	}
	RPpdb pdbFile(pathName);

	ReadingPlanWizard *wizard = new ReadingPlanWizard(this, &rpBible);

	if(wizard->Run())
	{
		dateBegin = wizard->getBeginDate();
		dateEnd = wizard->getEndDate();
		dayFlags = wizard->getDayFlags();
		wxString newPlanName = wizard->getPlanName();
		newPlanName += wxT("DTrp");

		buildKJVSEL(&rpBible,SEL_List);
		readingDays.reInitialize(dateBegin, dateEnd, dayFlags);
		calcReadingDays(SEL_List, readingDays);
		__u8 bookNames[MAX_BOOKS][MAX_BOOK_NAME];
		for (int i=0; i<MAX_BOOKS; i++) {
			strcpy((char *)bookNames[i], rpBible.getName(i).c_str());
		}
		char name[newPlanName.size()];
		strcpy(name, newPlanName.mb_str());
		pdbFile.NewReadingPlan(name, readingDays, getPalmDateType(dateBegin), getPalmDateType(dateEnd), dayFlags, 0, bookNames);
		m_pdbFile->Refresh();
		// Now we prepare the plan for install on the next HotSync.
		char	userName[256],
					planName[MAX_NAME_LEN + 4];
		strcpy(userName, m_Config.m_PalmUserName.mb_str());
		pdbFile.PDBDatabaseInfo(planName);
		pdbFile.Install(userName,planName);
	}
	m_PlanToolBar->SetComboPlanNames();
}

wxString BibleStudyMainFrame::BuildStringAssignment(dayRecord* recP) const
{
	int count;	
	wxString strBook, output;
	int prevBook = recP->pSel[0].m_nBookNum;
	output = wxT("<b>");
	output += wxString(rpBible.getName(recP->pSel[0].m_nBookNum).c_str(), wxConvUTF8);
	output += wxT("</b><br>   Chapter: ");
	strBook = wxString(rpBible.getName(recP->pSel[0].m_nBookNum).c_str(),wxConvUTF8);
	output += GetLinkString(strBook, recP->pSel[0].m_nChapterNum + 1);
	for(count = 1;count < recP->totalAssigned; count++)
	{
		strBook = wxString(rpBible.getName(recP->pSel[count].m_nBookNum).c_str(),wxConvUTF8);
		if(recP->pSel[count].m_nBookNum != prevBook)
		{
			output += wxT("<br><b>");
			output += strBook;
			output += wxT("</b><br>   Chapter: ");
			output += GetLinkString(strBook, recP->pSel[count].m_nChapterNum + 1);
			prevBook = recP->pSel[count].m_nBookNum;
		}else
		{
			output += wxT(", ");
			output += GetLinkString(strBook, recP->pSel[count].m_nChapterNum + 1);
		}
	}
	return output;
}

wxString BibleStudyMainFrame::GetLinkString(wxString strBook, int chapter) const
{
	// returns something like...
	// <a href=\"passage=Isaiah 7\" >link </a>
	wxString tempStr = wxT(" %i\">%i</a>");
	wxString output = wxT("<a href=\"passage=");
	output += strBook;
	output += wxString::Format(tempStr, chapter, chapter);
	return output;
}

void BibleStudyMainFrame::LayoutChildren()
{
    int offset = 0;
		wxSize size = GetClientSize();
		if(m_PlanToolBar != NULL)
		{
			m_PlanToolBar->SetSize(size.x, -1);
			m_PlanToolBar->Move(0, 0);
			offset = m_PlanToolBar->GetSize().y;
		}

    if(m_WindowSplit != NULL)
			m_WindowSplit->SetSize(0, offset, size.x , size.y - offset);
}

void BibleStudyMainFrame::OnSize(wxSizeEvent& event)
{
    if (m_PlanToolBar)
    {
        LayoutChildren();
    }
    else
    {
        event.Skip();
    }
}

void BibleStudyMainFrame::OnCheckDayDone(wxCommandEvent &event)
{
	m_pdbFile->MarkDone((RPDate)(&m_PlanDate), event.IsChecked());
	UpdatePlanToolBar();
}

void BibleStudyMainFrame::SetPlanDate(const wxDateTime& date) 
{
	m_PlanDate = date;
	m_WindowSplit->RefreshStartPages(BuildStartPage());
	UpdatePlanToolBar();
}

void BibleStudyMainFrame::OnShowHidePlanBar(wxCommandEvent& WXUNUSED(event))
{
	ShowHidePlanBar(m_PlanToolBar == NULL);
}

void BibleStudyMainFrame::ShowHidePlanBar(bool show)
{  
	if (!show)
  {
    if(m_PlanToolBar != NULL)
		{
			delete m_PlanToolBar;
			m_PlanToolBar = NULL;
		}
  }
  else if(show && m_PlanToolBar == NULL)
  {
		m_PlanToolBar =
    new ReadingPlannerToolBar(this, ID_ReadingPlannerToolBar, wxTB_HORIZONTAL | 
                       wxTB_FLAT );
		UpdatePlanToolBar();
  }

  LayoutChildren();

}

void BibleStudyMainFrame::LoadConfig()
{
	int defaultConfig = 0;
	wxConfig* config = new wxConfig(APPTITLE);
	m_Config.m_PalmUserName = config->Read(wxT("Palm_User_Name"), wxT("None"));
	m_Config.m_PalmUserInstallPath = config->Read(wxT("Palm_User_Install_Path"), wxT("Not Found"));
	m_Config.m_PalmUserBackupPath = config->Read(wxT("Palm_User_Backup_Path"), wxT("Not Found"));
	m_Config.m_PalmIntegration = config->Read(wxT("Use_Palm_Integration"), defaultConfig);
	delete config;
}

void BibleStudyMainFrame::SaveConfig()
{
	wxConfig* config = new wxConfig(APPTITLE);
	config->Write(wxT("Palm_User_Name"), m_Config.m_PalmUserName);
	config->Write(wxT("Palm_User_Install_Path"), m_Config.m_PalmUserInstallPath);
	config->Write(wxT("Palm_User_Backup_Path"), m_Config.m_PalmUserBackupPath);
	config->Write(wxT("Use_Palm_Integration"), m_Config.m_PalmIntegration);
	delete config;
}

void BibleStudyMainFrame::OnPrefs(wxCommandEvent &event)
{
	m_PrefsDialog = new PrefsDialog(this, -1, &m_Config);
	m_PrefsDialog->ShowModal();
	if(m_Config.m_PalmIntegration)
		m_pdbFile->SetBackupPath(m_Config.m_PalmUserBackupPath.mb_str());
	else
	{
		wxString localPath = ::wxGetHomeDir();
		localPath += wxT("/.biblestudy/readingplans");
		m_pdbFile->SetBackupPath(localPath.mb_str());
	}
	m_PlanToolBar->SetComboPlanNames();
}

wxArrayString BibleStudyMainFrame::GetPlanNames()
{
	wxArrayString retval;
	wxString tempString;
	PDBNode *stateInfoP = NULL;
	PDBNode *dbIDP = NULL;
	char tempName[MAX_NAME_LEN + 4];
	PDBErr err = errNone;

	err = m_pdbFile->PDBGetNextDatabaseByTypeCreator(true, &stateInfoP,appDBType,appFileCreator, &dbIDP);
	while(!err)
	{	
		strcpy(tempName, dbIDP->m_dbName);
		m_pdbFile->StripName(tempName);
		retval.Add(wxString(tempName, wxConvUTF8));
		err = m_pdbFile->PDBGetNextDatabaseByTypeCreator(false, &stateInfoP,appDBType,appFileCreator, &dbIDP);
	}
	return retval;
}

void BibleStudyMainFrame::OnPlanChanged(wxCommandEvent &event)
{
	m_pdbFile->PDBCloseDatabase();
	wxString planName = event.GetString();
	planName += wxT("DTrp");
	m_pdbFile->PDBOpenDatabase(m_pdbFile->PDBFindDatabase(planName.mb_str()));
	m_WindowSplit->RefreshStartPages(BuildStartPage());
	UpdatePlanToolBar();
}

void BibleStudyMainFrame::InstallCurrentPlan()
{
	if(m_pdbFile->isDirty() && m_Config.m_PalmIntegration)
	{
		m_pdbFile->savePDB();
		char	userName[256],
					planName[MAX_NAME_LEN + 4];
		strcpy(userName,m_Config.m_PalmUserName.mb_str());
		m_pdbFile->PDBDatabaseInfo(planName);
		m_pdbFile->Install(userName,planName);
	}
}
