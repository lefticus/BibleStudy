/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BibleStudyApp.h"

BibleStudyApp::BibleStudyApp()
{
}


BibleStudyApp::~BibleStudyApp()
{
}

bool BibleStudyApp::OnInit()
{
	BibleStudyMainFrame *frame = new BibleStudyMainFrame(&m_SwordTools, APPTITLE, wxPoint(50,50), wxSize(450,340));
	frame->Show(TRUE);
	//SetTopWindow(frame);
	return TRUE;
}
