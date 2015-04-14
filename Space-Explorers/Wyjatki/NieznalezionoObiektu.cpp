#include "NieznalezionoObiektu.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"

namespace SpEx{

	NieznalezionoObiektu::NieznalezionoObiektu(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Tekst& tNazwa)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), debug, idNieznalezionoObiektu, tytulNieznalezionoObiektu, trescNieznalezionoObiektu), identyfikator(tNazwa)
	{
	}

	const STyp::Tekst& NieznalezionoObiektu::getIdentyfikator() const{
		return identyfikator;
	}

	void NieznalezionoObiektu::setIdentyfikator(const STyp::Tekst& nazwa){
		this->identyfikator = nazwa;
	}

	STyp::Tekst NieznalezionoObiektu::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + STyp::Tekst("Identyfikator:") + identyfikator + STyp::Tekst("\n");
	}

	std::string NieznalezionoObiektu::napis() const{
		SLog::Logger str(NAZWAKLASY(NieznalezionoObiektu));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator);
		return str.napis();
	}
}