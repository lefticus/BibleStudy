/***************************************************************************
 *   Copyright (C) 2003 by David Trotz                                     *
 *   dtrotzjr@readingplanner.com                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _PREFSDIALOG_H_
#define _PREFSDIALOG_H_

#include <wx/dialog.h>
class wxTextCtrl;
class wxButton;
class wxRadioBox;
struct BibleStudyConfig;

/**
 * Preferences Dialog Box for BibleStudy
 *
 **/
class PrefsDialog: public wxDialog {
private:
	BibleStudyConfig* m_gConfig;
	wxTextCtrl* m_InstallPathCtl;
	wxTextCtrl* m_BackupPathCtl;
	wxButton  *	m_btnDetect;
	wxButton  *	m_btnBrowseInstall;
	wxButton  *	m_btnBrowseBackup;
	wxRadioBox* m_radConfig;
public:
	void OnChangeConfig(wxCommandEvent & event);
	void EnablePalmControls(bool enable);
	void BrowsePath(wxTextCtrl * ctl);
	void OnDetectPalmConfig(wxCommandEvent & event);
	void OnBrowseBackupPath(wxCommandEvent & event);
	void OnBrowseInstallPath(wxCommandEvent & event);
	bool TransferDataToWindow();
  PrefsDialog(wxWindow* parent, wxWindowID id, BibleStudyConfig* gConfig);
	~PrefsDialog(){}
  DECLARE_EVENT_TABLE()
};

#endif // _PREFSDIALOG_H_ 