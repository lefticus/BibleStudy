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
	#pragma interface "DropDownCtrl.h"
#endif


#ifndef DROPDOWNCTRL_H
	#define DROPDOWNCTRL_H
	#include <wx/wx.h>

	#include <swmodule.h>


	#include <wx/minifram.h>
	#include <wx/treectrl.h>
	#include <wx/calctrl.h>
	#include <wx/button.h>

	using namespace sword;


	enum bsDropDownMode {
		bsCalendar = 1,
		bsTree = 2,
		bsBible = 4
	};

	/**
	* @author Jason Turner
	*/
	class DropDownCtrl : public wxMiniFrame{
	private:
		wxTreeCtrl *m_Tree;
		wxCalendarCtrl *m_Calendar;
		wxComboBox *m_BookCB;
		wxComboBox *m_ChapterCB;
		wxComboBox *m_VerseCB;
		wxButton *m_Button;

		SWModule *m_Module;

		bsDropDownMode m_Mode;
		void UpdateBookCB();
		void UpdateVerseCB();
		void UpdateChapterCB();

		int m_LastChapter;
		char m_LastBook;
		int m_LastVerse;

	public:
		DropDownCtrl(wxWindow *parent, SWModule*, bsDropDownMode mode);
		~DropDownCtrl();

		wxTreeCtrl *GetTree();
		wxCalendarCtrl *GetCalendar();

		void UpdateCBs(wxCommandEvent &event);
		void OnButtonPress(wxCommandEvent &event);
		void OnKeyDown(wxKeyEvent &event);

		DECLARE_EVENT_TABLE()
	};


#endif
