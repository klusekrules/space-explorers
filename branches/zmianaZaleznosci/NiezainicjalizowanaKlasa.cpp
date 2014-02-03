#include "NiezainicjalizowanaKlasa.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	NiezainicjalizowanaKlasa::NiezainicjalizowanaKlasa(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& tNazwa)
		: Wyjatek(tPlik, iLinia,Aplikacja::pobierzInstancje().pobierzSladStosu(), idNiezainicjalizowanaKlasa, tytulNiezainicjalizowanaKlasa, trescNiezainicjalizowanaKlasa), nazwaKlasy(tNazwa)
	{
	}

	const STyp::Tekst& NiezainicjalizowanaKlasa::getNazwaKlasy() const{
		return nazwaKlasy;
	}

	void NiezainicjalizowanaKlasa::setNazwaKlasy(const STyp::Tekst& nazwa){
		this->nazwaKlasy = nazwa;
	}

	STyp::Tekst NiezainicjalizowanaKlasa::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + STyp::Tekst("Nazwa klasy:") + nazwaKlasy + STyp::Tekst("\n");
	}


	std::string NiezainicjalizowanaKlasa::napis() const{
		SLog::Logger str(NAZWAKLASY(NiezainicjalizowanaKlasa));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole("Nazwa klasy", nazwaKlasy);
		return str.napis();
	}
}
