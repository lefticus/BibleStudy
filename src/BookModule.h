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
	#pragma interface "BookModule.h"
#endif

#ifndef _BOOKMODULE_H_
#define _BOOKMODULE_H_

	#include <sword/swmgr.h>
	#include <sword/treekey.h>
	#include <sword/versekey.h>
	#include <sword/swmodule.h>

	#include <wx/minifram.h>
	#include <wx/treectrl.h>


	using namespace sword;

	enum bsKeyType {
		bsVerseKey = 1,
		bsStringKey,
		bsTreeKey
	};

	/**
	* Wraps a SWModule and contains data related to the module, i.e. last search
	* performed. Used for duplicating/detaching tabs as well as updating the toolbar
	**/
	class BookModule
	{

	private:
		/** The SWModule being wrapped */
		SWModule *m_Module;
		SWModule *m_Second_Module;

		/** The last key looked up */
		wxString m_LastLookupKey;
		wxString m_LastSearch;
		wxString m_Description;

		wxFrame *m_Frame;

		ModMap m_Modules;
		ListKey m_LastKey;
		void AddTreeSiblings(wxTreeCtrl *tree, wxTreeItemId parentid, TreeKey *key);

		bool m_isbrowsing;
		bsKeyType m_keytype;


	public:
		BookModule(SWModule *);
		~BookModule();

		/** Returns underlying module */
		SWModule *GetModule();
		ModMap *GetModules();

		/** Lookups up a key, returning HTML representation */
		wxString LookupKey(wxString key, wxString search=wxT(""), int searchtype=0, bool tooltip=false, bool browse=false);
		wxString BrowseForward();
		wxString BrowseBackward();

		/** Return the last lookup key */
		wxString GetLastLookupKey();

		wxString GetLastSearch();
		wxString ModInfo();


		/** Returns a combobox for this book */
		wxFrame *GetControl(wxWindow *parent);

		void AddModule(SWModule *mod);

		wxString GetName();
		bsKeyType GetKeyType();
		bsKeyType GetKeyType(SWModule *mod);
		bool IsBrowsing();


		static void Percent(char, void *);
	};

#endif
