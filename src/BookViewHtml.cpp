/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BookViewHtml.h"

BEGIN_EVENT_TABLE(BookViewHtml, wxHtmlWindow)
	EVT_LEFT_DOWN(BookViewHtml::OnMouseDown)
	EVT_LEAVE_WINDOW(BookViewHtml::OnLeaveWindow)
	EVT_KILL_FOCUS(BookViewHtml::OnKillFocus)
END_EVENT_TABLE()


DEFINE_EVENT_TYPE(bsEVT_LINK_CLICKED)
DEFINE_EVENT_TYPE(bsEVT_LINK_HOVER)

BookViewHtml::BookViewHtml(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxHtmlWindow(parent,id,pos,size, style, name)
{
	m_htmltooltip = new HTMLToolTip(this);
}


BookViewHtml::~BookViewHtml()
{
}

void BookViewHtml::OnLinkClicked(const wxHtmlLinkInfo& info)
{
	//wxLogTrace(wxTRACE_Messages, "Link Clicked");
	wxLogDebug(wxT("Link Clicked: %s"), info.GetHref().c_str());
	wxCommandEvent eventCustom(bsEVT_LINK_CLICKED);
	eventCustom.SetEventObject(this);
	eventCustom.SetString(info.GetHref());
	ProcessEvent(eventCustom);

	m_htmltooltip->Show(false);
}

void BookViewHtml::OnCellMouseHover(wxHtmlCell *cell, wxCoord x, wxCoord y)
{
	wxHtmlLinkInfo *link;

	link = cell->GetLink();

	if (link) {
		//m_htmltooltip->SetHTML(link->GetHref());
		wxCommandEvent eventCustom(bsEVT_LINK_HOVER);
		eventCustom.SetEventObject(this);
		eventCustom.SetString(link->GetHref());
		ProcessEvent(eventCustom);
	} else {
		m_htmltooltip->SetHTML(wxT(""));
	}

	m_htmltooltip->Show(true);
	if (m_htmltooltip->IsShown()) {
		m_htmltooltip->SetFocus();
	}
}

void BookViewHtml::SetHTMLToolTip(wxString html)
{
	m_htmltooltip->SetHTML(html);
}

void BookViewHtml::OnMouseDown(wxMouseEvent &event)
{
	m_htmltooltip->Show(false);
	event.Skip();
}

void BookViewHtml::OnKillFocus(wxFocusEvent &event)
{
	if (FindFocus()->GetParent() != m_htmltooltip) {
//		m_htmltooltip->Show(false);
	}

}

void BookViewHtml::OnLeaveWindow(wxMouseEvent &event)
{
	wxPoint pt;

	if (wxFindWindowAtPointer(pt)->GetParent() != m_htmltooltip) {
		//m_htmltooltip->Show(false);
	}
}