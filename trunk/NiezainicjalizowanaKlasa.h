#pragma once
#include "OgolnyWyjatek.h"

/**
* Wyj¹tek informuje, ¿e klasa zosta³a niepoprawnie zainicjalizowana lub w ogóle nie zosta³a zainicjalizowana.
*/
class NiezainicjalizowanaKlasa :
	public LoggerInterface<NiezainicjalizowanaKlasa>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<NiezainicjalizowanaKlasa> LogNiezainicjalizowanaKlasa;

	static const IdType idNiezainicjalizowanaKlasa;

	NiezainicjalizowanaKlasa(const Tekst& tPlik, const IdType& iLinia, const Tekst& tNazwa);
	virtual ~NiezainicjalizowanaKlasa(void);
	
	const Tekst& getNazwaKlasy() const;
	void setNazwaKlasy( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst nazwaKlasy;

	static const Tekst tytulNiezainicjalizowanaKlasa;
	static const Tekst trescNiezainicjalizowanaKlasa;
};

