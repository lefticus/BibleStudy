#include "BookList.h"
#include <libreadingplanner/KJVResource.h>
#include <libreadingplanner/RPUtils.h>

BEGIN_EVENT_TABLE(BookListBox, wxCheckListBox)
#ifdef __WXMSW__
    EVT_CONTEXT_MENU(BookListBox::OnContextMenu)
#else
    EVT_RIGHT_UP(BookListBox::OnRightUp)
#endif
	EVT_MENU(ID_PopSelectAll, BookListBox::OnSelectAll)
	EVT_MENU(ID_PopDeselectAll, BookListBox::OnDeselectAll)
	EVT_MENU(ID_PopInvertSel, BookListBox::OnInvertSelection)
	EVT_MENU(ID_PopSelectOTLaw, BookListBox::OnSelectOTLaw)
	EVT_MENU(ID_PopSelectOTHistory, BookListBox::OnSelectOTHistory)
	EVT_MENU(ID_PopSelectOTPsalms, BookListBox::OnSelectOTPsalms)
	EVT_MENU(ID_PopSelectOTProphets, BookListBox::OnSelectOTProphets)
	EVT_MENU(ID_PopSelectNTGospels, BookListBox::OnSelectNTGospels)
	EVT_MENU(ID_PopSelectNTHistory, BookListBox::OnSelectNTHistory)
	EVT_MENU(ID_PopSelectNTEpistles, BookListBox::OnSelectNTEpistles)
	EVT_CHECKLISTBOX(ID_BookList_OT, BookListBox::OnCheckboxToggle)
	EVT_CHECKLISTBOX(ID_BookList_NT, BookListBox::OnCheckboxToggle)
END_EVENT_TABLE()


BookListBox::BookListBox(testamentType testament, KJVBible *bible, wxWindow* parent, wxWindowID id, 
				const wxPoint& pos, const wxSize& size, long style, 
				const wxValidator& validator, const wxString& name)
				:wxCheckListBox(parent,id,pos,size,0,NULL,style ,validator , name), m_rpBible(bible)
{
	m_rpBible->selectRange(GENESIS, REVELATION, false); // Reset the selected book

	m_testament = testament;
	if(m_testament == tstOT)
	{
		wxString otChoices[39];
		for(int i = GENESIS; i <= MALACHI; i++)
			otChoices[i] = wxString(m_rpBible->getName(i).c_str(), wxConvUTF8);
			this->InsertItems(39,otChoices,0);
		this->Refresh(true);
			
	}else
	{
		wxString ntChoices[27];
		for(int i = MATTHEW; i <= REVELATION; i++)
			ntChoices[i - MATTHEW] = wxString(m_rpBible->getName(i).c_str(), wxConvUTF8);
			this->InsertItems(27,ntChoices,0);
	}
	
}

void BookListBox::ShowContextMenu(const wxPoint& pos)
{
    wxMenu menu(_T("Selections"));

    menu.Append(ID_PopSelectAll, _T("&Select All"));
	menu.Append(ID_PopDeselectAll, _T("&Deselect All"));
	menu.Append(ID_PopInvertSel, _T("&Invert Selection"));
	menu.AppendSeparator();
	if(m_testament == tstOT)
	{
		menu.Append(ID_PopSelectOTLaw, _T("&Law"));
		menu.Append(ID_PopSelectOTHistory, _T("&History"));
		menu.Append(ID_PopSelectOTPsalms, _T("&Psalms, ect."));
		menu.Append(ID_PopSelectOTProphets, _T("&Prophets"));
	}else if(m_testament == tstNT)
	{
		menu.Append(ID_PopSelectNTGospels, _T("&Gospels"));
		menu.Append(ID_PopSelectNTHistory, _T("&History"));
		menu.Append(ID_PopSelectNTEpistles, _T("&Epistles"));
	}
    PopupMenu(&menu, pos.x, pos.y);

    // test for destroying items in popup menus
#if 0 // doesn't work in wxGTK!
    menu.Destroy(Menu_Popup_Submenu);

    PopupMenu( &menu, event.GetX(), event.GetY() );
#endif // 0
}


void BookListBox::OnSelectAll(wxCommandEvent &event)
{
	for(int i = 0; i < GetCount(); i++)
		Check(i, true);
	if(m_testament == tstOT)
		m_rpBible->selectRange(GENESIS,MALACHI, true);
	else
		m_rpBible->selectRange(MATTHEW,REVELATION, true);
}

void BookListBox::OnDeselectAll(wxCommandEvent &event)
{
	for(int i = 0; i < GetCount(); i++)
		Check(i, false);
	if(m_testament == tstOT)
		m_rpBible->selectRange(GENESIS,MALACHI, false);
	else
		m_rpBible->selectRange(MATTHEW,REVELATION, false);
}

void BookListBox::OnInvertSelection(wxCommandEvent &event)
{
	int i = 0;
	for(i = 0; i < GetCount(); i++)
		if(IsChecked(i))
			Check(i, false);
		else
			Check(i, true);

	if(m_testament == tstOT)
		for(i = GENESIS; i <= MALACHI; i++)
				m_rpBible->select(i, !m_rpBible->isSelected(i));
	else
		for(i = MATTHEW; i <= REVELATION; i++)
				m_rpBible->select(i, !m_rpBible->isSelected(i));		

}
 
void BookListBox::OnCheckboxToggle(wxCommandEvent &event)
{
	int book;

	if(m_testament == tstNT)
		book = MATTHEW;
	else 
		book = GENESIS;
	for(int i = 0; i < GetCount(); i++, book++)
	{
		if(IsChecked(i))
			m_rpBible->select(book,true);
		else
			m_rpBible->select(book,false);
	}

}

void BookListBox::OnSelectOTLaw(wxCommandEvent &event)
 {
	for(int i = GENESIS; i <= DEUTERONOMY; i++)
	{
		Check(i, true);
		m_rpBible->select(i, true);
	}

 }

void BookListBox::OnSelectOTHistory(wxCommandEvent &event)
 {
	for(int i = JOSHUA; i <= JOB; i++)
	{
		Check(i, true);
		m_rpBible->select(i, true);
	}

 }

void BookListBox::OnSelectOTPsalms(wxCommandEvent &event)
 {
	for(int i = PSALMS; i <= SONG_OF_SONGS; i++)
	{
		Check(i, true);
		m_rpBible->select(i, true);
	}

 }

void BookListBox::OnSelectOTProphets(wxCommandEvent &event)
 {
	for(int i = ISAIAH; i <= MALACHI; i++)
	{
		Check(i, true);
		m_rpBible->select(i, true);
	}

 }

void BookListBox::OnSelectNTGospels(wxCommandEvent &event)
 {
	for(int i = MATTHEW; i <= JOHN; i++)
	{
		Check(i - MATTHEW, true);
		m_rpBible->select(i, true);
	}

 }

void BookListBox::OnSelectNTHistory(wxCommandEvent &event)
 {
	Check(4, true);
	m_rpBible->select(ACTS, true);
 }

void BookListBox::OnSelectNTEpistles(wxCommandEvent &event)
 {
	for(int i = ROMANS; i <= REVELATION; i++)
	{
		Check(i - MATTHEW, true);
		m_rpBible->select(i, true);
	}

 }
 
