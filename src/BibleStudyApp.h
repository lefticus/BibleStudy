/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BIBLESTUDYAPP_H_
#define _BIBLESTUDYAPP_H_

	#include "biblestudy.h"
	#include "BibleStudyMainFrame.h"
	#include "SwordTools.h"	
	
	/**
	* Main Class for BibleStudy.
	*
	* \todo Move SwordTools to be owned by app, so there is only one instance for
	* multiple windows.
	* 
	**/
	class BibleStudyApp: public wxApp
	{
	private:
		SwordTools m_SwordTools;
	
	public:
		BibleStudyApp();
		~BibleStudyApp();
		
		bool OnInit();
	};

#endif
