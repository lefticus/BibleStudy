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
	#pragma interface "BibleStudyWizard.h"
#endif

#ifndef _BIBLESTUDYWIZARD_H_
	#define _BIBLESTUDYWIZARD_H_

	#include "biblestudy.h"
	#include <wx/wizard.h>
	#include "BibleStudyWizardPage.h"
	/**
	* 
	* Jason Turner
	**/
	class BibleStudyWizard : public wxWizard
	{
	private:
		BibleStudyWizardPage *m_prevpage, *m_firstpage;
	
	public:
		BibleStudyWizard(wxWindow *parent, int id, wxString title);
		~BibleStudyWizard();
		
		bool RunWizard();
		void AddPage(SWModule *module, wxString text, wxString reference);
	};

#endif
