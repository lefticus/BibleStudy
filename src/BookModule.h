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

	#include "biblestudy.h"

	using namespace sword;

	/**
	* 
	* Jason Turner
	**/
	class BookModule
	{

	private:
		SWModule *m_Module;
		wxString m_LastLookupKey;
		

	public:
		BookModule(SWModule *);
		~BookModule();

		SWModule *GetModule();
		wxString LookupKey(wxString key);
		wxString GetLastLookupKey();
	};

#endif
