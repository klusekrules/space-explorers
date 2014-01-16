#include "Galaktyka.h"
#include "Logger.h"
#include "definicjeWezlowXML.h"
#include "XmlBO.h"

Galaktyka::Galaktyka( const Identyfikator& identyfikator )
	: Bazowa(identyfikator)
{
}

Galaktyka::~Galaktyka(){
}

shared_ptr<UkladSloneczny> Galaktyka::pobierzUklad( const Identyfikator& identyfikator ) const{
	auto iter = uklady_.find(identyfikator);
	if(iter!=uklady_.end())
		return iter->second;
	return nullptr;
}

bool Galaktyka::dodajUklad( shared_ptr<UkladSloneczny> uklad ){
	auto iter = uklady_.find(uklad->pobierzIdentyfikator());
	if(iter!=uklady_.end())
		return false;
	uklady_.insert(make_pair(uklad->pobierzIdentyfikator(),uklad));
	return true;
}

bool Galaktyka::zapisz( tinyxml2::XMLElement* wezel ) const{
	tinyxml2::XMLElement* element = wezel->GetDocument()->NewElement(WEZEL_XML_GALAKTYKA);
	wezel->LinkEndChild( element );
	for(auto uklad :  uklady_)
		if(!uklad.second->zapisz(element))
			return false;
	return Bazowa::zapisz(element);
}

bool Galaktyka::odczytaj( tinyxml2::XMLElement* wezel ){
	if(wezel){
		if(!Bazowa::odczytaj(wezel))
			return false;
		for(tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_UKLAD_SLONECZNY); element ; element = element->NextSiblingElement(WEZEL_XML_UKLAD_SLONECZNY)){
			auto uklad = make_shared<UkladSloneczny>(Identyfikator(),pobierzIdentyfikator());
			if(!uklad->odczytaj(element))
				return false;
			auto iter = uklady_.find(uklad->pobierzIdentyfikator());
			if(iter!=uklady_.end())
				return false;
			uklady_.insert(make_pair(uklad->pobierzIdentyfikator(),uklad));
		}
		return true;
	}
	return false;
}
	
string Galaktyka::napis() const{
	Logger str(NAZWAKLASY(Galaktyka));
	str.dodajKlase(Bazowa::napis());	
	for( auto a : uklady_ ){
		if(a.second){
			str.dodajPole("Uklad",*a.second);
		}
	}
	return str.napis();
}
