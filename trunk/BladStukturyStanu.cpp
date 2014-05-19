#include "BladStukturyStanu.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	BladStukturyStanu::BladStukturyStanu(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Identyfikator& id, const STyp::Tekst& komunikat)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), idBladStukturyStanu, STyp::Tekst("B��d struktury stanu!")
		, STyp::Tekst("Wyst�pi� b��d struktury stanu o id: " + id.napis() + ". Komunikat b��du : ") + komunikat),
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
