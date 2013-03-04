#pragma once
#include "Main.h"
#include "IdType.h"
#include "Tekst.h"


/**
* Podstawowa klasa wyj¹tku.
*/
class OgolnyWyjatek:
	public LoggerInterface<OgolnyWyjatek>
{
public:
	static const IdType domyslnyOgolnyWyjatekID; /// Domyœlna wartoœæ id klasy.
	
	OgolnyWyjatek( const Tekst& tPlik, const IdType& iLinia, const IdType& itId = IdType(), const Tekst& wwTytul = Tekst(), const Tekst& wwTresc = Tekst() );
	OgolnyWyjatek( const OgolnyWyjatek& a );
	virtual ~OgolnyWyjatek();

	virtual Tekst generujKomunikat() const;
	
	IdType getNumerWyjaku() const;
	void setNumerWyjatku( const IdType& itId );
	
	Tekst getTytul() const;
	void setTytul( const Tekst& wwTytul );
	
	Tekst getTresc() const;
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