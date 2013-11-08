#include "NiepowodzenieTranzakcji.h"
#include "Logger\Logger.h"

NiepowodzenieTranzakcji::NiepowodzenieTranzakcji(const Tekst& tPlik, const Ilosc& iLinia, const Tekst& tranzakcja)
	: OgolnyWyjatek(tPlik,iLinia,domyslnyNiepowodzenieTranzakcjiID,domyslnyNiepowodzenieTranzakcjiTytul,domyslnyNiepowodzenieTranzakcjiTresc), tranzakcja_(tranzakcja)
{
}

Tekst NiepowodzenieTranzakcji::generujKomunikat() const
{
	return  Tekst( "Tytul: " ) + tytul + 
		Tekst( "\nID: " ) + numerWyjatku.napis() +
		Tekst( "\nPlik: ") + plik +
		Tekst( "\nLinia: ") + linia.napis() +
		Tekst( "\nData kompilacji: ") + data + 
		Tekst( "\nTresc: " ) + tresc +
		Tekst( "\nOpis Tranzakcji: " ) + tranzakcja_ +
		Tekst( "\nStos wywo³añ: " ) + stack + Tekst( "\n" ); 
}

NiepowodzenieTranzakcji::~NiepowodzenieTranzakcji(void)
{
}

std::string NiepowodzenieTranzakcji::napis() const{
	Logger str(NAZWAKLASY(NiepowodzenieTranzakcji));
	str.dodajKlase(OgolnyWyjatek::napis());
	str.dodajPole("OpisTranzakcji",tranzakcja_);
	return str.napis();
}
