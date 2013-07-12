#include "Base.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

Base::Base( const Identyfikator& itID )throw()
	: id(itID)
{
}

Base::Base( TiXmlElement* n ) throw(WyjatekParseraXML){
	if(n){
		try{
			id( stoi(n->ToElement()->Attribute(ATRYBUT_XML_IDENTYFIKATOR),nullptr,0) );
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

Base::~Base(){
}

const Identyfikator& Base::getId()const{
	return id;
}

void Base::setId( const Identyfikator& id ){
	this->id = id;
}

bool Base::zapisz( TiXmlElement* n ) const{
	n->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR,id.napis());
	return true;
}

bool Base::odczytaj( TiXmlElement* n ){
	if(n){
		string c = n->Attribute(ATRYBUT_XML_IDENTYFIKATOR);
		if(c.empty())
			return false;
		Utils::trim(c);
		id(stoul(c,nullptr,0));
		return true;
	}
	return false;
}

string Base::napis() const{
	Logger str(NAZWAKLASY(Base));
	str.dodajPole("ID",id);
	return str.napis();
}
