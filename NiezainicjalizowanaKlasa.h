#pragma once
#include "OgolnyWyjatek.h"
class NiezainicjalizowanaKlasa :
	public LoggerInterface<NiezainicjalizowanaKlasa>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<NiezainicjalizowanaKlasa> LogNiezainicjalizowanaKlasa;

	static const IdType idNiezainicjalizowanaKlasa;

	NiezainicjalizowanaKlasa(const Tekst& tPlik, const IdType& iLinia, const Tekst& tNazwa);
	virtual ~NiezainicjalizowanaKlasa(void);
	
	Tekst getNazwaKlasy() const;
	void setNazwaKlasy( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst nazwaKlasy;

	static const Tekst tytulNiezainicjalizowanaKlasa;
	static const Tekst trescNiezainicjalizowanaKlasa;
};

