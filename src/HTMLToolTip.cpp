/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifdef __GNUG__
	#pragma implementation "HTMLToolTip.h"
#endif

#include "HTMLToolTip.h"

BEGIN_EVENT_TABLE(HTMLToolTip, wxFrame)
	EVT_LEAVE_WINDOW(HTMLToolTip::OnLeftWindow)
	EVT_KEY_DOWN(HTMLToolTip::OnKeyDown)
	EVT_KILL_FOCUS(HTMLToolTip::OnKillFocus)
END_EVENT_TABLE()

HTMLToolTip::HTMLToolTip(wxWindow *parent) : wxFrame(parent, -1, wxT(""), wxDefaultPosition, wxSize(200,200), wxSIMPLE_BORDER|wxFRAME_NO_TASKBAR|wxFRAME_FLOAT_ON_PARENT, wxT("ToolTip"))
{
	htmlwin = new wxHtmlWindow(this, -1, GetClientAreaOrigin(), GetClientSize(), wxHW_SCROLLBAR_AUTO, wxT("HTML"));
	m_html = wxT("");
	htmlwin->SetPage(m_html);
	m_tooltipchanged = false;
}

HTMLToolTip::~HTMLToolTip()
{
}

void HTMLToolTip::SetHTML(wxString html)
{
	if (html != m_html)
		m_tooltipchanged = true;
	else
		m_tooltipchanged = false;

	m_html = html;
	htmlwin->SetPage(html);

	if (m_html == wxT(""))
		Show(false);
}

void HTMLToolTip::OnLeftWindow(wxMouseEvent &event)
{
	Show(false);
}

void HTMLToolTip::OnKillFocus(wxFocusEvent &event)
{
//	wxFrame::Show(false);
}

bool HTMLToolTip::Show(bool show)
{
	bool retval;

	if (show) {

		if (m_html == wxT("")) {
			retval = wxFrame::Show(false);
		} else {
			if (!IsShown() || m_tooltipchanged) {
				Move(wxGetMousePosition().x-4, wxGetMousePosition().y-4);
				retval = wxFrame::Show(true);
				htmlwin->SetFocus();
			} else {
				retval = false;
			}
		}
	} else {
		retval = wxFrame::Show(false);
	}

	return retval;
}

void HTMLToolTip::OnKeyDown(wxKeyEvent &event)
{
	if (event.GetKeyCode() == WXK_ESCAPE) {
		wxFrame::Show(false);
	} else {
		event.Skip();
	}
}
