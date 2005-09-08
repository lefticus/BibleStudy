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

#ifndef BSOSISHTMLHREF_H
#define BSOSISHTMLHREF_H

#include <swbasicfilter.h>


/** this filter converts OSIS text to HTML text with hrefs
 */
class BSOSISHTMLHREF : public sword::SWBasicFilter {
private:
protected:
	class MyUserData : public sword::BasicFilterUserData {
	public:
		bool osisQToTick;
		bool inBold;
		sword::SWBuf lastTransChange;
		sword::SWBuf w;
		sword::SWBuf fn;
		sword::SWBuf version;
		MyUserData(const sword::SWModule *module, const sword::SWKey *key);
	};
	virtual sword::BasicFilterUserData *createUserData(const sword::SWModule *module, const sword::SWKey *key) {
		return new MyUserData(module, key);
	}
	virtual bool handleToken(sword::SWBuf &buf, const char *token, sword::BasicFilterUserData *userData);
public:
	BSOSISHTMLHREF();
};

#endif
