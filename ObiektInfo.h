#pragma once
#include "Main.h"
#include "ObiektBaseInfo.h"
#include "Obiekt.h"
#include "NiezainicjalizowanaKlasa.h"
#include "ZmianaInterfejs.h"

class ObiektInfo :
	public ObiektBaseInfo,
	public LoggerInterface<ObiektInfo>
{
private:
	Powierzchnia powierzchnia;
	ZmianaInterfejs<Powierzchnia>* zmPowierzchnia;

	Objetosc objetosc;
	ZmianaInterfejs<Objetosc>* zmObjetosc;

	Masa masa;
	ZmianaInterfejs<Masa>* zmMasa;

public:
	typedef LoggerInterface<ObiektInfo> LogObiektInfo;
	ObiektInfo( const Masa&, const Objetosc&, const Powierzchnia&, const Poziom& ,  const Info& );
	~ObiektInfo( );

	Powierzchnia getPowierzchnia() const;

	Objetosc getObjetosc() const;

	Masa getMasa() const;
	
	Obiekt* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;
};

