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


BibleStudyLanguages::BibleStudyLanguages()
{
	/** let's add them languages! */
	
	AddLanguage("aa"  , "Afar"        );
	AddLanguage("ab"  , "Abkhazian"   );
	AddLanguage("ae"  , "Avestan"     );
	AddLanguage("af"  , "Afrikaans"   );
	AddLanguage("am"  , "Amharic"     );
	AddLanguage("ang", "English, Old (ca.450-1100)");
	AddLanguage("ar"  , "Arabic"      );
	AddLanguage("as"  , "Assamese"    );
	AddLanguage("ay"  , "Aymara"      );
	AddLanguage("az"  , "Azerbaijani" );

	AddLanguage("ba"  , "Bashkir"     );
	AddLanguage("be"  , "Belarusian"  );
	AddLanguage("bg"  , "Bulgarian"   );
	AddLanguage("bh"  , "Bihari"      );
	AddLanguage("bi"  , "Bislama"     );
	AddLanguage("bn"  , "Bengali"     );
	AddLanguage("bo"  , "Tibetan"     );
	AddLanguage("br"  , "Breton"      );
	AddLanguage("bs"  , "Bosnian"     );

	AddLanguage("ca"  , "Catalan"     );
	AddLanguage("ce"  , "Chechen"     );
	AddLanguage("ceb"  , "Cebuano"     );
	AddLanguage("ch"  , "Chamorro"    );
	AddLanguage("co"  , "Corsican"    );
	AddLanguage("cop" , "Coptic"         );
	AddLanguage("cs"  , "Czech"       );
	AddLanguage("cu"  , "Church Slavic" );
	AddLanguage("cv"  , "Chuvash"     );
	AddLanguage("cy"  , "Welsh"       );

	AddLanguage("da"  , "Danish"      );
	AddLanguage("de"  , "German"      );
	AddLanguage("dz"  , "Dzongkha"    );

	AddLanguage("el"  , "Greek, Modern (1453-)" );
	AddLanguage("en"  , "English"     );
	AddLanguage("en_US",  "American English"     );
	AddLanguage("enm" , "English, Middle (1100-1500)");
	AddLanguage("eo"  , "Esperanto"   );
	AddLanguage("es"  , "Spanish"     );
	AddLanguage("et"  , "Estonian"    );
	AddLanguage("eu"  , "Basque"      );

	AddLanguage("fa"  , "Persian"     );
	AddLanguage("fi"  , "Finnish"     );
	AddLanguage("fj"  , "Fijian"      );
	AddLanguage("fo"  , "Faroese"     );
	AddLanguage("fr"  , "French"      );
	AddLanguage("fy"  , "Frisian"     );

	AddLanguage("ga"  , "Irish"       );
	AddLanguage("gd"  , "Gaelic (Scots)"     );
	AddLanguage("gl"  , "Gallegan"    );
	AddLanguage("gn"  , "Guarani"     );
	AddLanguage("gn"  , "Gujarati"    );
	AddLanguage("got"  , "Gothic"    );
	AddLanguage("gv"  , "Manx"        );
	AddLanguage("grc"  , "Greek, Ancient (to 1453)" );

	AddLanguage("he"  , "Hebrew"      );
	AddLanguage("haw"    , "Hawaiian"    );
	AddLanguage("hi"  , "Hindi"       );
	AddLanguage("ho"  , "Hiri Motu"   );
	AddLanguage("hr"  , "Croatian"    );
	AddLanguage("hu"  , "Hungarian"   );
	AddLanguage("hy"  , "Armenian"    );
	AddLanguage("hz"  , "Herero"      );

	AddLanguage("ia"  , "Interlingua" );
	AddLanguage("id"  , "Indonesian"  );
	AddLanguage("ie"  , "Interlingue" );
	AddLanguage("ik"  , "Inupiaq"     );
	AddLanguage("is"  , "Icelandic"   );
	AddLanguage("it"  , "Italian"     );
	AddLanguage("iu"  , "Inuktitut"   );

	AddLanguage("ja"  , "Japanese"    );

	AddLanguage("ka"  , "Georgian"    );
	AddLanguage("ki"  , "Kikuyu"      );
	AddLanguage("kj"  , "Kuanyama"    );
	AddLanguage("kk"  , "Kazakh"      );
	AddLanguage("kl"  , "Kalaallisut" );
	AddLanguage("km"  , "Khmer"       );
	AddLanguage("kn"  , "Kannada"     );
	AddLanguage("ko"  , "Korean"      );
	AddLanguage("ks"  , "Kashmiri"    );
	AddLanguage("ku"  , "Kurdish"     );
	AddLanguage("kv"  , "Komi"        );
	AddLanguage("kw"  , "Cornish"     );
	AddLanguage("ky"  , "Kirghiz"     );

	AddLanguage("la"  , "Latin"       );
	AddLanguage("lb"  , "Letzeburgesch" );
	AddLanguage("ln"  , "Lingala"     );
	AddLanguage("lo"  , "Lao"         );
	AddLanguage("lt"  , "Lithuanian"  );
	AddLanguage("lv"  , "Latvian"     );

	AddLanguage("mg"  , "Malagasy"    );
	AddLanguage("mh"  , "Marshall"    );
	AddLanguage("mi"  , "Maori"       );

	AddLanguage("mk"  , "Macedonian"  );
	AddLanguage("ml"  , "Malayalam"   );
	AddLanguage("mn"  , "Mongolian"   );
	AddLanguage("mo"  , "Moldavian"   );
	AddLanguage("mr"  , "Marathi"     );
	AddLanguage("ms"  , "Malay"       );
	AddLanguage("mt"  , "Maltese"     );
	AddLanguage("my"  , "Burmese"     );

	AddLanguage("na"  , "Nauru"       );
	AddLanguage("nb"  , "Norwegian Bokmål"       );
	AddLanguage("nd"  , "Ndebele, North" );
	AddLanguage("nds"  , "Low German; Low Saxon" );
	AddLanguage("ne"  , "Nepali"      );
	AddLanguage("ng"  , "Ndonga"      );
	AddLanguage("nl"  , "Dutch"       );
	AddLanguage("nn"  , "Norwegian Nynorsk"     );
	AddLanguage("no"  , "Norwegian"   );
	AddLanguage("nr"  , "Ndebele, South"     );
	AddLanguage("nv"  , "Navajo"      );
	AddLanguage("ny"  , "Chichewa; Nyanja"      );

	AddLanguage("oc"  , "Occitan (post 1500); Provençal"     );
	AddLanguage("om"  , "Oromo"       );
	AddLanguage("or"  , "Oriya"       );
	AddLanguage("os"  , "Ossetian; Ossetic"     );

	AddLanguage("pa"  , "Panjabi"     );
	AddLanguage("pap"  , "Papiamento"     );
	AddLanguage("pi"  , "Pali"        );
	AddLanguage("pl"  , "Polish"      );
	AddLanguage("ps"  , "Pushto"      );
	AddLanguage("pt"  , "Portuguese"  );

	AddLanguage("qu"  , "Quechua"     );

	AddLanguage("rm"  , "Raeto-Romance"    );
	AddLanguage("rn"  , "Rundi"       );

	AddLanguage("ro"  , "Romanian"    );
	AddLanguage("ru"  , "Russian"     );
	AddLanguage("rw"  , "Kinyarwanda" );

	AddLanguage("sa"  , "Sanskrit"    );
	AddLanguage("sc"  , "Sardinian"   );
	AddLanguage("sco"  , "Scots"   );
	AddLanguage("sd"  , "Sindhi"      );
	AddLanguage("se"  , "Northern Sami" );
	AddLanguage("sg"  , "Sango"       );
	AddLanguage("si"  , "Sinhalese"   );
	AddLanguage("sk"  , "Slovak"      );
	AddLanguage("sl"  , "Slovenian"   );
	AddLanguage("sm"  , "Samoan"      );
	AddLanguage("sn"  , "Shona"       );
	AddLanguage("so"  , "Somali"      );
	AddLanguage("sq"  , "Albanian"    );
	AddLanguage("sr"  , "Serbian"     );
	AddLanguage("ss"  , "Swati"       );
	AddLanguage("st"  , "Sotho, Southern"     );
	AddLanguage("su"  , "Sundanese"   );
	AddLanguage("sv"  , "Swedish"     );
	AddLanguage("sw"  , "Swahili"     );
	AddLanguage("syr"  , "Syriac"     );

	AddLanguage("ta"  , "Tamil"       );
	AddLanguage("te"  , "Telugu"      );
	AddLanguage("tg"  , "Tajik"       );
	AddLanguage("th"  , "Thai"        );
	AddLanguage("tk"  , "Turkmen"     );
	AddLanguage("tl"  , "Tagalog"     );
	AddLanguage("tn"  , "Tswana"      );
	AddLanguage("tr"  , "Turkish"     );
	AddLanguage("ts"  , "Tsonga"      );
	AddLanguage("tt"  , "Tatar"       );
	AddLanguage("tw"  , "Twi"         );
	AddLanguage("ty"  , "Tahitian"    );

	AddLanguage("ug"  , "Uighur"      );
	AddLanguage("uk"  , "Ukrainian"   );
	AddLanguage("ur"  , "Urdu"        );
	AddLanguage("uz"  , "Uzbek"       );

	AddLanguage("vi"  , "Vietnamese"  );
	AddLanguage("vo"  , "Volapük"     );

	AddLanguage("wo"  , "Wolof"       );

	AddLanguage("xh"  , "Xhosa"       );

	AddLanguage("x-E-BAR"  , "Bavarian"     );
	AddLanguage("x-E-GSW"  , "Alemannisch"  );
	AddLanguage("x-E-HAT"  , "Haitian Creole French" );
	AddLanguage("x-E-ITZ"  , "Itzá"         );  
	AddLanguage("x-E-JIV"  , "Shuar"        );
	AddLanguage("x-E-KEK"  , "Kekchí"       );
	AddLanguage("x-E-LMO"  , "Lombard"      );  
	AddLanguage("x-E-MKJ"  , "Macedonian"   );
	AddLanguage("x-E-PDG"  , "Tok Pisin"    );
	AddLanguage("x-E-PPK"  , "Uma"          );
	AddLanguage("x-E-RMY"  , "Romani, Vlax" );
	AddLanguage("x-E-SAJ"  , "Sango"        );
	AddLanguage("x-E-SRN"  , "Sranan"       );  

	AddLanguage("yi"  , "Yiddish"     );

	AddLanguage("za"  , "Zhuang"      );
	AddLanguage("zh"  , "Chinese"     );
	AddLanguage("zu"  , "Zulu"        );

}


BibleStudyLanguages::~BibleStudyLanguages()
{
}

void BibleStudyLanguages::AddLanguage(wxString abbreviation, wxString description)
{
	mLanguages[abbreviation] = description;
}

void BibleStudyLanguages::AddLanguage(const char *abbreviation, const char *description)
{
	mLanguages[wxString(abbreviation, wxConvUTF8)] = wxString(description, wxConvUTF8);
}

wxString BibleStudyLanguages::GetLanguage(wxString abbreviation)
{
	return mLanguages[abbreviation];
}

