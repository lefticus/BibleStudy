
/***************************************************************************
 *   Copyright (C) 2003 by Jason Turner                                    *
 *   jason@whensdinner.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "BibleStudyLanguages.h"
#include <wx/log.h>
#include <wx/intl.h>
#include <iostream>
/**
 * default constructor
 *
 * Adds all of the known languages
 */
BibleStudyLanguages::BibleStudyLanguages()
{
  /** let's add them languages! */
  AddLanguage(_T("aa"), _("Afar"));
  AddLanguage(_T("ab"), _("Abkhazian"));
  AddLanguage(_T("ae"), _("Avestan"));
  AddLanguage(_T("af"), _("Afrikaans"));
  AddLanguage(_T("am"), _("Amharic"));
  AddLanguage(_T("ang"), _("English, Old (ca.450-1100)"));
  AddLanguage(_T("ar"), _("Arabic"));
  AddLanguage(_T("as"), _("Assamese"));
  AddLanguage(_T("ay"), _("Aymara"));
  AddLanguage(_T("az"), _("Azerbaijani"));

  AddLanguage(_T("ba"), _("Bashkir"));
  AddLanguage(_T("be"), _("Belarusian"));
  AddLanguage(_T("bg"), _("Bulgarian"));
  AddLanguage(_T("bh"), _("Bihari"));
  AddLanguage(_T("bi"), _("Bislama"));
  AddLanguage(_T("bn"), _("Bengali"));
  AddLanguage(_T("bo"), _("Tibetan"));
  AddLanguage(_T("br"), _("Breton"));
  AddLanguage(_T("bs"), _("Bosnian"));

  AddLanguage(_T("ca"), _("Catalan"));
  AddLanguage(_T("ce"), _("Chechen"));
  AddLanguage(_T("ceb"), _("Cebuano"));
  AddLanguage(_T("ch"), _("Chamorro"));
  AddLanguage(_T("co"), _("Corsican"));
  AddLanguage(_T("cop"), _("Coptic"));
  AddLanguage(_T("cs"), _("Czech"));
  AddLanguage(_T("cu"), _("Church Slavic"));
  AddLanguage(_T("cv"), _("Chuvash"));
  AddLanguage(_T("cy"), _("Welsh"));

  AddLanguage(_T("da"), _("Danish"));
  AddLanguage(_T("de"), _("German"));
  AddLanguage(_T("dz"), _("Dzongkha"));

  AddLanguage(_T("el"), _("Greek, Modern (1453-)"));
  AddLanguage(_T("en"), _("English"));
  AddLanguage(_T("en_US"), _("American English"));
  AddLanguage(_T("enm"), _("English, Middle (1100-1500)"));
  AddLanguage(_T("eo"), _("Esperanto"));
  AddLanguage(_T("es"), _("Spanish"));
  AddLanguage(_T("et"), _("Estonian"));
  AddLanguage(_T("eu"), _("Basque"));

  AddLanguage(_T("fa"), _("Persian"));
  AddLanguage(_T("fi"), _("Finnish"));
  AddLanguage(_T("fj"), _("Fijian"));
  AddLanguage(_T("fo"), _("Faroese"));
  AddLanguage(_T("fr"), _("French"));
  AddLanguage(_T("fy"), _("Frisian"));

  AddLanguage(_T("ga"), _("Irish"));
  AddLanguage(_T("gd"), _("Gaelic (Scots)"));
  AddLanguage(_T("gl"), _("Gallegan"));
  AddLanguage(_T("gn"), _("Guarani"));
  AddLanguage(_T("gn"), _("Gujarati"));
  AddLanguage(_T("got"), _("Gothic"));
  AddLanguage(_T("gv"), _("Manx"));
  AddLanguage(_T("grc"), _("Greek, Ancient (to 1453)"));

  AddLanguage(_T("he"), _("Hebrew"));
  AddLanguage(_T("haw"), _("Hawaiian"));
  AddLanguage(_T("hi"), _("Hindi"));
  AddLanguage(_T("ho"), _("Hiri Motu"));
  AddLanguage(_T("hr"), _("Croatian"));
  AddLanguage(_T("hu"), _("Hungarian"));
  AddLanguage(_T("hy"), _("Armenian"));
  AddLanguage(_T("hz"), _("Herero"));

  AddLanguage(_T("ia"), _("Interlingua"));
  AddLanguage(_T("id"), _("Indonesian"));
  AddLanguage(_T("ie"), _("Interlingue"));
  AddLanguage(_T("ik"), _("Inupiaq"));
  AddLanguage(_T("is"), _("Icelandic"));
  AddLanguage(_T("it"), _("Italian"));
  AddLanguage(_T("iu"), _("Inuktitut"));

  AddLanguage(_T("i-klingon"), _("Klingon"));

  AddLanguage(_T("ja"), _("Japanese"));

  AddLanguage(_T("ka"), _("Georgian"));
  AddLanguage(_T("ki"), _("Kikuyu"));
  AddLanguage(_T("kj"), _("Kuanyama"));
  AddLanguage(_T("kk"), _("Kazakh"));
  AddLanguage(_T("kl"), _("Kalaallisut"));
  AddLanguage(_T("km"), _("Khmer"));
  AddLanguage(_T("kn"), _("Kannada"));
  AddLanguage(_T("ko"), _("Korean"));
  AddLanguage(_T("ks"), _("Kashmiri"));
  AddLanguage(_T("ku"), _("Kurdish"));
  AddLanguage(_T("kv"), _("Komi"));
  AddLanguage(_T("kw"), _("Cornish"));
  AddLanguage(_T("ky"), _("Kirghiz"));

  AddLanguage(_T("la"), _("Latin"));
  AddLanguage(_T("lb"), _("Letzeburgesch"));
  AddLanguage(_T("ln"), _("Lingala"));
  AddLanguage(_T("lo"), _("Lao"));
  AddLanguage(_T("lt"), _("Lithuanian"));
  AddLanguage(_T("lv"), _("Latvian"));

  AddLanguage(_T("mg"), _("Malagasy"));
  AddLanguage(_T("mh"), _("Marshall"));
  AddLanguage(_T("mi"), _("Maori"));

  AddLanguage(_T("mk"), _("Macedonian"));
  AddLanguage(_T("ml"), _("Malayalam"));
  AddLanguage(_T("mn"), _("Mongolian"));
  AddLanguage(_T("mo"), _("Moldavian"));
  AddLanguage(_T("mr"), _("Marathi"));
  AddLanguage(_T("ms"), _("Malay"));
  AddLanguage(_T("mt"), _("Maltese"));
  AddLanguage(_T("my"), _("Burmese"));

  AddLanguage(_T("na"), _("Nauru"));
  AddLanguage(_T("nb"), _("Norwegian Bokmal"));
  AddLanguage(_T("nd"), _("Ndebele, North"));
  AddLanguage(_T("nds"), _("Low German; Low Saxon"));
  AddLanguage(_T("ne"), _("Nepali"));
  AddLanguage(_T("ng"), _("Ndonga"));
  AddLanguage(_T("nl"), _("Dutch"));
  AddLanguage(_T("nn"), _("Norwegian Nynorsk"));
  AddLanguage(_T("no"), _("Norwegian"));
  AddLanguage(_T("nr"), _("Ndebele, South"));
  AddLanguage(_T("nv"), _("Navajo"));
  AddLanguage(_T("ny"), _("Chichewa; Nyanja"));

  AddLanguage(_T("oc"), _("Occitan (post 1500); Provencal"));
  AddLanguage(_T("om"), _("Oromo"));
  AddLanguage(_T("or"), _("Oriya"));
  AddLanguage(_T("os"), _("Ossetian; Ossetic"));
  
  AddLanguage(_T("pa"), _("Panjabi"));
  AddLanguage(_T("pap"), _("Papiamento"));
  AddLanguage(_T("pi"), _("Pali"));
  AddLanguage(_T("pl"), _("Polish"));
  AddLanguage(_T("po"), _("Polish"));
  AddLanguage(_T("ps"), _("Pushto"));
  AddLanguage(_T("pt"), _("Portuguese"));

  AddLanguage(_T("qu"), _("Quechua"));

  AddLanguage(_T("rm"), _("Raeto-Romance"));
  AddLanguage(_T("rn"), _("Rundi"));

  AddLanguage(_T("ro"), _("Romanian"));
  AddLanguage(_T("ru"), _("Russian"));
  AddLanguage(_T("rw"), _("Kinyarwanda"));

  AddLanguage(_T("sa"), _("Sanskrit"));
  AddLanguage(_T("sc"), _("Sardinian"));
  AddLanguage(_T("sco"), _("Scots"));
  AddLanguage(_T("sd"), _("Sindhi"));
  AddLanguage(_T("se"), _("Northern Sami"));
  AddLanguage(_T("sg"), _("Sango"));
  AddLanguage(_T("si"), _("Sinhalese"));
  AddLanguage(_T("sk"), _("Slovak"));
  AddLanguage(_T("sl"), _("Slovenian"));
  AddLanguage(_T("sm"), _("Samoan"));
  AddLanguage(_T("sn"), _("Shona"));
  AddLanguage(_T("so"), _("Somali"));
  AddLanguage(_T("sq"), _("Albanian"));
  AddLanguage(_T("sr"), _("Serbian"));
  AddLanguage(_T("ss"), _("Swati"));
  AddLanguage(_T("st"), _("Sotho, Southern"));
  AddLanguage(_T("su"), _("Sundanese"));
  AddLanguage(_T("sv"), _("Swedish"));
  AddLanguage(_T("sw"), _("Swahili"));
  AddLanguage(_T("syr"), _("Syriac"));

  AddLanguage(_T("ta"), _("Tamil"));
  AddLanguage(_T("te"), _("Telugu"));
  AddLanguage(_T("tg"), _("Tajik"));
  AddLanguage(_T("th"), _("Thai"));
  AddLanguage(_T("tk"), _("Turkmen"));
  AddLanguage(_T("tl"), _("Tagalog"));
  AddLanguage(_T("tn"), _("Tswana"));
  AddLanguage(_T("tr"), _("Turkish"));
  AddLanguage(_T("ts"), _("Tsonga"));
  AddLanguage(_T("tt"), _("Tatar"));
  AddLanguage(_T("tw"), _("Twi"));
  AddLanguage(_T("ty"), _("Tahitian"));

  AddLanguage(_T("ug"), _("Uighur"));
  AddLanguage(_T("uk"), _("Ukrainian"));
  AddLanguage(_T("ur"), _("Urdu"));
  AddLanguage(_T("uz"), _("Uzbek"));

  AddLanguage(_T("vi"), _("Vietnamese"));
  AddLanguage(_T("vo"), _("Volapruek"));

  AddLanguage(_T("wo"), _("Wolof"));

  AddLanguage(_T("xh"), _("Xhosa"));

  AddLanguage(_T("x-E-BAR"), _("Bavarian"));
  AddLanguage(_T("x-E-GSW"), _("Alemannisch"));
  AddLanguage(_T("x-E-HAT"), _("Haitian Creole French"));
  AddLanguage(_T("x-E-ITZ"), _("Itza"));
  AddLanguage(_T("x-E-JIV"), _("Shuar"));
  AddLanguage(_T("x-E-KEK"), _("Kekchi"));
  AddLanguage(_T("x-E-LMO"), _("Lombard"));
  AddLanguage(_T("x-E-MKJ"), _("Macedonian"));
  AddLanguage(_T("x-E-PDG"), _("Tok Pisin"));
  AddLanguage(_T("x-E-PPK"), _("Uma"));
  AddLanguage(_T("x-E-RMY"), _("Romani, Vlax"));
  AddLanguage(_T("x-E-SAJ"), _("Sango"));
  AddLanguage(_T("x-E-SRN"), _("Sranan"));

  AddLanguage(_T("yi"), _("Yiddish"));
  AddLanguage(_T("yo"), _("Yoruba"));
  
  AddLanguage(_T("za"), _("Zhuang"));
  AddLanguage(_T("zh"), _("Chinese"));
  AddLanguage(_T("zu"), _("Zulu"));
}

BibleStudyLanguages::~BibleStudyLanguages()
{}

void BibleStudyLanguages::AddLanguage(const wxString &abbreviation,
                                      const wxString &description)
{
  mLanguages[abbreviation] = description;
}

void BibleStudyLanguages::AddLanguage(const char *abbreviation,
                                      const char *description)
{
  /*
   * convert char arrays to wxStrings and call other function 
   */
  mLanguages[wxString(abbreviation, wxConvUTF8)] =
    wxString(description, wxConvUTF8);
}

wxString BibleStudyLanguages::GetLanguage(const wxString &abbreviation)
{
  if (mLanguages[abbreviation] == wxT("")) {
    wxLogDebug(wxT("Unknown abreviation: ") + abbreviation);
    std::cout << abbreviation.mb_str() << std::endl;
  }
  return mLanguages[abbreviation];
}
