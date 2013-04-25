#pragma once
#include "Main.h"
#include "ObiektBaseInfo.h"
#include "Obiekt.h"
#include "NiezainicjalizowanaKlasa.h"
#include "ZmianaInterfejs.h"

class ObiektInfo :
	public ObiektBaseInfo,
	virtual public LoggerInterface
{
private:
	Powierzchnia powierzchnia;
	ZmianaInterfejs* zmPowierzchnia;

	Objetosc objetosc;
	ZmianaInterfejs* zmObjetosc;

	Masa masa;
	ZmianaInterfejs* zmMasa;

public:
	ObiektInfo( const Masa&, const Objetosc&, const Powierzchnia&, const ObiektBaseInfo& ) throw();

	explicit ObiektInfo( ticpp::Node* ) throw(WyjatekParseraXML);

	~ObiektInfo( );

	Powierzchnia getPowierzchnia() const;

	Objetosc getObjetosc() const;

	Masa getMasa() const;
	
	Obiekt* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;
};

