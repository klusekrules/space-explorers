#include "BladLaczeniaObiektow.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
namespace SpEx{

	BladLaczeniaObiektow::BladLaczeniaObiektow(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& a, const STyp::Tekst& b)
		: Wyjatek(tPlik, iLinia,Aplikacja::pobierzInstancje().pobierzSladStosu(), idBladLaczeniaObiektow, tytulBladLaczeniaObiektow, trescBladLaczeniaObiektow), obiektA(a), obiektB(b)
	{
	}

	const STyp::Tekst& BladLaczeniaObiektow::getObiektA() const{
		return obiektA;
	}

	void BladLaczeniaObiektow::setObiektA(const STyp::Tekst& a){
		obiektA = a;
	}

	const STyp::Tekst& BladLaczeniaObiektow::getObiektB() const{
		return obiektB;
	}

	void BladLaczeniaObiektow::setObiektB(const STyp::Tekst& b){
		obiektB = b;
	}

	STyp::Tekst BladLaczeniaObiektow::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + STyp::Tekst("ObiektA:") + obiektA + STyp::Tekst("\nObiektB:") + obiektB + STyp::Tekst("\n");
	}

	std::string BladLaczeniaObiektow::napis() const{
		SLog::Logger str(NAZWAKLASY(BladLaczeniaObiektow));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(obiektA), obiektA);
		str.dodajPole(NAZWAPOLA(obiektB), obiektB);
		return str.napis();
	}
}
