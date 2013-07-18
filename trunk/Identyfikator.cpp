#include "Identyfikator.h"
#include "Logger.h"
#include <iomanip>
#include "Stale.h"

Identyfikator::Identyfikator()
	: PodstawowyInterfejs(Stale::idDomyslny)
{
}

Identyfikator::Identyfikator( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Identyfikator::Identyfikator( const Ilosc& wartosc )
	: PodstawowyInterfejs(static_cast<type_name>(wartosc()))
{
}

Identyfikator::Identyfikator( const Identyfikator& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Identyfikator::~Identyfikator(){
}

bool Identyfikator::operator==( const Identyfikator& wartosc )const{
	return wartosc_==wartosc.wartosc_;
}

bool Identyfikator::operator!=( const Identyfikator& wartosc )const{
	return wartosc_!=wartosc.wartosc_;
}

bool Identyfikator::operator<( const Identyfikator& wartosc )const{
	return wartosc_<wartosc.wartosc_;
}

Identyfikator::operator size_t()const{
	return wartosc_;
}

string Identyfikator::napis()const{
	stringstream str;
	str.imbue(std::locale::classic());
	str << "0x"<< std::uppercase << std::hex << wartosc_;
	return str.str();
}
