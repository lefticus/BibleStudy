/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BOOKVIEWTOOLBAR_H_
	
	#define _BOOKVIEWTOOLBAR_H_

	#include "biblestudy.h"
	#include <wx/toolbar.h>
	#include <wx/bitmap.h>

	
	/**
	* Toolbar with inputs for searching in a Module.
	* 
	**/
	class BookViewToolBar : public wxToolBar
	{
	private:
		wxTextCtrl *m_LookupKey;
		void SetupIcons();

	public:
		BookViewToolBar(wxWindow *parent, wxWindowID id, long style);
		~BookViewToolBar();

		wxString GetLookupKey();
		void SetLookupKey(wxString);
	};

#endif
