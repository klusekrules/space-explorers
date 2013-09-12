#include "Walidator.h"
#include <algorithm>

Walidator::~Walidator(){

}

Walidator& Walidator::pobierzInstancje(){
	static Walidator w;
	return w;
}

void Walidator::dodajNowyIdentyfikatorPlanety( const Identyfikator & id ){
	zbiorNowychIdPlanet.insert(id);
}

void Walidator::dodajUzytyIdentyfikatorPlanety( const Identyfikator & id ){
	zbiorUzytychIdPlanet.insert(id);
}

void Walidator::wyczysc(){
	zbiorNowychIdPlanet.clear();	
	zbiorUzytychIdPlanet.clear();
}

bool Walidator::waliduj()const{
	const set<Identyfikator>& zbior = zbiorNowychIdPlanet;
	return all_of(zbiorUzytychIdPlanet.begin(),zbiorUzytychIdPlanet.end(), [&zbior]( const Identyfikator& i){ return zbior.find(i)!=zbior.end(); });
}

Walidator::Walidator(){
}
