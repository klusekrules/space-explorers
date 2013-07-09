#include "IdType.h"
#include "Logger.h"
#include <iomanip>
#include "Stale.h"
#include "WyjatekParseraXML.h"

IdType::IdType()
	: BaseInterface(Stale::idDomyslny)
{
}

IdType::IdType( const type_name& ID )
	: BaseInterface(ID)
{
}

IdType::IdType( const Ilosc& ID )
	: BaseInterface(static_cast<type_name>(ID()))
{
}

IdType::IdType( const IdType& a )
	: BaseInterface(a)
{
}

IdType::IdType( TiXmlElement* n )
	: BaseInterface(Stale::idDomyslny)
{
	if(n!=nullptr){
		try{
			wartosc_ = stoi(n->Attribute("id"),nullptr,0);
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

IdType::~IdType(){
}


bool IdType::operator==( const IdType& a )const{
	return wartosc_==a.wartosc_;
}

bool IdType::operator!=( const IdType& a )const{
	return wartosc_!=a.wartosc_;
}

bool IdType::operator<( const IdType& a )const{
	return wartosc_<a.wartosc_;
}

IdType::operator size_t()const{
	return wartosc_;
}

IdType::type_name IdType::getId()const{
	return wartosc_;
}

void IdType::setId( const type_name & wartosc ){
	wartosc_=wartosc;
}

string IdType::toString()const{
	stringstream str;
	str.imbue(locale::classic());
	str << "0x"<< uppercase << hex << wartosc_;
	return str.str();
}
