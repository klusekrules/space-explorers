#pragma once
#include "Main.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

class XmlBO{
public:
	static ticpp::Node* IterateChildren(ticpp::Node* n , const string& s, bool throwifInvArg = true){
		if(n==nullptr || s.empty())
			if(throwifInvArg)
				throw WyjatekParseraXML(EXCEPTION_PLACE,exception((s + " isNull=" + to_string(n==nullptr)).c_str()),WyjatekParseraXML::trescBladStrukturyXml);
			else
				return nullptr;

		return n->IterateChildren(s,nullptr);
	}
};