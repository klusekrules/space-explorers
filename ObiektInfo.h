#pragma once
#include "Main.h"
#include "ObiektBaseInfo.h"
#include "Obiekt.h"
#include "NiezainicjalizowanaKlasa.h"
#include "FuncTransf\ZmianaInterfejs.h"

class ObiektInfo :
	public ObiektBaseInfo,
	virtual public LoggerInterface
{
private:
	Powierzchnia powierzchnia;
	shared_ptr<ZmianaInterfejs> zmPowierzchnia;

	Objetosc objetosc;
	shared_ptr<ZmianaInterfejs> zmObjetosc;

	Masa masa;
	shared_ptr<ZmianaInterfejs> zmMasa;

public:
	ObiektInfo( const Masa&, const Objetosc&, const Powierzchnia&, const ObiektBaseInfo& ) throw();

	explicit ObiektInfo( ticpp::Node* ) throw(WyjatekParseraXML);

	~ObiektInfo( );

	Powierzchnia getPowierzchnia(const Poziom& pz) const;

	Objetosc getObjetosc(const Poziom& pz) const;

	Masa getMasa(const Poziom& pz) const;
	
	Obiekt* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;
};

