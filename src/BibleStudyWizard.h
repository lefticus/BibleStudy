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

	#include <wx/wx.h>
	#include <wx/wizard.h>
	#include <swmodule.h>
	#include "BookViewCtrl.h"

	using namespace sword;

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

