/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BookModule.h"


BookModule::BookModule(SWModule *newModule)
{
	m_Module = newModule;
	m_Frame = NULL;
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

wxString BookModule::GetLastLookupKey()
{
	return m_LastLookupKey;
}
/**
 * @todo handle non-unicode case
 */
wxString BookModule::LookupKey(wxString key)
{
	VerseKey vk;
	wxString output;
	char book = 0;
	char numstr[10];
	int chapter = 0, verse = 0;
	
	#ifdef wxUSE_UNICODE
		output = wxT("<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>");
	#else
		//Do Something Else!
	#endif
	
	ListKey listkey = vk.ParseVerseList(key.mb_str(), "Gen1:1", true);
	int i;
	
	if (!strcmp(m_Module->Type(), "Biblical Texts") || !strcmp(m_Module->Type(), "Commentaries")) {
		for (i = 0; i < listkey.Count(); i++) {
			VerseKey *element = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(i));
			VerseKey *curkey;

			if (element) {
				m_Module->Key(element->LowerBound());

				vk = element->UpperBound();
				while (m_Module->Key() <= vk) {
					curkey = (VerseKey *)&(m_Module->Key());
					output.append(wxT("<small><font color='#0000FF'>"));
					if (curkey->Book() != book) {
						output.append(wxString(m_Module->KeyText(), wxConvUTF8));
					} else if (curkey->Chapter() != chapter) {
						if (chapter > 0)
							output.append(wxT("<br>"));
						output.append(wxString::Format(wxT("%i"), curkey->Chapter()));
						output.append(wxT(":"));
					} 

					if (curkey->Book() == book) {
						output.append(wxString::Format(wxT("%i"), curkey->Verse()));
					}
					book = curkey->Book();
					chapter = curkey->Chapter();
					verse = curkey->Verse();
					output.append(wxT("</font></small> "));
					output.append(wxString((const char *)(*m_Module), wxConvUTF8));
					output.append(wxT("<br />"));
					if (m_Module->Key() == vk) break;
					(*m_Module)++;
				}
			} else {
				output.append(wxT("<small><font color='#0000FF'>"));
				m_Module->Key(*listkey.GetElement(i));
				output.append(wxString(m_Module->KeyText(), wxConvUTF8));
				output.append(wxT("</font></small> "));
				output.append(wxString((const char *)(*m_Module), wxConvUTF8));
				output.append(wxT("<br />"));
			}
			output.append(wxT("<br />"));
		}
	} else {
		const char *moduleoutput;
		m_Module->SetKey((const char *)key.mb_str());
		moduleoutput = (const char *)(*m_Module);
		output.append(wxT("<font color='#0000FF'>"));
		output.append(wxString(m_Module->KeyText(), wxConvUTF8));
		output.append(wxT("</font><hr />"));
		output.append(wxString(moduleoutput, wxConvUTF8));
	}
	
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
