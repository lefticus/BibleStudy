/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BOOKTREECTRL_H_
	#define _BOOKTREECTRL_H_

	#include "biblestudy.h"
	#include "SwordTools.h"
	#include "BibleStudyLanguages.h"
	#include <sword/swlocale.h>
	#include <sword/localemgr.h>
	#include <wx/treectrl.h>
	#include <wx/bitmap.h>
	#include <wx/imaglist.h>


	BEGIN_DECLARE_EVENT_TYPES()
		DECLARE_EVENT_TYPE(bsEVT_OPEN_IN_CURRENT_TAB, 1)
		DECLARE_EVENT_TYPE(bsEVT_OPEN_IN_NEW_TAB, 2)
		DECLARE_EVENT_TYPE(bsEVT_OPEN_IN_NEW_WINDOW, 3)
	END_DECLARE_EVENT_TYPES()
	
	#define EVT_OPEN_IN_CURRENT_TAB(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_OPEN_IN_CURRENT_TAB, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
	#define EVT_OPEN_IN_NEW_TAB(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_OPEN_IN_NEW_TAB, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
	#define EVT_OPEN_IN_NEW_WINDOW(id, fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_OPEN_IN_NEW_WINDOW, id, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
	
	enum {
		ID_BookTreePopupOpenInNewTab = 2000,
		ID_BookTreePopupOpenInNewWindow,
		ID_BookTreePopupOpen
	};
	
	/**
	* 
	* Jason Turner
	**/

	class BookTreeItemData : public wxTreeItemData
	{
	private:
		SWModule *m_Module;

	public:
		BookTreeItemData(SWModule *);
		void SetModule(SWModule *);
		SWModule *GetModule();
	};


	class BookTreeCtrl : public wxTreeCtrl
	{
	private:
		SwordTools *m_SwordTools;

		wxBitmap m_ClosedFolderBMP;
		wxBitmap m_OpenFolderBMP;
		wxBitmap m_BookBMP;

		wxImageList *m_ImageList;
		
		wxMenu *m_PopupMenu;
		
		BibleStudyLanguages m_Languages;
		
		void OnOpenModule(wxMenuEvent &event);

	public:
		BookTreeCtrl();
		~BookTreeCtrl();
		BookTreeCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);

		void RefreshBookList();
		void SetSwordTools(SwordTools *);
		
		BookTreeItemData *GetItemData(const wxTreeItemId&);
		void SetItemData(const wxTreeItemId&, BookTreeItemData*);
		
		void OnRightUp(wxMouseEvent &event);
		void OnItemActivated(wxEvent &event); 
		
		DECLARE_EVENT_TABLE()
	};

#endif
