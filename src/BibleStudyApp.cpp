
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

void BibleStudyApp::OnExitApp(wxCommandEvent & event)
{
  wxMessageDialog dialog((wxWindow *) event.GetEventObject(),
                         wxT("Close all windows and exit BibleStudy?"),
                         wxT("Exit Bible Study?"), wxYES_NO | wxICON_QUESTION);

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
