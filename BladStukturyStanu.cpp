#include "BladStukturyStanu.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	BladStukturyStanu::BladStukturyStanu(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Identyfikator& id, const STyp::Tekst& komunikat)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), debug, idBladStukturyStanu, STyp::Tekst("B³¹d struktury stanu!")
		, STyp::Tekst("Wyst¹pi³ b³¹d struktury stanu o id: " + std::to_string(id()) + ". Komunikat b³êdu : ") + komunikat),
		identyfikatorStanu_(id)
	{
	}

	const STyp::Identyfikator& BladStukturyStanu::pobierzIdentyfikatorStanu() const{
		return identyfikatorStanu_;
	}

	std::string BladStukturyStanu::napis() const{
		SLog::Logger str(NAZWAKLASY(BladStukturyStanu));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(identyfikatorStanu_), identyfikatorStanu_);
		return str.napis();
	}
};
