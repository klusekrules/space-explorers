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

/*
	binomial_distribution<int> dystrybutor(16,0.45);
	uniform_real_distribution<double> dystrybutorPlanet(50,300);
	int liczba_planet = 2+dystrybutor(generator);
	cout<<"Liczba planet ukladu:"<< liczba_planet <<endl;
	double s = 0;
	for(int n = 0 ; n < liczba_planet ; ++n ){
		double o = dystrybutorPlanet(generator);
		s+=o;
		cout <<"  "<<setw(3) <<n+1 << " odleglosc: "<<setw(8)<< o <<" mln km, od slonca: "<<setw(10)<< s <<" mln km"<<endl;
	}
*/
shared_ptr< UkladSloneczny > UkladSloneczny::generuj(){
	random_device generator;
	binomial_distribution<int> iloscPlanetUkladu( 16 , 0.45 );
	auto uklad = make_shared<UkladSloneczny>();
	uklad->maksymalnaIloscPlanet = Ilosc(iloscPlanetUkladu(generator)+2);
	return uklad;
}