
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <BookViewHtml.h>
#include <HTMLToolTip.h>

#include <wx/log.h>

#ifdef HAVE_CONFIG_H
#include <../config.h>
#endif


#ifdef WITH_WXMOZILLA
#include <wxmozilla/wxMozilla.h>
#endif

#ifdef WITH_WXMOZILLA
IMPLEMENT_CLASS(BookViewHtml, wxMozillaBrowser)
BEGIN_EVENT_TABLE(BookViewHtml, wxMozillaBrowser)
EVT_MOZILLA_BEFORE_LOAD(BookViewHtml::OnBeforeLoad)
EVT_MOZILLA_TITLE_CHANGED(BookViewHtml::OnTitleChanged)
END_EVENT_TABLE()
#else
IMPLEMENT_CLASS(BookViewHtml, wxHtmlWindow)
BEGIN_EVENT_TABLE(BookViewHtml, wxHtmlWindow)
EVT_LEFT_DOWN(BookViewHtml::OnMouseDown)
END_EVENT_TABLE()
#endif 

DEFINE_EVENT_TYPE(bsEVT_LINK_CLICKED)
DEFINE_EVENT_TYPE(bsEVT_LINK_HOVER)
DEFINE_EVENT_TYPE(bsEVT_TITLE_CHANGED)

#ifdef WITH_WXMOZILLA
BookViewHtml::BookViewHtml(wxWindow * parent, wxWindowID id,
                           const wxPoint & pos, const wxSize & size,
                           long style,
                           const wxString &name)
    : wxMozillaBrowser(parent, id, pos, size, style, name),
    m_htmltooltip(this)
{}
#else
BookViewHtml::BookViewHtml(wxWindow * parent, wxWindowID id,
                           const wxPoint & pos, const wxSize & size,
                           long style,
                           const wxString &name)
    : wxHtmlWindow(parent, id, pos, size, style, name),
    m_htmltooltip(this)
{}
#endif


BookViewHtml::~BookViewHtml()
{}

#ifdef WITH_WXMOZILLA
void BookViewHtml::OnBeforeLoad(wxMozillaBeforeLoadEvent &evt)
{
  
  wxCommandEvent eventCustom(bsEVT_LINK_CLICKED);

  eventCustom.SetEventObject(this);
  eventCustom.SetString(evt.GetURL());
  evt.Cancel();
  ProcessEvent(eventCustom);
}

void BookViewHtml::OnTitleChanged(wxMozillaTitleChangedEvent &evt)
{
  
  wxCommandEvent eventCustom(bsEVT_TITLE_CHANGED);

  eventCustom.SetEventObject(this);
  eventCustom.SetString(evt.GetTitle());
  ProcessEvent(eventCustom);
}
#endif

void BookViewHtml::OnLinkClicked(const wxHtmlLinkInfo &info)
{
  wxLogDebug(wxT("Link Clicked: %s"), info.GetHref().c_str());
  wxCommandEvent eventCustom(bsEVT_LINK_CLICKED);

  eventCustom.SetEventObject(this);
  eventCustom.SetString(info.GetHref());
  ProcessEvent(eventCustom);

  m_htmltooltip.Show(false);
}

void BookViewHtml::OnCellMouseHover(wxHtmlCell *cell, wxCoord x, wxCoord y)
{
  wxHtmlLinkInfo *link;

  link = cell->GetLink();

  if (link)
  {
    wxCommandEvent eventCustom(bsEVT_LINK_HOVER);

    eventCustom.SetEventObject(this);
    eventCustom.SetString(link->GetHref());
    ProcessEvent(eventCustom);
  }
  else
  {
    m_htmltooltip.SetHTML(wxT(""));
  }

  m_htmltooltip.Show(true);
  if (m_htmltooltip.IsShown())
  {
    m_htmltooltip.SetFocus();
  }
}

void BookViewHtml::SetHTMLToolTip(const wxString &html)
{
  m_htmltooltip.SetHTML(html);
}

void BookViewHtml::OnMouseDown(wxMouseEvent & event)
{
  m_htmltooltip.Show(false);
  event.Skip();
}
