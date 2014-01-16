#pragma once
#include "Identyfikator.h"
#include "Tekst.h"
#include "Ilosc.h"

//Makro wstawiajace nazwe pliku i liniê i datê pliku.
#define EXCEPTION_PLACE Tekst(__FILE__) , Ilosc(__LINE__)

/**
* Podstawowa klasa wyj¹tku. S³u¿¹ca jako klasa bazowa dla pozosta³ych wyj¹tków
* lub jako klasa do tworzenia wyj¹tków nie posiadaj¹cych w³asnego typu.
*/
class OgolnyWyjatek:
	virtual public LoggerInterface
{
public:
	static const Identyfikator domyslnyOgolnyWyjatekID; /// Domyœlna wartoœæ id klasy.
	
	OgolnyWyjatek( const Tekst& tPlik, const Ilosc& iLinia, const Identyfikator& itId = Identyfikator(), const Tekst& wwTytul = Tekst(), const Tekst& wwTresc = Tekst() );
	OgolnyWyjatek( const OgolnyWyjatek& a );
	virtual ~OgolnyWyjatek();

	virtual Tekst generujKomunikat() const;
	
	const Identyfikator& getNumerWyjaku() const;
	void setNumerWyjatku( const Identyfikator& itId );
	
	const Tekst& getTytul() const;
	void setTytul( const Tekst& wwTytul );
	
	const Tekst& getTresc() const;
	void setTresc ( const Tekst& wwTresc );	
	
	std::string napis() const override;

protected:
	Identyfikator numerWyjatku;
	Tekst tytul;
	Tekst tresc;
	Tekst plik;
	Ilosc linia;
	Tekst data;
	Tekst stack;
	
private:

	void ustawSzczegoly( const Tekst& tPlik, const Ilosc& iLinia );

	static const Tekst domyslnyOgolnyWyjatekTytul; /// Domyœlny tytu³ wyjatku
	static const Tekst domyslnyOgolnyWyjatekTresc; /// Domyœlna treœæ wyj¹tku
};