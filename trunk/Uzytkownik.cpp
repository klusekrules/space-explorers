#include "Uzytkownik.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"

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

bool Uzytkownik::zapisz( TiXmlElement* e ) const{
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_UZYTKOWNIK);
	e->LinkEndChild( n );
	for(auto o :  listaPlanet)
		if(!o.second->zapisz(n))
			return false;
	return true;
}

bool Uzytkownik::odczytaj( TiXmlElement* e ){
	if(e){
		for(TiXmlElement* n = e->FirstChildElement(WEZEL_XML_PLANETA); n != nullptr ; n = n->NextSiblingElement(WEZEL_XML_PLANETA)){
			auto p = shared_ptr<Planeta>( new Planeta(IdType()) );
			if(!p->odczytaj(n))
				return false;
			listaPlanet.insert(make_pair(p->getId(),p));
			p->ustawWlasciciela(this);
		}
		return true;
	}
	return false;
}

string Uzytkownik::napis() const{
	Logger str(NAZWAKLASY(Uzytkownik));
	return str.napis();
}