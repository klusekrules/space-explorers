#pragma once
#include "Main.h"
#include "parser\ticpp.h"
#include "BaseTypes\WyjatekParseraXML.h"

class XmlBO{
public:
	static ticpp::Node* IterateChildren(const ticpp::Node* n , const string& s, bool throwifInvArg = true){
		if(n==nullptr || s.empty())
			if(throwifInvArg)
				throw WyjatekParseraXML(EXCEPTION_PLACE,exception((s + " isNull=" + to_string(n==nullptr)).c_str()),WyjatekParseraXML::trescBladStrukturyXml);
			else
				return nullptr;

		return n->IterateChildren(s,nullptr);
	}

	static ticpp::Element* IterateChildrenElement(const ticpp::Node* n , const string& s, bool throwifError = true){
		if(n==nullptr || s.empty())
			if(throwifError)
				throw WyjatekParseraXML(EXCEPTION_PLACE,exception((s + " isNull=" + to_string(n==nullptr)).c_str()),WyjatekParseraXML::trescBladStrukturyXml);
			else
				return nullptr;

		auto t = n->IterateChildren(s,nullptr);

		if( t )
			return t->ToElement();
		else
			return nullptr;
	}
};