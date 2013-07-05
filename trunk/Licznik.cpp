#include "Licznik.h"
#include "Logger.h"

Licznik::Licznik(const IdType& id, const Ilosc& w)
	: Base(id), wartoscLicznika(w)
{
}

Licznik::Licznik(const IdType& id)
	: Base(id), wartoscLicznika(0)
{
}

Licznik::Licznik()
	: Base(IdType(-1)), wartoscLicznika(0)
{
}

Licznik::~Licznik(void)
{
}

Ilosc Licznik::operator()(){
	return wartoscLicznika++;
}

Ilosc Licznik::pobierzWartosc()const{
	return wartoscLicznika;
}

void Licznik::resetujWartosc(){
	wartoscLicznika = Ilosc(0);
}

void Licznik::ustawWartosc( const Ilosc& w ){
	wartoscLicznika = w;
}

string Licznik::toString()const{
	Logger str(CLASSNAME(Licznik));
	str.addClass(Base::toString());
	return str.toString();
}