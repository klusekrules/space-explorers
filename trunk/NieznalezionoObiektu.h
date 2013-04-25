#pragma once
#include "OgolnyWyjatek.h"

/**
* Wyj¹tek infomuje, ¿e obiekt nie zosta³ znaleziony.
*/
class NieznalezionoObiektu :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const IdType idNieznalezionoObiektu;

	NieznalezionoObiektu(const Tekst& tPlik, const IdType& iLinia, const Tekst& tNazwa);
	virtual ~NieznalezionoObiektu(void);
	
	const Tekst& getIdentyfikator() const;
	void setIdentyfikator( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst identyfikator;

	static const Tekst tytulNieznalezionoObiektu;
	static const Tekst trescNieznalezionoObiektu;
};

