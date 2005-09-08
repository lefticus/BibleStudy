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

#ifndef BSGBFHTMLHREF_H
#define BSGBFHTMLHREF_H

#include <swbasicfilter.h>


/** this filter converts GBF  text to HTML text with hrefs
 */
class BSGBFHTMLHREF : public sword::SWBasicFilter {
protected:
	class MyUserData : public sword::BasicFilterUserData {
	public:
		MyUserData(const sword::SWModule *module, const sword::SWKey *key);
		bool hasFootnotePreTag;
		sword::SWBuf version;
	};
	virtual sword::BasicFilterUserData *createUserData(const sword::SWModule *module, const sword::SWKey *key) {
		return new MyUserData(module, key);
	}
	virtual bool handleToken(sword::SWBuf &buf, const char *token, sword::BasicFilterUserData *userData);
public:
	BSGBFHTMLHREF();
};

#endif
