#pragma once
#include "Main.h"
#include <vector>
#include "ObiektBase.h"

class Warunek :
	public LoggerInterface< Warunek >
{
public:
	typedef vector< ObiektBase* > ListaWarunkow;

	Warunek();
	Warunek(const Warunek& w);
	const Warunek& operator=(const Warunek& w);
	~Warunek();

	Warunek* Kopia(){
		return new Warunek(*this);
	}

	bool dodajWarunek( const ObiektBase& );
	bool usunWarunek( const ObiektBase& );

	bool sprawdzWarunki( const IdType& idPlanety ); //TODO: uzale¿niæ od id planety

	string toString() const override;

private:
	ListaWarunkow warunki;
};

