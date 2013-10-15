#pragma once
#include <random>
#include "UkladSloneczny.h"

using namespace std;

class GeneratorUkladow
{
public:
	const static SPG::Dystans SREDNICA_GWIAZDY_MIN;
	const static SPG::Dystans SREDNICA_GWIAZDY_MAX;
	const static SPG::Temperatura TEMPERATURA_GWIAZDY_MIN;
	const static SPG::Temperatura TEMPERATURA_GWIAZDY_MAX;
	const static double TEMPERATURA_GWIAZDY_PROCENT_SREDNICY;
	const static double TEMPERATURA_GWIAZDY_PROCENT_STALY;
	const static double TEMPERATURA_GWIAZDY_PROCENT_LOSOWY;

	const static double SREDNICA_GWIAZDY_PARAM_ALFA;
	const static double SREDNICA_GWIAZDY_PARAM_BETA;

	GeneratorUkladow(void);
	~GeneratorUkladow(void);

	shared_ptr<UkladSloneczny> generujUklad();

private:

	mutable random_device generator;
	gamma_distribution<SPG::Dystans> dystrybutorSrednicyGwiazdy;

	SPG::Dystans generujSredniceGwiazdy() const;

	SPG::Temperatura generujTemperatureGwiazdy( SPG::Dystans srednica ) const;
};

