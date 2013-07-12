#include "Identyfikator.h"
#include "Logger.h"
#include <iomanip>
#include "Stale.h"
#include "WyjatekParseraXML.h"

Identyfikator::Identyfikator()
	: PodstawowyInterfejs(Stale::idDomyslny)
{
}

Identyfikator::Identyfikator( const type_name& ID )
	: PodstawowyInterfejs(ID)
{
}

Identyfikator::Identyfikator( const Ilosc& ID )
	: PodstawowyInterfejs(static_cast<type_name>(ID()))
{
}

Identyfikator::Identyfikator( const Identyfikator& a )
	: PodstawowyInterfejs(a)
{
}

Identyfikator::~Identyfikator(){
}


bool Identyfikator::operator==( const Identyfikator& a )const{
	return wartosc_==a.wartosc_;
}

bool Identyfikator::operator!=( const Identyfikator& a )const{
	return wartosc_!=a.wartosc_;
}

bool Identyfikator::operator<( const Identyfikator& a )const{
	return wartosc_<a.wartosc_;
}

Identyfikator::operator size_t()const{
	return wartosc_;
}

string Identyfikator::napis()const{
	stringstream str;
	str.imbue(locale::classic());
	str << "0x"<< uppercase << hex << wartosc_;
	return str.str();
}
