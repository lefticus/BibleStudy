/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BIBLESTUDYLANGUAGES_H_
#define _BIBLESTUDYLANGUAGES_H_

#include <wx/string.h>
#include <map>

using namespace std;

/**
 * 
 * Jason Turner
 **/
class BibleStudyLanguages
{
private:
	map<wxString, wxString> mLanguages;

public:
  BibleStudyLanguages();
  ~BibleStudyLanguages();
  
  void AddLanguage(wxString, wxString);
  void AddLanguage(const char *abbreviation, const char *description);
  wxString GetLanguage(wxString);
};

#endif
