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
	#include <sword/treekey.h>
	#include <wx/combobox.h>
	#include <wx/treectrl.h>
	#include <wx/minifram.h>
	#include <wx/calctrl.h>
	
	using namespace sword;

	/**
	* Wraps a SWModule and contains data related to the module, i.e. last search
	* performed. Used for duplicating/detaching tabs as well as updating the toolbar
	* 
	**/
	class BookModule
	{

	private:
		/** The SWModule being wrapped */
		SWModule *m_Module;
		
		/** The last key looked up */
		wxString m_LastLookupKey;
		
		/** */
		wxMiniFrame *m_Frame;
		
		void AddTreeSiblings(wxTreeCtrl *tree, wxTreeItemId parentid, TreeKey *key);

	public:
		BookModule(SWModule *);
		~BookModule();

		/** Returns underlying module */
		SWModule *GetModule();
		
		/** Lookups up a key, returning HTML representation */
		wxString LookupKey(wxString key);
		
		/** Return the last lookup key */
		wxString GetLastLookupKey();
		
		/** Returns a combobox for this book */
		wxFrame *GetControl(wxWindow *parent);
	};

#endif
