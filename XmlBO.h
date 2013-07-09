#pragma once
#include "Main.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

class THROW { };
class NOTHROW { };

class XmlBO{
private:
	template < typename T > 
	static TiXmlElement * fail( bool n , string s ){
		return nullptr;
	}
	template < > 
	static TiXmlElement * fail<THROW>( bool n , string s ){
		throw WyjatekParseraXML(EXCEPTION_PLACE,exception((s + " isNull=" + to_string(n)).c_str()),WyjatekParseraXML::trescBladStrukturyXml);
	}
public:
	template<typename T>
	static TiXmlElement* IterateChildren( TiXmlElement* n , const string& s, TiXmlElement* p = nullptr ){
		if(n==nullptr || s.empty())
			return fail<T>(n==nullptr,s);
		if(p)
			return p->NextSiblingElement(s);
		else
			return n->FirstChildElement(s);
	}
	
	template<typename T>
	static TiXmlElement* IterateChildrenIf( TiXmlElement* n , const string& s, const string& atrybut, const string& wartosc, TiXmlElement* p = nullptr ){
		if(n==nullptr || s.empty())
			return fail<T>(n==nullptr,s);
		TiXmlElement* element = p ? p : n;
		for(TiXmlElement* t = element->FirstChildElement(s); t!= nullptr; t = t->NextSiblingElement(s) ){
			auto s = t->Attribute(atrybut);
			if(s && wartosc == *s)
				return t;
		}
		return nullptr;
	}
};