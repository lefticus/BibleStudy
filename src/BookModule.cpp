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
}


BookModule::~BookModule()
{
}

SWModule *BookModule::GetModule()
{
	return m_Module;
}

wxString BookModule::GetLastLookupKey()
{
	return m_LastLookupKey;
}

wxString BookModule::LookupKey(wxString key)
{
	VerseKey vk;
	wxString output;
	char book = 0;
	char numstr[10];
	int chapter = 0, verse = 0;
	
	output = wxT("<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>");
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
	//mod->SetKey((const char *)key);
	
	//wxMessageBox(output, wxT("HTML Output"), wxOK | wxICON_INFORMATION, this);
	//wxFontData data;
	//wxFontDialog dialog(this, data);
	//dialog.ShowModal();
	//html->SetFont(data.GetChosenFont());
	//html->SetPage(key);
}
