/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifdef __GNUG__
	#pragma implementation "BookModule.h"
#endif

#include "BookModule.h"
#include "DropDownCtrl.h"
#include <wx/calctrl.h>
#include <wx/combobox.h>
#include <wx/regex.h>
#include <wx/log.h>
#include <wx/progdlg.h>
#include <wx/utils.h>
#include <wx/msgdlg.h>

BookModule::BookModule(SWModule *newModule)
{
	if (newModule) {
		m_Module = newModule;
		m_Modules[newModule->Name()] = newModule;
		m_keytype = GetKeyType(newModule);
	}  else {
		m_Module = NULL;
	}

	m_Frame = NULL;
	m_Second_Module = NULL;
	m_LastKey = NULL;
	m_isbrowsing = false;
}

bsKeyType BookModule::GetKeyType(SWModule *mod)
{
	if (mod->Key().getClass()->isAssignableFrom("StrKey")) {
		return bsStringKey;
	} else if (mod->Key().getClass()->isAssignableFrom("TreeKeyIdx") || mod->Key().getClass()->isAssignableFrom("TreeKey")) {
		return bsTreeKey;
	} else if (mod->Key().getClass()->isAssignableFrom("VerseKey")) {
		return bsVerseKey;
	} else {
		return bsStringKey;
	}
}

BookModule::~BookModule()
{
	if (m_Frame)
		m_Frame->Destroy();
}

SWModule *BookModule::GetModule()
{
	return m_Module;
}

bsKeyType BookModule::GetKeyType()
{
	return m_keytype;
}

wxString BookModule::GetName()
{
	wxString name;

	ModMap::iterator it;
	SWModule* curMod = 0;


	for (it = m_Modules.begin(); it != m_Modules.end();) {
		curMod = (*it).second;
		name += wxString(curMod->Name(), wxConvUTF8);

		it++;

		if (it != m_Modules.end()) {
			name += wxT(" - ");
		}
	}


	return name;
}

wxString BookModule::GetLastLookupKey()
{
	return m_LastLookupKey;
}

wxString BookModule::GetLastSearch()
{
	return m_LastSearch;
}

void BookModule::AddModule(SWModule *mod)
{
	if (m_Module) {
		if (m_keytype == GetKeyType(mod)) {
			m_Second_Module = mod;
			m_Modules[mod->Name()] = mod;
		}
	} else {
		m_Module = mod;
		m_Modules[mod->Name()] = mod;
	}
}


bool BookModule::IsBrowsing()
{
	return m_isbrowsing;
}

wxString BookModule::BrowseForward()
{
	if (m_isbrowsing) {
		m_Module->SetKey((const char *)m_LastLookupKey.mb_str());
		if (m_keytype == bsVerseKey) {

			VerseKey vk((const char *)m_LastLookupKey.mb_str());

			vk.Chapter(vk.Chapter()+1);


			return LookupKey(wxString(vk.getText(), wxConvUTF8), wxT(""), 0, false, true);
		} else {
			wxLogDebug(wxT("Last Key:") + m_LastLookupKey);
			(*m_Module)++;
			wxLogDebug(wxT("Next Key:") + wxString(m_Module->KeyText(), wxConvUTF8));

			return LookupKey(wxString(m_Module->KeyText(), wxConvUTF8), wxT(""), 0, false, false);
		}
	} else {
		return wxT("");
	}
}

wxString BookModule::BrowseBackward()
{
	if (m_isbrowsing) {
		m_Module->setKey((const char *)m_LastLookupKey.mb_str());
		if (m_keytype == bsVerseKey) {
			VerseKey vk((const char *)m_LastLookupKey.mb_str());

			vk.Chapter(vk.Chapter()-1);

			return LookupKey(wxString(vk.getText(), wxConvUTF8), wxT(""), 0, false, true);
		} else {
			wxLogDebug(wxT("Last Key:") + m_LastLookupKey);
			(*m_Module)++;
			wxLogDebug(wxT("Next Key:") + wxString(m_Module->KeyText(), wxConvUTF8));

			return LookupKey(wxString(m_Module->KeyText(), wxConvUTF8), wxT(""), 0, false, false);
		}
	} else {
		return wxT("");
	}
}

void BookModule::Percent(char percent, void *pd)
{
	if (!((wxProgressDialog *)pd)->Update((int)percent))
		((SWModule *)((wxProgressDialog *)pd)->GetClientData())->terminateSearch = true;
	wxLogDebug(wxT("BookModule::Percent called")+wxString::Format(wxT("%i"),percent));
	wxYield();
}

/**
 * @todo handle non-unicode case
 */
wxString BookModule::LookupKey(wxString key, wxString search, int searchtype, bool tooltip, bool browse)
{
	VerseKey vk;
	wxString output;
	char book = 0;
	int chapter = 0, verse = 0;
	int versecount = 0;
	bool cont = true;

	wxBusyCursor busy;
	wxWindowDisabler disableAll;

	m_isbrowsing = browse;

	if (m_isbrowsing)
		key = key.BeforeLast(wxT(':'));

	#ifdef wxUSE_UNICODE
		output = wxT("<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>");
	#else
		//Do Something Else!
	#endif

	ListKey listkey;
	ListKey searchresult;

	if (m_keytype == bsVerseKey)
		listkey = vk.ParseVerseList(key.mb_str(), "Gen1:1", true);
	else
		listkey.ClearList();

	//if (key == wxT("") && m_LastKey.Count() > 0) {
	//	listkey = m_LastKey;
	//}

	if (search != wxT("")) {
		wxLogDebug(wxT("Range: %s, Key: %s"), key.c_str(), search.c_str());
		wxProgressDialog pd(wxT("Searching..."), wxT("Searching for \"")+search+wxT("\""), 100, NULL, wxPD_APP_MODAL|wxPD_AUTO_HIDE|wxPD_CAN_ABORT|wxPD_ELAPSED_TIME|wxPD_ESTIMATED_TIME|wxPD_REMAINING_TIME);
		pd.SetClientData(m_Module);
		pd.Show();

		if (listkey.Count() == 0 || m_keytype != bsVerseKey) {
			searchresult = m_Module->Search(search.mb_str(), searchtype, 0, NULL, 0, &Percent, (void *)&pd);
		} else {
			searchresult = m_Module->Search(search.mb_str(), searchtype, 0, &listkey, 0, &Percent, (void *)&pd);
		}
//		pd.Hide();
		listkey = searchresult;
	}

	m_LastKey = listkey;

	int i;

	if (tooltip)
		output.append(wxT("<html><body bgcolor=#FFFF99><font size=-2>"));
	else
		output.append(wxT("<html>"));

	output.append(wxT("<table>"));

	ModMap::iterator it;
	SWModule* curMod = 0;

	output.append(wxT("<tr>"));
	//These empty columns keep everything else in line
	output.append(wxT("<th width='1'></th>"));
	for (it = m_Modules.begin(); it != m_Modules.end();it++) {
		curMod = (*it).second;
		output.append(wxT("<th><font color='#0000FF'>"));
		output.append(wxString(curMod->Name(), wxConvUTF8));
		output.append(wxT("</font></th>"));
	}
	output.append(wxT("</tr>"));


	if (m_keytype == bsVerseKey) {
		for (i = 0; i < listkey.Count(); i++) {
			VerseKey *element = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(i));

			if (!cont) break;
			if (element) {
				wxLogDebug(wxT("BookModule::LookupKey valid element"));
				vk = element->UpperBound();

				while ((*element) <= vk && cont) {
					wxYield();
					versecount++;
					if (versecount == 300) {
						wxMessageDialog msg(NULL, wxT("More than 300 verses found, continue?"), wxT("Too many verses found."), wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT | wxCENTRE, wxDefaultPosition);
						if (msg.ShowModal() != wxID_YES)
							cont = false;
					}
					wxLogDebug(wxT("BookModule::LookupKey m_Module->Key()<= vk"));
					output.append(wxT("<tr align=left valign=top>"));

					//These empty columns keep everything else in line :)
					output.append(wxT("<td width='1'></td>"));

					for (it = m_Modules.begin(); it != m_Modules.end(); it++) {
						wxLogDebug(wxT("BookModule::LookupKey iterating through modules"));
						curMod = (*it).second;
						wxLogDebug(wxT("BookModule::LookupKey Setting Key"));

						curMod->Key((*element));

						wxLogDebug(wxT("BookModule::LookupKey writing verse to output"));

						wxString verseout = wxT("");
						bool outputcell = true;
						int rowspan = 1;
						wxString thisverse = wxString((const char *)(*curMod), wxConvUTF8);
						if ((*element) > element->LowerBound()) {

							(*element)--;
							curMod->Key((*element));
							wxString prevverse = wxString((const char *)(*curMod), wxConvUTF8);
							(*element)++;

							wxLogDebug(wxT("BookModule:LookupKey: Previous:"));
							wxLogDebug(prevverse);

							wxLogDebug(wxT("BookModule:LookupKey: Current:"));
							wxLogDebug(thisverse);

							if (thisverse.Cmp(prevverse)) {
								verseout = thisverse;
								outputcell = true;
							} else {
								outputcell = false;
							}
						} else {
							outputcell = true;
							verseout = thisverse;
						}

						VerseKey elemcopy(element);
						elemcopy++;
						curMod->Key(elemcopy);
						wxString nextverse = wxString((const char *)(*curMod), wxConvUTF8);
						while (elemcopy <= vk && !nextverse.Cmp(verseout) && outputcell) {
							rowspan++;
							elemcopy++;
							curMod->Key(elemcopy);
							nextverse = wxString((const char *)(*curMod), wxConvUTF8);

						}

						if (outputcell) {
							output.append(wxString::Format(wxT("<td align=left valign=top rowspan=%i>"), rowspan));

							output.append(wxT("<small><font color='#0000FF'>"));
							if (element->Book() != book) {
								wxLogDebug(wxT("BookModule::LookupKey new book"));
								output.append(wxString(element->getText(), wxConvUTF8));
							} else if (element->Chapter() != chapter) {
								wxLogDebug(wxT("BookModule::LookupKey new chapter"));

								output.append(wxString::Format(wxT("%i"), element->Chapter()));
								output.append(wxT(":"));
							}

							if (element->Book() == book) {
								output.append(wxString::Format(wxT("%i"), element->Verse()));
							}

							wxLogDebug(wxT("BookModule::LookupKey updating last chaper, book, verse"));
							output.append(wxT("</font></small> "));
							output.append(verseout);

							output.append(wxT("</td>"));
						}
					}

					book = element->Book();
					chapter = element->Chapter();
					verse = element->Verse();

					output.append(wxT("</tr>"));
					if ((*element) == vk) break;

					wxLogDebug(wxT("BookModule::LookupKey incrementing m_Module"));
					(*element)++;
				}
			} else {
				output.append(wxT("<tr align=left valign=top>"));
				output.append(wxT("<td width='1'></td>"));
				wxYield();
				versecount++;
				if (versecount == 300) {
					wxMessageDialog msg(NULL, wxT("More than 300 verses found, continue?"), wxT("Too many verses found."), wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT | wxCENTRE, wxDefaultPosition);
					if (msg.ShowModal() != wxID_YES)
						cont = false;
				}

				ModMap::iterator it;
				SWModule* curMod = 0;

				for (it = m_Modules.begin(); it != m_Modules.end(); it++) {
					curMod = it->second;
					curMod->Key(*listkey.GetElement(i));

					output.append(wxT("<td align=left valign=top>"));

					output.append(wxT("<small><font color='#0000FF'>"));
					m_Module->Key(*listkey.GetElement(i));
					output.append(wxString(m_Module->KeyText(), wxConvUTF8));
					output.append(wxT("</font></small> "));
					output.append(wxString((const char *)(*curMod), wxConvUTF8));

					output.append(wxT("</td>"));
				}

				output.append(wxT("</tr>"));
			}
//			if (key == wxT(""))
//				m_LastLookupKey.append(wxString(listkey.GetElement(i)->getText(), wxConvUTF8));

		}


	} else {
		m_isbrowsing = true;

		if (listkey.Count() == 0) {
			listkey << (const char *)key.mb_str();
		}

		SWKey *element;
		for (int i = 0; i<listkey.Count(); i++) {
			element = listkey.GetElement(i);

			output.append(wxT("<tr align=left valign=top>"));
			output.append(wxT("<td width='1'></td>"));
			const char *moduleoutput;
			for (it = m_Modules.begin(); it != m_Modules.end(); it++) {
				output.append(wxT("<td align=left valign=top>"));

				wxLogDebug(wxT("BookModule::LookupKey iterating through modules"));
				curMod = (*it).second;

				curMod->SetKey(element);
				moduleoutput = (const char *)(*curMod);
				output.append(wxT("<font color='#0000FF'>"));
				output.append(wxString(curMod->KeyText(), wxConvUTF8));
				output.append(wxT("</font><hr />"));
				output.append(wxString(moduleoutput, wxConvUTF8));

				output.append(wxT("</td>"));
			}

			output.append(wxT("</tr>"));
		}

		m_LastLookupKey = key;
	}

	output.append(wxT("</table>"));

	if (tooltip)
		output.append(wxT("</font></body></html>"));
	else
		output.append(wxT("</html>"));

	m_LastLookupKey = key;
	m_LastSearch = search;

	if (search != wxT("")) {
//		wxRegEx myregex(search, wxRE_ICASE);
//		myregex.ReplaceAll(&output, wxT("<font color=#999900'>\\0</font>"));
	}


	return output;
}

wxFrame *BookModule::GetControl(wxWindow *parent)
{
	if (m_Frame) return m_Frame;


	if (!strcmp(m_Module->Type(), "Generic Books")) {
		TreeKey *key;
		m_Frame = new DropDownCtrl(parent, m_Module, bsTree);

		wxTreeCtrl *tree = ((DropDownCtrl *)m_Frame)->GetTree();


		key = (TreeKey *)m_Module->CreateKey();
		key->firstChild();

		AddTreeSiblings(tree, tree->AddRoot(wxT("Root")), key);
	} else if (!strcmp(m_Module->Type(), "Daily Devotional")) {
		m_Frame = new DropDownCtrl(parent, m_Module, bsCalendar);
	} else if (!strcmp(m_Module->Type(), "Biblical Texts") || !strcmp(m_Module->Type(), "Commentaries")) {
		m_Frame = new DropDownCtrl(parent, m_Module, bsBible);
	}

	return m_Frame;
}


void BookModule::AddTreeSiblings(wxTreeCtrl *tree, wxTreeItemId parentid, TreeKey *key)
{
	wxTreeItemId itemadded;
	wxLogDebug(wxT("BookModule::AddTreeSiblings called: %s"), (const wxChar*)wxString(key->getFullName(), wxConvUTF8));
	bool cont;
	cont = true;

	while (cont) {
		itemadded = tree->AppendItem(parentid, wxString(key->getLocalName(), wxConvUTF8));

		if (key->hasChildren()) {
			key->firstChild();
			AddTreeSiblings(tree, itemadded, key);
			key->parent();
		}

		cont = key->nextSibling();
	}
}
