
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <BookViewCtrl.h>
#include <BookViewHtml.h>
#include <BookModule.h>

#include <wx/imaglist.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/log.h>
#include <wx/image.h>

#include <swmodule.h>
#include <swmgr.h>

using namespace sword;

#include "../icons/book.xpm"
#include "../icons/bible.xpm"
#include "../icons/lexicon.xpm"
#include "../icons/commentary.xpm"
#include "../icons/devotional.xpm"

enum {
  ID_BIBLICAL_TEXT_ICON = 0,
  ID_LEXICON_ICON,
  ID_COMMENTARY_ICON,
  ID_BOOK_ICON,
  ID_DEVOTIONAL_ICON
};

DEFINE_EVENT_TYPE(bsEVT_CHILD_SET_FOCUS)
  BEGIN_EVENT_TABLE(BookViewCtrl, wxNotebook)
  EVT_SET_FOCUS(BookViewCtrl::OnSetFocus)
  EVT_NOTEBOOK_PAGE_CHANGED(-1, BookViewCtrl::OnNotebookPageChanged)
  EVT_LEFT_UP(BookViewCtrl::OnLeftUp)
END_EVENT_TABLE()

BookViewCtrl::~BookViewCtrl()
{
}

BookViewCtrl::BookViewCtrl(wxWindow * parent, int id, const wxPoint pos,
                           const wxSize size)
            : wxNotebook(parent, id, pos, size, wxSIMPLE_BORDER, 
	                 wxT("notebook"))
{

  m_firstTabCreated = false;
	int imgsize = 16;

  wxImageList *images = new wxImageList(imgsize, imgsize, TRUE);
  wxIcon icons[5];

  icons[ID_BIBLICAL_TEXT_ICON] = wxIcon(bible_xpm);
  icons[ID_LEXICON_ICON] = wxIcon(lexicon_xpm);
  icons[ID_COMMENTARY_ICON] = wxIcon(commentary_xpm);
  icons[ID_BOOK_ICON] = wxIcon(book_xpm);
  icons[ID_DEVOTIONAL_ICON] = wxIcon(devotional_xpm);

  int sizeOrig = icons[0].GetWidth();

  for (size_t i = 0; i < WXSIZEOF(icons); i++) {
    if (imgsize == sizeOrig) {
      images->Add(icons[i]);
    } else {
      images->
        Add(wxBitmap
            (wxBitmap(icons[i]).ConvertToImage().Rescale(imgsize, imgsize)));
    }
  }

  AssignImageList(images);

  m_CustEventHandler = new BookViewEventHandler();
  m_CustEventHandler->SetParent(this);
}

int
  BookViewCtrl::AddTab()
{
  wxNotebookPage *page;
  BookViewHtml *html;
  wxBoxSizer *panelsizer = new wxBoxSizer(wxVERTICAL);

  page = new wxPanel(this);
  html =
    new BookViewHtml(page, -1, wxDefaultPosition, wxDefaultSize, wxVSCROLL,
                     wxT("htmlwindow"));

  BookViewEventHandler *neweventhandler;

  neweventhandler = new BookViewEventHandler();
  neweventhandler->SetParent(this);
  html->PushEventHandler(neweventhandler);

  // #ifdef _WIN32
  // Choose appropriate font sizes for windows
  const int sizes[7] = { 7, 8, 10, 12, 16, 22, 30 };
  // #else
  // Choose approriate font sizes for GTK
  // const int sizes[7] = {10, 12, 14, 16, 19, 24, 32};
  // #endif
  html->SetFonts(wxT(""), wxT(""), sizes);

  panelsizer->Add(html, 1, wxEXPAND);
  page->SetSizer(panelsizer);
  AddPage(page, wxT("*Empty*"));

  SetSelection(GetPageCount() - 1);

  OpenInCurrentTab(wxT("<html><head><title>*Empty*</title></head></html>"));
	m_firstTabCreated = GetPageCount(); 
  return GetPageCount() - 1;
}

void BookViewCtrl::CloseTab()
{
  BookViewHtml *html;
  BookModule *mod;
  unsigned int page;

  html =
    (BookViewHtml *) GetPage(GetSelection())->GetChildren().GetFirst()->
    GetData();
  mod = (BookModule *) html->GetClientData();

  if (GetPageCount() > 1) {
    if (mod)
      delete mod;

    page = GetSelection();
    RemovePage(page);
    if (GetPageCount() > page)
      SetSelection(page);
    else
      SetSelection(page - 1);
  }

  PostChildSetFocus();
}

void BookViewCtrl::LookupKey(const wxString &key)
{
  BookViewHtml *html;
  BookModule *mod;

  html =
    (BookViewHtml *) GetPage(GetSelection())->GetChildren().GetFirst()->
    GetData();
  mod = (BookModule *) html->GetClientData();

  if (mod)
    html->SetPage(mod->LookupKey(key));
}

void BookViewCtrl::BrowseKey(const wxString &key)
{
  BookViewHtml *html;
  BookModule *mod;

  html =
    (BookViewHtml *) GetPage(GetSelection())->GetChildren().GetFirst()->
    GetData();
  mod = (BookModule *) html->GetClientData();

  if (mod)
    html->SetPage(mod->LookupKey(key, wxT(""), 0, false, true));
}

void BookViewCtrl::BrowseForward()
{
  BookViewHtml *html;
  BookModule *mod;

  html =
    (BookViewHtml *) GetPage(GetSelection())->GetChildren().GetFirst()->
    GetData();
  mod = (BookModule *) html->GetClientData();

  if (mod)
    html->SetPage(mod->BrowseForward());
}

void BookViewCtrl::BrowseBackward()
{
  BookViewHtml *html;
  BookModule *mod;

  html =
    (BookViewHtml *) GetPage(GetSelection())->GetChildren().GetFirst()->
    GetData();
  mod = (BookModule *) html->GetClientData();

  if (mod)
    html->SetPage(mod->BrowseBackward());
}

void BookViewCtrl::Search(const wxString &range, const wxString &search, 
                          int searchtype)
{
  BookViewHtml *html;
  BookModule *mod;

  html =
    (BookViewHtml *) GetPage(GetSelection())->GetChildren().GetFirst()->
    GetData();
  mod = (BookModule *) html->GetClientData();

  if (mod) {
    wxLogDebug(wxT("search: %s, range: %s"), search.c_str(), range.c_str());
    html->SetPage(mod->LookupKey(range, search, searchtype));
  }
}

void BookViewCtrl::OpenInCurrentTab(BookModule * bm)
{
  if (bm) {
    OpenInCurrentTab(bm->GetModule());

    SWModule *curMod;

    ModMap::iterator it;

    for (it = bm->GetModules()->begin(); it != bm->GetModules()->end(); it++) {
      curMod = (*it).second;
      GetActiveBookModule()->AddModule(curMod);
    }

    SetPageText(GetSelection(), GetActiveBookModule()->GetName());

    if (bm->GetLastSearch() != wxT(""))
      Search(bm->GetLastLookupKey(), bm->GetLastSearch(), 0);
    else if (bm->IsBrowsing())
      BrowseKey(bm->GetLastLookupKey() + wxT(":"));
    else
      LookupKey(bm->GetLastLookupKey());
  } else {
    OpenInCurrentTab((SWModule *) NULL);
  }

  PostChildSetFocus();
}

void BookViewCtrl::OpenInCurrentTab(const wxString &html)
{
  BookViewHtml *htmlwindow;

  htmlwindow =
    (BookViewHtml *) GetPage(GetSelection())->GetChildren().GetFirst()->
    GetData();
  htmlwindow->SetPage(html);
  SetPageText(GetSelection(), wxString(htmlwindow->GetOpenedPageTitle()));

  PostChildSetFocus();
}

void BookViewCtrl::AddToCurrentTab(SWModule * mod)
{
  GetActiveBookModule()->AddModule(mod);
  SetPageText(GetSelection(), GetActiveBookModule()->GetName());
  LookupKey(GetActiveBookModule()->GetLastLookupKey());

}

void BookViewCtrl::AddToCurrentTab(BookModule * mod)
{
  AddToCurrentTab(mod->GetModule());
  PostChildSetFocus();
}

void BookViewCtrl::OpenInCurrentTab(SWModule * newModule)
{
  BookViewHtml *html;
  BookModule *bookmod,
  *prevbookmod;

  wxString key;
  wxString search;
  bool browse = false;
  bool performsearch = false;

  html =
    (BookViewHtml *) GetPage(GetSelection())->GetChildren().GetFirst()->
    GetData();
  prevbookmod = (BookModule *) html->GetClientData();

  if (newModule) {
    SetPageText(GetSelection(), wxString(newModule->Name(), wxConvUTF8));

    bookmod = new BookModule(newModule);
    html->SetClientData(bookmod);

    if (prevbookmod) {
      key = prevbookmod->GetLastLookupKey();
      search = prevbookmod->GetLastSearch();
      browse = prevbookmod->IsBrowsing();
      performsearch = (prevbookmod->GetKeyType() == bookmod->GetKeyType());
    }

    if (!performsearch && !strcmp(newModule->Type(), "Daily Devotional")) {
      key =
        wxString::Format(wxT("%02i.%02i"), wxDateTime::Today().GetMonth() + 1,
                         wxDateTime::Today().GetDay());
      performsearch = true;
    }

    if (performsearch) {
      if (search != wxT(""))
        Search(key, search, 0);
      else if (browse)
        BrowseKey(key + wxT(":"));
      else
        LookupKey(key);
    } else {
      LookupKey(wxT(""));
    }

    PostChildSetFocus(bookmod);
    wxYield();
  } else {
    PostChildSetFocus();
  }

  SetIcon();

  html->SetFocus();
  html->Refresh();

  if (prevbookmod)
    delete prevbookmod;
}

void BookViewCtrl::SetIcon()
{
  BookModule *bookmod = GetActiveBookModule();

  if (bookmod) {
    SWModule *module = bookmod->GetModule();

    if (!strcmp(module->Type(), "Biblical Texts")) {
      SetPageImage(GetSelection(), ID_BIBLICAL_TEXT_ICON);
    } else if (!strcmp(module->Type(), "Lexicons / Dictionaries")
               || !strcmp(module->Type(), "Glossaries")) {
      SetPageImage(GetSelection(), ID_LEXICON_ICON);
    } else if (!strcmp(module->Type(), "Commentaries")) {
      SetPageImage(GetSelection(), ID_COMMENTARY_ICON);
    } else if (!strcmp(module->Type(), "Daily Devotional")) {
      SetPageImage(GetSelection(), ID_DEVOTIONAL_ICON);
    } else {
      SetPageImage(GetSelection(), ID_BOOK_ICON);
    }
  } else {
    SetPageImage(GetSelection(), -1);
  }
}

void BookViewCtrl::OpenInNewTab(const wxString &html)
{
  SetSelection(AddTab());
  OpenInCurrentTab(html);
}

void BookViewCtrl::OpenInNewTab(SWModule * newModule)
{
  SetSelection(AddTab());
  OpenInCurrentTab(newModule);
}

void BookViewCtrl::OpenInNewTab(BookModule * bm)
{
  SetSelection(AddTab());
  OpenInCurrentTab(bm);
}

BookModule *BookViewCtrl::GetActiveBookModule()
{
  BookViewHtml *html;
  int page = (GetSelection() == -1) ? 0 : GetSelection();

  html = (BookViewHtml *) GetPage(page)->GetChildren().GetFirst()->GetData();
  return (BookModule *) html->GetClientData();
}

void BookViewCtrl::ChildGotFocus()
{
  PostChildSetFocus();
}

void BookViewCtrl::PostChildSetFocus(BookModule * bookmod)
{
  wxCommandEvent eventCustom(bsEVT_CHILD_SET_FOCUS);

  eventCustom.SetEventObject(this);
  if (bookmod)
    eventCustom.SetClientData(bookmod);
  else
    eventCustom.SetClientData(GetActiveBookModule());

  ProcessEvent(eventCustom);
}

void BookViewCtrl::OnNotebookPageChanged(wxNotebookEvent & event)
{
  event.Skip();
  Refresh();
  PostChildSetFocus();
}

void BookViewCtrl::OnSetFocus(wxFocusEvent & event)
{
  event.Skip();
  PostChildSetFocus();
}

void BookViewCtrl::OnLeftUp(wxMouseEvent & event)
{
  event.Skip();
  PostChildSetFocus();
}

void BookViewCtrl::CloseOtherTabs()
{
  int curtab = GetSelection();
  int numbefore;
  int numafter;
  int i;

  numbefore = curtab;
  numafter = GetPageCount() - (curtab + 1);

  for (i = 0; i < numbefore; i++) {
    SetSelection(0);
    CloseTab();
  }

  for (i = 0; i < numafter; i++) {
    SetSelection(1);
    CloseTab();
  }

}

void BookViewCtrl::DuplicateTab()
{
  DuplicateTab(GetActiveBookModule());
}

void BookViewCtrl::DuplicateTab(BookModule * bm)
{
  int selection = GetSelection();

  OpenInNewTab(bm);

  SetSelection(selection);
}


void BookViewCtrl::RefreshStartPages(const wxString html)
{
	for(int i = 0; i < GetPageCount(); i++)
	{
		if(GetPageText(i).IsSameAs(wxT("Start Page")))
		{
			BookViewHtml *htmlBook  = (BookViewHtml *) GetPage(i)->GetChildren().GetFirst()->GetData();
			htmlBook->SetPage(html);
		}
	}
}
