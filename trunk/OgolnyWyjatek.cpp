#include "OgolnyWyjatek.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "Stale.h"

OgolnyWyjatek::OgolnyWyjatek( const Tekst& tPlik, const Ilosc& iLinia, const Identyfikator& itId , const Tekst& wwTytul , const Tekst& wwTresc )
	: numerWyjatku( itId() != Stale::idDomyslny ? itId : domyslnyOgolnyWyjatekID ) , tytul( wwTytul.isEmpty() ? domyslnyOgolnyWyjatekTytul : wwTytul ) , tresc( wwTresc.isEmpty() ? domyslnyOgolnyWyjatekTresc : wwTresc )
{
	ustawSzczegoly( tPlik, iLinia );
}

OgolnyWyjatek::OgolnyWyjatek( const OgolnyWyjatek& owWyjatek )
	: numerWyjatku( owWyjatek.numerWyjatku ), tytul( owWyjatek.tytul ), tresc( owWyjatek.tresc ), 
	plik(owWyjatek.plik), linia(owWyjatek.linia), data(owWyjatek.data), stack( owWyjatek.stack )
	
{
}

OgolnyWyjatek::~OgolnyWyjatek(){
}


Tekst OgolnyWyjatek::generujKomunikat() const
{
	return  Tekst( "Tytul: " ) + tytul + 
		Tekst( "\nID: " ) + numerWyjatku.napis() +
		Tekst( "\nPlik: ") + plik +
		Tekst( "\nLinia: ") + linia.napis() +
		Tekst( "\nData kompilacji: ") + data + 
		Tekst( "\nTresc: " ) + tresc +
		Tekst( "\nStos wywo³añ: " ) + stack + Tekst( "\n" ); 
}
	
const Identyfikator& OgolnyWyjatek::getNumerWyjaku() const{
	return numerWyjatku;
}

void OgolnyWyjatek::setNumerWyjatku( const Identyfikator& itId ){
	numerWyjatku = itId;
}
	
const Tekst& OgolnyWyjatek::getTytul() const{
	return tytul;
}

void OgolnyWyjatek::setTytul( const Tekst& wwTytul ){
	tytul = wwTytul;
}
	
const Tekst& OgolnyWyjatek::getTresc() const{
	return tresc;
}

void OgolnyWyjatek::setTresc ( const Tekst& wwTresc ){
	tresc = wwTresc;
}

void OgolnyWyjatek::ustawSzczegoly( const Tekst& tPlik, const Ilosc& iLinia ){
	plik = tPlik;
	linia = iLinia;
	data = Tekst(__DATE__) + Tekst(", ") + Tekst(__TIME__);
	stack = Aplikacja::getInstance().getStackTrace();
}

string OgolnyWyjatek::napis() const{
	Logger str(NAZWAKLASY(OgolnyWyjatek));
	str.dodajPole("ID", numerWyjatku);
	str.dodajPole("Tytul", tytul);
	str.dodajPole("Tresc", tresc);
	str.dodajPole("Plik", plik);
	str.dodajPole("Linia", linia);
	str.dodajPole("Data", data);
	str.dodajPole("StackTrace",stack);
	return str.napis();
}