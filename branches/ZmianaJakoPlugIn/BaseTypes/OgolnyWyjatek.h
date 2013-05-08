#pragma once

//Makro wstawiajace nazwe pliku i liniê i datê pliku.
#define EXCEPTION_PLACE Tekst(__FILE__) , IdType(__LINE__)

#include "../Logger/LoggerInterface.h"
#include "IdType.h"
#include "Tekst.h"

/**
* Podstawowa klasa wyj¹tku. S³u¿¹ca jako klasa bazowa dla pozosta³ych wyj¹tków
* lub jako klasa do tworzenia wyj¹tków nie posiadaj¹cych w³asnego typu.
*/
class BASETYPES_API OgolnyWyjatek:
	virtual public LoggerInterface
{
public:
	static const IdType domyslnyOgolnyWyjatekID; /// Domyœlna wartoœæ id klasy.
	
	OgolnyWyjatek( const Tekst& tPlik, const IdType& iLinia, const IdType& itId = IdType(), const Tekst& wwTytul = Tekst(), const Tekst& wwTresc = Tekst() );
	OgolnyWyjatek( const OgolnyWyjatek& a );
	virtual ~OgolnyWyjatek();

	virtual Tekst generujKomunikat() const;
	
	const IdType& getNumerWyjaku() const;
	void setNumerWyjatku( const IdType& itId );
	
	const Tekst& getTytul() const;
	void setTytul( const Tekst& wwTytul );
	
	const Tekst& getTresc() const;
	void setTresc ( const Tekst& wwTresc );	
	
	string toString() const override;

protected:
	IdType numerWyjatku;
	Tekst tytul;
	Tekst tresc;
	Tekst plik;
	IdType linia;
	Tekst data;
	Tekst stack;
	
private:

	void ustawSzczegoly( const Tekst& tPlik, const IdType& iLinia );

	static const Tekst domyslnyOgolnyWyjatekTytul; /// Domyœlny tytu³ wyjatku
	static const Tekst domyslnyOgolnyWyjatekTresc; /// Domyœlna treœæ wyj¹tku
};