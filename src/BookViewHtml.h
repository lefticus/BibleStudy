/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BOOKVIEWHTML_H_
#define _BOOKVIEWHTML_H_

	#include "biblestudy.h"
	#include <wx/html/htmlwin.h>
	#include "HTMLToolTip.h"

	BEGIN_DECLARE_EVENT_TYPES()
		DECLARE_EVENT_TYPE(bsEVT_LINK_CLICKED, 1)
		DECLARE_EVENT_TYPE(bsEVT_LINK_HOVER, 1)
	END_DECLARE_EVENT_TYPES()

	#define EVT_LINK_CLICKED(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_LINK_CLICKED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
	#define EVT_LINK_HOVER(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_LINK_HOVER, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),



	/**
	* 
	* Jason Turner
	**/
	class BookViewHtml : public wxHtmlWindow
	{
	private:
		void OnLinkClicked(const wxHtmlLinkInfo& info);
		void OnCellMouseHover(wxHtmlCell *cell, wxCoord x, wxCoord y);
		HTMLToolTip *m_htmltooltip;

	public:
		BookViewHtml(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHW_SCROLLBAR_AUTO, const wxString& name = wxT("htmlWindow"));
		~BookViewHtml();
		void SetHTMLToolTip(wxString html);
		void OnMouseDown(wxMouseEvent &event);
		void OnLeaveWindow(wxMouseEvent &event);
		void OnKillFocus(wxFocusEvent &event);

	DECLARE_EVENT_TABLE()
	};


#endif
