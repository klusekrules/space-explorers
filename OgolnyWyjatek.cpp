#include "OgolnyWyjatek.h"
#include "Logger.h"
#include "Aplikacja.h"

OgolnyWyjatek::OgolnyWyjatek( const Tekst& tPlik, const IdType& iLinia, const IdType& itId , const Tekst& wwTytul , const Tekst& wwTresc )
	: numerWyjatku( itId != IdType::domyslny ? itId : domyslnyOgolnyWyjatekID ) , tytul( wwTytul.isEmpty() ? domyslnyOgolnyWyjatekTytul : wwTytul ) , tresc( wwTresc.isEmpty() ? domyslnyOgolnyWyjatekTresc : wwTresc )
{
	ustawSzczegoly( tPlik, iLinia );
}

OgolnyWyjatek::OgolnyWyjatek( const OgolnyWyjatek& owWyjatek )
	: plik(owWyjatek.plik), linia(owWyjatek.linia), data(owWyjatek.data),
	numerWyjatku( owWyjatek.numerWyjatku ), tytul( owWyjatek.tytul ), tresc( owWyjatek.tresc )
{
}

OgolnyWyjatek::~OgolnyWyjatek(){
}


Tekst OgolnyWyjatek::generujKomunikat() const
{
	return  Tekst( "Tytul: " ) + tytul + 
		Tekst( "\nID: " ) + numerWyjatku.toString() +
		Tekst( "\nPlik: ") + plik +
		Tekst( "\nLinia: ") + linia.toString() +
		Tekst( "\nData kompilacji: ") + data + 
		Tekst( "\nTresc: " ) + tresc +
		Tekst( "\nStos wywo³añ: " ) + stack + Tekst( "\n" ); 
}
	
IdType OgolnyWyjatek::getNumerWyjaku() const{
	return numerWyjatku;
}

void OgolnyWyjatek::setNumerWyjatku( const IdType& itId ){
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

void OgolnyWyjatek::ustawSzczegoly( const Tekst& tPlik, const IdType& iLinia ){
	plik = tPlik;
	linia = iLinia;
	data = Tekst(__DATE__) + Tekst(", ") + Tekst(__TIME__);
	stack = Aplikacja::getInstance().getStackTrace();
}

string OgolnyWyjatek::toString() const{
	Logger str(className());
	str.addField("ID", numerWyjatku);
	str.addField("Tytul", tytul);
	str.addField("Tresc", tresc);
	str.addField("Plik", plik);
	str.addField("Linia", linia);
	str.addField("Data", data);
	str.addField("StackTrace",stack);
	return str.toString();
}