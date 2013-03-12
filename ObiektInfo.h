#pragma once
#include "Main.h"
#include "Info.h"
#include "Obiekt.h"
#include "NiezainicjalizowanaKlasa.h"
#include "ZmianaInterfejs.h"

class ObiektInfo :
	public Info,
	public ObiektBase,
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
	
	virtual Obiekt* TworzEgzemplarz( const Ilosc& ) const;

	string toString() const override;
};

