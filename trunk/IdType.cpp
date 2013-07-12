#include "IdType.h"
#include "Logger.h"
#include <iomanip>
#include "Stale.h"
#include "WyjatekParseraXML.h"

IdType::IdType()
	: PodstawowyInterfejs(Stale::idDomyslny)
{
}

IdType::IdType( const type_name& ID )
	: PodstawowyInterfejs(ID)
{
}

IdType::IdType( const Ilosc& ID )
	: PodstawowyInterfejs(static_cast<type_name>(ID()))
{
}

IdType::IdType( const IdType& a )
	: PodstawowyInterfejs(a)
{
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

string IdType::napis()const{
	stringstream str;
	str.imbue(locale::classic());
	str << "0x"<< uppercase << hex << wartosc_;
	return str.str();
}
