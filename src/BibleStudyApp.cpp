
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <BibleStudyApp.h>
#include <BibleStudyMainFrame.h>
#include <wx/log.h>
#include <wx/splash.h>
#include <wx/msgdlg.h>
#include <biblestudy.h>
#include <libreadingplanner/KJVBible.h>

#include "../icons/splashscreen.xpm"

BEGIN_EVENT_TABLE(BibleStudyApp, wxApp)
EVT_EXIT_APP(BibleStudyApp::OnExitApp)
END_EVENT_TABLE()

BibleStudyApp::BibleStudyApp()
{}

BibleStudyApp::~BibleStudyApp()
{}

bool BibleStudyApp::OnInit()
{
#ifdef __WXDEBUG__
  wxLogStderr *log = new wxLogStderr();

  wxLog::SetActiveTarget(log);
#endif
  m_SwordTools.SetDefaultDevotional("SME", "en");
  m_SwordTools.SetDefaultBible("KJV", "en");  
  
  wxApp::OnInit();

  // wxHandleFatalExceptions(TRUE)

  /*
   * Show Splash Screen First 
   */

  /*wxSplashScreen *splash =*/ new wxSplashScreen(wxBitmap(splashscreen_xpm),
      wxSPLASH_CENTRE_ON_SCREEN |
      wxSPLASH_TIMEOUT,
      6000, NULL, -1,
      wxDefaultPosition,
      wxDefaultSize,
      wxSIMPLE_BORDER | wxSTAY_ON_TOP);

  wxYield();

  /*
   * create a default frame and display it 
   */
  BibleStudyMainFrame *frame =
    new BibleStudyMainFrame(&m_SwordTools, APPTITLE, wxDefaultPosition,
                            wxSize(640, 480));

  frame->Show(TRUE);
  wxYield();
  frame->ShowStartPage();
  // splash->Close();


  return TRUE;
}

void BibleStudyApp::OnInitCmdLine(wxCmdLineParser& parser)
{
  const wxCmdLineEntryDesc cmdLineDesc[] =
  {
    { wxCMD_LINE_OPTION, wxT("b"), wxT("bible"),  _("bible module name") },
    { wxCMD_LINE_OPTION, wxT("d"), wxT("devotional"),  _("devotional module name") },
    { wxCMD_LINE_OPTION, wxT("l"), wxT("language"),  _("language") },
    { wxCMD_LINE_NONE }
  };

  parser.SetDesc(cmdLineDesc);
}

bool BibleStudyApp::OnCmdLineParsed(wxCmdLineParser& parser)
{


  wxString bible, devotional, lang;
  bool biblefound, devofound, langfound;
  
  biblefound = parser.Found(wxT("b"), &bible);
  devofound = parser.Found(wxT("d"), &devotional);
  langfound = parser.Found(wxT("l"), &lang);

  if (biblefound) {
    if (langfound) {
      m_SwordTools.SetDefaultBible((const char*)bible.mb_str(), (const char *)lang.mb_str());
    } else {
      m_SwordTools.SetDefaultBible((const char *)bible.mb_str(), "en");
    }
  } else {
    if (langfound) {
      m_SwordTools.SetDefaultBible("", (const char *)lang.mb_str());
    } 
  }
 
  if (devofound) {
    if (langfound) {
      m_SwordTools.SetDefaultDevotional((const char *)devotional.mb_str(), (const char *)lang.mb_str());
    } else {
      m_SwordTools.SetDefaultDevotional((const char *)devotional.mb_str(), "en");
    }
  } else {
    if (langfound) {
      m_SwordTools.SetDefaultDevotional("", (const char *)lang.mb_str());
    } 
  }

  
  return wxApp::OnCmdLineParsed(parser);
}

void BibleStudyApp::OnExitApp(wxCommandEvent & event)
{
  wxMessageDialog dialog((wxWindow *) event.GetEventObject(),
                         _("Close all windows and exit BibleStudy?"),
                         _("Exit Bible Study?"), wxYES_NO | wxICON_QUESTION);

  if (dialog.ShowModal() == wxID_YES)
  {
    wxYield();
    wxLogDebug(wxT("Exiting Application"));
    wxWindow *window;

    window = wxWindow::FindWindowByName(wxT("BibleStudyWindow"));

    while (window)
    {
      window->Destroy();
      wxYield();
      window = wxWindow::FindWindowByName(wxT("BibleStudyWindow"));
    }
  }
}
