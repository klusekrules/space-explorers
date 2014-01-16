#pragma once
#include "Identyfikator.h"
#include <set>

using namespace std;

class Walidator
{
public:
	virtual ~Walidator();

	static Walidator& pobierzInstancje();

	void dodajNowyIdentyfikatorPlanety( const Identyfikator & );
	void dodajUzytyIdentyfikatorPlanety( const Identyfikator & );
	
	void wyczysc();

	bool waliduj()const;

private:
	set<Identyfikator> zbiorNowychIdPlanet;
	set<Identyfikator> zbiorUzytychIdPlanet;
	Walidator();
	Walidator( const Walidator& );
	Walidator& operator=( const Walidator& );
};

