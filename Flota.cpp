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

Identyfikator Flota::pobierzPlaneteDocelowa() const{
	return planetaDocelowa_;
}

Identyfikator Flota::pobierzPlanetePoczatkowa() const{
	return planetaPoczatkowa_;
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

bool Flota::dodajLadunek( shared_ptr<Surowce> obiekt ){
	if(!obiekt)
		return false;
	Objetosc objetoscObiektu = obiekt->pobierzObjetosc();
	if(pobierzDostepneMiejsceLadowni() < objetoscObiektu)
		return false;
	Objetosc objetoscJednostkowa = obiekt->pobierzObjetoscJednostkowa();

	map<Objetosc,Klucz,less<Objetosc> > posortowane;
	for( auto element : lista_ )
		posortowane.insert(make_pair(element.second->pobierzPojemnoscJednostkowaLadowni(),element.first));

	for( auto element : posortowane ){
		if( element.first < objetoscJednostkowa )
			continue;
		auto iter = lista_.find(element.second);
		if(iter == lista_.end())
			continue;
		shared_ptr<Surowce> obiektDoDodania = obiekt;
		Objetosc dostepneMiejsce = iter->second->pobierzDostepneMiejsceLadowni();
		if(objetoscObiektu > dostepneMiejsce){
			Ilosc ilosc( floor( dostepneMiejsce() / objetoscJednostkowa() ) );
			obiektDoDodania = shared_ptr<Surowce>(obiekt->podziel(ilosc));
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

bool Flota::dodajLadunek( shared_ptr<Statek> obiekt ){
	if(!obiekt)
		return false;
	Objetosc objetoscObiektu = obiekt->pobierzObjetosc();
	if(pobierzDostepneMiejsceHangaru() < objetoscObiektu)
		return false;
	Objetosc objetoscJednostkowa = obiekt->pobierzObjetoscJednostkowa();

	map<Objetosc,Klucz,less<Objetosc> > posortowane;
	for( auto element : lista_ )
		posortowane.insert(make_pair(element.second->pobierzPojemnoscJednostkowaHangaru(),element.first));

	for( auto element : posortowane ){
		if( element.first < objetoscJednostkowa )
			continue;
		auto iter = lista_.find(element.second);
		if(iter == lista_.end())
			continue;
		shared_ptr<Statek> obiektDoDodania = obiekt;
		Objetosc dostepneMiejsce = iter->second->pobierzDostepneMiejsceHangaru();
		if(objetoscObiektu > dostepneMiejsce){
			Ilosc ilosc( floor( dostepneMiejsce() / objetoscJednostkowa() ) );
			obiektDoDodania = shared_ptr<Statek>(obiekt->podziel(ilosc));
			if(iter->second->dodajStatekDoHangaru(obiektDoDodania))
				return true;
			else
				obiekt->polacz(*obiektDoDodania);
		}else{
			if(iter->second->dodajStatekDoHangaru(obiektDoDodania))
				return true;
		}		
	}
	return false;
}

Objetosc Flota::pobierzDostepneMiejsceLadowni() const{
	Objetosc suma(0.0);
	for(auto element : lista_){
		suma+=element.second->pobierzDostepneMiejsceLadowni();
	}
	return suma;
}

Objetosc Flota::pobierzDostepneMiejsceHangaru() const{
	Objetosc suma(0.0);
	for(auto element : lista_){
		suma+=element.second->pobierzDostepneMiejsceHangaru();
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
	case Stacjonowanie:
	case Transport: planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(planetaDocelowa_);
		break;
	case Powrot: planeta =Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(planetaPoczatkowa_);
		break;
	case Zwiad:
	case Szczatki:
	case Ekspedycja:
	case Atak: 
	default:
		return false;
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
	case Stacjonowanie:
	case Transport: planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(planetaDocelowa_);
		break;
	case Powrot: planeta =Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(planetaPoczatkowa_);
		break;
	case Zwiad:
	case Szczatki:
	case Ekspedycja:
	case Atak: 
	default:
		return false;
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

bool Flota::zawrocFlote(){
	if(celPodrozy_==Powrot)
		return false;
	celPodrozy_=Powrot;
	return true;
}

bool Flota::zapisz( TiXmlElement* wezel ) const{
	if(wezel){
		TiXmlElement* element = new TiXmlElement(WEZEL_XML_FLOTA);
		wezel->LinkEndChild( element );
		element->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETA_POCZATKOWA,planetaPoczatkowa_.napis());
		element->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETA_DOCELOWA,planetaDocelowa_.napis());
		element->SetAttribute(ATRYBUT_XML_CEL_PODROZY,celPodrozy_);
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
		case Stacjonowanie: celPodrozy_ = Stacjonowanie;
			break;
		case Szczatki: celPodrozy_ = Szczatki;
			break;
		case Ekspedycja: celPodrozy_ = Ekspedycja;
			break;
		case Powrot: celPodrozy_ = Powrot;
			break;
		default:
			return false;
		}
		for(TiXmlElement* element = wezel->FirstChildElement(); element ; element = element->NextSiblingElement()){
			Identyfikator identyfikator;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(element,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
				return false;
			shared_ptr<Statek> statek = shared_ptr<Statek>(Aplikacja::pobierzInstancje().pobierzGre().pobierzStatek(identyfikator).tworzEgzemplarz(Ilosc(),Identyfikator()));			
			if(!statek->odczytaj(element) )
				return false;
			lista_.insert(make_pair(statek->ID(),statek));
		}
		return true;
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
