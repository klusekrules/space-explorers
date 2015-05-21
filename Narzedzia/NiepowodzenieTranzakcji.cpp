#include "NiepowodzenieTranzakcji.h"
#include "Logger\Logger.h"

namespace SpEx{

	const STyp::Identyfikator	NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiID(0x1C);
	const STyp::Tekst		NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiTytul = "Niepowodzenie wykonania tranzakcji";
	const STyp::Tekst		NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiTresc = "Nie uda³o siê zachowaæ tanzakcyjnoœci wykonywanych operacji. Operacja powoduj¹ca wyj¹tek: ";
	
	NiepowodzenieTranzakcji::NiepowodzenieTranzakcji(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& tranzakcja)
		: Wyjatek(tPlik, funkcja, iLinia, STyp::Tekst(), domyslnyNiepowodzenieTranzakcjiID, domyslnyNiepowodzenieTranzakcjiTytul, domyslnyNiepowodzenieTranzakcjiTresc), tranzakcja_(tranzakcja)
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