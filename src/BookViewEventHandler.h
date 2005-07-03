
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BOOKVIEWEVENTHANDLER_H_
#define _BOOKVIEWEVENTHANDLER_H_

class BookViewCtrl;

#include <wx/event.h>

/**
 *
 * Custom event handler for wxHTMLWindow
 **/
class BookViewEventHandler:public wxEvtHandler
{
private:
  BookViewCtrl *m_parent;

public:
  BookViewEventHandler();
  ~BookViewEventHandler();

  void OnSetFocus(wxFocusEvent &event);
  void SetParent(BookViewCtrl *parent);

  DECLARE_EVENT_TABLE()
};
#endif
