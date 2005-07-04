
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

public:
  SwordTools();
  ~SwordTools();

  sword::ModMap *GetModuleMap();
  sword::SWMgr *GetSwordManager();
  sword::SWModule *GetModule(const char *ModuleName);

  BookModule *GetModuleFromLink(const wxString &link, BookModule *);
  wxString GetKeyFromLink(const wxString &link);
};

#endif
