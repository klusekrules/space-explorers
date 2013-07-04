#include "Uzytkownik.h"
#include "Logger.h"

Uzytkownik::Uzytkownik()
{
}

Uzytkownik::~Uzytkownik()
{
}

bool Uzytkownik::dodajPlanete( shared_ptr<Planeta> p ){
	auto i = listaPlanet.find(p->getId());
	if(i!=listaPlanet.end())
		return false;
	listaPlanet.insert(make_pair(p->getId(),p));
	p->ustawWlasciciela(this);
	return true;
}

Planeta& Uzytkownik::getPlaneta( const IdType& id ) const{
	auto i = listaPlanet.find(id);
	if(i!=listaPlanet.end())
		return *(i->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,Tekst("Nieznaleziono planety"));
}

string Uzytkownik::toString() const{
	Logger str(CLASSNAME(Uzytkownik));
	return str.toString();
}