#include "ReadingPlanWizard.h"
#include <typeinfo>
#include <wx/combobox.h>
#include <wx/panel.h>
#include <typeinfo>

BEGIN_EVENT_TABLE(ReadingPlanWizard, wxWizard)
EVT_WIZARD_PAGE_CHANGED(ID_RPWizard, ReadingPlanWizard::OnShowingBooksPage)
END_EVENT_TABLE()

ReadingPlanWizard::ReadingPlanWizard(wxWindow* parent, KJVBible *bible, int id) : wxWizard(parent, id, _("ReadingPlanner Wizard"), wxBitmap(readingplannerwiz_xpm))
{

  m_page1 = new wxWizardPageSimple(this);
  wxStaticText *text = new wxStaticText(m_page1, -1,
                                        wxString(_("This wizard will walk you through the steps of creating a ReadingPlan.")) 
					+ wxT("\n\n")
                                        + wxString(_("Follow the instructions on the following pages.")));
  //SetPageSize(wxSize(400,250));

  GetPageAreaSizer()->Add(m_page1);
  m_page2 = new ReadingPlanWizardBooksPage(this, bible);
  m_page3 = new ReadingPlanWizardDatesPage(this);
  m_page4 = new ReadingPlanWizardOptsPage(this);
  wxWizardPageSimple::Chain(m_page1, m_page2);
  wxWizardPageSimple::Chain(m_page2, m_page3);
  wxWizardPageSimple::Chain(m_page3, m_page4);
}

void ReadingPlanWizard::OnShowingBooksPage(wxWizardEvent& event)
{
  ReadingPlanWizardDatesPage* page3 = NULL;
  wxWizardPage* page = event.GetPage();
  try
  {
    if (page == m_page3) {
      page3 = static_cast<ReadingPlanWizardDatesPage*>(page);
    }
    
    //page3 = dynamic_cast<ReadingPlanWizardDatesPage*>(page);
    if(page3)
    {
      m_page3->m_calStart->Show();
      m_page3->m_calEnd->Show();
    }
    else
    {
      m_page3->m_calStart->Hide();
      m_page3->m_calEnd->Hide();
    }
  }
  catch(std::bad_cast)
  {
    return;
  }

}

ReadingPlanWizardBooksPage::ReadingPlanWizardBooksPage(wxWizard *parent, KJVBible *bible) : wxWizardPageSimple(parent)
{
  wxBoxSizer *topsizer = new wxBoxSizer( wxHORIZONTAL );
  wxBoxSizer *OTsizer = new wxBoxSizer( wxVERTICAL );
  wxBoxSizer *NTsizer = new wxBoxSizer( wxVERTICAL );
  m_listOT = new BookListBox(tstOT, bible, this, ID_BookList_OT, wxDefaultPosition, wxSize(170, 145), wxLB_MULTIPLE);
  m_listNT = new BookListBox(tstNT, bible, this, ID_BookList_NT, wxDefaultPosition, wxSize(170, 145), wxLB_MULTIPLE);
  m_strOT = new wxStaticText(this, -1,_("Old Testament Books:"), wxDefaultPosition);
  m_strNT = new wxStaticText(this, -1,_("New Testament Books:"), wxDefaultPosition);
  OTsizer->Add(m_strOT, 0, wxALIGN_LEFT, 2);
  OTsizer->Add(m_listOT, 1, wxALIGN_CENTER | wxEXPAND, 2);
  NTsizer->Add(m_strNT, 0, wxALIGN_LEFT, 2);
  NTsizer->Add(m_listNT, 1, wxALIGN_CENTER | wxEXPAND, 2);
  topsizer->Add(OTsizer, 1,  wxALIGN_CENTER | wxEXPAND, 5);
  topsizer->Add(8,5);
  topsizer->Add(NTsizer, 1, wxALIGN_CENTER | wxEXPAND, 5);
  SetSizer( topsizer );
  topsizer->SetSizeHints(this);
}

BEGIN_EVENT_TABLE(ReadingPlanWizardDatesPage, wxWizardPageSimple)
EVT_CHECKBOX(ID_CheckCtrlSun, ReadingPlanWizardDatesPage::OnCheckSun)
EVT_CHECKBOX(ID_CheckCtrlMon, ReadingPlanWizardDatesPage::OnCheckMon)
EVT_CHECKBOX(ID_CheckCtrlTue, ReadingPlanWizardDatesPage::OnCheckTue)
EVT_CHECKBOX(ID_CheckCtrlWed, ReadingPlanWizardDatesPage::OnCheckWed)
EVT_CHECKBOX(ID_CheckCtrlThu, ReadingPlanWizardDatesPage::OnCheckThu)
EVT_CHECKBOX(ID_CheckCtrlFri, ReadingPlanWizardDatesPage::OnCheckFri)
EVT_CHECKBOX(ID_CheckCtrlSat, ReadingPlanWizardDatesPage::OnCheckSat)
EVT_CALENDAR_SEL_CHANGED(ID_CalendarCtrlStart , ReadingPlanWizardDatesPage::OnCalStartChange)
EVT_CALENDAR_SEL_CHANGED(ID_CalendarCtrlEnd, ReadingPlanWizardDatesPage::OnCalEndChange)
END_EVENT_TABLE()


ReadingPlanWizardDatesPage::ReadingPlanWizardDatesPage(wxWizard *parent) : wxWizardPageSimple(parent)
{
  wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );
  wxBoxSizer *topDatesizer = new wxBoxSizer( wxHORIZONTAL );
  wxBoxSizer *startDatesizer = new wxBoxSizer( wxVERTICAL );
  wxBoxSizer *endDatesizer = new wxBoxSizer( wxVERTICAL );
  wxGridSizer *weekdaysSizer = new wxGridSizer(2,4,2,10);

  m_calStart = new wxCalendarCtrl(this, ID_CalendarCtrlStart ,
                                  wxDateTime(wxDefaultDateTime).SetToCurrent(),
                                  wxDefaultPosition,
                                  wxDefaultSize,
                                  wxCAL_SUNDAY_FIRST |
                                  wxCAL_SHOW_HOLIDAYS |
                                  wxRAISED_BORDER );
  wxDateTime endDate(wxDefaultDateTime);
  endDate.SetToCurrent();
  endDate.Add(wxDateSpan(1,0,0,-1));
  m_calEnd = new wxCalendarCtrl(this, ID_CalendarCtrlEnd,
                                endDate,
                                wxDefaultPosition,
                                wxDefaultSize,
                                wxCAL_SUNDAY_FIRST |
                                wxCAL_SHOW_HOLIDAYS |
                                wxRAISED_BORDER );
//  m_calStart->Hide();
//  m_calEnd->Hide();

  m_strStart = new wxStaticText(this, -1, _("Start Date:"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE);
  m_strEnd = new wxStaticText(this, -1, _("End Date:"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE);

  m_strEnd->SetMinSize(wxSize(m_calEnd->GetSize().GetWidth(), m_strEnd->GetSize().GetHeight()));
  m_strStart->SetMinSize(wxSize(m_calStart->GetSize().GetWidth(), m_strStart->GetSize().GetHeight()));

  startDatesizer->Add(m_strStart, 0);
  startDatesizer->Add(m_calStart, 1, wxEXPAND);
//  startDatesizer->SetSizeHints(this);
//  
  endDatesizer->Add(m_strEnd, 0);
  endDatesizer->Add(m_calEnd, 1, wxEXPAND);
  topDatesizer->Add(startDatesizer, 1, wxEXPAND, 10);
  topDatesizer->Add(15,5);
  topDatesizer->Add(endDatesizer, 1, wxEXPAND, 10);

//  SetSizer( topDatesizer );
//  topDatesizer->SetSizeHints(this);

  
  
  
  m_statBox = new wxStaticBox(this, -1, _("Days of Week"));
  wxStaticBoxSizer* statsizer = new wxStaticBoxSizer(m_statBox, wxHORIZONTAL);
  m_ckSunday = new wxCheckBox(this, ID_CheckCtrlSun, _("Sunday"), wxDefaultPosition, wxSize(-1,-1));
  m_ckSunday->SetValue(true);
  m_ckMonday = new wxCheckBox(this, ID_CheckCtrlMon, _("Monday"), wxDefaultPosition, wxSize(-1,-1));
  m_ckMonday->SetValue(true);
  m_ckTuesday = new wxCheckBox(this, ID_CheckCtrlTue, _("Tuesday"), wxDefaultPosition, wxSize(-1,-1));
  m_ckTuesday->SetValue(true);
  m_ckWednesday = new wxCheckBox(this, ID_CheckCtrlWed, _("Wednesday"), wxDefaultPosition, wxSize(-1,-1));
  m_ckWednesday->SetValue(true);
  m_ckThursday = new wxCheckBox(this, ID_CheckCtrlThu, _("Thursday"), wxDefaultPosition, wxSize(-1,-1));
  m_ckThursday->SetValue(true);
  m_ckFriday = new wxCheckBox(this, ID_CheckCtrlFri, _("Friday"), wxDefaultPosition, wxSize(-1,-1));
  m_ckFriday->SetValue(true);
  m_ckSaturday = new wxCheckBox(this, ID_CheckCtrlSat, _("Saturday"), wxDefaultPosition, wxSize(-1,-1));
  m_ckSaturday->SetValue(true);

  weekdaysSizer->Add(m_ckSunday);
  weekdaysSizer->Add(m_ckMonday);
  weekdaysSizer->Add(m_ckTuesday);
  weekdaysSizer->Add(m_ckWednesday);
  weekdaysSizer->Add(m_ckThursday);
  weekdaysSizer->Add(m_ckFriday);
  weekdaysSizer->Add(m_ckSaturday);
  statsizer->Add(weekdaysSizer);

  m_lblDayTotal = new wxStaticText(this, ID_TextCtrlTotal, _("Total Days:") + wxString(wxT(" 0")),wxDefaultPosition, wxSize(-1,-1));

  m_dateBegin = (RPDate)(&m_calStart->GetDate());
  m_dateEnd = (RPDate)(&m_calEnd->GetDate());
  m_dayFlags = SUNDAY | MONDAY | TUESDAY | WEDNESDAY | THURSDAY | FRIDAY | SATURDAY;
  UpdateDays();
  topsizer->Add(topDatesizer,1);
  topsizer->Add(5,15);
  topsizer->Add(statsizer,0);
  topsizer->Add(5,5);
  topsizer->Add(m_lblDayTotal,0);
  SetSizer( topsizer );
  topsizer->SetSizeHints(this);

}

void ReadingPlanWizardDatesPage::UpdateDays()
{
  RPDate currDay = m_dateBegin;
  m_intTotalDays = 0;
  int intTotalSpan =  m_dateEnd - m_dateBegin + 1;
  int intThisDay;
  wxString caption;

  if(intTotalSpan > 0)
  {
    for( int count = 0; count < intTotalSpan; count++)
    {
      intThisDay = dayofweek(currDay.getDay(), currDay.getMonth(), currDay.getYear());
      switch(intThisDay)
      {
      case 0:
        if(m_ckSunday->IsChecked())
          m_intTotalDays++;
        break;
      case 1:
        m_intTotalDays++;
        break;
      case 2:
        if(m_ckTuesday->IsChecked())
          m_intTotalDays++;
        break;
      case 3:
        if(m_ckWednesday->IsChecked())
          m_intTotalDays++;
        break;
      case 4:
        if(m_ckThursday->IsChecked())
          m_intTotalDays++;
        break;
      case 5:
        if(m_ckFriday->IsChecked())
          m_intTotalDays++;
        break;
      case 6:
        if(m_ckSaturday->IsChecked())
          m_intTotalDays++;
        break;
      }
      currDay.advanceDate(1);
    }
    caption.Printf(wxT(" %d"), m_intTotalDays);
    m_lblDayTotal->SetLabel(_("Total Days:") + caption);
  }
  else
  {
    m_lblDayTotal->SetLabel(_("Total Days:") + wxString(wxT(" 0")));
  }
}

void ReadingPlanWizardDatesPage::OnCheckSun(wxCommandEvent &event)
{
  if(m_ckSunday->IsChecked())
    m_dayFlags |= SUNDAY;
  else
    m_dayFlags  ^= SUNDAY;
  UpdateDays();
}

void ReadingPlanWizardDatesPage::OnCheckMon(wxCommandEvent &event)
{
  if(m_ckMonday->IsChecked())
    m_dayFlags |= MONDAY;
  else
    m_dayFlags  ^= MONDAY;
  UpdateDays();
}

void ReadingPlanWizardDatesPage::OnCheckTue(wxCommandEvent &event)
{
  if(m_ckTuesday->IsChecked())
    m_dayFlags |= TUESDAY;
  else
    m_dayFlags  ^= TUESDAY;
  UpdateDays();

}

void ReadingPlanWizardDatesPage::OnCheckWed(wxCommandEvent &event)
{
  if(m_ckWednesday->IsChecked())
    m_dayFlags |= WEDNESDAY;
  else
    m_dayFlags  ^= WEDNESDAY;
  UpdateDays();
}

void ReadingPlanWizardDatesPage::OnCheckThu(wxCommandEvent &event)
{
  if(m_ckThursday->IsChecked())
    m_dayFlags |= THURSDAY;
  else
    m_dayFlags  ^= THURSDAY;
  UpdateDays();
}

void ReadingPlanWizardDatesPage::OnCheckFri(wxCommandEvent &event)
{
  if(m_ckFriday->IsChecked())
    m_dayFlags |= FRIDAY;
  else
    m_dayFlags  ^= FRIDAY;
  UpdateDays();
}

void ReadingPlanWizardDatesPage::OnCheckSat(wxCommandEvent &event)
{
  if(m_ckSaturday->IsChecked())
    m_dayFlags |= SATURDAY;
  else
    m_dayFlags  ^= SATURDAY;
  UpdateDays();
}

void ReadingPlanWizardDatesPage::OnCalStartChange(wxCalendarEvent &event)
{
  m_dateBegin = (RPDate)(&m_calStart->GetDate());
  UpdateDays();
}

void ReadingPlanWizardDatesPage::OnCalEndChange(wxCalendarEvent &event)
{
  m_dateEnd = (RPDate)(&m_calEnd->GetDate());
  UpdateDays();
}

RPDate ReadingPlanWizardDatesPage::getBeginDate()
{
  return m_dateBegin;
}

RPDate ReadingPlanWizardDatesPage::getEndDate()
{
  return m_dateEnd;
}

DAYFLAGS ReadingPlanWizardDatesPage::getDayFlags()
{
  return m_dayFlags;
}

ReadingPlanWizardOptsPage::ReadingPlanWizardOptsPage(wxWizard *parent) : wxWizardPageSimple(parent)
{
  new wxStaticText(this, wxID_ANY, _("Name ReadingPlan (31 characters max): "), wxPoint(0,0));
  m_planName = new wxTextCtrl(this, ID_EditPlanName, _("Un-named ReadingPlan"), wxPoint(0,16), wxSize(200, 20));
}

wxString ReadingPlanWizardOptsPage::getPlanName()
{
  return m_planName->GetValue();
}
