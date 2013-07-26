#include "Flota.h"
#include "Aplikacja.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"

Flota::Flota(const Identyfikator& id, const Identyfikator& planetaPoczatkowa, const Identyfikator& planetaDocelowa, CelPodrozy celPodrozy)
	: Bazowa(id),planetaPoczatkowa_(planetaPoczatkowa), planetaDocelowa_(planetaDocelowa), celPodrozy_(celPodrozy)
{
}

Flota::~Flota(void)
{
}

bool Flota::dodajStatek( shared_ptr<Statek> statek ){
	if(!statek)
		return false;
	auto iterator = lista_.find(statek->ID());
	if(iterator == lista_.end()){
		statek->ustawIdentyfikatorPlanety(Identyfikator());
		lista_.insert(make_pair(statek->ID(),statek));
	}else{
		return iterator->second->polacz( *statek );
	}
	return true;
}

bool Flota::dodajLadunek( shared_ptr<Obiekt> obiekt ){
	if(!obiekt)
		return false;
	Objetosc objetoscObiektu = obiekt->pobierzObjetosc();
	if(pobierzDostepneMiejsce() < objetoscObiektu)
		return false;
	Objetosc objetoscJednostkowa = obiekt->pobierzObjetoscJednostkowa();

	map<Objetosc,Klucz,less<Objetosc> > posortowane;
	for( auto element : lista_ )
		posortowane.insert(make_pair(element.second->pobierzPojemnoscJednostkowa(),element.first));

	for( auto element : posortowane ){
		if( element.first < objetoscJednostkowa )
			continue;
		auto iter = lista_.find(element.second);
		if(iter == lista_.end())
			continue;
		shared_ptr<Obiekt> obiektDoDodania = obiekt;
		Objetosc dostepneMiejsce = iter->second->pobierzDostepneMiejsce();
		if(objetoscObiektu > dostepneMiejsce){
			Ilosc ilosc( floor( dostepneMiejsce() / objetoscJednostkowa() ) );
			obiektDoDodania = shared_ptr<Obiekt>(obiekt->podziel(ilosc));
			if(iter->second->dodajObiektDoLadowni(obiektDoDodania))
				return true;
			else
				obiekt->polacz(*obiektDoDodania);
		}else{
			if(iter->second->dodajObiektDoLadowni(obiektDoDodania))
				return true;
		}		
	}
	return false;
}

Objetosc Flota::pobierzDostepneMiejsce() const{
	Objetosc suma(0.0);
	for(auto element : lista_){
		suma+=element.second->pobierzDostepneMiejsce();
	}
	return suma;
}

void Flota::ustawPlaneteDocelowa( const Identyfikator& identyfikatorPlanety ){
	planetaDocelowa_ = identyfikatorPlanety;
}

void Flota::ustawPlanetePoczatkowa( const Identyfikator& identyfikatorPlanety ){
	planetaPoczatkowa_ = identyfikatorPlanety;
}

void Flota::ustawCelPodrozy( CelPodrozy cel ){
	celPodrozy_ = cel;
}

bool Flota::rozladujLadownieNaPlanecie(){
	shared_ptr<Planeta> planeta;
	switch(celPodrozy_){
	case Transport: planeta = Aplikacja::getInstance().getGra().pobierzPlanete(planetaDocelowa_);
		break;
	case Zwiad:
	case Atak: Aplikacja::getInstance().getGra().pobierzPlanete(planetaPoczatkowa_);
		break;
	}
	if(!planeta)
		return false;
	for(auto statek : lista_)
		if(statek.second){
			planeta->rozladujStatek(statek.second);
		}
		return true;
}

bool Flota::rozladujFloteNaPlanecie(){
	shared_ptr<Planeta> planeta;
	switch(celPodrozy_){
	case Transport: planeta = Aplikacja::getInstance().getGra().pobierzPlanete(planetaDocelowa_);
		break;
	case Zwiad:
	case Atak: Aplikacja::getInstance().getGra().pobierzPlanete(planetaPoczatkowa_);
		break;
	}
	if(!planeta)
		return false;
	for(auto statek : lista_)
		if(statek.second){
			planeta->rozladujStatek(statek.second);
			planeta->wybuduj(statek.second);
		}
		lista_.clear();
		return true;
}

bool Flota::zapisz( TiXmlElement* wezel ) const{
	if(wezel){
		TiXmlElement* element = new TiXmlElement(WEZEL_XML_FLOTA);
		wezel->LinkEndChild( element );
		wezel->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETA_POCZATKOWA,planetaPoczatkowa_.napis());
		wezel->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETA_DOCELOWA,planetaDocelowa_.napis());
		wezel->SetAttribute(ATRYBUT_XML_CEL_PODROZY,celPodrozy_);
		for(auto statek : lista_)
			if(statek.second)
				statek.second->zapisz(element);
		return Bazowa::zapisz(element);
	}
	return false;
}

bool Flota::odczytaj( TiXmlElement* wezel ) {
	if(wezel && Bazowa::odczytaj(wezel)){
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR_PLANETA_POCZATKOWA,planetaPoczatkowa_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR_PLANETA_DOCELOWA,planetaDocelowa_))
			return false;
		int cel;
		if(!wezel->Attribute(ATRYBUT_XML_CEL_PODROZY,&cel)) 
			return false;
		switch(cel){
		case Zwiad: celPodrozy_ = Zwiad;
			break;
		case Atak: celPodrozy_ = Atak;
			break;
		case Transport: celPodrozy_ = Transport;
			break;
		default:
			return false;
		}
		for(TiXmlElement* element = wezel->FirstChildElement(); element ; element = element->NextSiblingElement()){
			Identyfikator identyfikator;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(element,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
				return false;
			shared_ptr<Statek> statek = shared_ptr<Statek>(Aplikacja::getInstance().getGra().pobierzStatek(identyfikator).tworzEgzemplarz(Ilosc(),Identyfikator()));			
			if(!statek->odczytaj(element) )
				return false;
			lista_.insert(make_pair(statek->ID(),statek));
		}
	}
	return false;
}

string Flota::napis()const {
	Logger str(NAZWAKLASY(Ladownia));
	str.dodajKlase(Bazowa::napis());
	str.dodajPole(NAZWAKLASY(CelPodrozy),std::to_string(celPodrozy_));
	str.dodajPole(NAZWAKLASY(Planeta)+"IdDocelowa",planetaDocelowa_);
	str.dodajPole(NAZWAKLASY(Planeta)+"IdPoczatkowa",planetaPoczatkowa_);
	for(auto s : lista_)
		if(s.second)
			str.dodajPole(NAZWAKLASY(Statek),*s.second);
	return str.napis();
}
