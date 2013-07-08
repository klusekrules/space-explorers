#include "Base.h"
#include "Logger.h"

Base::Base( const IdType& itID )throw()
	: id(itID)
{
}

Base::Base( ticpp::Node* n ) throw(WyjatekParseraXML){
	if(n){
		try{
			id.setId( stoi(n->ToElement()->GetAttribute("id"),nullptr,0) );
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

Base::~Base(){
}

const IdType& Base::getId()const{
	return id;
}

void Base::setId( const IdType& id ){
	this->id = id;
}

bool Base::zapisz( TiXmlElement* n ) const{
	n->SetAttribute("id",id.toString());
	return true;
}

bool Base::odczytaj( TiXmlElement* n ){
	if(n){
		auto c = n->Attribute("id");
		if(!c)
			return false;
		id.setId(stoul(c,nullptr,0));
		return true;
	}
	return false;
}

string Base::toString() const{
	Logger str(CLASSNAME(Base));
	str.addField("ID",id);
	return str.toString();
}
