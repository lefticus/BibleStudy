/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BookTreeCtrl.h"

#include "../icons/book.xpm"
#include "../icons/closedfolder.xpm"
#include "../icons/openfolder.xpm"


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
	EVT_TREE_ITEM_ACTIVATED(-1, BookTreeCtrl::OnItemActivated)
END_EVENT_TABLE() 

DEFINE_EVENT_TYPE(bsEVT_OPEN_IN_CURRENT_TAB)
DEFINE_EVENT_TYPE(bsEVT_OPEN_IN_NEW_TAB)
DEFINE_EVENT_TYPE(bsEVT_OPEN_IN_NEW_WINDOW)


BookTreeCtrl::BookTreeCtrl()
{
	

}


BookTreeCtrl::~BookTreeCtrl()
{
	if (m_PopupMenu) {
		delete m_PopupMenu;
	}
}

void BookTreeCtrl::OnItemActivated(wxEvent &event)
{
	if (GetChildrenCount(GetSelection(), false)) {
		if (IsExpanded(GetSelection())) {
			Collapse(GetSelection());
		} else {
			Expand(GetSelection());
		}
	} else {
		wxCommandEvent eventCustom(bsEVT_OPEN_IN_CURRENT_TAB);
		eventCustom.SetEventObject(this);
		eventCustom.SetClientData(GetItemData(GetSelection())->GetModule());
		ProcessEvent(eventCustom);
	}
}

void BookTreeCtrl::OnOpenModule(wxMenuEvent &event)
{
	wxCommandEvent *eventCustom;
	
	
	switch (event.GetId()) {
	case ID_BookTreePopupOpenInNewTab:
		eventCustom = new wxCommandEvent(bsEVT_OPEN_IN_NEW_TAB);
		printf("Open In New Tab\n");
		break;
	case ID_BookTreePopupOpenInNewWindow:
		eventCustom = new wxCommandEvent(bsEVT_OPEN_IN_NEW_WINDOW);
		printf("Open In New Window\n");
		break;
	case ID_BookTreePopupOpen:
		eventCustom = new wxCommandEvent(bsEVT_OPEN_IN_CURRENT_TAB);
		printf("Open In Cur Tab\n");
		break;
	}
	
	printf("Selection: %i", (int)GetSelection());
	eventCustom->SetEventObject(this);
	if (GetItemData(GetSelection())) {
		eventCustom->SetClientData(GetItemData(GetSelection())->GetModule());
	} else {
		printf("No Item Data\n");
	}
	ProcessEvent(*eventCustom);
	//delete eventCustom;
	
}


void BookTreeCtrl::OnRightUp(wxMouseEvent &event) 
{
	if (!GetChildrenCount(GetSelection(), false)) {
		PopupMenu(m_PopupMenu, event.GetPosition());
	}
}

void BookTreeCtrl::OnRightDown(wxMouseEvent &event)
{
	wxTreeItemId hititem;
	int flags;
	
	hititem = HitTest(event.GetPosition(), flags);
	
	SelectItem(hititem);
}

void BookTreeCtrl::SetSwordTools(SwordTools *newSwordTools)
{
	m_SwordTools = newSwordTools;
}

void BookTreeCtrl::RefreshBookList()
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
		//childnode = 0;
		
		configEntry = wxT("");
		configEntry = wxString(curMod->getConfigEntry("Category"), wxConvUTF8);
		if (!configEntry.CompareTo(wxT(""))) {
			childnode = treenodes[curMod->Type()];
			if (!childnode.IsOk()) {
				childnode = AppendItem(rootnode, wxString(curMod->Type(), wxConvUTF8), 1);
				SetItemImage(childnode, 2, wxTreeItemIcon_Expanded);
				treenodes[curMod->Type()] = childnode;
			}
			
			group = curMod->Type();
		} else {
			childnode = treenodes[(const char *)configEntry.mb_str()];
			if (!childnode.IsOk()) {
				childnode = AppendItem(rootnode, configEntry, 1);
				SetItemImage(childnode, 2, wxTreeItemIcon_Expanded);
				treenodes[(const char *)configEntry.mb_str()] = childnode;
			}
			
			group = (const char *)configEntry.mb_str();
		}
		
		//group = curMod->Type();
		grouplang = group;
		grouplang.append( curMod->Lang() );
		
		langnode = treelangnodes[grouplang];
		if (!langnode.IsOk()) {
			SWLocale *locale;
			wxString language;
			
			language = m_Languages.GetLanguage(wxString(curMod->Lang(), wxConvUTF8));

			langnode = AppendItem(childnode, language, 1);
			SetItemImage(langnode, 2, wxTreeItemIcon_Expanded);
			treelangnodes[grouplang] = langnode;
		}
			
		curNode = AppendItem(langnode, wxString(curMod->Name(), wxConvUTF8) + wxT(" - ") + wxString(curMod->Description(), wxConvUTF8), 0);
		SetItemData(curNode, new BookTreeItemData(curMod));
		//curMod->AddRenderFilter(new PLAINHTML());
		SortChildren(childnode);
		SortChildren(langnode);
	}
	
	SortChildren(rootnode);
}



BookTreeCtrl::BookTreeCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) : wxTreeCtrl(parent, id, pos, size, wxTR_HIDE_ROOT|wxTR_LINES_AT_ROOT, wxDefaultValidator, wxT("listCtrl")) 
{
	SetIndent(10);
	SetSpacing(10);
		
	SetupIcons();
	
	/* Build Popup Menu */
	m_PopupMenu = new wxMenu();
	m_PopupMenu->Append(ID_BookTreePopupOpen, wxT("Open"));
	m_PopupMenu->Append(ID_BookTreePopupOpenInNewTab, wxT("Open In New Tab"));
	m_PopupMenu->Append(ID_BookTreePopupOpenInNewWindow, wxT("Open In New Window"));
}

void BookTreeCtrl::SetupIcons()
{
	int size = 16;
	
	wxImageList *images = new wxImageList(size, size, TRUE);
	wxIcon icons[3];
	icons[0] = wxIcon(book_xpm);
	icons[1] = wxIcon(closedfolder_xpm);
	icons[2] = wxIcon(openfolder_xpm);
	
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

