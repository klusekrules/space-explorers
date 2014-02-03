#include "NiepowodzenieTranzakcji.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	NiepowodzenieTranzakcji::NiepowodzenieTranzakcji(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& tranzakcja)
		: Wyjatek(tPlik, iLinia,Aplikacja::pobierzInstancje().pobierzSladStosu(), domyslnyNiepowodzenieTranzakcjiID, domyslnyNiepowodzenieTranzakcjiTytul, domyslnyNiepowodzenieTranzakcjiTresc), tranzakcja_(tranzakcja)
	{
	}

	STyp::Tekst NiepowodzenieTranzakcji::generujKomunikat() const
	{
		return Wyjatek::generujKomunikat();
			//TODO: Dokonczyc metode
			/*STyp::Tekst("Tytul: ") + tytul +
			STyp::Tekst("\nID: ") + numerWyjatku.napis() +
			STyp::Tekst("\nPlik: ") + plik +
			STyp::Tekst("\nLinia: ") + linia.napis() +
			STyp::Tekst("\nData kompilacji: ") + data +
			STyp::Tekst("\nTresc: ") + tresc +
			STyp::Tekst("\nOpis Tranzakcji: ") + tranzakcja_ +
			STyp::Tekst("\nStos wywo³añ: ") + stack + STyp::Tekst("\n");*/
	}

	std::string NiepowodzenieTranzakcji::napis() const{
		SLog::Logger str(NAZWAKLASY(NiepowodzenieTranzakcji));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(tranzakcja_), tranzakcja_);
		return str.napis();
	}
}