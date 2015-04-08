#include "NiepowodzenieTranzakcji.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"

namespace SpEx{
	NiepowodzenieTranzakcji::NiepowodzenieTranzakcji(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Tekst& tranzakcja)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), debug, domyslnyNiepowodzenieTranzakcjiID, domyslnyNiepowodzenieTranzakcjiTytul, domyslnyNiepowodzenieTranzakcjiTresc), tranzakcja_(tranzakcja)
	{
	}

	STyp::Tekst NiepowodzenieTranzakcji::generujKomunikat() const
	{
		return Wyjatek::generujKomunikat() + STyp::Tekst("\nOpis Tranzakcji: ") + tranzakcja_;
	}

	std::string NiepowodzenieTranzakcji::napis() const{
		SLog::Logger str(NAZWAKLASY(NiepowodzenieTranzakcji));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(tranzakcja_), tranzakcja_);
		return str.napis();
	}
}