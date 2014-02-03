#include "WyjatekSTL.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
namespace SpEx{
	WyjatekSTL::WyjatekSTL(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const std::exception& e, const STyp::Tekst& str)
		: Wyjatek(tPlik, iLinia,Aplikacja::pobierzInstancje().pobierzSladStosu(), idWyjatekSTL, tytulWyjatekSTL, str.isEmpty() ? trescWyjatekSTL : str), powod(e.what())
	{
	}

	WyjatekSTL::WyjatekSTL(const WyjatekSTL& e)
		: Wyjatek(e), powod(e.powod)
	{
	}

	const STyp::Tekst& WyjatekSTL::getPowod() const{
		return powod;
	}

	void WyjatekSTL::setPowod(const STyp::Tekst& powod){
		this->powod = powod;
	}

	STyp::Tekst WyjatekSTL::generujKomunikat()const {
		return Wyjatek::generujKomunikat() + powod + STyp::Tekst("\n");
	}

	std::string WyjatekSTL::napis() const{
		SLog::Logger str(NAZWAKLASY(WyjatekSTL));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(powod), powod);
		return str.napis();
	}
}