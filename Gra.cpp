#include "Gra.h"
#include "Aplikacja.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"
#include <iostream>
#include <fstream>
#include "Walidator.h"

Gra::Gra(Aplikacja& aplikacja)
	: aplikacja_(aplikacja), fabryka_(ZmianaFabryka::pobierzInstancje()), uzytkownik_(nullptr)
{
}

Gra::Gra(const Gra& gra)
	: aplikacja_(gra.aplikacja_), fabryka_(ZmianaFabryka::pobierzInstancje()),uzytkownik_(gra.uzytkownik_)
{
}

Gra& Gra::operator=(const Gra& gra){
	return *this;
}

ZmianaFabryka& Gra::pobierzFabrykeZmian() const{
	return fabryka_;
}

bool Gra::przeniesPlaneteDoUzytkownika( const Identyfikator& identyfikator ){
	auto planeta = zarzadca_.pobierzPlanete(identyfikator);
	if(!planeta)
		return false;
	return uzytkownik_->dodajPlanete(planeta);
}

int Gra::pobierzIloscGalaktyk() const{
	return zarzadca_.pobierzIloscGalaktyk();
}

bool Gra::generujNowaGalaktyke(){
	return zarzadca_.generujNowaGalaktyke();
}

shared_ptr<Surowce> Gra::tworzSurowce( tinyxml2::XMLElement* wezel )const{
	Identyfikator identyfikator;
	if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
		return nullptr;
	auto obiektOpisowy = listaSurowcowInfo_.find(identyfikator);
	if( obiektOpisowy == listaSurowcowInfo_.end() )
		return nullptr;
	shared_ptr<Surowce> obiekt = shared_ptr<Surowce>(obiektOpisowy->second->tworzEgzemplarz(Ilosc(0),Identyfikator(0)));
	if(!obiekt || !obiekt->odczytaj(wezel))
		return nullptr;
	return obiekt;
}

shared_ptr<Statek> Gra::tworzStatek( tinyxml2::XMLElement* wezel )const{
	Identyfikator identyfikator;
	if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
		return nullptr;
	auto obiektOpisowy = listaStatkowInfo_.find(identyfikator);
	if( obiektOpisowy == listaStatkowInfo_.end() )
		return nullptr;
	shared_ptr<Statek> obiekt = shared_ptr<Statek>(obiektOpisowy->second->tworzEgzemplarz(Ilosc(0),Identyfikator(0)));
	if(!obiekt || !obiekt->odczytaj(wezel))
		return nullptr;
	return obiekt;
}

Gra::~Gra()
{
}

Uzytkownik& Gra::pobierzUzytkownika() const throw (NieznalezionoObiektu) {
	if(!uzytkownik_)
		throw NieznalezionoObiektu(EXCEPTION_PLACE,Tekst("Uzytkownik"));
	return *uzytkownik_;
}

shared_ptr<Planeta> Gra::pobierzPlanete( const Identyfikator& identyfikator ){
	return zarzadca_.pobierzPlanete(identyfikator);
}

bool Gra::wybudujNaPlanecie( Planeta& planeta , const Identyfikator& identyfikator , const Ilosc& ilosc, const Poziom& poziom )const{
	auto iterator = listaObiektowBaseInfo_.find(identyfikator);
	if(iterator != listaObiektowBaseInfo_.end()){
		return iterator->second->tworz(*this,planeta,ilosc, poziom);
	}
	return false;
}

bool Gra::wybudujNaPlanecie( Planeta& planeta , const Identyfikator& identyfikator , const Ilosc& ilosc )const{
	auto iterator = listaObiektowBaseInfo_.find(identyfikator);
	if(iterator != listaObiektowBaseInfo_.end()){
		return iterator->second->tworz(*this,planeta,ilosc, iterator->second->pobierzPoziom());
	}
	return false;
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const ObiektBazowyInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const{
	return obiektInfo.tworz(*this,planeta,ilosc,poziom);
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const BudynekInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const{
	return planeta.dodajObiekt(shared_ptr<Budynek>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator(),poziom)));
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const TechnologiaInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const{
	return planeta.dodajObiekt(shared_ptr<Technologia>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator(),poziom)));
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const StatekInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const{
	return planeta.dodajObiekt(shared_ptr<Statek>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator(),poziom)));
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const SurowceInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const{
	return planeta.dodajObiekt(shared_ptr<Surowce>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator(),poziom)));
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const ObronaInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const{
	return planeta.dodajObiekt(shared_ptr<Obrona>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator(),poziom)));
}

StatekInfo& Gra::pobierzStatek(const Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
	auto iterator = listaStatkowInfo_.find(identyfikator);
	if(iterator==listaStatkowInfo_.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
	return *(iterator->second);
}

SurowceInfo& Gra::pobierzSurowce(const Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
	auto iterator = listaSurowcowInfo_.find(identyfikator);
	if(iterator==listaSurowcowInfo_.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
	return *(iterator->second);
}

TechnologiaInfo& Gra::pobierzTechnologia(const Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
	auto iterator = listaTechnologiInfo_.find(identyfikator);
	if(iterator==listaTechnologiInfo_.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
	return *(iterator->second);
}

BudynekInfo& Gra::pobierzBudynek(const Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
	auto iterator = listaBudynkowInfo_.find(identyfikator);
	if(iterator==listaBudynkowInfo_.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
	return *(iterator->second);
}

ObiektInfo& Gra::pobierzObiekt(const Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
	auto iterator = listaObiektowInfo_.find(identyfikator);
	if(iterator==listaObiektowInfo_.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
	return *(iterator->second);
}

ObronaInfo& Gra::pobierzObrone(const Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
	auto iterator = listaObronaInfo_.find(identyfikator);
	if(iterator==listaObronaInfo_.end())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,identyfikator.napis());
	return *(iterator->second);
}

bool Gra::wczytajDane( const string& adresPliku ){
	tinyxml2::XMLDocument dane;
	try{
		dane.LoadFile( adresPliku.c_str() );
		auto root_data = dane.FirstChildElement(WEZEL_XML_ROOT);
		if(root_data){
			if(!wczytajSurowce(root_data))
				return false;
			if(!wczytajStatki(root_data))
				return false;
			if(!wczytajObrone(root_data))
				return false;
			if(!wczytajTechnologie(root_data))
				return false;
			if(!wczytajBudynki(root_data))
				return false;
		}
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().loguj(Log::Error,wyjatek.generujKomunikat());
		return false;
	}catch(exception& wyjatek){
		aplikacja_.pobierzLogger().loguj(Log::Error,wyjatek.what());
		return false;
	}
	return true;
}

bool Gra::wczytajTechnologie(tinyxml2::XMLElement* wezel){
	try{
		tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_TECHNOLOGIA_INFO);
		do{
			if(element){
				shared_ptr<TechnologiaInfo> obiekt(new TechnologiaInfo(element));
				aplikacja_.pobierzLogger().loguj(Log::Debug,*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaTechnologiInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_TECHNOLOGIA_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().loguj(Log::Warning,wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().loguj(Log::Debug,wyjatek);
		return false;
	}
	return true;
}

bool Gra::wczytajBudynki(tinyxml2::XMLElement* wezel){
	try{
		tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_BUDYNEK_INFO);
		do{
			if(element){
				shared_ptr<BudynekInfo> obiekt(new BudynekInfo(element));
				aplikacja_.pobierzLogger().loguj(Log::Debug,*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaBudynkowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_BUDYNEK_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().loguj(Log::Warning,wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().loguj(Log::Debug,wyjatek);
		return false;
	}
	return true;
}

bool Gra::wczytajSurowce(tinyxml2::XMLElement* wezel){
	try{
		tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_SUROWCE_INFO);
		do{
			if(element){
				shared_ptr<SurowceInfo> obiekt(new SurowceInfo(element));
				aplikacja_.pobierzLogger().loguj(Log::Debug,*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaSurowcowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_SUROWCE_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().loguj(Log::Warning,wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().loguj(Log::Debug,wyjatek);
		return false;
	}
	return true;
}

bool Gra::wczytajObrone(tinyxml2::XMLElement* wezel){
	try{
		tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_OBRONA_INFO);
		do{
			if(element){
				shared_ptr<ObronaInfo> obiekt(new ObronaInfo(element));
				aplikacja_.pobierzLogger().loguj(Log::Debug,*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaObronaInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_OBRONA_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().loguj(Log::Warning,wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().loguj(Log::Debug,wyjatek);
		return false;
	}
	return true;
}

bool Gra::wczytajStatki(tinyxml2::XMLElement* wezel){
	try{
		tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_STATEK_INFO);
		do{
			if(element){
				shared_ptr<StatekInfo> obiekt(new StatekInfo(element));
				aplikacja_.pobierzLogger().loguj(Log::Debug,*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaStatkowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_STATEK_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().loguj(Log::Warning,wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().loguj(Log::Debug,wyjatek);
		return false;
	}
	return true;
}

bool Gra::zapisz( tinyxml2::XMLElement* wezel ) const{
	tinyxml2::XMLElement* element = wezel->GetDocument()->NewElement(WEZEL_XML_GRA);
	wezel->LinkEndChild( element );
	return zarzadca_.zapisz(element);
}

bool Gra::odczytaj( tinyxml2::XMLElement* wezel ){
	if(wezel){
		auto element = XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_ZARZADCA);
		if(element)
			return zarzadca_.odczytaj(element);	
		return true;
	}
	return false;
}

bool Gra::odczytaj( const string& nazwa, const string& hash ){
	return logowanie(nazwa,hash);
}

bool Gra::logowanie(const string& nazwa, const string& hash){
	std::string plik;
	auto dokument = plikUzytkownika(nazwa,hash,plik,false);
	if( !dokument )
		return false;
	auto nowyUzytkownik = make_shared<Uzytkownik>(*this);
	if(nowyUzytkownik->odczytaj(dokument->RootElement()) && Walidator::pobierzInstancje().waliduj())
		uzytkownik_ = nowyUzytkownik;
	else
		return false;
	return true;
}

bool Gra::nowyGracz(const string& nazwa, const string& hash){
	std::string plik;
	if(plikUzytkownika(nazwa,hash,plik,false))
		return false;
	return plikUzytkownika(nazwa,hash,plik);
}

bool Gra::usunGracza(const string& nazwa, const string& hash){
	std::string plik;
	auto dokument = plikUzytkownika(nazwa,hash,plik,false);
	if( !dokument )
		return false;
	return !remove(dokument->Value());
}

bool Gra::zapisz( const string& nazwa, const string& hash ) const{
	std::string plik;
	auto dokument = plikUzytkownika(nazwa,hash,plik);
	if( !dokument || !uzytkownik_->zapisz(dokument->RootElement()) )
		return false;
	return dokument->SaveFile(plik.c_str());
}

shared_ptr<tinyxml2::XMLDocument> Gra::plikUzytkownika(const string& nazwa, const string& hash, string& nazwaPliku , bool tworzPlik ) const{
	if( hash.empty() || nazwa.empty() )
		return nullptr;
	string plik("save\\");
	plik.append(nazwa);
	plik.append("_.xml");
	shared_ptr<tinyxml2::XMLDocument> dokument = make_shared<tinyxml2::XMLDocument>();
	if(dokument->LoadFile(plik.c_str())==tinyxml2::XML_NO_ERROR){
		if( hash!=XmlBO::WczytajAtrybut(dokument->RootElement(),"hash",string()))
			return nullptr;
		if(tworzPlik){
			dokument = make_shared<tinyxml2::XMLDocument>();
			dokument->LoadFile(plik.c_str());
			tinyxml2::XMLElement* uzytkownik = dokument->NewElement(WEZEL_XML_UZYTKOWNIK);
			uzytkownik->SetAttribute(ATRYBUT_XML_HASH,hash.c_str());
			uzytkownik->SetAttribute(ATRYBUT_XML_NAZWA,nazwa.c_str());
			dokument->LinkEndChild(uzytkownik);
			dokument->SaveFile(plik.c_str());
		}
	}else{
		if(!tworzPlik)
			return nullptr;
		tinyxml2::XMLElement* uzytkownik = dokument->NewElement(WEZEL_XML_UZYTKOWNIK);
		uzytkownik->SetAttribute(ATRYBUT_XML_HASH,hash.c_str());
		uzytkownik->SetAttribute(ATRYBUT_XML_NAZWA,nazwa.c_str());
		dokument->LinkEndChild(uzytkownik);
		dokument->SaveFile(plik.c_str());
	}
	return dokument;
}
