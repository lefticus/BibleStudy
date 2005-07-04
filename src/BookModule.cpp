
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <BookModule.h>
#include <DropDownCtrl.h>

#include <wx/string.h>
#include <wx/progdlg.h>
#include <wx/log.h>
#include <wx/msgdlg.h>

#include <sword/swmodule.h>
#include <sword/versekey.h>

using namespace sword;

BookModule::BookModule(SWModule *newModule)
    : m_Second_Module(NULL),
    m_Description(wxT("")),
    m_Frame(NULL),
    m_LastKey(NULL),
    m_isbrowsing(false)
{
  if (newModule)
  {
    m_Module = newModule;
    m_Modules[newModule->Name()] = newModule;
    m_keytype = GetKeyType(newModule);
  }
  else
  {
    m_Module = NULL;
  }
}

bsKeyType BookModule::GetKeyType(SWModule * mod) const
{
  if (mod->Key().getClass()->isAssignableFrom("StrKey"))
  {
    return bsStringKey;
  }
  else if (mod->Key().getClass()->isAssignableFrom("TreeKeyIdx")
           || mod->Key().getClass()->isAssignableFrom("TreeKey"))
  {
    return bsTreeKey;
  }
  else if (mod->Key().getClass()->isAssignableFrom("VerseKey"))
  {
    return bsVerseKey;
  }
  else
  {
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

ModMap *BookModule::GetModules()
{
  return &m_Modules;
}

bsKeyType BookModule::GetKeyType() const
{
  return m_keytype;
}

wxString BookModule::GetName() const
{
  wxString name;

  ModMap::const_iterator it;
  SWModule *curMod = 0;

  for (it = m_Modules.begin(); it != m_Modules.end();)
  {
    curMod = (*it).second;
    name += wxString(curMod->Name(), wxConvUTF8);

    it++;

    if (it != m_Modules.end())
    {
      name += wxT(" - ");
    }
  }

  return name;
}

wxString BookModule::GetLastLookupKey() const
{
  return m_LastLookupKey;
}

wxString BookModule::GetLastSearch() const
{
  return m_LastSearch;
}

void BookModule::AddModule(SWModule * mod)
{
  if (m_Module)
  {
    if (m_keytype == GetKeyType(mod))
    {
      m_Second_Module = mod;
      m_Modules[mod->Name()] = mod;
    }
  }
  else
  {
    m_Module = mod;
    m_Modules[mod->Name()] = mod;
  }
}

bool BookModule::IsBrowsing() const
{
  return m_isbrowsing;
}

wxString BookModule::BrowseForward()
{
  if (m_isbrowsing)
  {
    m_Module->SetKey((const char *) m_LastLookupKey.mb_str(wxConvUTF8));
    if (m_keytype == bsVerseKey)
    {

      VerseKey vk((const char *) m_LastLookupKey.mb_str(wxConvUTF8));

      vk.Chapter(vk.Chapter() + 1);

      if (vk.Error() != 0)
        return wxT("");

      return LookupKey(wxString(vk.getText(), wxConvUTF8), wxT(""), 0, false,
                       true);
    }
    else
    {
      // wxLogDebug(wxT("Last Key:") + m_LastLookupKey);
      (*m_Module)++;
      // wxLogDebug(wxT("Next Key:") + wxString(m_Module->KeyText(),
      // wxConvUTF8));

      if (m_Module->Error() != 0)
        return wxT("");

      return LookupKey(wxString(m_Module->KeyText(), wxConvUTF8), wxT(""), 0,
                       false, false);
    }
  }
  else
  {
    return wxT("");
  }
}

wxString BookModule::BrowseBackward()
{
  if (m_isbrowsing)
  {
    m_Module->setKey((const char *) m_LastLookupKey.mb_str(wxConvUTF8));
    if (m_keytype == bsVerseKey)
    {
      VerseKey vk((const char *) m_LastLookupKey.mb_str(wxConvUTF8));

      vk.Chapter(vk.Chapter() - 1);

      if (vk.Error() != 0)
        return wxT("");

      return LookupKey(wxString(vk.getText(), wxConvUTF8), wxT(""), 0, false,
                       true);
    }
    else
    {
      // wxLogDebug(wxT("Last Key:") + m_LastLookupKey);
      (*m_Module)--;
      // wxLogDebug(wxT("Next Key:") + wxString(m_Module->KeyText(),
      // wxConvUTF8));

      if (m_Module->Error() != 0)
        return wxT("");

      return LookupKey(wxString(m_Module->KeyText(), wxConvUTF8), wxT(""), 0,
                       false, false);
    }
  }
  else
  {
    return wxT("");
  }
}

void BookModule::Percent(char percent, void *pd)
{
  if (!((wxProgressDialog *) pd)->Update((int) percent))
    ((SWModule *) ((wxProgressDialog *) pd)->GetClientData())->terminateSearch =
      true;
  wxLogDebug(wxT("BookModule::Percent called") +
             wxString::Format(wxT("%i"), percent));
  wxYield();
}

/**
 * @todo handle non-unicode case
 */
wxString BookModule::LookupKey(wxString key, wxString search, int searchtype,
                               bool tooltip, bool browse)
{
  VerseKey vk;
  wxString output;
  char book = 0;
  int chapter = 0,
                verse = 0;
  int versecount = 0;
  bool cont = true;
  bool isfootnote = false;

  wxWindowDisabler disableAll;

  if (!tooltip)
  {

    wxBusyCursor busy;
  }

  int footnoteindex = key.Find(wxT(".n."));

  if (footnoteindex > -1)
  {
    if (key.Mid(footnoteindex + 3).IsNumber())
    {
      isfootnote = true;
      wxLogDebug(wxT("BookModule::LookupKey key isfootnote"));
      key = key.Left(footnoteindex);
    }
  }

  m_isbrowsing = browse;

  if (m_isbrowsing)
    key = key.BeforeLast(wxT(':'));

#if wxUSE_UNICODE
  output =
    wxT("<meta http-equiv='Content-Type' content='text/html; charset=UTF8'>");
#else
  output =
    wxT("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
#endif

  ListKey listkey;
  ListKey searchresult;

  // char keybuf[512];
  // keybuf[wxConvUTF8.WC2MB(keybuf, key.c_str(), key.Length())]=0;

  if (m_keytype == bsVerseKey)
    listkey = vk.ParseVerseList(key.mb_str(wxConvUTF8), "Gen1:1", true);
  else
    listkey.ClearList();

  if (search != wxT(""))
  {
    wxLogDebug(wxT("Range: %s, Key: %s"), key.c_str(), search.c_str());
    wxProgressDialog pd(wxT("Searching..."),
                        wxT("Searching for \"") + search + wxT("\""), 100, NULL,
                        wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_CAN_ABORT |
                        wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME |
                        wxPD_REMAINING_TIME);
    pd.SetClientData(m_Module);
    pd.Show();

    if (listkey.Count() == 0 || m_keytype != bsVerseKey)
    {
      searchresult =
        m_Module->Search(search.mb_str(), searchtype, 0, NULL, 0, &Percent,
                         (void *) &pd);
    }
    else
    {
      searchresult =
        m_Module->Search(search.mb_str(), searchtype, 0, &listkey, 0, &Percent,
                         (void *) &pd);
    }

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
  SWModule *curMod = 0;

  output.append(wxT("<tr>"));
  // These empty columns keep everything else in line
  output.append(wxT("<th width='1'></th>"));
  for (it = m_Modules.begin(); it != m_Modules.end(); it++)
  {
    curMod = (*it).second;
    output.append(wxT("<th><font color='#0000FF'>"));
    output.append(wxString(curMod->Description(), wxConvUTF8));
    output.append(wxT("</font></th>"));
  }
  output.append(wxT("</tr>"));

  if (m_keytype == bsVerseKey)
  {
    m_LastLookupKey = key;
    for (i = 0; i < listkey.Count(); i++)
    {
      VerseKey *element = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(i));

      if (!cont)
        break;
      if (element)
      {
        wxLogDebug(wxT("BookModule::LookupKey valid element"));
        vk = element->UpperBound();

        while ((*element) <= vk && cont)
        {
          wxYield();
          versecount++;
          if (versecount == 300)
          {
            wxMessageDialog *msg;

            if (m_Frame)
              msg =
                new wxMessageDialog(m_Frame->GetParent(),
                                    wxT
                                    ("More than 300 verses found, continue?"),
                                    wxT("Too many verses found."),
                                    wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT |
                                    wxCENTRE, wxDefaultPosition);
            else
              msg =
                new wxMessageDialog(NULL,
                                    wxT
                                    ("More than 300 verses found, continue?"),
                                    wxT("Too many verses found."),
                                    wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT |
                                    wxCENTRE, wxDefaultPosition);

            if (msg->ShowModal() != wxID_YES)
              cont = false;

            msg->Destroy();
          }
          wxLogDebug(wxT("BookModule::LookupKey m_Module->Key()<= vk"));
          output.append(wxT("<tr align=left valign=top>"));

          // These empty columns keep everything else in line :)
          output.append(wxT("<td width='1'></td>"));

          for (it = m_Modules.begin(); it != m_Modules.end(); it++)
          {
            wxLogDebug(wxT("BookModule::LookupKey iterating through modules"));
            curMod = (*it).second;
            wxLogDebug(wxT("BookModule::LookupKey Setting Key"));

            curMod->Key((*element));

            wxLogDebug(wxT("BookModule::LookupKey writing verse to output"));

            wxString verseout = wxT("");
            bool outputcell = true;
            int rowspan = 1;
            wxString thisverse = wxString((const char *) (*curMod), wxConvUTF8);

            if ((*element) > element->LowerBound())
            {

              (*element)--;
              curMod->Key((*element));
              wxString prevverse = wxString((const char *) (*curMod),
                                            wxConvUTF8);

              (*element)++;

              wxLogDebug(wxT("BookModule:LookupKey: Previous:"));
              wxLogDebug(prevverse);

              wxLogDebug(wxT("BookModule:LookupKey: Current:"));
              wxLogDebug(thisverse);

              if (thisverse.Cmp(prevverse))
              {
                verseout = thisverse;
                outputcell = true;
              }
              else
              {
                outputcell = false;
              }
            }
            else
            {
              outputcell = true;
              verseout = thisverse;
            }

            VerseKey elemcopy(element);

            elemcopy++;
            curMod->Key(elemcopy);
            wxString nextverse = wxString((const char *) (*curMod), wxConvUTF8);

            while (elemcopy <= vk && !nextverse.Cmp(verseout)
                   && outputcell)
            {
              rowspan++;
              elemcopy++;
              curMod->Key(elemcopy);
              nextverse = wxString((const char *) (*curMod), wxConvUTF8);

            }

            if (outputcell)
            {
              output.
              append(wxString::
                     Format(wxT("<td align=left valign=top rowspan=%i>"),
                            rowspan));

              output.append(wxT("<small><font color='#0000FF'>"));
              if (element->Book() != book)
              {
                wxLogDebug(wxT("BookModule::LookupKey new book"));
                output.append(wxString(element->getText(), wxConvUTF8));
              }
              else if (element->Chapter() != chapter)
              {
                wxLogDebug(wxT("BookModule::LookupKey new chapter"));

                output.append(wxString::Format(wxT("%i"), element->Chapter()));
                output.append(wxT(":"));
              }

              if (element->Book() == book)
              {
                output.append(wxString::Format(wxT("%i"), element->Verse()));
              }

              wxLogDebug(wxT
                         ("BookModule::LookupKey updating last chaper, book, verse"));
              output.append(wxT("</font></small> "));
              if (!isfootnote)
              {
                output.append(verseout);
              }
              else
              {
                SWBuf body;
                wxString wxBody;

                curMod->RenderText();
                body = curMod->getEntryAttributes()["Footnote"]["1"]
                       ["body"].c_str();
                curMod->RenderText(body);
                wxBody = wxString((const char *) body.c_str(), wxConvUTF8);
                output.append(wxBody);
              }

              output.append(wxT("</td>"));
            }
          }

          book = element->Book();
          chapter = element->Chapter();
          verse = element->Verse();

          output.append(wxT("</tr>"));
          if ((*element) == vk)
            break;

          wxLogDebug(wxT("BookModule::LookupKey incrementing m_Module"));
          (*element)++;
        }
      }
      else
      {
        output.append(wxT("<tr align=left valign=top>"));
        output.append(wxT("<td width='1'></td>"));
        wxYield();
        versecount++;
        if (versecount == 300)
        {
          wxMessageDialog *msg;

          if (m_Frame)
            msg =
              new wxMessageDialog(m_Frame->GetParent(),
                                  wxT("More than 300 verses found, continue?"),
                                  wxT("Too many verses found."),
                                  wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT |
                                  wxCENTRE, wxDefaultPosition);
          else
            msg =
              new wxMessageDialog(NULL,
                                  wxT("More than 300 verses found, continue?"),
                                  wxT("Too many verses found."),
                                  wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT |
                                  wxCENTRE, wxDefaultPosition);

          if (msg->ShowModal() != wxID_YES)
            cont = false;

          msg->Destroy();
        }

        ModMap::iterator it;
        SWModule *curMod = 0;

        for (it = m_Modules.begin(); it != m_Modules.end(); it++)
        {
          curMod = it->second;
          curMod->Key(*listkey.GetElement(i));

          output.append(wxT("<td align=left valign=top>"));

          output.append(wxT("<small><font color='#0000FF'>"));
          m_Module->Key(*listkey.GetElement(i));
          output.append(wxString(m_Module->KeyText(), wxConvUTF8));
          output.append(wxT("</font></small> "));

          if (!isfootnote)
          {
            output.append(wxString((const char *) (*curMod), wxConvUTF8));
          }
          else
          {
            SWBuf body;
            wxString wxBody;

            // curMod->SetKey("jn3:3");
            curMod->RenderText();
            body =
              curMod->getEntryAttributes()["Footnote"]["1"]["body"].c_str();
            curMod->RenderText(body);
            wxBody = wxString((const char *) body.c_str(), wxConvUTF8);
            // wxLogDebug(wxT("BookModule::LookupKey adding
            // footnote ") + wxBody);
            output.append(wxBody);
          }

          output.append(wxT("</td>"));
        }

        output.append(wxT("</tr>"));
      }

    }

  }
  else
  {
    m_isbrowsing = true;

    if (listkey.Count() == 0)
    {
      listkey << (const char *) key.mb_str(wxConvUTF8);
    }
    // printf("%s", keybuf);

    SWKey *element;

    for (int i = 0; i < listkey.Count(); i++)
    {
      element = listkey.GetElement(i);

      output.append(wxT("<tr align=left valign=top>"));
      output.append(wxT("<td width='1'></td>"));
      const char *moduleoutput;

      for (it = m_Modules.begin(); it != m_Modules.end(); it++)
      {
        output.append(wxT("<td align=left valign=top>"));

        wxLogDebug(wxT("BookModule::LookupKey iterating through modules"));
        curMod = (*it).second;

        curMod->SetKey(element);
        moduleoutput = (const char *) (*curMod);
        output.append(wxT("<font color='#0000FF'>"));
        output.append(wxString(curMod->KeyText(), wxConvUTF8));
        output.append(wxT("</font><hr />"));
        output.append(wxString(moduleoutput, wxConvUTF8));

        output.append(wxT("</td>"));
      }

      output.append(wxT("</tr>"));
    }

    if (listkey.Count() == 1)
      m_LastLookupKey = wxString(m_Module->KeyText(), wxConvUTF8);
  }

  output.append(wxT("</table>"));

  if (tooltip)
    output.append(wxT("</font></body></html>"));
  else
    output.append(wxT("</html>"));

  m_LastSearch = search;

  // if (search != wxT("")) {
  // wxRegEx myregex(search, wxRE_ICASE);
  // myregex.ReplaceAll(&output, wxT("<font
  // color=#999900'>\\0</font>"));
  // }

  return output;
}

wxFrame *BookModule::GetControl(wxWindow * parent)
{
  if (m_Frame)
    return m_Frame;

  if (!strcmp(m_Module->Type(), "Generic Books")
      || !strcmp(m_Module->Type(), "Essays"))
  {
    TreeKey *key;

    m_Frame = new DropDownCtrl(parent, m_Module, bsTree);

    wxTreeCtrl *tree = ((DropDownCtrl *) m_Frame)->GetTree();

    key = (TreeKey *) m_Module->CreateKey();
    key->firstChild();

    AddTreeSiblings(tree, tree->AddRoot(wxT("Root")), key);
  }
  else if (!strcmp(m_Module->Type(), "Daily Devotional"))
  {
    m_Frame = new DropDownCtrl(parent, m_Module, bsCalendar);
  }
  else if (!strcmp(m_Module->Type(), "Biblical Texts")
           || !strcmp(m_Module->Type(), "Commentaries"))
  {
    m_Frame = new DropDownCtrl(parent, m_Module, bsBible);
  }

  wxLogDebug(wxT("BookModule::GetControl exiting"));
  return m_Frame;
}

void BookModule::AddTreeSiblings(wxTreeCtrl * tree, wxTreeItemId parentid,
                                 TreeKey * key)
{
  wxTreeItemId itemadded;

  wxString fullname = wxString(key->getFullName(), wxConvUTF8);

  // wxLogDebug(wxT("BookModule::AddTreeSiblings called: %s"), (const
  // wxChar*)wxString(key->getFullName(), wxConvUTF8));
  // wxLogDebug(wxT("BookModule::AddTreeSiblings called: %s"),
  // fullname.mb_str());

  bool cont = true;

  while (cont)
  {

    wxLogDebug(wxT
               ("BookModule::AddTreeSiblings starting next iteration of while loop"));
    wxLogDebug(wxT("BookModule::AddTreeSiblings adding: %i"), key->Index());
    wxString name;

    // wxMessageBox(wxString(key->getLocalName(), wxConvUTF8),
    // wxT("test"), wxOK| wxICON_INFORMATION, tree->GetParent());
    itemadded =
      tree->AppendItem(parentid, wxString(key->getLocalName(), wxConvUTF8));

    if (key->hasChildren())
    {
      wxLogDebug(wxT("BookModule::AddTreeSiblings item has children"));

      key->firstChild();
      wxLogDebug(wxT("BookModule::AddTreeSiblings adding children"));
      AddTreeSiblings(tree, itemadded, key);
      key->parent();
    }
    else
    {
      wxLogDebug(wxT("BookModule::AddTreeSiblings no children"));
    }

    wxLogDebug(wxT("BookModule::AddTreeSiblings moving to next sibling"));
    cont = key->nextSibling();
    if (key->Error() != 0)
    {
      wxLogDebug(wxT("BookModule::AddTreeSiblings error occured"));
      cont = false;
    }
    tree->Expand(itemadded);
  }

  wxLogDebug(wxT("BookModule::AddTreeSiblings exiting"));
}

wxString BookModule::ModInfo() const
{
  ConfigEntMap confmap;

  ConfigEntMap::iterator cit;
  wxString desc;

  if (m_Description == wxT(""))
  {
    desc =
      wxString(m_Module->Description(),
               wxConvUTF8) + wxT(":") + wxString(m_Module->Type(),
                                                 wxConvUTF8) + wxT("\n\n");
    confmap = m_Module->getConfig();
    for (cit = confmap.begin(); cit != confmap.end(); cit++)
    {
      if (!strcmp(cit->first.c_str(), "About")
          || !strcmp(cit->first.c_str(), "DistributionLicense"))
      {
        desc +=
          wxString(cit->first.c_str(),
                   wxConvUTF8) + wxT(": ") + wxString(cit->second.c_str(),
                                                      wxConvUTF8) + wxT("\n\n");
      }
    }

    desc.Replace(wxT("\\par"), wxT("\n"), TRUE);

    m_Description = desc;
  }

  return m_Description;
}
