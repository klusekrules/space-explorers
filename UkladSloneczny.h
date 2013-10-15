#pragma once
#include <memory>
#include "SygnaturaPlanety.h"
#include "Ilosc.h"
#include "Dystans.h"
#include "Temperatura.h"
#include "Moc.h"

using namespace std;
class UkladSloneczny
{
public:
	typedef shared_ptr<SygnaturaPlanety> Sygnatura;
	typedef vector< Sygnatura > Planety;

	UkladSloneczny();
	virtual ~UkladSloneczny();
	
	void ustawSredniceGwiazdy(SPG::Dystans srednica);

	const Dystans& pobierzSredniceGwiazdy() const;

	void ustawSredniaTemperatureGwiazdy(SPG::Temperatura temperatura);

	const Temperatura& pobierzSredniaTemperatureGwiazdy() const;

	Moc pobierzMocGwiazdy() const;

	bool dodajPlanete( Sygnatura planeta );

	Sygnatura pobierzPlanete( int numer ) const ;

	int liczbaPlanet() const;

private:
	Dystans srednicaGwiazdy;
	Temperatura sredniaTemperaturaGwiazdy;
	
	Planety planety;
};

