#include "UkladSloneczny.h"
#include <random>
#include "Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

UkladSloneczny::UkladSloneczny( const Identyfikator& id )
	: Bazowa(id)
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

bool UkladSloneczny::dodajPlanete( UkladSloneczny::Sygnatura planeta ){
	if( !planeta || find(planety_.begin(),planety_.end(),planeta) != planety_.end() )
		return false;
	planety_.push_back(planeta);
	return true;
}

UkladSloneczny::Sygnatura UkladSloneczny::pobierzPlanete( int numer ) const{
	return planety_.at(numer);
}

int UkladSloneczny::liczbaPlanet() const{
	return static_cast<int>( planety_.size() );
}

bool UkladSloneczny::zapisz( TiXmlElement* wezel ) const{
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_UKLAD_SLONECZNY);
	wezel->LinkEndChild( element );
	element->SetAttribute(ATRYBUT_XML_SREDNICA_GWIAZDY, srednicaGwiazdy_.napis());
	element->SetAttribute(ATRYBUT_XML_SREDNIA_TEMPERATURA_GWIAZDY, sredniaTemperaturaGwiazdy_.napis());
	for(auto sygnatura :  planety_)
		if(!sygnatura->zapisz(element))
			return false;
	return Bazowa::zapisz(element);
}

bool UkladSloneczny::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_SREDNICA_GWIAZDY,srednicaGwiazdy_))
			return false;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_SREDNIA_TEMPERATURA_GWIAZDY,sredniaTemperaturaGwiazdy_))
			return false;
		SygnaturaPlanety sygnatura;
		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_SYGNATURA_PLANETY) ; element ; element = element->NextSiblingElement(WEZEL_XML_SYGNATURA_PLANETY)){
			if(!sygnatura.odczytaj(element))
				return false;
			planety_.push_back(sygnatura.pobierzOryginalnyWskaznik());
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
	for( auto a : planety_ ){
		if(a){
			str.dodajPole("Planeta",*a);
		}
	}
	return str.napis();
}
