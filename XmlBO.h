#pragma once
#include "Main.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

class THROW { };
class NOTHROW { };

class XmlBO{
private:
	template < typename T > 
	static ticpp::Element * fail( bool n , string s ){
		return nullptr;
	}
	template < > 
	static ticpp::Element * fail<THROW>( bool n , string s ){
		throw WyjatekParseraXML(EXCEPTION_PLACE,exception((s + " isNull=" + to_string(n)).c_str()),WyjatekParseraXML::trescBladStrukturyXml);
	}
public:
	template<typename T>
	static ticpp::Node* IterateChildren(const ticpp::Node* n , const string& s){
		if(n==nullptr || s.empty())
			return fail<T>(n==nullptr,s);

		return n->IterateChildren(s,nullptr);
	}
	template<typename T>
	static ticpp::Element* IterateChildrenElement(const ticpp::Node* n , const string& s){
		if(n==nullptr || s.empty())
			return fail<T>(n==nullptr,s);

		auto t = n->IterateChildren(s,nullptr);

		if( t )
			return t->ToElement();
		else
			return nullptr;
	}

	template<typename T>
	static ticpp::Element* IterateChildrenElementIf(const ticpp::Node* n , const string& s, const string& atrybut, const string& wartosc){
		if(n==nullptr || s.empty())
			return fail<T>(n==nullptr,s);

		for(auto t = n->IterateChildren(s,nullptr); t!= nullptr; t = n->IterateChildren("Zmiana",t) ){
			auto el = t->ToElement();
			if(el){
				if(wartosc == el->GetAttribute(atrybut))
					return el;
			}
		}
		return nullptr;
	}
};