
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _SWORDTOOLS_H_
#define _SWORDTOOLS_H_

#include <wx/string.h>

#include <sword/swmgr.h>
#include <sword/swmodule.h>

#include <string>

class BookModule;

/**
 * Wrapper for SWMgr, with utilities
 *
 **/
class SwordTools
{

private:

  /** testing function */
  void ModInfo();

  /** testing function */
  void OptionInfo();

  sword::SWMgr *m_SwordManager;
  sword::SWModule *m_DefaultBible;
  sword::SWModule *m_DefaultDevotional;
  bool m_BibleSearched;
  bool m_DevotionalSearched;

  std::string m_BibleLang;
  std::string m_BibleName;
  std::string m_DevotionalLang;
  std::string m_DevotionalName;
  
public:
  SwordTools();
  ~SwordTools();

  sword::ModMap *GetModuleMap();
  sword::SWMgr *GetSwordManager();
  sword::SWModule *GetModule(const char *ModuleName);

  sword::SWModule *GetDefaultBible();
  sword::SWModule *GetDefaultDevotional();
  
  void SetDefaultDevotional(const std::string &name = "", const std::string &type = "");
  void SetDefaultBible(const std::string &name = "", const std::string &type = "");
  
  sword::SWModule *FindModule(const std::string &name = "", const std::string &lang = "", const std::string &type = "");

  BookModule *GetModuleFromLink(const wxString &link, BookModule *);
  wxString GetKeyFromLink(const wxString &link);

};

#endif
