#include "BladDzieleniaLadowni.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	BladDzieleniaLadowni::BladDzieleniaLadowni(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& tLadownia)
		: Wyjatek(tPlik, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), idBladDzieleniaLadowni, tytulBladDzieleniaLadowni, trescBladDzieleniaLadowni), ladownia(tLadownia)
	{
	}

	STyp::Tekst BladDzieleniaLadowni::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + STyp::Tekst("Ladownia:") + ladownia + STyp::Tekst("\n");
	}

	const STyp::Tekst& BladDzieleniaLadowni::getLadownia() const{
		return ladownia;
	}

	void BladDzieleniaLadowni::setLadownia(const STyp::Tekst& tLadownia){
		ladownia = tLadownia;
	}

	std::string BladDzieleniaLadowni::napis() const{
		SLog::Logger str(NAZWAKLASY(BladDzieleniaLadowni));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole("Ladownia", ladownia);
		return str.napis();
	}
}
