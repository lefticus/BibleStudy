/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#if defined(__GNUG__) && !defined(__APPLE__)
	#pragma interface "SwordTools.h"
#endif

#ifndef _SWORDTOOLS_H_
	#define _SWORDTOOLS_H_

	#include "biblestudy.h"
	#include "BookModule.h"

	using namespace sword;
	using namespace std;

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

		SWMgr *m_SwordManager;

	public:
		SwordTools();
		~SwordTools();

		ModMap *GetModuleMap();
		SWMgr *GetSwordManager();
		SWModule *GetModule(const char *ModuleName);

		BookModule *GetModuleFromLink(wxString link);
		wxString GetKeyFromLink(wxString link);
	};

#endif
