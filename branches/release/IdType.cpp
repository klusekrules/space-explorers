#include "IdType.h"
#include "Logger.h"
#include <iomanip>
#include "Stale.h"
#include "WyjatekParseraXML.h"

IdType::IdType()
	: id(Stale::idDomyslny)
{
}

IdType::IdType( const type_name& ID )
	: id(ID)
{
}

IdType::IdType( const IdType& a )
	: id(a.id)
{
}

IdType::IdType( ticpp::Node* n )
	: id(Stale::idDomyslny)
{
	if(n!=nullptr){
		try{
			ticpp::Element* e = n->ToElement();
			id = stoi(e->GetAttribute("id"),nullptr,0);
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

IdType::~IdType(){
}


bool IdType::operator==( const IdType& a )const{
	return id==a.id;
}

bool IdType::operator!=( const IdType& a )const{
	return id!=a.id;
}

bool IdType::operator<( const IdType& a )const{
	return id<a.id;
}

IdType::operator size_t()const{
	return id;
}

IdType::type_name IdType::getId()const{
	return id;
}

void IdType::setId( const type_name & ID ){
	id=ID;
}

IdType::type_name IdType::value()const{
	return getId();
}


string IdType::toString()const{
	stringstream str;
	str.imbue(locale::classic());
	str << "0x"<< uppercase << hex << id;
	return str.str();
}
