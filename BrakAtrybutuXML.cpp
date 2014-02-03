#include "BrakAtrybutuXML.h"
#include "Logger\Logger.h"

namespace SpEx{
	BrakAtrybutuXML::BrakAtrybutuXML(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& str)
		: WyjatekParseraXML(tPlik, iLinia, std::exception(), trescBrakAtrybutuXML), atrybut(str)
	{
		//TODO: dokonczyc metode
	}

	BrakAtrybutuXML::BrakAtrybutuXML(const BrakAtrybutuXML& e)
		: WyjatekParseraXML(e), atrybut(e.atrybut)
	{
	}

	const STyp::Tekst& BrakAtrybutuXML::getAtrybut() const{
		return atrybut;
	}

	void BrakAtrybutuXML::setAtrybut(const STyp::Tekst& atrybut){
		this->atrybut = atrybut;
	}

	STyp::Tekst BrakAtrybutuXML::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + atrybut + STyp::Tekst("\n");
	}

	std::string BrakAtrybutuXML::napis() const{
		SLog::Logger str(NAZWAKLASY(BrakAtrybutuXML));
		str.dodajKlase(WyjatekParseraXML::napis());
		str.dodajPole(NAZWAPOLA(atrybut), atrybut);
		return str.napis();
	}
}