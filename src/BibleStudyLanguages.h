
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   Part of BibleStudy: www.sf.net/projects/christiangame                 *
 ***************************************************************************/

#ifndef _BIBLESTUDYLANGUAGES_H_
#define _BIBLESTUDYLANGUAGES_H_

#include <map>

#include <wx/string.h>

/**
 * Used to decode language abbreviations to language names
 **/
class BibleStudyLanguages {
private:

  /** The C++ map which links abbreviations to full names */
  std::map < wxString, wxString > mLanguages;

public:
  BibleStudyLanguages();
  ~BibleStudyLanguages();
  
  /** 
   * Add a language using wxString objects 
   * called by AddLanguage (const char *, const char *)
   *
   * @param abbreviation Language abbreviation
   * @param description Full Name of language
   */
  void AddLanguage(const wxString &abbreviation, const wxString &description);

  /** Add a language using char arrays 
   *
   * @param abbreviation Language abbreviation
   * @param description Full Name of language
   */
  void AddLanguage(const char *abbreviation, const char *description);

  /** 
   * Returns the full name of a language from an abbreviation 
   *
   * @param abbreviation Abbreviation of the language being looked up.
   */
  wxString GetLanguage(const wxString &abbreviation);
};

#endif
