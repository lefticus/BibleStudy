
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <SwordTools.h>
#include <BookModule.h>

#include <wx/tokenzr.h>
#include <wx/log.h>

#include <sword/markupfiltmgr.h>
#include <sword/swmgr.h>

#include <iostream>

using namespace sword;

SwordTools::SwordTools()
{
#if wxUSE_UNICODE
  m_SwordManager =
    new SWMgr(0, 0, TRUE, new MarkupFilterMgr(FMT_HTMLHREF, ENC_HTML));
#else
   m_SwordManager =
    new SWMgr(0, 0, TRUE, new MarkupFilterMgr(FMT_HTMLHREF, ENC_LATIN1));
#endif
}

BookModule *SwordTools::GetModuleFromLink(const wxString &link, 
                                          BookModule * oldbm)
{
  wxLogDebug(wxT("GetModuleFromLink called with link: ") + link);
  BookModule *bm = NULL;

  if (link.StartsWith(wxT("#G"))) {
    bm = new BookModule(GetModule("StrongsGreek"));
  } else if (link.StartsWith(wxT("#H"))) {
    bm = new BookModule(GetModule("StrongsHebrew"));
  } else if (link.Find(wxT("type=Strongs")) > -1) {
    if (link.Find(wxT("value=G")) > -1) {
      bm = new BookModule(GetModule("StrongsGreek"));
    } else {
      bm = new BookModule(GetModule("StrongsHebrew"));
    }
  } else if (link.Find(wxT("type=morph")) > -1) {
    if (link.Find(wxT("Robinson")) > -1) {
      bm = new BookModule(GetModule("Robinson"));
    } else if (link.Find(wxT("Packard")) > -1) {
      bm = new BookModule(GetModule("Packard"));
    } else if (link.Find(wxT("class=none")) == -1) {
      bm = new BookModule(GetModule("Robinson"));
    }
  } else if (link.Find(wxT("passage=")) > -1) {
    wxStringTokenizer tokenizer(link, wxT(" ="));

    while (tokenizer.HasMoreTokens()) {
      wxString token = tokenizer.GetNextToken();

      if (token == wxT("version")) {
        bm = new BookModule(GetModule(tokenizer.GetNextToken().mb_str()));
        break;
      }
    }

    if (!bm) {
      bm = new BookModule(GetModule("KJV"));
    }
  } else if (link.Find(wxT("noteID=")) > -1) {
    bm = new BookModule(GetModule(oldbm->GetName().mb_str()));
  }

  return bm;
}

wxString SwordTools::GetKeyFromLink(const wxString &link)
{
  wxString key;

  if (link.StartsWith(wxT("#G"), &key)) {
    // nothing to do, key is now in "key"
  } else if (link.StartsWith(wxT("#H"), &key)) {
    // nothing to do, key is now in "key"
  } else if (link.Find(wxT("value=")) > -1) {
    wxStringTokenizer tokenizer(link, wxT(" ="));

    key = link.Mid(link.Find(wxT("value=")) + 6);

    if (link.Find(wxT("type=Strongs")) > -1) {
      key.StartsWith(wxT("G"), &key);
      key.StartsWith(wxT("H"), &key);
    }
  } else if (link.Find(wxT("passage=")) > -1) {
    key = link.Mid(link.Find(wxT("passage=")) + 8);
  } else if (link.Find(wxT("noteID=")) > -1) {
    key = link.Mid(link.Find(wxT("noteID=")) + 7);
  } else {
    key = link;
  }

  return key;
}

SWMgr *SwordTools::GetSwordManager()
{
  return m_SwordManager;
}

ModMap *SwordTools::GetModuleMap()
{
  return &m_SwordManager->Modules;
}

SwordTools::~SwordTools()
{
}

SWModule *SwordTools::GetModule(const char *modulename)
{
  return m_SwordManager->Modules[modulename];
}

void SwordTools::ModInfo()
{
  using namespace sword;

  ModMap::iterator it;
  SWModule *curMod = 0;
  ModMap *Modules;

  Modules = GetModuleMap();
  ConfigEntMap confmap;

  ConfigEntMap::iterator cit;

  for (it = Modules->begin(); it != Modules->end(); it++) {
    curMod = (*it).second;

    printf("%s : %s\n", curMod->Description(), curMod->Type());
    confmap = curMod->getConfig();
    for (cit = confmap.begin(); cit != confmap.end(); cit++) {
      printf("\t%s: %s\n", cit->first.c_str(), cit->second.c_str());
    }

    printf("\n");
  }
}

void SwordTools::OptionInfo()
{
  using namespace sword;

  StringList optlist;

  optlist = m_SwordManager->getGlobalOptions();

  StringList::iterator it;

  for (it = optlist.begin(); it != optlist.end(); it++) {
    printf("%s\n", it->c_str());
  }

}
