#include "Technologia.h"
#include "TechnologiaInfo.h"

Technologia::Technologia( const Poziom& p, const IdType& idP, const TechnologiaInfo& t)
	: ObiektBase(Ilosc(1),p,idP,t), technologiaInfo(t)
{
}

Technologia::~Technologia(void)
{
}

Technologia* Technologia::Kopia() const{
	return new Technologia(getPoziom(),getIdPlanety(),technologiaInfo);
}

Technologia* Technologia::Podziel( const Ilosc& ilosc){
	return nullptr;
}

bool Technologia::Polacz( const ObiektBase& obiektBase){
	return false;
}
	
bool Technologia::czyMoznaPolaczyc( const ObiektBase& obiektBase) const{
	return false;
}

bool Technologia::czyMoznaPodzielic( const Ilosc& ilosc) const{
	return false;
}

string Technologia::toString() const{
	Logger str(CLASSNAME(Technologia));
	str.addClass(ObiektBase::toString());
	str.addField(CLASSNAME(TechnologiaInfo)+"ID",technologiaInfo.getId());
	return str.toString();
}

