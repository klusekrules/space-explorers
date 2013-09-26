#include "Planeta.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"
#include "Walidator.h"

Planeta::Planeta(const Identyfikator& identyfikator)
	: Bazowa(identyfikator), wlasciciel_(nullptr),
	pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),Identyfikator(0),Wymagania(nullptr)) , Poziom(0) )
{
	pustyObiektBase = shared_ptr<ObiektBazowy>(new ObiektBazowy( Ilosc(0), Poziom(0),Identyfikator(0), pustyobiekBaseInfo ));
}

Planeta::~Planeta(void)
{
}

void Planeta::ustawWlasciciela( Uzytkownik* wlasciciel ){
	wlasciciel_=wlasciciel;
	odswiezNazweUzytkownika();
}

Uzytkownik* Planeta::pobierzWlasciciela( void ) const{
	return wlasciciel_;
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
	return *pustyObiektBase;
}

const ObiektBazowy& Planeta::pobierzObiekt(const Identyfikator& identyfikator) const{
	auto iterator = listaObiektow_.end();
	for( auto element = listaObiektow_.begin() ; element != listaObiektow_.end() ; ++element ){
		if( element->first.pobierzIdentyfikator() == identyfikator && ( iterator == listaObiektow_.end() || (iterator != listaObiektow_.end() && iterator->first.pobierzPoziom()<element->first.pobierzPoziom() ) )){
				iterator = element;
		}
	}
	return iterator == listaObiektow_.end() ? *pustyObiektBase : *(iterator->second);
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

bool Planeta::wybuduj( const Indeks& identyfikator, TiXmlElement* wezel ){
	if(pobierzObiekt(identyfikator).pobierzIdentyfikator() != Identyfikator())
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

bool Planeta::zapisz( TiXmlElement* wezel ) const{
	TiXmlElement* planeta = new TiXmlElement(WEZEL_XML_PLANETA);
	wezel->LinkEndChild( planeta );
	planeta->SetAttribute(ATRYBUT_XML_ODLEGLOSC_OD_SLONCA, odlegloscOdSlonca_.napis());
	planeta->SetAttribute(ATRYBUT_XML_PREDKOSC_KATOWA_PLANETY, predkoscKatowaPlanety_.napis());
	planeta->SetAttribute(ATRYBUT_XML_NASLONECZNIENIE_PLANETY, naslonecznieniePlanety_.napis());
	planeta->SetAttribute(ATRYBUT_XML_WIETRZNOSC_PLANETY, wietrznoscPlanety_.napis());
	planeta->SetAttribute(ATRYBUT_XML_TEMPERATURA_PLANETY, temperaturaPlanety_.napis());
	planeta->SetAttribute(ATRYBUT_XML_CALKOWITA_POWIERZNIA_PLANETY, calkowitaPowierzchniaPlanety_.napis() );
	planeta->SetAttribute(ATRYBUT_XML_POWIERZCHNIA_ZAJETA_PRZEZ_WODE,powierzchniaZajetaPrzezWode_.napis() );
	planeta->SetAttribute(ATRYBUT_XML_POWIERZCHNIA_LADOW, powierzchniaLadow_.napis() );
	planeta->SetAttribute(ATRYBUT_XML_POWIERZCHNIA_UZYTKOWA_LADOW, powierzchniaUzytkowaLadow_.napis() );
	planeta->SetAttribute(ATRYBUT_XML_NAZWA, nazwaPlanety_());
	licznikIdentyfikatorowFloty_.zapisz(planeta);
	for(auto element :  dostepneZasobyPlanety_){
		TiXmlElement* zasob = new TiXmlElement(WEZEL_XML_ZASOB);
		zasob->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR, element.first.pobierzIdentyfikator().napis());
		zasob->SetAttribute(ATRYBUT_XML_POZIOM, element.first.pobierzPoziom().napis());
		zasob->SetAttribute(ATRYBUT_XML_ILOSC, element.second.napis());
		planeta->LinkEndChild(zasob);
	}
	TiXmlElement* obiekty = new TiXmlElement(WEZEL_XML_OBIEKTY);
	planeta->LinkEndChild( obiekty );
	for(auto element :  listaObiektow_)
		if(!element.second->zapisz(obiekty))
			return false;
	TiXmlElement* floty = new TiXmlElement(WEZEL_XML_FLOTY);
	planeta->LinkEndChild( floty );
	for(auto element :  listaFlot_)
		if(!element.second->zapisz(floty))
			return false;
	return Bazowa::zapisz(planeta);
}

bool Planeta::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		Identyfikator identyfikatorPlanety;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_ODLEGLOSC_OD_SLONCA,odlegloscOdSlonca_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_PREDKOSC_KATOWA_PLANETY,predkoscKatowaPlanety_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NASLONECZNIENIE_PLANETY,naslonecznieniePlanety_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_WIETRZNOSC_PLANETY,wietrznoscPlanety_))
			return false;
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
		for(TiXmlElement* zasob = wezel->FirstChildElement(WEZEL_XML_ZASOB); zasob ; zasob = zasob->NextSiblingElement(WEZEL_XML_ZASOB)){
			Identyfikator identyfikator;
			Poziom poziom;
			Ilosc ilosc;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(zasob,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
				return false;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(zasob,ATRYBUT_XML_POZIOM,poziom))
				return false;
			if(!XmlBO::WczytajAtrybut<NOTHROW>(zasob,ATRYBUT_XML_ILOSC,ilosc))
				return false;
			auto iter = dostepneZasobyPlanety_.find(Indeks(identyfikator,poziom));
			if( iter != dostepneZasobyPlanety_.end())
				return false;
			dostepneZasobyPlanety_.insert(make_pair(Indeks(identyfikator,poziom),ilosc));
		}
			
		TiXmlElement* obiekt = wezel->FirstChildElement(WEZEL_XML_OBIEKTY);
		if(obiekt)
			for(TiXmlElement* element = obiekt->FirstChildElement(); element ; element = element->NextSiblingElement()){
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
		TiXmlElement* flota = wezel->FirstChildElement(WEZEL_XML_FLOTY);
		if(flota)
			for(TiXmlElement* element = flota->FirstChildElement(); element ; element = element->NextSiblingElement()){
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
	if(sygnatura_)
		sygnatura_->ustawNazwePlanety(nazwa);
}

void Planeta::odswiezNazweUzytkownika(){
	if(sygnatura_)
		sygnatura_->ustawNazweGracza(wlasciciel_ ? wlasciciel_->pobierzNazweUzytkownika() : Tekst());
}

shared_ptr<SygnaturaPlanety> Planeta::pobierzSygnature() const{
	if(sygnatura_)
		return sygnatura_;
	sygnatura_ = make_shared<SygnaturaPlanety>( pobierzIdentyfikator() , wlasciciel_ ? wlasciciel_->pobierzNazweUzytkownika() : Tekst() , pobierzNazwePlanety() );
	return sygnatura_;
}

bool Planeta::ustawSygnature( shared_ptr<SygnaturaPlanety> sygnatura ){
	if(sygnatura_)
		return sygnatura_==sygnatura;
	sygnatura_ = sygnatura;
	return true;
}

string Planeta::napis() const{
	Logger str(NAZWAKLASY(Planeta));
	str.dodajKlase(Bazowa::napis());
	str.dodajPole(NAZWAKLASY(Licznik),licznikIdentyfikatorowFloty_);
	str.dodajPole("odlegloscOdSlonca",odlegloscOdSlonca_);
	str.dodajPole("predkoscKatowaPlanety",predkoscKatowaPlanety_);
	str.dodajPole("naslonecznieniePlanety",naslonecznieniePlanety_);
	str.dodajPole("wietrznoscPlanety",wietrznoscPlanety_);
	str.dodajPole("temperaturaPlanety",temperaturaPlanety_);
	str.dodajPole("calkowitaPowierzchniaPlanety",calkowitaPowierzchniaPlanety_);
	str.dodajPole("powierzchniaZajetaPrzezWode",powierzchniaZajetaPrzezWode_);
	str.dodajPole("powierzchniaLadow",powierzchniaLadow_);
	str.dodajPole("powierzchniaUzytkowaLadow",powierzchniaUzytkowaLadow_);
	str.dodajPole("nazwaPlanety",nazwaPlanety_);
	for( auto element : dostepneZasobyPlanety_ )
		str.dodajPole("Zasob", element.second);
	for( auto element : listaObiektow_ )
		str.dodajPole("Obiekt", *(element.second));
	for( auto element : listaFlot_ )
		str.dodajPole("Flota", *(element.second));
	return str.napis();
}
