#include "Budynek.h"
#include "BudynekInfo.h"
#include "Logger.h"

Budynek::Budynek(const Poziom& p, const BudynekInfo& o)
	: Obiekt( Ilosc(1), p, o ), budynekInfo(o)
{
}

Budynek* Budynek::Kopia() const{
	return new Budynek(getPoziom(),budynekInfo);
}

Budynek* Budynek::Podziel( const Ilosc& ilosc){
	return nullptr;
}

bool Budynek::Polacz( const ObiektBase& obiektBase){
	return false;
}
	
bool Budynek::czyMoznaPolaczyc( const ObiektBase& obiektBase) const{
	return false;
}

bool Budynek::czyMoznaPodzielic( const Ilosc& ilosc) const{
	return false;
}

Budynek::~Budynek(void)
{
}

Cennik::ListaSurowcow Budynek::PobierzZapotrzebowanie( )const{
	return budynekInfo.PobierzZapotrzebowanie(getPoziom());
}

Cennik::ListaSurowcow Budynek::PobierzProdukcje( )const{
	return budynekInfo.PobierzProdukcje(getPoziom());
}

string Budynek::toString()const{
	Logger str(CLASSNAME(Budynek));
	str.addClass(Obiekt::toString());
	str.addField(CLASSNAME(BudynekInfo)+"ID",budynekInfo.getId());
	return str.toString();
}