#pragma once
#include <memory>
#include "Ilosc.h"
#include "Dystans.h"
#include "Temperatura.h"
//#include "Mo

using namespace std;
class UkladSloneczny
{
public:
	UkladSloneczny();
	virtual ~UkladSloneczny();

	static shared_ptr< UkladSloneczny > generuj();

	void ustawSredniceGwiazdy(SPG::Dystans srednica);

	const Dystans& pobierzSredniceGwiazdy() const;

	void ustawSredniaTemperatureGwiazdy(SPG::Temperatura temperatura);

	const Temperatura& pobierzSredniaTemperatureGwiazdy() const;

	//const Temperatura& pobierzSredniaTemperatureGwiazdy() const;

private:
	Dystans srednicaGwiazdy;
	Temperatura sredniaTemperaturaGwiazdy;

	Ilosc maksymalnaIloscPlanet;
	Dystans rozmiarSloncaUkladu;

};

