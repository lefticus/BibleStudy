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
	#pragma implementation "BookTreeCtrl.h"
#endif
 
 
#include "BookTreeCtrl.h"

#include "../icons/book.xpm"
#include "../icons/bible.xpm"
#include "../icons/lexicon.xpm"
#include "../icons/commentary.xpm"
#include "../icons/devotional.xpm"
#include "../icons/closedfolder.xpm"
#include "../icons/openfolder.xpm"

enum {
	ID_CLOSEDFOLDER_ICON = 0,
	ID_OPENFOLDER_ICON,
	ID_BIBLICAL_TEXT_ICON,
	ID_LEXICON_ICON,
	ID_COMMENTARY_ICON,
	ID_BOOK_ICON,
	ID_DEVOTIONAL_ICON
};

#if USE_GENERIC_TREECTRL
BEGIN_EVENT_TABLE(BookTreeCtrl, wxGenericTreeCtrl)
#else
BEGIN_EVENT_TABLE(BookTreeCtrl, wxTreeCtrl)
#endif
	EVT_RIGHT_UP(BookTreeCtrl::OnRightUp)
	EVT_RIGHT_DOWN(BookTreeCtrl::OnRightDown)
	EVT_MENU(ID_BookTreePopupOpenInNewTab, BookTreeCtrl::OnOpenModule)
	EVT_MENU(ID_BookTreePopupOpenInNewWindow, BookTreeCtrl::OnOpenModule)
	EVT_MENU(ID_BookTreePopupOpen, BookTreeCtrl::OnOpenModule)
	EVT_MENU(ID_BookTreePopupAddToCurrentTab, BookTreeCtrl::OnOpenModule)
	EVT_TREE_ITEM_ACTIVATED(-1, BookTreeCtrl::OnItemActivated)
END_EVENT_TABLE() 

DEFINE_EVENT_TYPE(bsEVT_OPEN_IN_CURRENT_TAB)
DEFINE_EVENT_TYPE(bsEVT_OPEN_IN_NEW_TAB)
DEFINE_EVENT_TYPE(bsEVT_OPEN_IN_NEW_WINDOW)
DEFINE_EVENT_TYPE(bsEVT_ADD_TO_CURRENT_TAB)


BookTreeCtrl::~BookTreeCtrl()
{
	if (m_PopupMenu) {
		delete m_PopupMenu;
	}
}

void BookTreeCtrl::OnItemActivated(wxEvent &event)
{
	wxLogTrace(wxTRACE_Messages, "BookTreeCtrl::OnItemActivated called");
	if (GetChildrenCount(GetSelection(), false)) {
		wxLogDebug(wxT("BookTreeCtrl::OnItemActivated not a leaf"));
		
		/* windows process the dblclick and collapses immediately after this expand */ 
		#ifndef __WINDOWS__
		if (IsExpanded(GetSelection())) {
			wxLogDebug(wxT("BookTreeCtrl::OnItemActivated Collapse"));
			Collapse(GetSelection());
		} else {
			wxLogDebug(wxT("BookTreeCtrl::OnItemActivated Expand"));
			Expand(GetSelection());
		}
		#endif
		
	} else {
		wxLogDebug(wxT("BookTreeCtrl::OnItemActivated is a leaf"));
		wxCommandEvent eventCustom(bsEVT_OPEN_IN_CURRENT_TAB);
		eventCustom.SetEventObject(this);
		eventCustom.SetClientData(GetItemData(GetSelection())->GetModule());
		ProcessEvent(eventCustom);
	}
}

void BookTreeCtrl::OnOpenModule(wxMenuEvent &event)
{
	wxCommandEvent *eventCustom;
	
	wxLogTrace(wxTRACE_Messages, wxT("BookTreeCtrl::OnOpenModule called"));
	
	switch (event.GetId()) {
	case ID_BookTreePopupOpenInNewTab:
		eventCustom = new wxCommandEvent(bsEVT_OPEN_IN_NEW_TAB);
		break;
	case ID_BookTreePopupOpenInNewWindow:
		eventCustom = new wxCommandEvent(bsEVT_OPEN_IN_NEW_WINDOW);
		break;
	case ID_BookTreePopupOpen:
		eventCustom = new wxCommandEvent(bsEVT_OPEN_IN_CURRENT_TAB);
		break;
	case ID_BookTreePopupAddToCurrentTab:
		eventCustom = new wxCommandEvent(bsEVT_ADD_TO_CURRENT_TAB);
		break;
	default:
		return;
	}
	
	eventCustom->SetEventObject(this);
	if (GetItemData(GetSelection())) {
		eventCustom->SetClientData(GetItemData(GetSelection())->GetModule());
	} else {
		wxLogDebug(wxT("BookTreeCtrl::OnOpenModule no item selected"));
	}
	ProcessEvent(*eventCustom);
	
	delete eventCustom;
}


void BookTreeCtrl::OnRightUp(wxMouseEvent &event) 
{
	wxLogTrace(wxTRACE_Messages, wxT("BookTreeCtrl::OnRightUp called"));
	if (!GetChildrenCount(GetSelection(), false)) {
		PopupMenu(m_PopupMenu, event.GetPosition());
	}
}

void BookTreeCtrl::OnRightDown(wxMouseEvent &event)
{
	wxLogTrace(wxTRACE_Messages, wxT("BookTreeCtrl::OnRightDown called"));

	wxTreeItemId hititem;
	int flags;
	
	hititem = HitTest(event.GetPosition(), flags);
	
	SelectItem(hititem);
}

void BookTreeCtrl::SetSwordTools(SwordTools *newSwordTools)
{
	m_SwordTools = newSwordTools;
}

void BookTreeCtrl::RefreshBookList(bool ShowLanguages)
{	
	using namespace sword;
	ModMap::iterator it;
	SWModule* curMod = 0;
	ModMap* Modules;
	Modules = m_SwordTools->GetModuleMap();
	wxTreeItemId rootnode, childnode, langnode, curNode;
	
	std::map< string, wxTreeItemId > treenodes;
	std::map< string, wxTreeItemId > treelangnodes;
	
	string group, grouplang;
	
	wxString configEntry;
	
	rootnode = AddRoot(wxT("books"));
	for (it = Modules->begin(); it != Modules->end(); it++) {
		curMod = (*it).second;
		wxLogDebug(wxT("type %s"), (const wxChar *)wxString(curMod->Type(), wxConvUTF8));
		//childnode = 0;
		
		configEntry = wxT("");
		configEntry = wxString(curMod->getConfigEntry("Category"), wxConvUTF8);
		if (!configEntry.CompareTo(wxT(""))) {
			childnode = treenodes[curMod->Type()];
			if (!childnode.IsOk()) {
				wxLogDebug(wxT("appending type"));
				childnode = AppendItem(rootnode, wxString(curMod->Type(), wxConvUTF8), ID_CLOSEDFOLDER_ICON, ID_CLOSEDFOLDER_ICON);
				#ifndef __WINDOWS__
				SetItemImage(childnode, ID_OPENFOLDER_ICON, wxTreeItemIcon_Expanded);
				SetItemImage(childnode, ID_OPENFOLDER_ICON, wxTreeItemIcon_SelectedExpanded);
				#endif
				treenodes[curMod->Type()] = childnode;
			}
			
			group = curMod->Type();
		} else {
			childnode = treenodes[(const char *)configEntry.mb_str()];
			if (!childnode.IsOk()) {
				childnode = AppendItem(rootnode, configEntry, ID_CLOSEDFOLDER_ICON, ID_CLOSEDFOLDER_ICON);
				#ifndef __WINDOWS__
				SetItemImage(childnode, ID_OPENFOLDER_ICON, wxTreeItemIcon_Expanded);
				SetItemImage(childnode, ID_OPENFOLDER_ICON, wxTreeItemIcon_SelectedExpanded);
				#endif
				treenodes[(const char *)configEntry.mb_str()] = childnode;
			}
			
			curMod->Type((const char *)configEntry.mb_str());
			group = (const char *)configEntry.mb_str();
		}
		
		//group = curMod->Type();
		grouplang = group;
		wxLogDebug(wxT("language %s"), (const wxChar *)wxString(curMod->Lang(), wxConvUTF8));
		grouplang.append( curMod->Lang() );
		
		if (ShowLanguages) {
			langnode = treelangnodes[grouplang];
			if (!langnode.IsOk()) {
				wxString language;
				wxLogDebug(wxT("appending language"));

				language = m_Languages.GetLanguage(wxString(curMod->Lang(), wxConvUTF8));

				langnode = AppendItem(childnode, language, ID_CLOSEDFOLDER_ICON, ID_CLOSEDFOLDER_ICON);

				#ifndef __WINDOWS__
				SetItemImage(langnode, ID_OPENFOLDER_ICON, wxTreeItemIcon_Expanded);
				SetItemImage(langnode, ID_OPENFOLDER_ICON, wxTreeItemIcon_SelectedExpanded);
				#endif

				treelangnodes[grouplang] = langnode;
			}
		} else {
			langnode = childnode;
		}
			
		wxString modname = wxString(curMod->Name(), wxConvUTF8);
		modname += wxT(" - ");
		modname += wxString(curMod->Description(), wxConvUTF8);
		wxLogDebug(wxT("appending module %s"), (const wxChar *)modname);
		
		/** SET ICON **/
		if (!strcmp(curMod->Type(), "Biblical Texts")) {
			curNode = AppendItem(langnode, wxString(curMod->Name(), wxConvUTF8) + wxT(" - ") + wxString(curMod->Description(), wxConvUTF8), ID_BIBLICAL_TEXT_ICON, ID_BIBLICAL_TEXT_ICON);
		} else if (!strcmp(curMod->Type(), "Lexicons / Dictionaries") ||
					!strcmp(curMod->Type(), "Glossaries")) {
			curNode = AppendItem(langnode, wxString(curMod->Name(), wxConvUTF8) + wxT(" - ") + wxString(curMod->Description(), wxConvUTF8), ID_LEXICON_ICON, ID_LEXICON_ICON);
		} else if (!strcmp(curMod->Type(), "Commentaries")) {
			curNode = AppendItem(langnode, wxString(curMod->Name(), wxConvUTF8) + wxT(" - ") + wxString(curMod->Description(), wxConvUTF8), ID_COMMENTARY_ICON, ID_COMMENTARY_ICON);
		} else if (!strcmp(curMod->Type(), "Daily Devotional")) {
			curNode = AppendItem(langnode, wxString(curMod->Name(), wxConvUTF8) + wxT(" - ") + wxString(curMod->Description(), wxConvUTF8), ID_DEVOTIONAL_ICON, ID_DEVOTIONAL_ICON);
		} else {
			curNode = AppendItem(langnode, wxString(curMod->Name(), wxConvUTF8) + wxT(" - ") + wxString(curMod->Description(), wxConvUTF8), ID_BOOK_ICON, ID_BOOK_ICON);
		}
		/** END SET ICON **/
		
		SetItemData(curNode, new BookTreeItemData(curMod));
		//curMod->AddRenderFilter(new PLAINHTML());
		SortChildren(childnode);
		SortChildren(langnode);
	}
	
	SortChildren(rootnode);
}



BookTreeCtrl::BookTreeCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) : wxTreeCtrl(parent, id, pos, size, wxTR_HIDE_ROOT|wxTR_DEFAULT_STYLE, wxDefaultValidator, wxT("listCtrl")) 
{
//	SetIndent(10);
//	SetSpacing(10);
		
	SetupIcons();
	
	/* Build Popup Menu */
	m_PopupMenu = new wxMenu();
	m_PopupMenu->Append(ID_BookTreePopupOpen, wxT("Open"));
	m_PopupMenu->Append(ID_BookTreePopupOpenInNewTab, wxT("Open In New Tab"));
	m_PopupMenu->Append(ID_BookTreePopupOpenInNewWindow, wxT("Open In New Window"));
	m_PopupMenu->Append(ID_BookTreePopupAddToCurrentTab, wxT("Add To Current Tab"));
}

void BookTreeCtrl::SetupIcons()
{
	int size = 16;
	
	wxImageList *images = new wxImageList(size, size, TRUE);
	wxIcon icons[7];
	icons[ID_BOOK_ICON] = wxIcon(book_xpm);
	icons[ID_CLOSEDFOLDER_ICON] = wxArtProvider::GetIcon(wxART_FOLDER, wxART_OTHER, wxSize(16,16));
	icons[ID_OPENFOLDER_ICON] = wxArtProvider::GetIcon(wxART_FOLDER, wxART_OTHER, wxSize(16,16));
	icons[ID_BIBLICAL_TEXT_ICON] = wxIcon(bible_xpm);
	icons[ID_LEXICON_ICON] = wxIcon(lexicon_xpm);
	icons[ID_COMMENTARY_ICON] = wxIcon(commentary_xpm);
	icons[ID_DEVOTIONAL_ICON] = wxIcon(devotional_xpm);

		
	int sizeOrig = icons[0].GetWidth();
	
	for ( size_t i = 0; i < WXSIZEOF(icons); i++ ) {
		if (size == sizeOrig ) {
			images->Add(icons[i]);
		} else {
			images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size,size)));
		}
	}
	
	AssignImageList(images);
}

BookTreeItemData *BookTreeCtrl::GetItemData(const wxTreeItemId& item)
{
	return (BookTreeItemData *)wxTreeCtrl::GetItemData(item);
}

void BookTreeCtrl::SetItemData(const wxTreeItemId& item, BookTreeItemData* data)
{
	wxTreeCtrl::SetItemData(item, (wxTreeItemData *)data);
}

BookTreeItemData::BookTreeItemData(SWModule *newModule)
{
	m_Module = newModule;
}
	
void BookTreeItemData::SetModule(SWModule *newModule)
{
	m_Module = newModule;
}

SWModule *BookTreeItemData::GetModule()
{
	return m_Module;
}

