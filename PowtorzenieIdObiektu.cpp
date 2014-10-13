#include "PowtorzenieIdObiektu.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	PowtorzenieIdObiektu::PowtorzenieIdObiektu(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Identyfikator& id, const STyp::Tekst& komunikat)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), debug, idPowtorzeniaIdObiektu, STyp::Tekst("B��d powt�rzenia obiektu!")
		, STyp::Tekst("Wyst�pi�o powt�rzenie obiektu o id: " + id.napis() + ". Komunikat b��du : ") + komunikat),
		identyfikatorObiektu_(id)
	{
	}

	const STyp::Identyfikator& PowtorzenieIdObiektu::pobierzIdentyfikatorObiektu() const{
		return identyfikatorObiektu_;
	}

	std::string PowtorzenieIdObiektu::napis() const{
		SLog::Logger str(NAZWAKLASY(PowtorzenieIdObiektu));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(identyfikatorObiektu_), identyfikatorObiektu_);
		return str.napis();
	}
};
