
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _BOOKMODULE_H_
#define _BOOKMODULE_H_
#include <sword/swmodule.h>
#include <sword/swmgr.h>
#include <sword/treekey.h>

#include <wx/frame.h>
#include <wx/treectrl.h>
#include <wx/string.h>

enum bsKeyType {
  bsVerseKey = 1,
  bsStringKey,
  bsTreeKey
};

/**
 * Wraps a SWModule and contains data related to the module, i.e. last search
 * performed. Used for duplicating/detaching tabs as well as updating the 
 * toolbar
 **/
class BookModule {
public:
  BookModule(sword::SWModule *);
  ~BookModule();

  /** Returns underlying module */
  sword::SWModule * GetModule();
  sword::ModMap * GetModules();

  /** Lookups up a key, returning HTML representation */
  wxString LookupKey(wxString key, wxString search = wxT(""), 
                     int searchtype = 0, bool tooltip = false, 
		     bool browse = false);
		     
  wxString BrowseForward();
  wxString BrowseBackward();

  /** Return the last lookup key */
  wxString GetLastLookupKey() const;

  wxString GetLastSearch() const;
  wxString ModInfo() const;

  /** Returns a combobox for this book */
  wxFrame *GetControl(wxWindow * parent);

  void AddModule(sword::SWModule * mod);

  wxString GetName() const;
  bsKeyType GetKeyType() const;
  bsKeyType GetKeyType(sword::SWModule * mod) const;
  bool IsBrowsing() const;

  static void Percent(char, void *);

private:
  /** The SWModule being wrapped */
  sword::SWModule *m_Module;
  sword::SWModule *m_Second_Module;

  /** The last key looked up */
  wxString m_LastLookupKey;
  wxString m_LastSearch;
  mutable wxString m_Description;

  wxFrame *m_Frame;

  sword::ModMap m_Modules;
  sword::ListKey m_LastKey;
  void AddTreeSiblings(wxTreeCtrl * tree, wxTreeItemId parentid,
                       sword::TreeKey * key);

  bool m_isbrowsing;
  bsKeyType m_keytype;

};

#endif
