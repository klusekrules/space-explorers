#pragma once
#include "Main.h"
#include "Obiekt.h"
#include "OgolnyWyjatek.h"
#include "NiezgodnyTypSurowca.h"
#include "NiepoprawnaIloscObiektow.h"
#include "BladLaczeniaObiektow.h"
#include "PodstawoweParametry.h"

class SurowceInfo;
class Ladownia;

class Surowce :
	public Obiekt,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class SurowceInfo;
public:
	Surowce* kopia() const override;

	Obiekt* podziel( const Ilosc& ) override;
		
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

	Czas pobierzCzas()const;

	bool zapisz( TiXmlElement* e) const override;
	bool odczytaj ( TiXmlElement* e ) override;
	Surowce( TiXmlElement* e  );
			
	string napis() const override;

private:

	Surowce( const Ilosc&, const Surowce& );
	Surowce( const Ilosc&, const Poziom& p, const Identyfikator& idP, const SurowceInfo&  );
	Surowce( const Ilosc&, const PodstawoweParametry& p, const SurowceInfo&  );

	const SurowceInfo& surowceInfo;

};
