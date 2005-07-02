#ifndef _BOOKLIST_H_
#define _BOOKLIST_H_
	
#include <wx/wx.h>
#include <wx/checklst.h>
#include <wx/string.h>
	
#include <libreadingplanner/KJVBible.h>
#include "biblestudy.h"

extern KJVBible rpBible;

enum testamentType
{
		tstOT,
		tstNT
};

// Extended wxCheckListBox to add popup event
class BookListBox : public wxCheckListBox
{
public:
		BookListBox(testamentType testament, wxWindow* parent, wxWindowID id, 
				const wxPoint& pos = wxDefaultPosition, 
				const wxSize& size = wxDefaultSize, 
				long style = 0, const wxValidator& validator = wxDefaultValidator,
				const wxString& name = wxT("listBox"));
protected:
		void OnSelectAll(wxCommandEvent& event);
		void OnInvertSelection(wxCommandEvent &event);
		void OnDeselectAll(wxCommandEvent &event);
		void OnSelectOTLaw(wxCommandEvent &event);
		void OnSelectOTHistory(wxCommandEvent &event);
		void OnSelectOTPsalms(wxCommandEvent &event);
		void OnSelectOTProphets(wxCommandEvent &event);
		void OnSelectNTGospels(wxCommandEvent &event);
		void OnSelectNTHistory(wxCommandEvent &event);
		void OnSelectNTEpistles(wxCommandEvent &event);
		void OnCheckboxToggle(wxCommandEvent &event);
#ifdef __WXMSW__
		void OnContextMenu(wxContextMenuEvent& event)
			{ ShowContextMenu(ScreenToClient(event.GetPosition())); }
#else
		void OnRightUp(wxMouseEvent& event)
			{ ShowContextMenu(event.GetPosition()); }
#endif
private:
		void ShowContextMenu(const wxPoint& pos);
		testamentType m_testament;
		DECLARE_EVENT_TABLE()
};

#endif // _BOOKLIST_H_

