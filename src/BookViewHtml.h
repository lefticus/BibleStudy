
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

#include <HTMLToolTip.h>

#include <wx/html/htmlwin.h>
#include <wx/window.h>


#ifdef HAVE_CONFIG_H
#include <../config.h>
#endif

#ifdef WITH_WXMOZILLA
#include <wxmozilla/wxMozilla.h>
#endif

const wxEventType bsEVT_LINK_CLICKED = 5420;
const wxEventType bsEVT_LINK_HOVER = 5421;
const wxEventType bsEVT_TITLE_CHANGED = 5422;


#define EVT_LINK_CLICKED(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_LINK_CLICKED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
#define EVT_LINK_HOVER(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_LINK_HOVER, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
#define EVT_TITLE_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_TITLE_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

/**
 *
 * Jason Turner
 **/

#ifdef WITH_WXMOZILLA
class BookViewHtml: public wxMozillaBrowser
#else
class BookViewHtml: public wxHtmlWindow
#endif
{
private:
  void OnLinkClicked(const wxHtmlLinkInfo & info);
  void OnCellMouseHover(wxHtmlCell * cell, wxCoord x, wxCoord y);
#ifdef WITH_WXMOZILLA
  void OnBeforeLoad(wxMozillaBeforeLoadEvent &);
  void OnTitleChanged(wxMozillaTitleChangedEvent &);
#endif
  
  HTMLToolTip m_htmltooltip;

public:
  BookViewHtml(wxWindow * parent, wxWindowID id = -1,
               const wxPoint & pos = wxDefaultPosition,
               const wxSize & size = wxDefaultSize,
               long style = wxHW_SCROLLBAR_AUTO,
               const wxString & name = wxT("htmlWindow"));

  ~BookViewHtml();

  void SetHTMLToolTip(const wxString &html);
  void OnMouseDown(wxMouseEvent &event);

#ifdef WITH_WXMOZILLA
  void SetFonts(wxString normal_face, wxString fixed_face,
		const int *sizes = NULL) {};

  wxString GetOpenedPageTitle() {
    return GetTitle();
  }
  
  wxString SelectionToText() {return GetSelection();}
#endif

  DECLARE_DYNAMIC_CLASS(BookViewHtml)
  DECLARE_EVENT_TABLE()
};

#endif
