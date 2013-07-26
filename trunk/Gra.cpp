#include "Gra.h"
#include "Aplikacja.h"
#include "DefinicjeWezlowXML.h"

Gra::Gra(Aplikacja& aplikacja)
	: aplikacja_(aplikacja), fabryka_(ZmianaFabryka::pobierzInstancje()), uzytkownik_(new Uzytkownik(*this))
{
	licznikIdentyfikatorowPlanet_.ustawWartosc(Ilosc(1));
}

Gra::Gra(const Gra& gra)
	: aplikacja_(gra.aplikacja_), fabryka_(ZmianaFabryka::pobierzInstancje()),uzytkownik_(gra.uzytkownik_), licznikIdentyfikatorowPlanet_(gra.licznikIdentyfikatorowPlanet_)
{
}

Gra& Gra::operator=(const Gra& gra){
	return *this;
}

ZmianaFabryka& Gra::pobierzFabrykeZmian() const{
	return fabryka_;
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
	auto iterator = wszystkiePlanety_.find(identyfikator);
	if(iterator!=wszystkiePlanety_.end())
		return iterator->second;
	return nullptr;
}

//TODO: Dopisanie poprawnego logowania
bool Gra::logowanie(const string& nazwa, const string& hash){
	uzytkownik_ = shared_ptr<Uzytkownik>(new Uzytkownik(*this));
	return true;
}
//TODO: Dopisanie poprawnego generowania planet
shared_ptr<Planeta> Gra::stworzPlanete(){
	auto planeta = shared_ptr<Planeta>( new Planeta(Identyfikator(licznikIdentyfikatorowPlanet_())));
	wolnePlanety_.insert(make_pair(planeta->pobierzIdentyfikator(),planeta));
	wszystkiePlanety_.insert(make_pair(planeta->pobierzIdentyfikator(),planeta));
	return planeta;
}

bool Gra::przeniesPlaneteDoUzytkownika( const Identyfikator& identyfikator ){
	if(!uzytkownik_)
		return false;
	auto iterator = wolnePlanety_.find(identyfikator);
	if(iterator==wolnePlanety_.end())
		return false;
	if(uzytkownik_->dodajPlanete(iterator->second)){
		wolnePlanety_.erase(iterator);
		return true;
	}
	return false;
}

bool Gra::wybudujNaPlanecie( Planeta& planeta , const Identyfikator& identyfikator , const Ilosc& ilosc )const{
	auto iterator = listaObiektowBaseInfo_.find(identyfikator);
	if(iterator != listaObiektowBaseInfo_.end()){
		return iterator->second->tworz(*this,planeta,ilosc);
	}
	return false;
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const ObiektBazowyInfo& obiektInfo, const Ilosc& ilosc )const{
	return obiektInfo.tworz(*this,planeta,ilosc);
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const BudynekInfo& obiektInfo, const Ilosc& ilosc )const{
	return planeta.dodajObiekt(shared_ptr<Budynek>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator())));
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const TechnologiaInfo& obiektInfo, const Ilosc& ilosc )const{
	return planeta.dodajObiekt(shared_ptr<Technologia>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator())));
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const StatekInfo& obiektInfo, const Ilosc& ilosc )const{
	return planeta.dodajObiekt(shared_ptr<Statek>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator())));
}

bool Gra::wybudujNaPlanecie( Planeta& planeta, const SurowceInfo& obiektInfo, const Ilosc& ilosc )const{
	return planeta.dodajObiekt(shared_ptr<Surowce>(obiektInfo.tworzEgzemplarz(ilosc,planeta.pobierzIdentyfikator())));
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
			if(!wczytajTechnologie(root_data))
				return false;
			if(!wczytajBudynki(root_data))
				return false;
		}
	}catch(ticpp::Exception& wyjatek){
		cout<< wyjatek.what();
		aplikacja_.getLog().error("Nie uda³o siê otworzyæ pliku!");
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
				aplikacja_.getLog().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaTechnologiInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_TECHNOLOGIA_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.getLog().warn(wyjatek.generujKomunikat());
		aplikacja_.getLog().debug(wyjatek);
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
				aplikacja_.getLog().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaBudynkowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_BUDYNEK_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.getLog().warn(wyjatek.generujKomunikat());
		aplikacja_.getLog().debug(wyjatek);
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
				aplikacja_.getLog().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaSurowcowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_SUROWCE_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& wyjatek){
		aplikacja_.getLog().warn(wyjatek.generujKomunikat());
		aplikacja_.getLog().debug(wyjatek);
		return false;
	}
	return true;
}

bool Gra::dodajPlanete( shared_ptr<Planeta> planeta ){
	if(wszystkiePlanety_.find(planeta->pobierzIdentyfikator()) == wszystkiePlanety_.end()){
		wszystkiePlanety_.insert(make_pair(planeta->pobierzIdentyfikator(), planeta));
		if(!planeta->czyMaWlasciciela())
			wolnePlanety_.insert(make_pair(planeta->pobierzIdentyfikator(), planeta));
		return true;
	}
	return false;
}


bool Gra::wczytajStatki(TiXmlElement* wezel){
	try{
		TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_STATEK_INFO);
		do{
			if(element){
				shared_ptr<StatekInfo> obiekt(new StatekInfo(element));
				aplikacja_.getLog().debug(*obiekt);
				if(listaObiektowBaseInfo_.find(obiekt->pobierzIdentyfikator())!=listaObiektowBaseInfo_.end())
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("B³¹d wczytywania danych"),Tekst("Obiekt o podanym id istnieje"));
				listaStatkowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowBaseInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()]=obiekt;
				element = element->NextSiblingElement(WEZEL_XML_STATEK_INFO);
			}
		}while(element);
	}catch(OgolnyWyjatek& obiekt){
		aplikacja_.getLog().warn(obiekt.generujKomunikat());
		aplikacja_.getLog().debug(obiekt);
		return false;
	}
	return true;
}

bool Gra::zapisz( TiXmlElement* wezel ) const{
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_GRA);
	wezel->LinkEndChild( element );
	for(auto planeta :  wolnePlanety_)
		if(!planeta.second->zapisz(element))
			return false;
	return licznikIdentyfikatorowPlanet_.zapisz(element) && ( uzytkownik_ ? uzytkownik_->zapisz(element) : true );
}

bool Gra::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		if(!licznikIdentyfikatorowPlanet_.odczytaj(wezel->FirstChildElement(WEZEL_XML_LICZNIK)))
			return false;
		TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_UZYTKOWNIK);
		if(element){
			uzytkownik_ = shared_ptr<Uzytkownik>(new Uzytkownik(*this));
			if(!uzytkownik_->odczytaj(element))
				return false;
		}else{
			uzytkownik_ = nullptr;
		}
		for(element = wezel->FirstChildElement(WEZEL_XML_PLANETA); element ; element = element->NextSiblingElement(WEZEL_XML_PLANETA)){
			auto planeta = shared_ptr<Planeta>( new Planeta(Identyfikator()) );
			if(!planeta->odczytaj(element))
				return false;
			wolnePlanety_.insert(make_pair(planeta->pobierzIdentyfikator(),planeta));
			wszystkiePlanety_.insert(make_pair(planeta->pobierzIdentyfikator(),planeta));
		}
		return true;	
	}
	return false;
}
