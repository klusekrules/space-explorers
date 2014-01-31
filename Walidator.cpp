#include "Walidator.h"
#include <algorithm>

Walidator& Walidator::pobierzInstancje(){
	static Walidator w;
	return w;
}

void Walidator::dodajNowyIdentyfikatorPlanety(const STyp::Identyfikator & id){
	zbiorNowychIdPlanet.insert(id);
}

void Walidator::dodajUzytyIdentyfikatorPlanety(const STyp::Identyfikator & id){
	zbiorUzytychIdPlanet.insert(id);
}

void Walidator::wyczysc(){
	zbiorNowychIdPlanet.clear();	
	zbiorUzytychIdPlanet.clear();
}

bool Walidator::waliduj()const{
	const std::set<STyp::Identyfikator>& zbior = zbiorNowychIdPlanet;
	return all_of(zbiorUzytychIdPlanet.begin(), zbiorUzytychIdPlanet.end(), [&zbior](const STyp::Identyfikator& i){ return zbior.find(i) != zbior.end(); });
}
