#include "UkladSloneczny.h"
#include <random>

UkladSloneczny::UkladSloneczny()
{
}


UkladSloneczny::~UkladSloneczny()
{
}

void UkladSloneczny::ustawSredniceGwiazdy(SPG::Dystans srednica){
	srednicaGwiazdy(srednica);
}

const Dystans& UkladSloneczny::pobierzSredniceGwiazdy() const{
	return srednicaGwiazdy;
}

void UkladSloneczny::ustawSredniaTemperatureGwiazdy(SPG::Temperatura temperatura){
	sredniaTemperaturaGwiazdy(temperatura);
}

const Temperatura& UkladSloneczny::pobierzSredniaTemperatureGwiazdy() const{
	return sredniaTemperaturaGwiazdy;
}

Moc UkladSloneczny::pobierzMocGwiazdy() const{
	return Moc(srednicaGwiazdy()*sredniaTemperaturaGwiazdy());
}

bool UkladSloneczny::dodajPlanete( UkladSloneczny::Sygnatura planeta ){
	if(find(planety.begin(),planety.end(),planeta) != planety.end())
		return false;
	planety.push_back(planeta);
	return true;
}

UkladSloneczny::Sygnatura UkladSloneczny::pobierzPlanete( int numer ) const{
	return planety.at(numer);
}

int UkladSloneczny::liczbaPlanet() const{
	return static_cast<int>( planety.size() );
}
