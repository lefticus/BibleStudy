/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BOOKVIEWCTRL_H_
	
	#define _BOOKVIEWCTRL_H_

	#include "biblestudy.h"
	#include <wx/notebook.h>
	#include <wx/html/htmlwin.h>
	#include <wx/fontdlg.h>
	#include <string>
	#include "BookModule.h"

	using namespace sword;
	using namespace std;

	/**
	* Tabbed viewing of book modules
	* 
	**/
	class BookViewCtrl : public wxNotebook
	{

	public:
		BookViewCtrl();
		BookViewCtrl(wxWindow *parent, int id, const wxPoint pos, const wxSize size);
		~BookViewCtrl();
		
		int AddTab();
		void RemoveTab();
		
		/**
		 * Sets the module for the active tab
		 */
		void OpenInCurrentTab(SWModule *);
		void OpenInNewTab(SWModule *);
		void LookupKey(wxString key);
		BookModule *GetActiveBookModule();
	};

#endif
