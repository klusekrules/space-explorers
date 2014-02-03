#include "NiezgodnyTypSurowca.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	NiezgodnyTypSurowca::NiezgodnyTypSurowca(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Identyfikator & tsP, const STyp::Identyfikator & tsD)
		: Wyjatek(tPlik, iLinia,Aplikacja::pobierzInstancje().pobierzSladStosu(), idNiezgodnyTypSurowca, tytulNiezgodnyTypSurowcaDomyslny, STyp::Tekst())
	{
		std::stringstream str;
		str << "Brak zgodnosci typow. Uzyte typy = [ID Pierwszy = " << tsP.napis() << " ], [ID Drugi = " << tsD.napis() << " ].";
		//TODO: dokonczyc metode setTresc(str.str());
	}

	std::string NiezgodnyTypSurowca::napis() const{
		SLog::Logger str(NAZWAKLASY(NiezgodnyTypSurowca));
		str.dodajKlase(Wyjatek::napis());
		return str.napis();
	}
}