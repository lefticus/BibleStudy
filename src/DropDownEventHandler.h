/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _DROPDOWNEVENTHANDLER_H_
#define _DROPDOWNEVENTHANDLER_H_

#include "biblestudy.h"

class DropDownEventHandler;

#include <wx/event.h>
#include <wx/calctrl.h>
#include <wx/treectrl.h>
#include "BookViewToolBar.h"


	/**
	* 
	* Custom event handler
	**/
	class DropDownEventHandler : public wxEvtHandler
	{
	private:
		BookViewToolBar *m_parent;

	public:
		DropDownEventHandler();
		~DropDownEventHandler();

		void OnSetFocus(wxFocusEvent &event);
		void OnKillFocus(wxFocusEvent &event);
		void OnItemActivated(wxTreeEvent &event);
		void OnDateSelected(wxCalendarEvent &event);
		void OnMove(wxMoveEvent &event);
		
		void SetParent(BookViewToolBar *parent);

		DECLARE_EVENT_TABLE()  
	};

#endif
