
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <ReadingPlannerToolBar.h>
#include <BibleStudyMainFrame.h>
#include <biblestudy.h>
#include <DropDownEventHandler.h>

#include <wx/toolbar.h>
#include <wx/tbarbase.h>

#include <wx/event.h>
#include <wx/frame.h>
#include <wx/log.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/combobox.h>
#include <wx/minifram.h>
#include <wx/button.h>

#include "../icons/nextdate.xpm"
#include "../icons/previousdate.xpm"
#include "../icons/calendar.xpm"

DEFINE_EVENT_TYPE(bsEVT_BROWSE_NEXT_DAY)
DEFINE_EVENT_TYPE(bsEVT_BROWSE_PREV_DAY)
DEFINE_EVENT_TYPE(bsEVT_CHECK_DONE)
DEFINE_EVENT_TYPE(bsEVT_CAL_CHOOSER)
DEFINE_EVENT_TYPE(bsEVT_PLAN_CHANGED)

BEGIN_EVENT_TABLE(ReadingPlannerToolBar, wxToolBar)
	EVT_COMBOBOX(ID_ComboPlans, ReadingPlannerToolBar::OnPlanChanged)
  EVT_TOOL(ID_ToolNext, ReadingPlannerToolBar::OnBrowseNextDay)
	EVT_TOOL(ID_ToolPrev, ReadingPlannerToolBar::OnBrowsePrevDay)
	EVT_CHECKBOX(ID_CheckDone, ReadingPlannerToolBar::OnBrowseCheckDone)
	EVT_TOOL(ID_ToolCalendar, ReadingPlannerToolBar::OnClickCalendar)
	EVT_BUTTON(ID_DateDone, ReadingPlannerToolBar::OnCalendarDone)
	EVT_BUTTON(ID_DateToday, ReadingPlannerToolBar::OnCalendarToday)
	EVT_CALENDAR_SEL_CHANGED(ID_DateCalendar, ReadingPlannerToolBar::OnCalendarChange)
	EVT_CALENDAR(ID_DateCalendar, ReadingPlannerToolBar::OnCalendarClose) 
END_EVENT_TABLE()


ReadingPlannerToolBar::ReadingPlannerToolBar(wxWindow * parent, wxWindowID id, long style)
                : wxToolBar(parent, id, wxDefaultPosition, wxDefaultSize,
		            style, wxPanelNameStr)
{
	SetToolBitmapSize(wxSize(22, 22));
	SetToolSeparation(5);
	wxArrayString planNames = ((BibleStudyMainFrame*) GetParent())->GetPlanNames();
	if(!planNames.Count())
		planNames.Insert(wxT("No Plans Found"),0);
	m_DropDownPlans = new wxComboBox((wxWindow *)this, (wxWindowID)ID_ComboPlans, planNames[0], wxDefaultPosition, wxSize(200,-1),planNames, wxCB_READONLY);	
	AddSeparator();
	AddControl(new wxStaticText(this,-1,wxT("Reading Plan")));
	AddSeparator();
  AddControl(m_DropDownPlans);
	AddSeparator();
	AddSeparator();

	AddTool(ID_ToolPrev, wxT("Previous"), wxBitmap(previousdate_xpm), 
      wxNullBitmap, wxITEM_NORMAL, wxT("Previous"),
      wxT("Browse ReadingPlan forward one day."));
	
	
	AddTool(ID_ToolCalendar, wxT("Calendar"), wxBitmap(calendar_xpm), 
      wxNullBitmap, wxITEM_NORMAL, wxT("Open Calendar Chooser"),
      wxT("Browse backward in the current book."));
		

	AddTool(ID_ToolNext, wxT("Next"), wxBitmap(nextdate_xpm), 
      wxNullBitmap, wxITEM_NORMAL, wxT("Next"),
      wxT("Browse ReadingPlan forward one day."));

	AddSeparator();
	AddSeparator();
	m_checkDone = new wxCheckBox(this, ID_CheckDone, wxT("Done"));
	m_checkDone->SetToolTip(wxT("Mark Assignment Read"));
	AddControl(m_checkDone);
	AddSeparator();
	m_gaugeDone = new wxGauge(this, ID_GaugeDone, 104,wxDefaultPosition, wxSize(175,18));
	AddControl(m_gaugeDone);
	//AddControl(new wxCalendarCtrl(this, ID_ToolCalendar));
	m_subFrame = new wxMiniFrame(this, ID_DateFrame, wxT("Select Date"), wxDefaultPosition, wxDefaultSize, wxCLOSE_BOX | wxSTAY_ON_TOP | wxCAPTION);
	wxBoxSizer *frameTopSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *frameButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	m_Calendar = new wxCalendarCtrl(m_subFrame, ID_DateCalendar, wxDefaultDateTime, wxPoint(1,1), wxDefaultSize, wxCAL_SUNDAY_FIRST);
	m_Calendar->EnableYearChange(true);
	m_Calendar->SetHeaderColours(wxColor(12,34,139),wxColor(102,155,205));
	//wxSize size = m_Calendar->GetSize();
	//size.y += 51;
	//size.x += 9;
	wxButton* btnDone = new wxButton(m_subFrame, ID_DateDone, wxT("Done"), wxDefaultPosition, wxSize(55,-1));
	wxButton* btnToday = new wxButton(m_subFrame, ID_DateToday, wxT("Today"), wxDefaultPosition, wxSize(55,-1));

	frameButtonSizer->Add(btnToday, 0, wxALIGN_RIGHT | wxRIGHT,3);
	frameButtonSizer->Add(btnDone, 0, wxALIGN_RIGHT);
	frameTopSizer->Add(m_Calendar, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 3);
	frameTopSizer->Add(frameButtonSizer, 0, wxALIGN_RIGHT | wxALL, 3);
	m_subFrame->SetSizer(frameTopSizer);
	frameTopSizer->SetSizeHints(m_subFrame);   
	//m_subFrame->SetSize(size);
	m_subFrame->SetBackgroundColour(wxColor(196,221,244));
	Realize();
}

void ReadingPlannerToolBar::SetComboPlanNames()
{
	// It is crashing here  BUG
	
	wxCommandEvent fakeEvent = wxCommandEvent();
	wxArrayString planNames = ((BibleStudyMainFrame*) GetParent())->GetPlanNames();
	if(!planNames.Count())
		planNames.Insert(wxT("No Plans Found"),0);
	m_DropDownPlans->Clear();
	for(unsigned int i = 0; i < planNames.Count(); i++)
		m_DropDownPlans->Insert(planNames[i], i);
	m_DropDownPlans->SetSelection(0);
	m_DropDownPlans->SetValue(m_DropDownPlans->GetStringSelection());
	OnPlanChanged(fakeEvent/*Fake Event, just want to cause the event to update the pages*/);
	
}

ReadingPlannerToolBar::~ReadingPlannerToolBar()
{
}

void ReadingPlannerToolBar::SetControlStates(int percent, bool done, bool enable)
{
	m_gaugeDone->SetValue(percent);
	wxString toolTip = wxString::Format(wxT("%d"), percent);
	toolTip += wxT("% Read");
	m_gaugeDone->SetToolTip(toolTip);

	m_checkDone->SetValue(done);
	m_checkDone->Enable(enable);
	
}

void ReadingPlannerToolBar::OnBrowseNextDay(wxCommandEvent & event)
{
  wxCommandEvent eventCustom(bsEVT_BROWSE_NEXT_DAY);
  eventCustom.SetEventObject(this);
  ProcessEvent(eventCustom);
}

void ReadingPlannerToolBar::OnBrowsePrevDay(wxCommandEvent & event)
{
  wxCommandEvent eventCustom(bsEVT_BROWSE_PREV_DAY);
  eventCustom.SetEventObject(this);
  ProcessEvent(eventCustom);
}

void ReadingPlannerToolBar::OnBrowseCheckDone(wxCommandEvent & event)
{
  wxCommandEvent eventCustom(bsEVT_CHECK_DONE);
  eventCustom.SetEventObject(this);
  eventCustom.SetInt(m_checkDone->IsChecked());
  ProcessEvent(eventCustom);
}

void ReadingPlannerToolBar::OnClickCalendar(wxCommandEvent & event)
{
	m_Calendar->SetDate(reinterpret_cast<BibleStudyMainFrame*>(GetParent())->GetPlanDate());
	m_subFrame->Move(::wxGetMousePosition());
	m_subFrame->Show();
}

void ReadingPlannerToolBar::OnCalendarDone(wxCommandEvent & event)
{
	m_subFrame->Hide();
	reinterpret_cast<BibleStudyMainFrame*>(GetParent())->SetPlanDate(m_Calendar->GetDate());
}

void ReadingPlannerToolBar::OnCalendarChange(wxCalendarEvent & event)
{
	reinterpret_cast<BibleStudyMainFrame*>(GetParent())->SetPlanDate(m_Calendar->GetDate());
}

void ReadingPlannerToolBar::OnCalendarClose(wxCalendarEvent & event)
{
	m_subFrame->Hide();
	reinterpret_cast<BibleStudyMainFrame*>(GetParent())->SetPlanDate(m_Calendar->GetDate());
}

void ReadingPlannerToolBar::OnCalendarToday(wxCommandEvent & event)
{
	m_subFrame->Hide();
	m_Calendar->SetDate(wxDateTime(wxDefaultDateTime).SetToCurrent());
	reinterpret_cast<BibleStudyMainFrame*>(GetParent())->SetPlanDate(m_Calendar->GetDate());
}

void ReadingPlannerToolBar::OnPlanChanged(wxCommandEvent &event)
{
	long sel = event.GetInt();
	m_DropDownPlans->SetValue(m_DropDownPlans->GetString(sel));
	wxCommandEvent eventCustom(bsEVT_PLAN_CHANGED);
	eventCustom.SetString(m_DropDownPlans->GetValue());
  eventCustom.SetEventObject(this);
  ProcessEvent(eventCustom);
}
