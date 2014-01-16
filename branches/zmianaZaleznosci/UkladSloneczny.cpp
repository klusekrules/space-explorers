#include "UkladSloneczny.h"
#include <random>
#include "Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

UkladSloneczny::UkladSloneczny( const Identyfikator& id , const Identyfikator& idGalaktyki )
	: Bazowa(id), idGalaktyki_(idGalaktyki)
{
}

UkladSloneczny::~UkladSloneczny()
{
}

void UkladSloneczny::ustawSredniceGwiazdy(SPG::Dystans srednica){
	srednicaGwiazdy_(srednica);
}

const Dystans& UkladSloneczny::pobierzSredniceGwiazdy() const{
	return srednicaGwiazdy_;
}

void UkladSloneczny::ustawSredniaTemperatureGwiazdy(SPG::Temperatura temperatura){
	sredniaTemperaturaGwiazdy_(temperatura);
}

const Temperatura& UkladSloneczny::pobierzSredniaTemperatureGwiazdy() const{
	return sredniaTemperaturaGwiazdy_;
}

Moc UkladSloneczny::pobierzMocGwiazdy() const{
	return Moc(srednicaGwiazdy_()*sredniaTemperaturaGwiazdy_());
}

bool UkladSloneczny::dodajPlanete( UkladSloneczny::Planeta planeta ){
	if( !planeta || planety_.find(planeta->pobierzIdentyfikator()) != planety_.end() )
		return false;
	planety_[planeta->pobierzIdentyfikator()] = planeta;
	return true;
}

UkladSloneczny::Planeta UkladSloneczny::pobierzPlanete( const Identyfikator& numer ){
	return planety_[numer];
}

int UkladSloneczny::liczbaPlanet() const{
	return static_cast<int>( planety_.size() );
}

const Identyfikator& UkladSloneczny::pobierzIdGalaktyki() const{
	return idGalaktyki_;
}

bool UkladSloneczny::zapisz( tinyxml2::XMLElement* wezel ) const{
	tinyxml2::XMLElement* element = wezel->GetDocument()->NewElement(WEZEL_XML_UKLAD_SLONECZNY);
	wezel->LinkEndChild( element );
	element->SetAttribute(ATRYBUT_XML_SREDNICA_GWIAZDY, srednicaGwiazdy_.napis().c_str());
	element->SetAttribute(ATRYBUT_XML_SREDNIA_TEMPERATURA_GWIAZDY, sredniaTemperaturaGwiazdy_.napis().c_str());
	for(auto planeta :  planety_)
		if(!planeta.second->zapisz(element))
			return false;
	return Bazowa::zapisz(element);
}

bool UkladSloneczny::odczytaj( tinyxml2::XMLElement* wezel ){
	if(wezel){
		if(!Bazowa::odczytaj(wezel))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_SREDNICA_GWIAZDY,srednicaGwiazdy_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_SREDNIA_TEMPERATURA_GWIAZDY,sredniaTemperaturaGwiazdy_))
			return false;
		for(tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_PLANETA) ; element ; element = element->NextSiblingElement(WEZEL_XML_PLANETA)){
			auto planeta = make_shared<::Planeta>(Identyfikator(),pobierzIdentyfikator());
			if(!planeta->odczytaj(element))
				return false;
			planety_[planeta->pobierzIdentyfikator()] =planeta;
		}
		return true; 
	}
	return false;
}

string UkladSloneczny::napis() const {
	Logger str(NAZWAKLASY(UkladSloneczny));
	str.dodajKlase(Bazowa::napis());
	str.dodajPole("srednicaGwiazdy",srednicaGwiazdy_);
	str.dodajPole("sredniaTemperaturaGwiazdy",sredniaTemperaturaGwiazdy_);
	for( auto planeta : planety_ ){
		if(planeta.second){
			str.dodajPole("Planeta",*planeta.second);
		}
	}
	return str.napis();
}
