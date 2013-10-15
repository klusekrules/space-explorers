#include "GeneratorUkladow.h"


const SPG::Dystans GeneratorUkladow::SREDNICA_GWIAZDY_MIN = 0.5;
const SPG::Dystans GeneratorUkladow::SREDNICA_GWIAZDY_MAX = 70.0;

const SPG::Temperatura GeneratorUkladow::TEMPERATURA_GWIAZDY_MIN = 1700.0;
const SPG::Temperatura GeneratorUkladow::TEMPERATURA_GWIAZDY_MAX = 50000.0;

const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_SREDNICY = 0.78;
const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_STALY = 0.1;
const double GeneratorUkladow::TEMPERATURA_GWIAZDY_PROCENT_LOSOWY = 0.02;

const double GeneratorUkladow::SREDNICA_GWIAZDY_PARAM_ALFA = 3;
const double GeneratorUkladow::SREDNICA_GWIAZDY_PARAM_BETA = 2.5;

GeneratorUkladow::GeneratorUkladow(void)
	: dystrybutorSrednicyGwiazdy(SREDNICA_GWIAZDY_PARAM_ALFA,SREDNICA_GWIAZDY_PARAM_BETA)
{
	if( TEMPERATURA_GWIAZDY_PROCENT_SREDNICY + TEMPERATURA_GWIAZDY_PROCENT_STALY + TEMPERATURA_GWIAZDY_PROCENT_LOSOWY >= 1.0 || 
		TEMPERATURA_GWIAZDY_PROCENT_SREDNICY + TEMPERATURA_GWIAZDY_PROCENT_STALY + TEMPERATURA_GWIAZDY_PROCENT_LOSOWY <= 0.0 )
		throw exception("Invalid const params.");
}

GeneratorUkladow::~GeneratorUkladow(void)
{
}

shared_ptr<UkladSloneczny> GeneratorUkladow::generujUklad(){
	auto uklad = make_shared<UkladSloneczny>();
	uklad->ustawSredniceGwiazdy(generujSredniceGwiazdy());
	uklad->ustawSredniaTemperatureGwiazdy(generujTemperatureGwiazdy(uklad->pobierzSredniceGwiazdy()()));
	return uklad;
}

SPG::Temperatura GeneratorUkladow::generujTemperatureGwiazdy( SPG::Dystans srednica ) const{
	uniform_real_distribution<SPG::Temperatura> dystrybutorLosowejCzesciTemperatury(0,TEMPERATURA_GWIAZDY_PROCENT_LOSOWY);
	double procentLosowy = dystrybutorLosowejCzesciTemperatury(generator) - (TEMPERATURA_GWIAZDY_PROCENT_LOSOWY / 2.0 );
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

