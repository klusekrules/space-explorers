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
	auto iterator = planety_.find(planeta->pobierzIdentyfikator());
	if(iterator!=planety_.end())
		return false;
	planety_.insert(make_pair(planeta->pobierzIdentyfikator(),planeta));
	planeta->ustawWlasciciela(this);
	return true;
}

bool Uzytkownik::usunPlanete( const Identyfikator& identyfikator ){
	auto iterator = planety_.find(identyfikator);
	if(iterator==planety_.end())
		return false;
	planety_.erase(iterator);
	return true;
}

Planeta& Uzytkownik::pobierzPlanete( const Identyfikator& identyfikator ) const{
	auto iterator = planety_.find(identyfikator);
	if(iterator!=planety_.end())
		return *(iterator->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,Tekst("Nieznaleziono planety"));
}

Tekst Uzytkownik::pobierzNazweUzytkownika()const{
	return nazwaUzytkownika_;
}

void Uzytkownik::ustawNazweUzytkownika( const Tekst& nazwa ){
	nazwaUzytkownika_ = nazwa;
}

bool Uzytkownik::zapisz( TiXmlElement* wezel ) const{
	if(!wezel)
		return false;
	wezel->SetAttribute(ATRYBUT_XML_NAZWA,nazwaUzytkownika_());
	for(auto planeta :  planety_){
		TiXmlElement* element = new TiXmlElement(WEZEL_XML_PLANETA);
		element->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_RODZICA,planeta.first.napis());
		wezel->LinkEndChild(element);
	}
	return true;
}

bool Uzytkownik::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NAZWA,nazwaUzytkownika_);
		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_PLANETA); element ; element = element->NextSiblingElement(WEZEL_XML_PLANETA)){
			Identyfikator idPlanety;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(element,ATRYBUT_XML_IDENTYFIKATOR_RODZICA,idPlanety))
				return false;
			auto planeta = instancjaGry.pobierzPlanete(idPlanety);
			if(!planeta)
				return false;
			planeta->ustawWlasciciela(this);
			planety_[idPlanety] = planeta;
		}
		return true;
	}
	return false;
}

string Uzytkownik::napis() const{
	Logger str(NAZWAKLASY(Uzytkownik));
	str.dodajPole("Nazwa",nazwaUzytkownika_);
	for(auto planeta :  planety_)
		if(!planeta.second)
			str.dodajPole(NAZWAKLASY(Planeta),*(planeta.second));
	return str.napis();
}
