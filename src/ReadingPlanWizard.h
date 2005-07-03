#ifndef _READINGPLANWIZARD_H_
#define _READINGPLANWIZARD_H_

#include <wx/wx.h>
#include <wx/wizard.h>
#include <wx/string.h>
#include <wx/calctrl.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/statbox.h>

#include "../icons/readingplannerwiz.xpm"
#include "BookList.h"
#include <libreadingplanner/RPDate.h>
#include <libreadingplanner/RPUtils.h>

class ReadingPlanWizardOptsPage : public wxWizardPageSimple
{
public:
  wxString getPlanName();
  ReadingPlanWizardOptsPage(wxWizard *parent);
  ~ReadingPlanWizardOptsPage(){};
protected:

private:
  wxTextCtrl* m_planName;
};

class ReadingPlanWizardBooksPage : public wxWizardPageSimple
{
public:
  ReadingPlanWizardBooksPage(wxWizard *parent, KJVBible *bible);
  ~ReadingPlanWizardBooksPage(){};
private:
  BookListBox* m_listOT;
  BookListBox* m_listNT;
  wxStaticText* m_strOT;
  wxStaticText* m_strNT;
};

class ReadingPlanWizardDatesPage : public wxWizardPageSimple
{
public:
  RPDate getBeginDate();
  RPDate getEndDate();
  DAYFLAGS getDayFlags();
  ReadingPlanWizardDatesPage(wxWizard *parent);
  ~ReadingPlanWizardDatesPage(){};
  friend class ReadingPlanWizard;
protected:
  void OnCheckSun(wxCommandEvent &event);
  void OnCheckMon(wxCommandEvent &event);
  void OnCheckTue(wxCommandEvent &event);
  void OnCheckWed(wxCommandEvent &event);
  void OnCheckThu(wxCommandEvent &event);
  void OnCheckFri(wxCommandEvent &event);
  void OnCheckSat(wxCommandEvent &event);
  void OnCalStartChange(wxCalendarEvent &event);
  void OnCalEndChange(wxCalendarEvent &event);
  void UpdateDays();

private:
  wxCalendarCtrl* m_calStart;
  wxCalendarCtrl* m_calEnd;
  wxStaticText* m_strStart;
  wxStaticText* m_strEnd;
  wxCheckBox* m_ckSunday;
  wxCheckBox* m_ckMonday;
  wxCheckBox* m_ckTuesday;
  wxCheckBox* m_ckWednesday;
  wxCheckBox* m_ckThursday;
  wxCheckBox* m_ckFriday;
  wxCheckBox* m_ckSaturday;
  wxStaticBox* m_statBox;
  wxStaticText* m_lblDayTotal;
  int m_intTotalDays;

  RPDate m_dateBegin;
  RPDate m_dateEnd;
  DAYFLAGS m_dayFlags;
  DECLARE_EVENT_TABLE()

};

class ReadingPlanWizard : public wxWizard
{
public:
  ReadingPlanWizard(wxWindow* parent, KJVBible*, int id = ID_RPWizard);
  bool Run() {return (wxWizard*)this->RunWizard((wxWizardPage*)m_page1);}
  RPDate getBeginDate(){return m_page3->getBeginDate();}
  RPDate getEndDate(){return m_page3->getEndDate();}
  DAYFLAGS getDayFlags(){return m_page3->getDayFlags();}
  wxString getPlanName() {return m_page4->getPlanName();}
  void OnShowingBooksPage(wxWizardEvent& event);
private:
  wxWizardPageSimple* m_page1;
  ReadingPlanWizardBooksPage* m_page2;
  ReadingPlanWizardDatesPage* m_page3;
  ReadingPlanWizardOptsPage* m_page4;
  DECLARE_EVENT_TABLE()
};
#endif
