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
	#pragma interface "BibleStudyApp.h"
#endif

#ifndef _BIBLESTUDYAPP_H_
#define _BIBLESTUDYAPP_H_

	#include "biblestudy.h"
	#include "BibleStudyMainFrame.h"
	#include "SwordTools.h"	
	#include <wx/log.h>
	
	/**
	* Main Class for BibleStudy.
	*
	* Straight forward subclass of wxApp 
	**/
	class BibleStudyApp: public wxApp
	{
	private:
		/** 
		 * Global reference to sword tools, so that sword
		 * gets initialized only once.
		 **/
		SwordTools m_SwordTools;
	
	public:
		BibleStudyApp();
		~BibleStudyApp();
		
		/**
		 * Automatically executed on application start
		 */
		bool OnInit();
	};

#endif
