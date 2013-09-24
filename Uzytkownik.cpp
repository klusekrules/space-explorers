#include "Uzytkownik.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"
#include "Gra.h"
#include "XmlBO.h"

Uzytkownik::Uzytkownik(Gra& gra)
	: instancjaGry(gra)
{
}

Uzytkownik::~Uzytkownik()
{
}

bool Uzytkownik::dodajPlanete( shared_ptr<Planeta> planeta ){
	auto iterator = listaPlanet.find(planeta->pobierzIdentyfikator());
	if(iterator!=listaPlanet.end())
		return false;
	listaPlanet.insert(make_pair(planeta->pobierzIdentyfikator(),planeta));
	planeta->ustawWlasciciela(this);
	return true;
}

Planeta& Uzytkownik::pobierzPlanete( const Identyfikator& identyfikator ) const{
	auto iterator = listaPlanet.find(identyfikator);
	if(iterator!=listaPlanet.end())
		return *(iterator->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,Tekst("Nieznaleziono planety"));
}

Tekst Uzytkownik::pobierzNazweUzytkownika()const{
	return nazwaUzytkownika_;
}

void Uzytkownik::ustawNazweUzytkownika( const Tekst& nazwa ){
	nazwaUzytkownika_ = nazwa;
	for(auto planeta :  listaPlanet)
		planeta.second->odswiezNazweUzytkownika();
}

bool Uzytkownik::zapisz( TiXmlElement* wezel ) const{
	if(!wezel)
		return false;
	wezel->SetAttribute(ATRYBUT_XML_NAZWA,nazwaUzytkownika_());
	for(auto planeta :  listaPlanet)
		if(!planeta.second->zapisz(wezel))
			return false;
	return true;
}

bool Uzytkownik::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NAZWA,nazwaUzytkownika_);
		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_PLANETA); element ; element = element->NextSiblingElement(WEZEL_XML_PLANETA)){
			auto planeta = shared_ptr<Planeta>( new Planeta(Identyfikator()) );
			if(!planeta->odczytaj(element))
				return false;
			listaPlanet.insert(make_pair(planeta->pobierzIdentyfikator(),planeta));
			planeta->ustawWlasciciela(this);
			if(!instancjaGry.dodajPlanete(planeta))
				return false;
		}
		return true;
	}
	return false;
}

string Uzytkownik::napis() const{
	Logger str(NAZWAKLASY(Uzytkownik));
	str.dodajPole("Nazwa",nazwaUzytkownika_);
	for(auto planeta :  listaPlanet)
		if(!planeta.second)
			str.dodajPole(NAZWAKLASY(Planeta),*(planeta.second));
	return str.napis();
}
