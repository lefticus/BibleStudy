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
	#pragma implementation "BibleStudyWizard.h"
#endif

#include "BibleStudyWizard.h"
#include "../icons/biblestudywiz.xpm"

BibleStudyWizard::BibleStudyWizard(wxWindow *parent, int id, wxString title) : wxWizard(parent, id, title, wxBitmap(biblestudywiz_xpm), wxDefaultPosition)
{
	m_prevpage = NULL;
}


BibleStudyWizard::~BibleStudyWizard()
{
}

bool BibleStudyWizard::RunWizard()
{
	return wxWizard::RunWizard(m_firstpage);
}

void BibleStudyWizard::AddPage(SWModule *module, wxString text, wxString reference)
{
	BibleStudyWizardPage *page;
	page = new BibleStudyWizardPage(this, module, text, reference);
	
	if (m_prevpage) {
		BibleStudyWizardPage::Chain(m_prevpage, page);
	} else {
		m_firstpage = page;
	}
	
	m_prevpage = page;
}
