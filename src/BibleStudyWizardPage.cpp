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
	#pragma implementation "BibleStudyWizardPage.h"
#endif

#include "BibleStudyWizardPage.h"

BEGIN_EVENT_TABLE(BibleStudyWizardPage, wxWizardPageSimple)
	EVT_SIZE(BibleStudyWizardPage::OnResize)
END_EVENT_TABLE() 


BibleStudyWizardPage::BibleStudyWizardPage(wxWizard *parent, SWModule *module, wxString text, wxString reference) : wxWizardPageSimple(parent)
{
	m_Module = module;
	//SetSize(GetBestSize());
	//Refresh();
	wxSize size = GetClientSize();
	wxLogDebug(wxT("BibleStudyWizardPage::BibleStudyWizardPage client area: %i, %i"), size.GetWidth(), size.GetHeight());
	
	if (reference != wxT("")) {
		
		m_TextCtrl = new wxTextCtrl(this, -1, text, wxPoint(0,0),wxSize(size.GetWidth(), size.GetHeight()*1/3), wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP);
		m_BookViewCtrl = new BookViewCtrl(this, -1, wxPoint(0,size.GetHeight()*1/3+1), wxSize(size.GetWidth(), size.GetHeight()*2/3-1));
		m_BookViewCtrl->OpenInNewTab(module);
		m_BookViewCtrl->LookupKey(reference);
	} else {
		m_TextCtrl = new wxTextCtrl(this, -1, text, wxPoint(0,0), size, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP);
		m_BookViewCtrl = NULL;
	}
}


BibleStudyWizardPage::~BibleStudyWizardPage()
{
}

void BibleStudyWizardPage::OnResize(wxSizeEvent &event)
{
	wxSize size = GetClientSize();

	if (m_BookViewCtrl) {
		m_TextCtrl->SetSize(wxSize(size.GetWidth(), size.GetHeight()*1/3));
		m_BookViewCtrl->Move(wxPoint(0,size.GetHeight()*1/3+1));
		m_BookViewCtrl->SetSize(wxSize(size.GetWidth(), size.GetHeight()*2/3-1));
	} else {
		m_TextCtrl->SetSize(size);	
	}
}
