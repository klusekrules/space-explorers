#define _USE_MATH_DEFINES
#include "Planeta.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"
#include "Walidator.h"

Planeta::Planeta(const Identyfikator& identyfikator, const Identyfikator& idUkladu)
	: Bazowa(identyfikator), wlasciciel_(nullptr), idUkladu_(idUkladu)
{
}

Planeta::~Planeta(void)
{
}

void Planeta::ustawWlasciciela( Uzytkownik* wlasciciel ){
	wlasciciel_ = wlasciciel;
	idUzytkownika_ = wlasciciel_->pobierzNazweUzytkownika();
}

Uzytkownik* Planeta::pobierzWlasciciela( void ) const{
	return wlasciciel_;
}

void Planeta::wyczyscZawartoscPlanety(){

	if( wlasciciel_ && !idUzytkownika_.isEmpty() && Aplikacja::pobierzInstancje().pobierzGre().pobierzUzytkownika().pobierzNazweUzytkownika() == idUzytkownika_ ){
		wlasciciel_->usunPlanete(pobierzIdentyfikator());
		wlasciciel_ = nullptr;
		idUzytkownika_ = Tekst();
	}
	licznikIdentyfikatorowFloty_.resetujWartosc();
	listaSurowcow_.clear();
	listaStatkow_.clear();
	listaObrona_.clear();
	listaTechnologii_.clear();
	listaBudynkow_.clear();
	listaObiektow_.clear();
	listaObiektowZaladunkowych_.clear();
	listaFlot_.clear();
}

Ilosc Planeta::pobierzIloscTypowObiektow()const{
	if(listaObiektow_.size() != listaBudynkow_.size()+listaStatkow_.size()+listaSurowcow_.size()+listaTechnologii_.size())
		throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE,Ilosc(static_cast<long double>(listaObiektow_.size())));
	return Ilosc(static_cast<long double>(listaObiektow_.size())); 
}

const ObiektBazowy& Planeta::pobierzObiekt(const Indeks& identyfikator) const{
	auto iterator = listaObiektow_.find(identyfikator);
	if(iterator!=listaObiektow_.end())
		return *(iterator->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
}

const ObiektBazowy& Planeta::pobierzObiekt(const Identyfikator& identyfikator) const{
	auto iterator = listaObiektow_.end();
	for( auto element = listaObiektow_.begin() ; element != listaObiektow_.end() ; ++element ){
		if( element->first.pobierzIdentyfikator() == identyfikator && ( iterator == listaObiektow_.end() || (iterator != listaObiektow_.end() && iterator->first.pobierzPoziom()<element->first.pobierzPoziom() ) )){
				iterator = element;
		}
	}
	if( iterator != listaObiektow_.end() )
		return *(iterator->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
}

Poziom Planeta::pobierzPoziomObiektu( const Identyfikator& identyfikator ) const{
	auto iterator = listaObiektow_.end();
	for( auto element = listaObiektow_.begin() ; element != listaObiektow_.end() ; ++element ){
		if( element->first.pobierzIdentyfikator() == identyfikator && ( iterator == listaObiektow_.end() || (iterator != listaObiektow_.end() && iterator->first.pobierzPoziom()<element->first.pobierzPoziom() ) )){
				iterator = element;
		}
	}
	if( iterator != listaObiektow_.end() )
		return iterator->second->pobierzPoziom();
	return Poziom(0);
}

Ilosc Planeta::pobierzIloscObiektu( const Indeks& indeks ) const{
	auto iterator = listaObiektow_.find(indeks);
	if(iterator!=listaObiektow_.end())
		return iterator->second->pobierzIlosc();
	return Ilosc(0.0);
}

const Statek& Planeta::pobierzStatek(const Indeks& identyfikator) const{
	auto iterator = listaStatkow_.find(identyfikator);
	if(iterator!=listaStatkow_.end())
		return *(iterator->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
}

const Obrona& Planeta::pobierzObrone(const Indeks& identyfikator) const{
	auto iterator = listaObrona_.find(identyfikator);
	if(iterator!=listaObrona_.end())
		return *(iterator->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
}

const Technologia& Planeta::pobierzTechnologie(const Indeks& identyfikator) const{
	auto iterator = listaTechnologii_.find(identyfikator);
	if(iterator!=listaTechnologii_.end())
		return *(iterator->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
}

const Budynek& Planeta::pobierzBudynek(const Indeks& identyfikator) const{
	auto iterator = listaBudynkow_.find(identyfikator);
	if(iterator!=listaBudynkow_.end())
		return *(iterator->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
}

bool Planeta::dodajObiekt( shared_ptr< Budynek > obiekt ){
	auto iterator = listaObiektow_.find(obiekt->ID());
	if(iterator!=listaObiektow_.end())
		return false;
	listaBudynkow_.insert(make_pair(obiekt->ID(),obiekt));
	listaObiektow_.insert(make_pair(obiekt->ID(),obiekt));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Obrona > obiekt ){
	auto iterator = listaObiektow_.find(obiekt->ID());
	if(iterator!=listaObiektow_.end())
		return false;
	listaObrona_.insert(make_pair(obiekt->ID(),obiekt));
	listaObiektow_.insert(make_pair(obiekt->ID(),obiekt));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Statek > obiekt ){
	auto iterator = listaObiektow_.find(obiekt->ID());
	if(iterator!=listaObiektow_.end())
		return false;
	listaStatkow_.insert(make_pair(obiekt->ID(),obiekt));
	listaObiektowZaladunkowych_.insert(make_pair(obiekt->ID(),obiekt));
	listaObiektow_.insert(make_pair(obiekt->ID(),obiekt));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Technologia > obiekt ){
	auto iterator = listaObiektow_.find(obiekt->ID());
	if(iterator!=listaObiektow_.end())
		return false;
	listaTechnologii_.insert(make_pair(obiekt->ID(),obiekt));
	listaObiektow_.insert(make_pair(obiekt->ID(),obiekt));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Surowce > obiekt ){
	auto iterator = listaObiektow_.find(obiekt->ID());
	if(iterator!=listaObiektow_.end())
		return false;
	listaSurowcow_.insert(make_pair(obiekt->ID(),obiekt));
	listaObiektowZaladunkowych_.insert(make_pair(obiekt->ID(),obiekt));
	listaObiektow_.insert(make_pair(obiekt->ID(),obiekt));
	return true;
}

bool Planeta::wybuduj( const Indeks& identyfikator, const Ilosc& ilosc ){
	auto iterator = listaObiektow_.find(identyfikator);
	if(iterator!=listaObiektow_.end()){
		iterator->second->wybuduj(ilosc);
		if(iterator->first != iterator->second->ID()){
			auto klucz = iterator->first;			
			auto wskaznik = iterator->second;
			auto nowyKlucz = wskaznik->ID();
			auto nowyIterator = listaObiektow_.find(nowyKlucz);
			if(nowyIterator!=listaObiektow_.end()){
				if(!nowyIterator->second->polacz(*wskaznik))
					return false;
			}else{
				Utils::zamianaKlucza(listaObiektow_,klucz,nowyKlucz);
				Utils::zamianaKlucza(listaSurowcow_,klucz,nowyKlucz);
				Utils::zamianaKlucza(listaStatkow_,klucz,nowyKlucz);
				Utils::zamianaKlucza(listaObrona_,klucz,nowyKlucz);
				Utils::zamianaKlucza(listaTechnologii_,klucz,nowyKlucz);
				Utils::zamianaKlucza(listaBudynkow_,klucz,nowyKlucz);
				Utils::zamianaKlucza(listaObiektowZaladunkowych_,klucz,nowyKlucz);
			}
		}
		return true;
	}else{
		return Aplikacja::pobierzInstancje().pobierzGre().wybudujNaPlanecie(*this,identyfikator.pobierzIdentyfikator(),ilosc);
	}
}

bool Planeta::wybuduj( const Indeks& identyfikator, tinyxml2::XMLElement* wezel ){
	if(listaObiektow_.find(identyfikator) != listaObiektow_.end())
		return false;
	if(!Aplikacja::pobierzInstancje().pobierzGre().wybudujNaPlanecie(*this,identyfikator.pobierzIdentyfikator(),Ilosc(0),identyfikator.pobierzPoziom()))
		return false;	
	auto iterator = listaObiektow_.find(identyfikator);
	if(iterator == listaObiektow_.end())
		return false;
	return iterator->second->odczytaj(wezel);
}

void Planeta::wybuduj( shared_ptr< ObiektBazowy > obiekt ){
	auto iterator = listaObiektow_.find(obiekt->ID());
	if(iterator!=listaObiektow_.end()){
		iterator->second->wybuduj(obiekt->pobierzIlosc());
	}else{
		Aplikacja::pobierzInstancje().pobierzGre().wybudujNaPlanecie(*this,obiekt->pobierzObiektBaseInfo(),obiekt->pobierzIlosc(),obiekt->pobierzPoziom());
	}
}

void Planeta::wybuduj( shared_ptr< Statek > obiekt ){
	auto iterator = listaObiektow_.find(obiekt->ID());
	if(iterator!=listaObiektow_.end()){
		iterator->second->wybuduj(obiekt->pobierzIlosc());
	}else{
		dodajObiekt(obiekt);
	}
}

Identyfikator Planeta::dodajFlote(){
	shared_ptr< Flota > flota = shared_ptr< Flota >(new Flota(Identyfikator(licznikIdentyfikatorowFloty_()),Identyfikator(),Identyfikator(),Flota::CelPodrozy::Transport));
	listaFlot_.insert(make_pair(flota->pobierzIdentyfikator(),flota));
	return flota->pobierzIdentyfikator();
}

bool Planeta::przeniesDoFloty(const Identyfikator& identyfikatorFloty, const Indeks& obiekt, const Ilosc& ilosc){
	auto statek = listaStatkow_.find(obiekt);
	if(statek!=listaStatkow_.end()){
		auto flota = listaFlot_.find(identyfikatorFloty);
		if(flota!=listaFlot_.end()){
			if(ilosc <= statek->second->pobierzIlosc()){
				if(ilosc < statek->second->pobierzIlosc()){
					auto podzial = shared_ptr<Statek>(statek->second->podziel(ilosc));
					if(flota->second->dodajStatek(podzial)){
						return true;
					}else{
						statek->second->polacz(*podzial);
						return false;
					}
				}else{
					if(flota->second->dodajStatek(statek->second)){
						listaStatkow_.erase(obiekt);
						listaObiektowZaladunkowych_.erase(obiekt);
						listaObiektow_.erase(obiekt);
						return true;
					}else{
						return false;
					}
				}
			}
		}
	}
	return false;
}

bool Planeta::zaladujSurowceNaFlote(const Identyfikator& identyfikatorFloty, const Indeks& identyfikator, const Ilosc& ilosc){
	auto iterator = listaSurowcow_.find(identyfikator);
	if(iterator==listaSurowcow_.end())
		return false;

	if(ilosc <= Ilosc(0.0) || iterator->second->pobierzIlosc() < ilosc)
		return false;

	auto flota = listaFlot_.find(identyfikatorFloty);
	if(flota==listaFlot_.end())
		return false;
	shared_ptr<Surowce> ladunek = shared_ptr<Surowce>( iterator->second->podziel(ilosc));
	if(!flota->second->dodajLadunek(ladunek)){
		iterator->second->polacz(*ladunek);
		return false;
	}
	return true;
}

bool Planeta::zaladujStatekNaFlote(const Identyfikator& identyfikatorFloty, const Indeks& identyfikator, const Ilosc& ilosc){
	auto iterator = listaStatkow_.find(identyfikator);
	if(iterator==listaStatkow_.end())
		return false;

	if(ilosc <= Ilosc(0.0) || iterator->second->pobierzIlosc() < ilosc)
		return false;

	auto flota = listaFlot_.find(identyfikatorFloty);
	if(flota==listaFlot_.end())
		return false;
	shared_ptr<Statek> ladunek = shared_ptr<Statek>( iterator->second->podziel(ilosc));
	if(!flota->second->dodajLadunek(ladunek)){
		iterator->second->polacz(*ladunek);
		return false;
	}
	return true;
}

bool Planeta::czyMaWlasciciela()const{
	return wlasciciel_!=nullptr;
}

void Planeta::rozladujStatek( shared_ptr< Statek > statek ){
	if(statek){
		for(auto element : statek->oproznijLadownie()){
			wybuduj(element.second);
		}
		for(auto element : statek->oproznijHangar()){
			wybuduj(element.second);
		}
	}
}

shared_ptr< Flota > Planeta::pobierzFlote(const Identyfikator& identyfikator) const{
	auto iterator = listaFlot_.find(identyfikator);
	if(iterator!=listaFlot_.end())
		return iterator->second;
	return nullptr;
}

bool Planeta::usunFlote(const Identyfikator& identyfikator){
	return listaFlot_.erase(identyfikator) != 0;
}

bool Planeta::zapisz( tinyxml2::XMLElement* wezel ) const{
	tinyxml2::XMLElement* planeta = wezel->GetDocument()->NewElement(WEZEL_XML_PLANETA);
	wezel->LinkEndChild( planeta );
	planeta->SetAttribute(ATRYBUT_XML_ODLEGLOSC_OD_SLONCA, odlegloscOdSlonca_.napis().c_str());
	planeta->SetAttribute(ATRYBUT_XML_SREDNICA, srednicaPlanety_.napis().c_str());
	/*planeta->SetAttribute(ATRYBUT_XML_PREDKOSC_KATOWA_PLANETY, predkoscKatowaPlanety_.napis());
	planeta->SetAttribute(ATRYBUT_XML_NASLONECZNIENIE_PLANETY, naslonecznieniePlanety_.napis());
	planeta->SetAttribute(ATRYBUT_XML_WIETRZNOSC_PLANETY, wietrznoscPlanety_.napis());*/
	planeta->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_RODZICA,idUkladu_.napis().c_str());
	planeta->SetAttribute(ATRYBUT_XML_NAZWAGRACZA,idUzytkownika_().c_str());
	planeta->SetAttribute(ATRYBUT_XML_TEMPERATURA_PLANETY, temperaturaPlanety_.napis().c_str());
	planeta->SetAttribute(ATRYBUT_XML_CALKOWITA_POWIERZNIA_PLANETY, calkowitaPowierzchniaPlanety_.napis().c_str() );
	planeta->SetAttribute(ATRYBUT_XML_POWIERZCHNIA_ZAJETA_PRZEZ_WODE,powierzchniaZajetaPrzezWode_.napis().c_str() );
	planeta->SetAttribute(ATRYBUT_XML_POWIERZCHNIA_LADOW, powierzchniaLadow_.napis().c_str() );
	planeta->SetAttribute(ATRYBUT_XML_POWIERZCHNIA_UZYTKOWA_LADOW, powierzchniaUzytkowaLadow_.napis().c_str() );
	planeta->SetAttribute(ATRYBUT_XML_NAZWA, nazwaPlanety_().c_str());
	licznikIdentyfikatorowFloty_.zapisz(planeta);
	/*for(auto element :  dostepneZasobyPlanety_){
		TiXmlElement* zasob = new TiXmlElement(WEZEL_XML_ZASOB);
		zasob->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR, element.first.pobierzIdentyfikator().napis());
		zasob->SetAttribute(ATRYBUT_XML_POZIOM, element.first.pobierzPoziom().napis());
		zasob->SetAttribute(ATRYBUT_XML_ILOSC, element.second.napis());
		planeta->LinkEndChild(zasob);
	}*/
	tinyxml2::XMLElement* obiekty = wezel->GetDocument()->NewElement(WEZEL_XML_OBIEKTY);
	planeta->LinkEndChild( obiekty );
	for(auto element :  listaObiektow_)
		if(!element.second->zapisz(obiekty))
			return false;
	tinyxml2::XMLElement* floty = wezel->GetDocument()->NewElement(WEZEL_XML_FLOTY);
	planeta->LinkEndChild( floty );
	for(auto element :  listaFlot_)
		if(!element.second->zapisz(floty))
			return false;
	return Bazowa::zapisz(planeta);
}

bool Planeta::odczytaj( tinyxml2::XMLElement* wezel ){
	if(wezel){
		Identyfikator identyfikatorPlanety;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_ODLEGLOSC_OD_SLONCA,odlegloscOdSlonca_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_SREDNICA,srednicaPlanety_))
			return false;
		/*if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_PREDKOSC_KATOWA_PLANETY,predkoscKatowaPlanety_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NASLONECZNIENIE_PLANETY,naslonecznieniePlanety_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_WIETRZNOSC_PLANETY,wietrznoscPlanety_))
			return false;*/
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR_RODZICA,idUkladu_))
			return false;

		XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NAZWAGRACZA,idUzytkownika_);

		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_TEMPERATURA_PLANETY,temperaturaPlanety_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_CALKOWITA_POWIERZNIA_PLANETY,calkowitaPowierzchniaPlanety_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_POWIERZCHNIA_ZAJETA_PRZEZ_WODE,powierzchniaZajetaPrzezWode_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_POWIERZCHNIA_LADOW,powierzchniaLadow_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_POWIERZCHNIA_UZYTKOWA_LADOW,powierzchniaUzytkowaLadow_))
			return false;
		XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NAZWA,nazwaPlanety_);
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,identyfikatorPlanety))
			return false;
		Walidator::pobierzInstancje().dodajNowyIdentyfikatorPlanety(identyfikatorPlanety);
		for(tinyxml2::XMLElement* zasob = wezel->FirstChildElement(WEZEL_XML_ZASOB); zasob ; zasob = zasob->NextSiblingElement(WEZEL_XML_ZASOB)){
			Identyfikator identyfikator;
			Poziom poziom;
			Ilosc ilosc;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(zasob,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
				return false;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(zasob,ATRYBUT_XML_POZIOM,poziom))
				return false;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(zasob,ATRYBUT_XML_ILOSC,ilosc))
				return false;
			/*auto iter = dostepneZasobyPlanety_.find(Indeks(identyfikator,poziom));
			if( iter != dostepneZasobyPlanety_.end())
				return false;
			dostepneZasobyPlanety_.insert(make_pair(Indeks(identyfikator,poziom),ilosc));*/
		}
			
		tinyxml2::XMLElement* obiekt = wezel->FirstChildElement(WEZEL_XML_OBIEKTY);
		if(obiekt)
			for(tinyxml2::XMLElement* element = obiekt->FirstChildElement(); element ; element = element->NextSiblingElement()){
				Identyfikator identyfikator;
				Poziom poziom;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(element,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
					return false;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(element,ATRYBUT_XML_POZIOM,poziom))
					return false;
				if( !wybuduj(Indeks(identyfikator,poziom),element) )
					return false;
				auto iter = listaObiektow_.find(Indeks(identyfikator,poziom));
				if( iter == listaObiektow_.end())
					return false;
				if( iter->second->pobierzIdentyfikatorPlanety() != identyfikatorPlanety )
					return false;
			}
		tinyxml2::XMLElement* flota = wezel->FirstChildElement(WEZEL_XML_FLOTY);
		if(flota)
			for(tinyxml2::XMLElement* element = flota->FirstChildElement(); element ; element = element->NextSiblingElement()){
				Identyfikator identyfikator;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(element,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
					return false;
				shared_ptr<Flota> wskaznik = shared_ptr<Flota>(new Flota (identyfikator,Identyfikator(),Identyfikator(),Flota::CelPodrozy::Transport));
				auto iterator = listaFlot_.find(identyfikator);
				if( iterator != listaFlot_.end()|| !wskaznik->odczytaj(element) )
					return false;
				if(wskaznik->pobierzPlanetePoczatkowa() != identyfikatorPlanety)
					return false;
				Walidator::pobierzInstancje().dodajUzytyIdentyfikatorPlanety(wskaznik->pobierzPlanetePoczatkowa());
				Walidator::pobierzInstancje().dodajUzytyIdentyfikatorPlanety(wskaznik->pobierzPlaneteDocelowa());
				listaFlot_.insert(make_pair(wskaznik->pobierzIdentyfikator(),wskaznik));
			}
		return Bazowa::odczytaj(wezel);
	}
	return false;
}

Tekst Planeta::pobierzNazwePlanety() const{
	return nazwaPlanety_;
}

void Planeta::ustawNazwePlanety( const Tekst& nazwa ){
	nazwaPlanety_ = nazwa;
}

const Identyfikator& Planeta::pobierzIdUkladu() const{
	return idUkladu_;
}

void Planeta::ustawTemperature( const Temperatura& temperatura ){
	temperaturaPlanety_ = temperatura;
}

void Planeta::ustawSrednice( const Dystans& srednica ){
	srednicaPlanety_ = srednica;
}

void Planeta::ustawOdlegloscOdSrodkaUkladu( const Dystans& odleglosc ){
	odlegloscOdSlonca_ = odleglosc;
}

bool Planeta::wyliczPowierzchnie( const Fluktuacja& procentWody, const Fluktuacja& procentUzytkowa ){
	if( procentWody > Fluktuacja(Fluktuacja::MAX) || procentWody < Fluktuacja(Fluktuacja::MIN) || 
		procentUzytkowa > Fluktuacja(Fluktuacja::MAX) || procentUzytkowa < Fluktuacja(Fluktuacja::MIN) )
		return false;
	SPG::Powierzchnia calkowita = M_PI * srednicaPlanety_() * srednicaPlanety_();
	calkowitaPowierzchniaPlanety_(calkowita);
	powierzchniaZajetaPrzezWode_( calkowita * procentWody() );
	powierzchniaLadow_( calkowita * ( Fluktuacja::MAX - procentWody() ) );
	powierzchniaUzytkowaLadow_( powierzchniaLadow_() * procentUzytkowa() );
	return true;
}

string Planeta::napis() const{
	Logger str(NAZWAKLASY(Planeta));
	str.dodajKlase(Bazowa::napis());
	str.dodajPole(NAZWAKLASY(Licznik),licznikIdentyfikatorowFloty_);
	str.dodajPole("odlegloscOdSlonca",odlegloscOdSlonca_);
	//str.dodajPole("predkoscKatowaPlanety",predkoscKatowaPlanety_);
	//str.dodajPole("naslonecznieniePlanety",naslonecznieniePlanety_);
	str.dodajPole("idUkladu",idUkladu_);
	str.dodajPole("temperaturaPlanety",temperaturaPlanety_);
	str.dodajPole("calkowitaPowierzchniaPlanety",calkowitaPowierzchniaPlanety_);
	str.dodajPole("powierzchniaZajetaPrzezWode",powierzchniaZajetaPrzezWode_);
	str.dodajPole("powierzchniaLadow",powierzchniaLadow_);
	str.dodajPole("powierzchniaUzytkowaLadow",powierzchniaUzytkowaLadow_);
	str.dodajPole("nazwaPlanety",nazwaPlanety_);
	//for( auto element : dostepneZasobyPlanety_ )
	//	str.dodajPole("Zasob", element.second);
	for( auto element : listaObiektow_ )
		str.dodajPole("Obiekt", *(element.second));
	for( auto element : listaFlot_ )
		str.dodajPole("Flota", *(element.second));
	return str.napis();
}
