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
	#pragma interface "BibleStudyWizardPage.h"
#endif

#ifndef _BIBLESTUDYWIZARDPAGE_H_
	#define _BIBLESTUDYWIZARDPAGE_H_

	#include "biblestudy.h"
	#include "BookViewCtrl.h"
	#include <wx/wizard.h>
	#include <wx/textctrl.h>

	/**
	* 
	* Jason Turner
	**/
	class BibleStudyWizardPage : public wxWizardPageSimple
	{

	public:
		BibleStudyWizardPage(wxWizard *parent, SWModule *module, wxString text, wxString reference);
		~BibleStudyWizardPage();
		
		void OnResize(wxSizeEvent &event);
		
	private:
		BookViewCtrl *m_BookViewCtrl;
		wxTextCtrl *m_TextCtrl;
		SWModule *m_Module;
	
		
		DECLARE_EVENT_TABLE()
	};

#endif
