
/***************************************************************************
 *   Copyright (C) 2003 by David Trotz                                     *
 *   dtrotzjr@readingplanner.com                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _READINGPLANNERTOOLBAR_H_
#define _READINGPLANNERTOOLBAR_H_

#include <wx/toolbar.h>
#include <wx/gauge.h>

class wxComboBox;
class wxCheckBox;
class wxMiniFrame;
class wxCalendarCtrl;
class wxCalendarEvent;
//class wxGauge;


BEGIN_DECLARE_EVENT_TYPES() 
	DECLARE_EVENT_TYPE(bsEVT_BROWSE_NEXT_DAY, 1) 
	DECLARE_EVENT_TYPE(bsEVT_BROWSE_PREV_DAY, 1)
	DECLARE_EVENT_TYPE(bsEVT_CHECK_DONE, 1)
	DECLARE_EVENT_TYPE(bsEVT_PLAN_CHANGED, 1)
END_DECLARE_EVENT_TYPES()

#define EVT_BROWSE_NEXT_DAY(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_BROWSE_NEXT_DAY, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
#define EVT_BROWSE_PREV_DAY(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_BROWSE_PREV_DAY, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
#define EVT_CHECK_DONE(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_CHECK_DONE, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),
#define EVT_PLAN_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY(bsEVT_PLAN_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, (wxObject *) NULL ),

/**
 * Toolbar for dealing with ReadingPlanner Navigation
 *
 **/
class ReadingPlannerToolBar: public wxToolBar {
private:
  wxComboBox *m_DropDownPlans;
  wxMiniFrame* m_subFrame;
	wxCalendarCtrl* m_Calendar;
	wxCheckBox *m_checkDone;
	wxGauge *m_gaugeDone;

public:
  ReadingPlannerToolBar(wxWindow * parent, wxWindowID id, long style);
  ~ReadingPlannerToolBar();
	void SetControlStates(int percent, bool done, bool enable);
	void OnBrowseNextDay(wxCommandEvent & event);
	void OnBrowsePrevDay(wxCommandEvent & event);
	void OnBrowseCheckDone(wxCommandEvent & event);
	void OnClickCalendar(wxCommandEvent & event);
	void OnCalendarDone(wxCommandEvent & event);
	void OnCalendarClose(wxCalendarEvent & event);
	void OnCalendarChange(wxCalendarEvent & event);
	void OnCalendarToday(wxCommandEvent & event);
	void OnPlanChanged(wxCommandEvent & event);
	void SetComboPlanNames();
  DECLARE_EVENT_TABLE()
};

#endif // _READINGPLANNERTOOLBAR_H_
