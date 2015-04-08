#include "NiezgodnyTypSurowca.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"

namespace SpEx{
	NiezgodnyTypSurowca::NiezgodnyTypSurowca(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Identyfikator & tsP, const STyp::Identyfikator & tsD)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), debug, idNiezgodnyTypSurowca, tytulNiezgodnyTypSurowcaDomyslny,
		STyp::Tekst("Brak zgodnosci typow. Uzyte typy = [ID Pierwszy = " + std::to_string(tsP()) + " ], [ID Drugi = " + std::to_string(tsD()) + " ]."))
	{
	}

	std::string NiezgodnyTypSurowca::napis() const{
		SLog::Logger str(NAZWAKLASY(NiezgodnyTypSurowca));
		str.dodajKlase(Wyjatek::napis());
		return str.napis();
	}
}