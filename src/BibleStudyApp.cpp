/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifdef __GNUG__
	#pragma implementation "BibleStudyApp.h"
#endif

#include "BibleStudyApp.h"

BibleStudyApp::BibleStudyApp()
{
}


BibleStudyApp::~BibleStudyApp()
{
}

bool BibleStudyApp::OnInit()
{
	//wxLogWindow *mylogwindow;
	//mylogwindow = new wxLogWindow(NULL, wxT("Log Output"));
	//mylogwindow->Show();
	
	#ifdef __WXDEBUG__
	wxLogStderr *log = new wxLogStderr();
	wxLog::SetActiveTarget(log);
	#endif
	
	/* create a default frame and display it */
	BibleStudyMainFrame *frame = new BibleStudyMainFrame(&m_SwordTools, APPTITLE, wxPoint(50,50), wxSize(450,340));
	frame->Show(TRUE);
	return TRUE;
	
	
}
