#include "NiepoprawnaIloscObiektow.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
namespace SpEx{

	NiepoprawnaIloscObiektow::NiepoprawnaIloscObiektow(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Ilosc& ilosc)
		: Wyjatek(tPlik, iLinia,Aplikacja::pobierzInstancje().pobierzSladStosu(), idNiepoprawnaIloscObiektow, tytulNiepoprawnaIloscObiektow, trescNiepoprawnaIloscObiektow), i(ilosc)
	{
	}
	
	const STyp::Ilosc& NiepoprawnaIloscObiektow::getIlosc() const{
		return i;
	}

	void NiepoprawnaIloscObiektow::setIlosc(const STyp::Ilosc& ilosc){
		i = ilosc;
	}

	STyp::Tekst NiepoprawnaIloscObiektow::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + STyp::Tekst("Ilosc:") + i.STyp::Ilosc::napis() + STyp::Tekst("\n");
	}

	std::string NiepoprawnaIloscObiektow::napis() const{
		SLog::Logger str(NAZWAKLASY(NiepoprawnaIloscObiektow));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole("Ilosc", i);
		return str.napis();
	}
}
