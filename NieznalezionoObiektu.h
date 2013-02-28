#pragma once
#include "OgolnyWyjatek.h"
class NieznalezionoObiektu :
	public LoggerInterface<NieznalezionoObiektu>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<NieznalezionoObiektu> LogNieznalezionoObiektu;

	static const IdType idNieznalezionoObiektu;

	NieznalezionoObiektu(const Tekst& tPlik, const IdType& iLinia, const Tekst& tNazwa);
	virtual ~NieznalezionoObiektu(void);
	
	Tekst getIdentyfikator() const;
	void setIdentyfikator( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst identyfikator;

	static const Tekst tytulNieznalezionoObiektu;
	static const Tekst trescNieznalezionoObiektu;
};

