#pragma once
#include "Main.h"
#include "Obiekt.h"
#include "OgolnyWyjatek.h"
#include "NiezgodnyTypSurowca.h"
#include "NiepoprawnaIloscObiektow.h"

class SurowceInfo;

class Surowce :
	public Obiekt,
	public LoggerInterface<Surowce>
{
	friend class SurowceInfo;
public:
	typedef LoggerInterface<Surowce> LogSurowce;
	Surowce( const Surowce& );
	virtual ~Surowce( );

	Obiekt* Kopia() const override;

	Obiekt* Podziel( const Ilosc& ) throw( OgolnyWyjatek ) ;

	bool Polacz( const Obiekt& ) throw ( std::bad_cast ) ;

	Objetosc Objetosc() const ;

	Masa Masa() const ;
		
	Surowce& operator=( const Surowce& );
	
	bool operator==( const Surowce& ) const;
	
	bool operator!=( const Surowce& ) const;
	
	bool operator>( const Surowce& ) const;
	
	bool operator<( const Surowce& ) const;
	
	bool operator>=( const Surowce& ) const;
	
	bool operator<=( const Surowce& ) const;
	
	Surowce operator+( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	Surowce operator+=( const Surowce& ) throw ( NiezgodnyTypSurowca );
	
	Surowce operator-( const Surowce& ) const throw ( NiezgodnyTypSurowca );
	
	Surowce operator-=( const Surowce& ) throw ( NiezgodnyTypSurowca );
	
	bool Dodaj( const Surowce& );
	
	bool Usun( const Surowce& );
	
	Ilosc getIlosc() const;
	
	void setIlosc( const Ilosc& );

	SurowceInfo* getSurowceInfo() const;
	
	void setSurowceInfo( SurowceInfo* );
		
	string toString() const override;

private:

	Surowce( );
	Surowce( const Ilosc& , const Surowce& );
	Surowce( const Ilosc& , const SurowceInfo&  );
	
	Ilosc ilosc;

	SurowceInfo* info;

};
