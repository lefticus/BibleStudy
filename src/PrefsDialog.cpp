/***************************************************************************
 *   Copyright (C) 2003 by David Trotz                                     *
 *   dtrotzjr@readingplanner.com                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <PrefsDialog.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/valgen.h>
#include <wx/dirdlg.h>
#include <wx/filename.h>
//#include <wx/boxsizer.h>

#include <BibleStudyMainFrame.h>
#include <biblestudy.h>
#include "dirtraversersimple.h"
#include <libreadingplanner/pdbResource.h>
#include "BookList.h"

// If Windows build we want to include a PalmDesktop helper file
// Requires Palm CDK 4.03
#ifdef WIN32
// I had to define these for a very specific case because
// wxWidgets must be redefining TCHAR when unicode is on and
// I got linker errors for these functions.
extern int WINAPI PltGetUserCount(void);
extern int WINAPI PltGetUser(unsigned int iIndex, char *pUserBuffer, short *psUserBufSize);
extern int WINAPI PltGetUserDirectory(char *pUser, char *pBuffer, int *piBufferSize);
#endif

BEGIN_EVENT_TABLE(PrefsDialog, wxDialog)
EVT_BUTTON(ID_DetectPalm, PrefsDialog::OnDetectPalmConfig)
EVT_BUTTON(ID_BrowseInstall, PrefsDialog::OnBrowseInstallPath)
EVT_BUTTON(ID_BrowseBackup, PrefsDialog::OnBrowseBackupPath)
EVT_RADIOBOX(ID_RadioChoice, PrefsDialog::OnChangeConfig)
END_EVENT_TABLE()

PrefsDialog::PrefsDialog(wxWindow* parent, wxWindowID id, BibleStudyConfig* gConfig):wxDialog(parent, id, wxT("BibleStudy Preferences"),wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
  m_gConfig = gConfig;
  wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *rowOneSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *rowTwoSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *backupSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *installSizer = new wxBoxSizer(wxHORIZONTAL);

  static const wxString choices[] =
    {
      wxT("Use Default"),
      wxT("Use Palm Desktop Directories")
    };
  Centre();


  wxStaticBox *box = new wxStaticBox(this, wxID_ANY, wxT("ReadingPlanner Integration"), wxDefaultPosition, wxDefaultSize);
  wxStaticBoxSizer* staticSizer = new wxStaticBoxSizer(box, wxVERTICAL );
  m_radConfig = new wxRadioBox(this, ID_RadioChoice, wxT("Location Configurations"),
                               wxDefaultPosition, wxDefaultSize, 2, choices, 1, wxRA_SPECIFY_COLS, wxGenericValidator(&m_gConfig->m_PalmIntegration) );

  wxButton *btnOK = new wxButton(this,wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize);
  wxButton *btnCancel = new wxButton(this,wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize);

  m_btnDetect = new wxButton(this,ID_DetectPalm, wxT("Detect Palm User Settings"), wxDefaultPosition, wxDefaultSize);
  m_btnBrowseInstall = new wxButton(this,ID_BrowseInstall, wxT("Browse"), wxDefaultPosition, wxDefaultSize);
  m_btnBrowseBackup = new wxButton(this,ID_BrowseBackup, wxT("Browse"), wxDefaultPosition, wxDefaultSize);


  wxStaticText* txtInstall = new wxStaticText(this, wxID_ANY,wxT("Palm User Install Path"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
  wxStaticText* txtBackup = new wxStaticText(this, wxID_ANY,wxT("Palm User Backup Path"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

  m_InstallPathCtl = new wxTextCtrl(this, wxID_ANY,wxT(""), wxDefaultPosition, wxSize(490,-1), 0, wxTextValidator(wxFILTER_NONE, &m_gConfig->m_PalmUserInstallPath));
  m_BackupPathCtl = new wxTextCtrl(this, wxID_ANY,wxT(""), wxDefaultPosition, wxSize(490,-1), 0, wxTextValidator(wxFILTER_NONE, &m_gConfig->m_PalmUserBackupPath));


  rowOneSizer->Add(m_radConfig, 2, wxALIGN_LEFT | wxALIGN_TOP | wxALL,7);
  rowOneSizer->Add(10,10);
  rowOneSizer->Add(m_btnDetect, 1, wxALIGN_RIGHT| wxALIGN_BOTTOM | wxALL,7);

  installSizer->Add(m_InstallPathCtl,0,wxALIGN_LEFT | wxTOP | wxBOTTOM | wxLEFT, 7);
  installSizer->Add(m_btnBrowseInstall,0,wxALIGN_RIGHT | wxALL, 7);

  backupSizer->Add(m_BackupPathCtl,0,wxALIGN_LEFT | wxTOP | wxBOTTOM | wxLEFT, 7);
  backupSizer->Add(m_btnBrowseBackup,0,wxALIGN_RIGHT | wxALL, 7);

  buttonSizer->Add(btnCancel, 0, wxALIGN_RIGHT | wxRIGHT, 7);
  buttonSizer->Add(btnOK, 0, wxALIGN_RIGHT);

  rowTwoSizer->Add(10,10);
  rowTwoSizer->Add(txtInstall, 0, wxALIGN_LEFT | wxLEFT, 7);
  rowTwoSizer->Add(installSizer, 0, wxALIGN_LEFT);
  rowTwoSizer->Add(txtBackup, 0, wxALIGN_LEFT | wxLEFT, 7);
  rowTwoSizer->Add(backupSizer, 0, wxALIGN_LEFT);

  staticSizer->Add(rowOneSizer, 0, wxALIGN_LEFT | wxEXPAND);
  staticSizer->Add(rowTwoSizer, 0, wxALIGN_CENTER);

  topLevelSizer->Add(staticSizer, 0, wxALIGN_CENTER | wxALL,5);
  topLevelSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxBOTTOM | wxRIGHT ,5);

  SetSizer(topLevelSizer);
  topLevelSizer->SetSizeHints(this);
}

bool PrefsDialog::TransferDataToWindow()
{
  bool retval = wxDialog::TransferDataToWindow();
  EnablePalmControls(m_radConfig->GetSelection());
  return retval;
}

void PrefsDialog::OnBrowseInstallPath(wxCommandEvent &event)
{
  BrowsePath(m_InstallPathCtl);
}

void PrefsDialog::OnBrowseBackupPath(wxCommandEvent &event)
{
  BrowsePath(m_BackupPathCtl);
}

void PrefsDialog::BrowsePath(wxTextCtrl * ctl)
{
  wxDirDialog *dirDialog = new wxDirDialog(this);
  if(dirDialog->ShowModal() == wxID_OK)
    ctl->SetValue(dirDialog->GetPath());
}

void PrefsDialog::EnablePalmControls(bool enable)
{
  m_BackupPathCtl->Enable(enable);
  m_InstallPathCtl->Enable(enable);
  m_btnBrowseBackup->Enable(enable);
  m_btnBrowseInstall->Enable(enable);
  m_btnDetect->Enable(enable);
}

void PrefsDialog::OnChangeConfig(wxCommandEvent &event)
{
  EnablePalmControls(m_radConfig->GetSelection());
}

void PrefsDialog::OnDetectPalmConfig(wxCommandEvent &event)
{
  // If Windows build we want to handle being able to detect the Palm Desktop settings.
#ifdef WIN32
  wxArrayString users;
  wxString user;
  char pPath[MAX_PATH_NAME];
  char buf[32];
  char pUser[64];
  int psPathBufSize = sizeof (pPath);
  short psbufSize = sizeof(buf);
  int userCount = PltGetUserCount();

  for(int i = 0; i < userCount;i++)
  {
    PltGetUser(i,buf,&psbufSize);
    users.Add(wxString(buf, wxConvUTF8));
  }
  user = wxGetSingleChoice(wxT("Select a user name to use for configuration:"),wxT("Choose HotSync ID"),users ,this);

  m_gConfig->m_PalmUserName = user;
  memcpy(&pUser, user.mb_str(), user.length() + 1);
  PltGetUserDirectory(pUser, pPath, &psPathBufSize);
  wxString rootPath = wxString(pPath, wxConvUTF8);
  wxString backupPath = wxString(rootPath, wxConvUTF8);
  wxString installPath = rootPath;
  backupPath += wxT("\\Backup\\");
  installPath += wxT("\\Install\\");
  m_InstallPathCtl->SetValue(installPath);
  m_BackupPathCtl->SetValue(backupPath);
#endif
  // Actually this should be a specific define for Linux since Macs will be entirely different as well, but I am being lazy and no one is building on a Mac yet so, if you are I apologize: dtrotzjr
#ifndef WIN32
  wxMessageDialog* errorMsg = new wxMessageDialog(this, wxT("Error locating KPilot's directories, if you know you have KPilot installed then locate and browse the directory manually"),wxT("Cannot find KPilot Directories"),wxOK );
  wxString basePath = ::wxGetHomeDir();
  wxString installPath, backupPath;
  basePath += wxT("/.kde/share/apps/kpilot/");
  installPath = backupPath = basePath;

  installPath += wxT("pending_install");
  backupPath += wxT("DBBackup/");
  if(!wxFileName::DirExists(basePath) || !wxFileName::DirExists(installPath))
  {
    errorMsg->ShowModal();
    return;
  }
  wxString user;
  int leafIndex = 0;
  wxArrayString paths;
  wxArrayString users;
  DirTraverserSimple traverser(paths);
  wxDir dir(backupPath);
  dir.Traverse(traverser);
  for(unsigned int i = 0; i < paths.GetCount(); i++)
  {
    leafIndex = paths[i].Find('/',true);
    users.Add(paths[i].SubString(++leafIndex, paths[i].Length()));
  }
  user = wxGetSingleChoice(wxT("Select a user name to use for configuration:"),wxT("Choose HotSync ID"),users ,this);
  backupPath += user;
  m_InstallPathCtl->SetValue(installPath);
  m_BackupPathCtl->SetValue(backupPath);
#endif
}
