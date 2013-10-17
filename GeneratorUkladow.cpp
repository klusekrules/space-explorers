#include "GeneratorUkladow.h"
#include "XmlBO.h"
#include "Gra.h"

const Identyfikator GeneratorUkladow::LICZNIK_PLANET_ID( 0x1 );
const Identyfikator GeneratorUkladow::LICZNIK_UKLADOW_ID( 0x2 );
const Identyfikator GeneratorUkladow::LICZNIK_GALAKTYK_ID( 0x3 );

const SPG::Dystans GeneratorUkladow::SREDNICA_GWIAZDY_MIN = 0.5;
const SPG::Dystans GeneratorUkladow::SREDNICA_GWIAZDY_MAX = 70.0;

const double GeneratorUkladow::SREDNICA_GWIAZDY_PARAM_ALFA = 3;
const double GeneratorUkladow::SREDNICA_GWIAZDY_PARAM_BETA = 2.5;

const SPG::Temperatura GeneratorUkladow::TEMPERATURA_GWIAZDY_MIN = 1700.0;
const SPG::Temperatura GeneratorUkladow::TEMPERATURA_GWIAZDY_MAX = 50000.0;

const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_SREDNICY = 0.78;
const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_STALY = 0.1;
const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_LOSOWY = 0.02;

const int GeneratorUkladow::ILOSC_PLANET_MIN = 2;
const int GeneratorUkladow::ILOSC_PLANET_MAX = 18;
const double GeneratorUkladow::ILOSC_PLANET_PARAM = 0.45;

const SPG::Dystans GeneratorUkladow::SREDNICA_PLANETY_MIN = 0.01;
const SPG::Dystans GeneratorUkladow::SREDNICA_PLANETY_MAX = 0.16;
const double GeneratorUkladow::SREDNICA_PLANETY_ODCHYLENIE = 0.7;
const double GeneratorUkladow::SREDNICA_PLANETY_PRZESUNIECIE = 2.5;
const double GeneratorUkladow::SREDNICA_PLANETY_ROZCIAGNIECIE = 386.0;

const SPG::Dystans GeneratorUkladow::ODLEGLOSC_MIEDZYPLANETARNA_MIN = 50.0;
const SPG::Dystans GeneratorUkladow::ODLEGLOSC_MIEDZYPLANETARNA_MAX = 300.0;

const SPG::Fluktuacja GeneratorUkladow::POWIERZCHNIA_UZYTKOWA_MIN = 0.1f;
const SPG::Fluktuacja GeneratorUkladow::POWIERZCHNIA_UZYTKOWA_MAX = 0.9f;

const SPG::Temperatura GeneratorUkladow::TEMPERATURA_PLANETY_MAX = 500;

const SPG::Fluktuacja GeneratorUkladow::POWIERZCHNIA_WODY_MAX = 0.9f;

#ifdef DEBUG

const int GeneratorUkladow::ILOSC_UKLADOW_MIN = 10;
const int GeneratorUkladow::ILOSC_UKLADOW_MAX = 100;

#else

const int GeneratorUkladow::ILOSC_UKLADOW_MIN = 1000;
const int GeneratorUkladow::ILOSC_UKLADOW_MAX = 10000;

#endif // DEBUG


GeneratorUkladow::GeneratorUkladow()
	: licznikIdPlanet(LICZNIK_PLANET_ID,Ilosc(1)), licznikIdUkladow(LICZNIK_UKLADOW_ID,Ilosc(1)), licznikIdGalaktyk(LICZNIK_GALAKTYK_ID,Ilosc(1)),
	dystrybutorSrednicyGwiazdy(SREDNICA_GWIAZDY_PARAM_ALFA,SREDNICA_GWIAZDY_PARAM_BETA), 
	dystrybutorIlosciPlanet( ILOSC_PLANET_MAX - ILOSC_PLANET_MIN , ILOSC_PLANET_PARAM ), 
	dystrybutorIlosciUkladow( ILOSC_UKLADOW_MIN , ILOSC_UKLADOW_MAX ),
	dystrybucjaPowierzchniUzytkowej(POWIERZCHNIA_UZYTKOWA_MIN,POWIERZCHNIA_UZYTKOWA_MAX)
{
	if( TEMPERATURA_GWIAZDY_PROCENT_SREDNICY + TEMPERATURA_GWIAZDY_PROCENT_STALY + TEMPERATURA_GWIAZDY_PROCENT_LOSOWY >= 1.0 || 
		TEMPERATURA_GWIAZDY_PROCENT_SREDNICY + TEMPERATURA_GWIAZDY_PROCENT_STALY + TEMPERATURA_GWIAZDY_PROCENT_LOSOWY <= 0.0 )
		throw exception("Invalid const params.");

	//TODO: Walidacja sta³ych, wyswietlanie sta³ych w logach.
}

GeneratorUkladow::~GeneratorUkladow()
{
}

shared_ptr<Galaktyka> GeneratorUkladow::generujGalaktyke() const{
	auto galaktyka = make_shared<Galaktyka>(Identyfikator(licznikIdGalaktyk()));
	galaktyka->iloscUkladow_= dystrybutorIlosciUkladow(generator);
	/*
	for(; iloscUkladow > 0 ; --iloscUkladow){
		auto uklad = generujUklad(galaktyka->pobierzIdentyfikator());
		galaktyka->dodajUklad(uklad);
	}*/
	return galaktyka;
}

shared_ptr<UkladSloneczny> GeneratorUkladow::generujUklad( const Identyfikator& idGalatyki ) const{
	auto uklad = make_shared<UkladSloneczny>(Identyfikator(licznikIdUkladow()),idGalatyki);

	uklad->ustawSredniceGwiazdy(generujSredniceGwiazdy());
	uklad->ustawSredniaTemperatureGwiazdy(generujTemperatureGwiazdy(uklad->pobierzSredniceGwiazdy()()));

	int iloscPlanet = ILOSC_PLANET_MIN + dystrybutorIlosciPlanet(generator);
	Moc mocGwiazdy = uklad->pobierzMocGwiazdy();	
	Dystans odlegloscOdSrodkaUkladu = uklad->pobierzSredniceGwiazdy() / 2.0 ;
	uniform_real_distribution<SPG::Dystans> dystrybutorOdleglosciMiedzyplanetarnej( ODLEGLOSC_MIEDZYPLANETARNA_MIN , ODLEGLOSC_MIEDZYPLANETARNA_MAX );

	for(  ; iloscPlanet > 0 ; --iloscPlanet ){
		odlegloscOdSrodkaUkladu += Dystans(dystrybutorOdleglosciMiedzyplanetarnej(generator));
		auto planeta = generujPlanete(odlegloscOdSrodkaUkladu,mocGwiazdy,uklad->pobierzIdentyfikator());
		uklad->dodajPlanete(planeta);
	}
	return uklad;
}

SPG::Temperatura GeneratorUkladow::generujTemperatureGwiazdy( SPG::Dystans srednica ) const{
	uniform_real_distribution<SPG::Temperatura> dystrybutorLosowejCzesciTemperatury( 0 , TEMPERATURA_GWIAZDY_PROCENT_LOSOWY );
	double procentLosowy = dystrybutorLosowejCzesciTemperatury(generator) - ( TEMPERATURA_GWIAZDY_PROCENT_LOSOWY / 2.0 );
	double procentSrednicy = (srednica/SREDNICA_GWIAZDY_MAX) * TEMPERATURA_GWIAZDY_PROCENT_SREDNICY;
	double procentZlozony = procentLosowy + procentSrednicy + TEMPERATURA_GWIAZDY_PROCENT_STALY;
	binomial_distribution<SPG::Temperatura> dystrybutorTemperatury(TEMPERATURA_GWIAZDY_MAX-TEMPERATURA_GWIAZDY_MIN, procentZlozony );
	SPG::Temperatura temperatura(dystrybutorTemperatury(generator));
	return temperatura;
}

SPG::Dystans GeneratorUkladow::generujSredniceGwiazdy() const{
	SPG::Dystans srednica = SREDNICA_GWIAZDY_MIN + dystrybutorSrednicyGwiazdy(generator);
	return srednica > SREDNICA_GWIAZDY_MAX ? SREDNICA_GWIAZDY_MAX  : srednica;
}

shared_ptr<Planeta> GeneratorUkladow::generujPlanete( const Dystans& odlegloscOdCentrum, const Moc& mocGwiazdy, const Identyfikator& idUkladu ) const{
	auto planeta = make_shared<Planeta>(Identyfikator(licznikIdPlanet()),idUkladu);
	auto srednica = generujSrednicePlanety(odlegloscOdCentrum);
	auto temperatura = generujTemperaturePlanety(odlegloscOdCentrum,mocGwiazdy);
	
	SPG::Fluktuacja procentWody = Fluktuacja::MIN;
	if( temperatura < 373.0 ){
		SPG::Fluktuacja temp = (static_cast<SPG::Fluktuacja>(temperatura) - 273.0f) / 100.0f;
		uniform_real_distribution<SPG::Fluktuacja> dystrybutorPowierzchniWody ( Fluktuacja::MIN , temp <= Fluktuacja::MIN || temp > POWIERZCHNIA_WODY_MAX ? POWIERZCHNIA_WODY_MAX : POWIERZCHNIA_WODY_MAX - temp );
		procentWody = dystrybutorPowierzchniWody(generator);
	}
	auto powierzchniaUzytkowa = dystrybucjaPowierzchniUzytkowej(generator);

	planeta->ustawSrednice( Dystans( srednica ) );
	planeta->ustawTemperature( Temperatura( temperatura ) );
	planeta->ustawOdlegloscOdSrodkaUkladu(odlegloscOdCentrum);
	planeta->wyliczPowierzchnie(Fluktuacja(procentWody),Fluktuacja(powierzchniaUzytkowa));
	return planeta;
}

SPG::Dystans GeneratorUkladow::generujSrednicePlanety( const Dystans& odlegloscOdCentrum ) const{
	double x = ( odlegloscOdCentrum() / SREDNICA_PLANETY_ROZCIAGNIECIE ) - SREDNICA_PLANETY_PRZESUNIECIE;
	SPG::Dystans d = SREDNICA_PLANETY_MIN + SREDNICA_PLANETY_MAX - SREDNICA_PLANETY_MIN * exp( - ( x * x ) ); 
	SPG::Dystans d_min = d - d * SREDNICA_PLANETY_ODCHYLENIE;
	SPG::Dystans d_max = d + d * SREDNICA_PLANETY_ODCHYLENIE;
	uniform_real_distribution<SPG::Dystans> dystrybutor(d_min,d_max);
	return dystrybutor(generator);
}

SPG::Temperatura GeneratorUkladow::generujTemperaturePlanety( const Dystans& odlegloscOdCentrum, const Moc& mocGwiazdy ) const{
	return TEMPERATURA_PLANETY_MAX + 200.0 * ( 1.0 / ( (-4 * mocGwiazdy()) / (odlegloscOdCentrum() * odlegloscOdCentrum()) - 0.5 )  );
}

bool GeneratorUkladow::zapisz( TiXmlElement* wezel ) const{
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_GENERATOR_UKLADOW);
	wezel->LinkEndChild( element );
	return licznikIdPlanet.zapisz(element) && licznikIdUkladow.zapisz(element) && licznikIdGalaktyk.zapisz(element);
}

bool GeneratorUkladow::odczytaj( TiXmlElement* wezel ){
	if(wezel){

		auto element = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_LICZNIK,ATRYBUT_XML_IDENTYFIKATOR,LICZNIK_PLANET_ID.napis());
		if(!licznikIdPlanet.odczytaj(element))
			return false;

		element = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_LICZNIK,ATRYBUT_XML_IDENTYFIKATOR,LICZNIK_UKLADOW_ID.napis());
		if(!licznikIdUkladow.odczytaj(element))
			return false;

		element = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_LICZNIK,ATRYBUT_XML_IDENTYFIKATOR,LICZNIK_GALAKTYK_ID.napis());
		if(!licznikIdGalaktyk.odczytaj(element))
			return false;
		
		return true;
	}
	return false;
}

string GeneratorUkladow::napis() const {
	Logger str(NAZWAKLASY(GeneratorUkladow));
	str.dodajPole("LicznikIDPlanet",licznikIdPlanet);
	str.dodajPole("LicznikIDUkladow",licznikIdUkladow);
	str.dodajPole("LicznikIDGalaktyk",licznikIdGalaktyk);
	return str.napis();
}
