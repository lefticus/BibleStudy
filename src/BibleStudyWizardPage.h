/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BIBLESTUDYWIZARDPAGE_H_
	#define _BIBLESTUDYWIZARDPAGE_H_

	#include "biblestudy.h"
	#include "BookViewCtrl.h"
	#include <wx/wizard.h>
	#include <wx/stattext.h>

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
		wxStaticText *m_StaticText;
		SWModule *m_Module;
	
		
		DECLARE_EVENT_TABLE()
	};

#endif
