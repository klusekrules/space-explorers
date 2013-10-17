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

shared_ptr<Surowce> Gra::tworzSurowce( TiXmlElement* wezel )const{
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

shared_ptr<Statek> Gra::tworzStatek( TiXmlElement* wezel )const{
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
	TiXmlDocument dane;
	try{
		dane.LoadFile( adresPliku );
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
		aplikacja_.pobierzLogger().error(wyjatek.generujKomunikat());
		return false;
	}catch(exception& wyjatek){
		aplikacja_.pobierzLogger().error(wyjatek.what());
		return false;
	}
	return true;
}

bool Gra::wczytajTechnologie(TiXmlElement* wezel){
	try{
		TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_TECHNOLOGIA_INFO);
		do{
			if(element){
				shared_ptr<TechnologiaInfo> obiekt(new TechnologiaInfo(element));
				aplikacja_.pobierzLogger().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaTechnologiInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_TECHNOLOGIA_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().warn(wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().debug(wyjatek);
		return false;
	}
	return true;
}

bool Gra::wczytajBudynki(TiXmlElement* wezel){
	try{
		TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_BUDYNEK_INFO);
		do{
			if(element){
				shared_ptr<BudynekInfo> obiekt(new BudynekInfo(element));
				aplikacja_.pobierzLogger().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaBudynkowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_BUDYNEK_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().warn(wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().debug(wyjatek);
		return false;
	}
	return true;
}

bool Gra::wczytajSurowce(TiXmlElement* wezel){
	try{
		TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_SUROWCE_INFO);
		do{
			if(element){
				shared_ptr<SurowceInfo> obiekt(new SurowceInfo(element));
				aplikacja_.pobierzLogger().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaSurowcowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_SUROWCE_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().warn(wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().debug(wyjatek);
		return false;
	}
	return true;
}

bool Gra::wczytajObrone(TiXmlElement* wezel){
	try{
		TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_OBRONA_INFO);
		do{
			if(element){
				shared_ptr<ObronaInfo> obiekt(new ObronaInfo(element));
				aplikacja_.pobierzLogger().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaObronaInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_OBRONA_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.pobierzLogger().warn(wyjatek.generujKomunikat());
		aplikacja_.pobierzLogger().debug(wyjatek);
		return false;
	}
	return true;
}

bool Gra::wczytajStatki(TiXmlElement* wezel){
	try{
		TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_STATEK_INFO);
		do{
			if(element){
				shared_ptr<StatekInfo> obiekt(new StatekInfo(element));
				aplikacja_.pobierzLogger().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaStatkowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_STATEK_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& obiekt){
		aplikacja_.pobierzLogger().warn(obiekt.generujKomunikat());
		aplikacja_.pobierzLogger().debug(obiekt);
		return false;
	}
	return true;
}

bool Gra::zapisz( TiXmlElement* wezel ) const{
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_GRA);
	wezel->LinkEndChild( element );
	return zarzadca_.zapisz(element);
}

bool Gra::odczytaj( TiXmlElement* wezel ){
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
	auto dokument = plikUzytkownika(nazwa,hash,false);
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
	if(plikUzytkownika(nazwa,hash,false))
		return false;
	return plikUzytkownika(nazwa,hash);
}

bool Gra::usunGracza(const string& nazwa, const string& hash){
	auto dokument = plikUzytkownika(nazwa,hash,false);
	if( !dokument )
		return false;
	return !remove(dokument->Value());
}

bool Gra::zapisz( const string& nazwa, const string& hash ) const{
	auto dokument = plikUzytkownika(nazwa,hash);
	if( !dokument || !uzytkownik_->zapisz(dokument->RootElement()) )
		return false;
	return dokument->SaveFile();
}

shared_ptr<TiXmlDocument> Gra::plikUzytkownika(const string& nazwa, const string& hash , bool tworzPlik ) const{
	if( hash.empty() || nazwa.empty() )
		return nullptr;
	string plik("save\\");
	plik.append(nazwa);
	plik.append("_.xml");
	shared_ptr<TiXmlDocument> dokument = make_shared<TiXmlDocument>(plik);
	if(dokument->LoadFile()){
		if( hash!=XmlBO::WczytajAtrybut(dokument->RootElement(),"hash",string()))
			return nullptr;
		if(tworzPlik){
			dokument = make_shared<TiXmlDocument>(plik);
			TiXmlElement* uzytkownik = new TiXmlElement(WEZEL_XML_UZYTKOWNIK);
			uzytkownik->SetAttribute(ATRYBUT_XML_HASH,hash);
			uzytkownik->SetAttribute(ATRYBUT_XML_NAZWA,nazwa);
			dokument->LinkEndChild(uzytkownik);
			dokument->SaveFile(plik);
		}
	}else{
		if(!tworzPlik)
			return nullptr;
		TiXmlElement* uzytkownik = new TiXmlElement(WEZEL_XML_UZYTKOWNIK);
		uzytkownik->SetAttribute(ATRYBUT_XML_HASH,hash);
		uzytkownik->SetAttribute(ATRYBUT_XML_NAZWA,nazwa);
		dokument->LinkEndChild(uzytkownik);
		dokument->SaveFile(plik);
	}
	return dokument;
}
