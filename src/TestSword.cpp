/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifdef __GNUG__
	#pragma implementation "TestSword.h"
#endif

#include "TestSword.h"
#include <swmgr.h>
#include <swmodule.h>

TestSword::TestSword()

{
}


TestSword::~TestSword()
{
}

void TestSword::TestAPI()
{
	using namespace sword;
	ModMap::iterator it;
	ConfigEntMap::iterator cit;
	ConfigEntMap confmap;
	SWMgr SwordManager;
	SWModule* curMod = 0;
	SWKey *Key;
	ModMap* Modules;
	Modules = &SwordManager.Modules;
	
	
	for (it = Modules->begin(); it != Modules->end(); it++) {
		curMod = (*it).second;
		Key = curMod->CreateKey();
		printf("%s : %s\n", curMod->Description(), curMod->Type());
		confmap = curMod->getConfig();
		for (cit = confmap.begin(); cit != confmap.end(); cit++) {
			printf("\t%s: %s\n", cit->first.c_str(),  cit->second.c_str());
		}
		
		printf("\n");
		
		/*		
		printf("%s : %s\n", curMod->Description(), curMod->Type());
		confmap = curMod->getConfig();
		for (cit = confmap.begin(); cit != confmap.end(); cit++) {
			printf("\t%s: %s\n", cit->first.c_str(),  cit->second.c_str());
		}
		
		printf("\n");
		*/

		
		/*
		if (!strcmp(curMod->Type(), "Biblical Texts")) {
			curMod->SetKey(Key);
			printf("John 3:16: <%s> %s\n", curMod->Description(0), (const char *)(*curMod));
		}
		else if (!strcmp(curMod->Type(), "Commentaries")) {
			printf("Commentaries: %s\n", curMod->Description(0));
		}
		else if (!strcmp(curMod->Type(), "Lexicons / Dictionaries")) {
			printf("Lexicon/Dictionary: %s\n", curMod->Description(0));
		}
		*/
	}
}
