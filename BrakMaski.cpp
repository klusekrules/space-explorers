#include "BrakMaski.h"
#include "Logger\Logger.h"

namespace SpEx{
	BrakMaski::BrakMaski(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& nazwa)
		: WyjatekParseraXML(tPlik, iLinia, std::exception(), trescBrakMaski), nazwaMaski(nazwa)
	{
		//TODO: Dokonczyc metode
		/*
		this->setNumerWyjatku(idBrakMaski);
		this->setTytul(tytulBrakMaski);*/
	}

	BrakMaski::BrakMaski(const BrakMaski& e)
		: WyjatekParseraXML(e), nazwaMaski(e.nazwaMaski)
	{
	}
	
	const STyp::Tekst& BrakMaski::getNazwaMaski() const{
		return nazwaMaski;
	}

	void BrakMaski::setNazwaMaski(const STyp::Tekst& nazwaMaski){
		this->nazwaMaski = nazwaMaski;
	}

	STyp::Tekst BrakMaski::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + nazwaMaski + STyp::Tekst("\n");
	}

	std::string BrakMaski::napis() const{
		SLog::Logger str(NAZWAKLASY(BrakMaski));
		str.dodajKlase(WyjatekParseraXML::napis());
		str.dodajPole(NAZWAPOLA(nazwaMaski), nazwaMaski);
		return str.napis();
	}
}
