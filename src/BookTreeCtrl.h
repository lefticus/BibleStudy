
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _BOOKTREECTRL_H_
#define _BOOKTREECTRL_H_

#include <swmodule.h>
#include <wx/event.h>
#include <wx/icon.h>
#include <wx/treectrl.h>
#include <BibleStudyLanguages.h>

class SwordTools;

BEGIN_DECLARE_EVENT_TYPES()DECLARE_EVENT_TYPE(bsEVT_OPEN_IN_CURRENT_TAB, 1)
  DECLARE_EVENT_TYPE(bsEVT_OPEN_IN_NEW_TAB, 2)
  DECLARE_EVENT_TYPE(bsEVT_OPEN_IN_NEW_WINDOW, 3)
  DECLARE_EVENT_TYPE(bsEVT_ADD_TO_CURRENT_TAB, 4) 
END_DECLARE_EVENT_TYPES()

#define EVT_OPEN_IN_CURRENT_TAB(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_OPEN_IN_CURRENT_TAB, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

#define EVT_OPEN_IN_NEW_TAB(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_OPEN_IN_NEW_TAB, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

#define EVT_OPEN_IN_NEW_WINDOW(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_OPEN_IN_NEW_WINDOW, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

#define EVT_ADD_TO_CURRENT_TAB(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_ADD_TO_CURRENT_TAB, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

enum {
  ID_BookTreePopupOpenInNewTab = 2000,
  ID_BookTreePopupOpenInNewWindow,
  ID_BookTreePopupOpen,
  ID_BookTreePopupAddToCurrentTab,
  ID_BookTreePopupInformation
};

/**
 * Item data for one tree node.
 **/
class BookTreeItemData:public wxTreeItemData {
private:
  sword::SWModule * m_Module;

public:
  BookTreeItemData(sword::SWModule *);
  void SetModule(sword::SWModule *);
  sword::SWModule * GetModule();
};

/**
 * Treeview of BookModules installed
 */
class BookTreeCtrl: public wxTreeCtrl {
private:
  SwordTools * m_SwordTools;

  wxIcon m_ClosedFolderBMP;
  wxIcon m_OpenFolderBMP;
  wxIcon m_BookBMP;

  wxImageList *m_ImageList;

  wxMenu *m_PopupMenu;

  BibleStudyLanguages m_Languages;

  void OnOpenModule(wxCommandEvent & event);
  void SetupIcons();

public:
  ~BookTreeCtrl();
  BookTreeCtrl(wxWindow *parent, wxWindowID id, const wxPoint & pos,
               const wxSize & size);

  void RefreshBookList(bool = true);
  void SetSwordTools(SwordTools *);

  BookTreeItemData *GetItemData(const wxTreeItemId &);
  void SetItemData(const wxTreeItemId &, BookTreeItemData *);

  void OnRightUp(wxMouseEvent &event);
  void OnRightDown(wxMouseEvent &event);
  void OnItemActivated(wxTreeEvent &event);
  void OnInformation(wxCommandEvent &event);

  DECLARE_EVENT_TABLE()
};

#endif
