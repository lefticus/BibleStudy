/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "SwordTools.h"


SwordTools::SwordTools()
{
	MarkupFilterMgr *myFilterMgr = new MarkupFilterMgr;
	m_SwordManager = new SWMgr(myFilterMgr);
	myFilterMgr->Markup(FMT_HTML);
	myFilterMgr->Encoding(ENC_HTML);
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
	SWModule* curMod = 0;
	ModMap* Modules;
	Modules = GetModuleMap();
	ConfigEntMap confmap;
	ConfigEntMap::iterator cit;
	
	
	for (it = Modules->begin(); it != Modules->end(); it++) {
		curMod = (*it).second;

		printf("%s : %s\n", curMod->Description(), curMod->Type());
		confmap = curMod->getConfig();
		for (cit = confmap.begin(); cit != confmap.end(); cit++) {
			//if (!strcmp(cit->first.c_str(), "GlobalOptionFilter")) {
				printf("\t%s: %s\n", cit->first.c_str(),  cit->second.c_str());
			//}
		}

		printf("\n");
	}
}

void SwordTools::OptionInfo()
{
	using namespace sword;
	OptionsList optlist;
	
	optlist = m_SwordManager->getGlobalOptions();
	
	OptionsList::iterator it;
	
	for (it = optlist.begin(); it != optlist.end(); it++) {
		printf("%s\n", it->c_str());
	}
		
}
