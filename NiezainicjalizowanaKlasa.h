#pragma once
#include "OgolnyWyjatek.h"

/**
* Wyj�tek informuje, �e klasa zosta�a niepoprawnie zainicjalizowana lub w og�le nie zosta�a zainicjalizowana.
*/
class NiezainicjalizowanaKlasa :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const Identyfikator idNiezainicjalizowanaKlasa;

	NiezainicjalizowanaKlasa(const Tekst& tPlik, const Ilosc& iLinia, const Tekst& tNazwa);
	virtual ~NiezainicjalizowanaKlasa(void);
	
	const Tekst& getNazwaKlasy() const;
	void setNazwaKlasy( const Tekst& );

	Tekst generujKomunikat() const override;

	string napis() const override;

private:
	Tekst nazwaKlasy;

	static const Tekst tytulNiezainicjalizowanaKlasa;
	static const Tekst trescNiezainicjalizowanaKlasa;
};

