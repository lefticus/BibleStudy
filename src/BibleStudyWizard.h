
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _BIBLESTUDYWIZARD_H_
#define _BIBLESTUDYWIZARD_H_

#include <wx/textctrl.h>
#include <wx/wizard.h>
#include <wx/window.h>

#include <sword/swmodule.h>

class BookViewCtrl;

/**
 *
 * Jason Turner
 **/
class BibleStudyWizardPage:public wxWizardPageSimple {
public:
  BibleStudyWizardPage(wxWizard *parent, sword::SWModule *module,
                       wxString text, wxString reference);
  ~BibleStudyWizardPage();

  void OnResize(wxSizeEvent & event);

private:
  BookViewCtrl *m_BookViewCtrl;
  wxTextCtrl *m_TextCtrl;
  sword::SWModule *m_Module;

  DECLARE_EVENT_TABLE()
};

/**
 *
 * Jason Turner
 **/
class BibleStudyWizard : public wxWizard {
public:
  BibleStudyWizard(wxWindow *parent, int id, wxString title);
   ~BibleStudyWizard();

  bool RunWizard();
  void AddPage(sword::SWModule *module, wxString text, wxString reference);
 
private:
  BibleStudyWizardPage *m_prevpage, *m_firstpage;

};

#endif
