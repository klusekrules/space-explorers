#pragma once
#include <random>
#include "UkladSloneczny.h"
#include "Planeta.h"
#include "Licznik.h"

using namespace std;

class GeneratorUkladow
{
public:
	const static SPG::Dystans SREDNICA_GWIAZDY_MIN;
	const static SPG::Dystans SREDNICA_GWIAZDY_MAX;
	const static double SREDNICA_GWIAZDY_PARAM_ALFA;
	const static double SREDNICA_GWIAZDY_PARAM_BETA;

	const static SPG::Temperatura TEMPERATURA_GWIAZDY_MIN;
	const static SPG::Temperatura TEMPERATURA_GWIAZDY_MAX;
	const static double TEMPERATURA_GWIAZDY_PROCENT_SREDNICY;
	const static double TEMPERATURA_GWIAZDY_PROCENT_STALY;
	const static double TEMPERATURA_GWIAZDY_PROCENT_LOSOWY;
	
	const static int ILOSC_PLANET_MIN;
	const static int ILOSC_PLANET_MAX;
	const static double ILOSC_PLANET_PARAM;

	const static SPG::Dystans SREDNICA_PLANETY_MIN;
	const static SPG::Dystans SREDNICA_PLANETY_MAX;
	const static double SREDNICA_PLANETY_ODCHYLENIE;
	const static double SREDNICA_PLANETY_PRZESUNIECIE;
	const static double SREDNICA_PLANETY_ROZCIAGNIECIE;

	const static SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MIN;
	const static SPG::Dystans ODLEGLOSC_MIEDZYPLANETARNA_MAX;

	const static SPG::Temperatura TEMPERATURA_PLANETY_MAX;

	const static SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MIN;
	const static SPG::Fluktuacja POWIERZCHNIA_UZYTKOWA_MAX;

	const static SPG::Fluktuacja POWIERZCHNIA_WODY_MAX;

	GeneratorUkladow( Licznik& licznikIdPlanet );
	~GeneratorUkladow(void);

	shared_ptr<UkladSloneczny> generujUklad() const;
	shared_ptr<Planeta> generujPlanete( const Dystans& odlegloscOdCentrum, const Moc& mocGwiazdy ) const;

private:

	mutable random_device generator;
	gamma_distribution<SPG::Dystans> dystrybutorSrednicyGwiazdy;
	binomial_distribution<int> dystrybutorIlosciPlanet;
	uniform_real_distribution<SPG::Fluktuacja>  dystrybucjaPowierzchniUzytkowej;
	Licznik& licznikIdPlanet;

	SPG::Dystans generujSredniceGwiazdy() const;

	SPG::Dystans generujSrednicePlanety( const Dystans& odlegloscOdCentrum ) const;

	SPG::Temperatura generujTemperatureGwiazdy( SPG::Dystans srednica ) const;

	SPG::Temperatura generujTemperaturePlanety( const Dystans& odlegloscOdCentrum, const Moc& mocGwiazdy ) const;
};

