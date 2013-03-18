#pragma once
#include "Main.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

class XmlBO{
public:
	static ticpp::Node* IterateChildren(ticpp::Node* n , const string& s){
		if(n==nullptr || s.empty())
			throw WyjatekParseraXML(EXCEPTION_PLACE,exception((s + to_string(n==nullptr)).c_str()),WyjatekParseraXML::trescBladStrukturyXml);
		return n->IterateChildren(s,nullptr);
	}
};