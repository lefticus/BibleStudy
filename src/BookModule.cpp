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
#include <wx/calctrl.h>
#include <wx/combobox.h>



BookModule::BookModule(SWModule *newModule)
{
	if (newModule) {
		m_Module = newModule;
		m_Modules[newModule->Name()] = newModule;
	}  else {
		m_Module = NULL;
	}

	m_Frame = NULL;
	m_Second_Module = NULL;
	m_LastKey = NULL;

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

void BookModule::AddModule(SWModule *mod)
{
	if (m_Module) {
		if (!strcmp(m_Module->Type(), mod->Type()) || 
			(!strcmp(m_Module->Type(), "Commentaries") && !strcmp(mod->Type(), "Biblical Texts")) ||
			(!strcmp(mod->Type(), "Commentaries") && !strcmp(m_Module->Type(), "Biblical Texts"))) {
			m_Second_Module = mod;
			m_Modules[mod->Name()] = mod;
		}
	} else {
		m_Module = mod;
		m_Modules[mod->Name()] = mod;
	}
}






/**
 * @todo handle non-unicode case
 */
wxString BookModule::LookupKey(wxString key, wxString search, int searchtype, bool tooltip)
{
	VerseKey vk;
	wxString output;
	char book = 0;
	int chapter = 0, verse = 0;

	#ifdef wxUSE_UNICODE
		output = wxT("<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>");
	#else
		//Do Something Else!
	#endif
	ListKey listkey;
	ListKey searchresult;

	if (key != wxT("")) {
		 listkey = vk.ParseVerseList(key.mb_str(), "Gen1:1", true);

	} else {
		if (m_LastKey)
			listkey = m_LastKey;
		else
			listkey = vk.ParseVerseList("", "Gen1:1", true);
	}
	if (search != wxT("")) {
		wxLogDebug(wxT("Range: %s, Key: %s"), key.c_str(), search.c_str());
		searchresult = m_Module->Search(search.mb_str(), searchtype, 0, &listkey);
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


	if (!strcmp(m_Module->Type(), "Biblical Texts") || !strcmp(m_Module->Type(), "Commentaries")) {
		for (i = 0; i < listkey.Count(); i++) {
			VerseKey *element = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(i));
			//VerseKey *curkey;



			if (element) {
				wxLogDebug(wxT("BookModule::LookupKey valid element"));
				//m_Module->Key(element->LowerBound());

				vk = element->UpperBound();
				//while (m_Module->Key() <= vk) {
				while ((*element) <= vk) {
				//while (!element->Error()) {
					wxLogDebug(wxT("BookModule::LookupKey m_Module->Key()<= vk"));
					//curkey = (VerseKey *)&(m_Module->Key());


					output.append(wxT("<tr align=left valign=top>"));

					//These empty columns keep everything else in line :)
					output.append(wxT("<td width='1'></td>"));

					for (it = m_Modules.begin(); it != m_Modules.end(); it++) {
						wxLogDebug(wxT("BookModule::LookupKey iterating through modules"));
						curMod = (*it).second;
						wxLogDebug(wxT("BookModule::LookupKey Setting Key"));
						/*
						if (curMod != m_Module)
							curMod->Key(m_Module->Key());
						*/

						//if (curMod != m_Module)
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
	/*							if (chapter > 0)
									output.append(wxT("<td><br></td>"));*/
								output.append(wxString::Format(wxT("%i"), element->Chapter()));
								output.append(wxT(":"));
							}

							if (element->Book() == book) {
								output.append(wxString::Format(wxT("%i"), element->Verse()));
							}

							wxLogDebug(wxT("BookModule::LookupKey updating last chaper, book, verse"));
							output.append(wxT("</font></small> "));
							output.append(verseout);
							//output.append(wxT("<br />"));

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
					//output.append(wxT("<br />"));

					output.append(wxT("</td>"));
				}

				output.append(wxT("</tr>"));
			}


		}
	} else {
		output.append(wxT("<tr align=left valign=top>"));
		output.append(wxT("<td width='1'></td>"));
		const char *moduleoutput;
		for (it = m_Modules.begin(); it != m_Modules.end(); it++) {
			output.append(wxT("<td align=left valign=top>"));

			wxLogDebug(wxT("BookModule::LookupKey iterating through modules"));
			curMod = (*it).second;

			curMod->SetKey((const char *)key.mb_str());
			moduleoutput = (const char *)(*curMod);
			output.append(wxT("<font color='#0000FF'>"));
			output.append(wxString(curMod->KeyText(), wxConvUTF8));
			output.append(wxT("</font><hr />"));
			output.append(wxString(moduleoutput, wxConvUTF8));

			output.append(wxT("</td>"));
		}

		output.append(wxT("</tr>"));
	}

	output.append(wxT("</table>"));

	if (tooltip)
		output.append(wxT("</font></body></html>"));
	else
		output.append(wxT("</html>"));

	m_LastLookupKey = key;
	return output;
}

wxFrame *BookModule::GetControl(wxWindow *parent)
{
	if (m_Frame) return m_Frame;


	if (!strcmp(m_Module->Type(), "Generic Books")) {
		TreeKey *key;
		wxTreeCtrl *tree;

		m_Frame = new wxMiniFrame(parent, -1, wxT("Select A Section"));
		tree = new wxTreeCtrl(m_Frame, -1, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT|wxTR_HAS_BUTTONS);
		
		key = (TreeKey *)m_Module->CreateKey();
		key->firstChild();

		AddTreeSiblings(tree, tree->AddRoot(wxT("Root")), key);
	} else if (!strcmp(m_Module->Type(), "Daily Devotional")) {
		wxCalendarCtrl *cal;
		
		m_Frame = new wxMiniFrame(parent, -1, wxT("Select A Date"));
		
		cal = new wxCalendarCtrl(m_Frame, -1, wxDateTime::Now(), wxDefaultPosition, wxDefaultSize, wxCAL_SEQUENTIAL_MONTH_SELECTION|wxCAL_NO_YEAR_CHANGE|wxCAL_SHOW_SURROUNDING_WEEKS|wxCAL_SUNDAY_FIRST|wxCAL_SHOW_HOLIDAYS);
		m_Frame->SetClientSize(cal->GetSize());
		cal->Move(0,0);
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
