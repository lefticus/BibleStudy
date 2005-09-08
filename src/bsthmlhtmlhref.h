/******************************************************************************
 *
 * $Id$
 *
 * Copyright 1998 CrossWire Bible Society (http://www.crosswire.org)
 *	CrossWire Bible Society
 *	P. O. Box 2528
 *	Tempe, AZ  85280-2528
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */

#ifndef _BSTHMLHTMLHREF_H
#define _BSTHMLHTMLHREF_H

#include <swbasicfilter.h>
#include <utilxml.h>


/** this filter converts ThML text to HTML text with hrefs
 */
class BSThMLHTMLHREF : public sword::SWBasicFilter {
protected:
	class MyUserData : public sword::BasicFilterUserData {
	public:
		MyUserData(const sword::SWModule *module, const sword::SWKey *key);//: BasicFilterUserData(module, key) {}
		sword::SWBuf inscriptRef;
		bool SecHead;
		bool BiblicalText;
		sword::SWBuf version;
		sword::XMLTag startTag;
	};
	virtual sword::BasicFilterUserData *createUserData(const sword::SWModule *module, const sword::SWKey *key) {
		return new MyUserData(module, key);
	}
	virtual bool handleToken(sword::SWBuf &buf, const char *token, sword::BasicFilterUserData *userData);
public:
	BSThMLHTMLHREF();
};
#endif /* _BSTHMLHTMLHREF_H */
