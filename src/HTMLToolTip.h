
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _HTMLTOOLTIP_H_
#define _HTMLTOOLTIP_H_

#include <wx/frame.h>
#include <wx/html/htmlwin.h>

/**
 *
 * Jason Turner
 **/
class HTMLToolTip:public wxFrame {
private:
  wxHtmlWindow *htmlwin;
  wxString m_html;
  bool m_tooltipchanged;

public:
  HTMLToolTip(wxWindow * parent);
  ~HTMLToolTip();

  void SetHTML(const wxString&);
  bool Show(bool show = TRUE);
  void OnLeftWindow(wxMouseEvent &event);
  void OnKillFocus(wxFocusEvent &event);
  void OnKeyDown(wxKeyEvent &event);
  
  DECLARE_EVENT_TABLE()

};

#endif
