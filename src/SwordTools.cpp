
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
#include <wx/uri.h>

#include <sword/markupfiltmgr.h>
#include <sword/swmgr.h>

#include <bsmarkupfiltmgr.h>

#include <iostream>

using namespace sword;

SwordTools::SwordTools() : m_DefaultBible(NULL), m_DefaultDevotional(NULL),
			   m_BibleSearched(false), m_DevotionalSearched(false)
{
#if wxUSE_UNICODE
  m_SwordManager =
    new SWMgr(0, 0, TRUE, new BSMarkupFilterMgr(FMT_HTMLHREF, ENC_HTML));
#else
  m_SwordManager =
    new SWMgr(0, 0, TRUE, new BSMarkupFilterMgr(FMT_HTMLHREF, ENC_LATIN1));
#endif
}

SWModule* SwordTools::GetDefaultBible()
{

  if (!m_BibleSearched) {
    m_DefaultBible = FindModule(m_BibleName.c_str(), m_BibleLang.c_str(), "Biblical Texts");
    m_BibleSearched = true;
  }

  return m_DefaultBible;
}

SWModule* SwordTools::GetDefaultDevotional()
{

  if (!m_DevotionalSearched) {
    m_DefaultDevotional = FindModule(m_DevotionalName.c_str(), m_DevotionalLang.c_str(), "Daily Devotional");
    m_DevotionalSearched = true;
  }
  
  return m_DefaultDevotional;
}


SWModule * SwordTools::FindModule(const std::string &name, const std::string &language, const std::string &type)
{
  SWModule *mod = NULL;
  if (type == "") {
    return NULL;
  }
  
  if (name != "") {
    mod = GetModule(name.c_str());
    if (mod != NULL) {
      if (type != mod->Type()) {
        mod = NULL;
      }
    }
  } 
  
  if (mod == NULL) {
    ModMap::iterator it;
    ModMap *mods = GetModuleMap();
    if (mods != NULL) {
      for (it = mods->begin(); it != mods->end(); it++) {
        SWModule *tempmod;
        tempmod = (*it).second;
        if (type == tempmod->Type()) {
  	  if (language == tempmod->Lang()) {
	    return tempmod;
	  } else {
	    if (mod == NULL) {
              mod = tempmod;
	    }
	  }
        }
      }
    }
  }

  return mod;
}

void SwordTools::SetDefaultDevotional(const std::string &name, const std::string &lang)
{
  m_DevotionalName = name;
  m_DevotionalLang = lang;
}

void SwordTools::SetDefaultBible(const std::string &name, const std::string &lang)
{
  std::cout << "Default bible: " << name << " " << lang << std::endl;
  m_BibleName = name;
  m_BibleLang = lang;
}

BookModule *SwordTools::GetModuleFromLink(const wxString &link,
    BookModule * oldbm)
{
  wxLogDebug(wxT("GetModuleFromLink called with link: ") + link);
  SWModule *sm = NULL;

  if (link.StartsWith(wxT("#G")))
  {
    sm = GetModule("StrongsGreek");
  }
  else if (link.StartsWith(wxT("#H")))
  {
    sm = GetModule("StrongsHebrew");
  }
  else if (link.Find(wxT("type=Strongs")) > -1)
  {
    if (link.Find(wxT("value=G")) > -1)
    {
      sm = GetModule("StrongsGreek");
    }
    else
    {
      sm = GetModule("StrongsHebrew");
    }
  }
  else if (link.Find(wxT("type=Greek")) > -1)
  {
    sm = GetModule("StrongsGreek");
  }
  else if (link.Find(wxT("type=Hebrew")) > -1)
  {
    sm = GetModule("StrongsHebrew");
  }
  else if (link.Find(wxT("type=x-Robinson")) > -1)
  {
    sm = GetModule("Robinson");
  }
  else if (link.Find(wxT("type=morph")) > -1)
  {
    if (link.Find(wxT("Robinson")) > -1)
    {
      sm = GetModule("Robinson");
    }
    else if (link.Find(wxT("Packard")) > -1)
    {
      sm = GetModule("Packard");
    }
    else if (link.Find(wxT("class=none")) == -1)
    {
      sm = GetModule("Robinson");
    }
  }
  else if (link.Find(wxT("passage=")) > -1 || link.Find(wxT("scripRef")) > -1)
  {
    wxStringTokenizer tokenizer(link, wxT(" ="));

    while (tokenizer.HasMoreTokens())
    {
      wxString token = tokenizer.GetNextToken();

      if (token == wxT("version"))
      {
        sm = GetModule(tokenizer.GetNextToken().mb_str());
        break;
      }
    }

    if (!sm)
    {
      sm = GetDefaultBible();
    }
  }
  else if (link.Find(wxT("noteID=")) > -1)
  {
    sm = GetModule(oldbm->GetName().mb_str());
  }

  
  if (sm != NULL) {
    return new BookModule(sm);
  } else {
    return NULL;
  }
}

wxString SwordTools::GetKeyFromLink(const wxString &link)
{
  wxString key;


  if (link.StartsWith(wxT("#G"), &key))
  {
    // nothing to do, key is now in "key"
  }
  else if (link.StartsWith(wxT("#H"), &key))
  {
    // nothing to do, key is now in "key"
  }
  else if (link.Find(wxT("value=")) > -1)
  {
    key = link.Mid(link.Find(wxT("value=")) + 6);
    int end = key.Find(wxT("&"));
    key = key.Mid(0, end);
    key = wxURI::Unescape(key);
    key.Replace(wxT("+"), wxT(" "), true);
  }
  else if (link.Find(wxT("passage=")) > -1)
  {
    key = link.Mid(link.Find(wxT("passage=")) + 8);
    int end = key.Find(wxT("&"));
    key = key.Mid(0, end);
    key = wxURI::Unescape(key);
    key.Replace(wxT("+"), wxT(" "), true);
  }
  else if (link.Find(wxT("noteID=")) > -1)
  {
    key = link.Mid(link.Find(wxT("noteID=")) + 7);
  }
  else
  {
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
{}

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

  for (it = Modules->begin(); it != Modules->end(); it++)
  {
    curMod = (*it).second;

    printf("%s : %s\n", curMod->Description(), curMod->Type());
    confmap = curMod->getConfig();
    for (cit = confmap.begin(); cit != confmap.end(); cit++)
    {
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

  for (it = optlist.begin(); it != optlist.end(); it++)
  {
    printf("%s\n", it->c_str());
  }

}
