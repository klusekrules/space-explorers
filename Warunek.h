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

	bool sprawdzWarunki( ListaWarunkow& a );

	string toString() const override;

private:

	static bool spelnienieWarunku(const ObiektBase& warunek, const ListaWarunkow& zrodlo){
		for( auto z : zrodlo ){
			if( warunek.getId() == z->getId() ){
				return warunek.getPoziom() <= z->getPoziom();
			}
		}
		return false;
	}

	ListaWarunkow warunki;
};

