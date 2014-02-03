#include "WyjatekParseraXML.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
namespace SpEx{
	WyjatekParseraXML::WyjatekParseraXML(const WyjatekParseraXML& a)
		: Wyjatek(a), powod(a.powod)
	{
	}

	WyjatekParseraXML::WyjatekParseraXML(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const std::exception& ex, const STyp::Tekst& str)
		: Wyjatek(tPlik, iLinia,Aplikacja::pobierzInstancje().pobierzSladStosu(), idWyjatekParseraXML, tytulWyjatekParseraXML, str.isEmpty() ? trescWyjatekParseraXML : str), powod(ex.what())
	{
	}

	const STyp::Tekst& WyjatekParseraXML::getPowod() const{
		return powod;
	}
	void WyjatekParseraXML::setPowod(const STyp::Tekst& powod){
		this->powod = powod;
	}

	STyp::Tekst WyjatekParseraXML::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + powod + STyp::Tekst("\n");
	}

	std::string WyjatekParseraXML::napis() const{
		SLog::Logger str(NAZWAKLASY(WyjatekParseraXML));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(powod), powod);
		return str.napis();
	}
}