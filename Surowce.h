#pragma once
#include "Main.h"
#include "Obiekt.h"
#include "OgolnyWyjatek.h"
#include "NiezgodnyTypSurowca.h"
#include "NiepoprawnaIloscObiektow.h"
#include "BladLaczeniaObiektow.h"

class SurowceInfo;
class Ladownia;

class Surowce :
	public Obiekt,
	virtual public LoggerInterface
{
	friend class SurowceInfo;
public:
	virtual ~Surowce( );

	Surowce* Kopia() const override;

	Obiekt* Podziel( const Ilosc& ) throw( NiepoprawnaIloscObiektow ) ;

	bool Polacz( const Obiekt& ) throw ( BladLaczeniaObiektow ) ;

	Objetosc Objetosc() const ;

	Masa Masa() const ;
	
	Surowce& operator=( const Surowce& ) throw ( NiezgodnyTypSurowca );
	
	bool operator==( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	bool operator!=( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	bool operator>( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	bool operator<( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	bool operator>=( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	bool operator<=( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	Surowce operator+( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	Surowce& operator+=( const Surowce& ) throw ( NiezgodnyTypSurowca );
	
	Surowce operator-( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	Surowce& operator-=( const Surowce& ) throw ( NiezgodnyTypSurowca );
	
	bool Dodaj( const Surowce& );
	
	bool Usun( const Surowce& );
	
	const Ilosc& getIlosc() const;
	
	void setIlosc( const Ilosc& );

	const SurowceInfo& getSurowceInfo() const;
		
	bool czyTypPrzyrostowy()const;

	bool czMoznaDodacDoLadownii( const Ladownia& c ) const override;
			
	string toString() const override;

private:

	Surowce( const Ilosc&, const Surowce& );
	Surowce( const Ilosc&, const Poziom& p, const SurowceInfo&  );
	
	const SurowceInfo& surowceInfo;

};
