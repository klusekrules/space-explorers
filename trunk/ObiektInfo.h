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

	explicit ObiektInfo( TiXmlElement* ) throw(WyjatekParseraXML);

	~ObiektInfo( );

	Powierzchnia getPowierzchnia(const Poziom& pz, const IdType&) const;

	Objetosc getObjetosc(const Poziom& pz, const IdType&) const;

	Masa getMasa(const Poziom& pz, const IdType&) const;
	
	Obiekt* TworzEgzemplarz( const Ilosc&, const IdType& ) const override;

	string napis() const override;
};

