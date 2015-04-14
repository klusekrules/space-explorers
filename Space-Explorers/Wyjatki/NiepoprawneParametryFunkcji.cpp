#include "NiepoprawneParametryFunkcji.h"
#include "Logger\Logger.h"

namespace SpEx{

	STyp::Tekst NiepoprawneParametryFunkcji::generujKomunikat() const{
		return Wyjatek::generujKomunikat() + STyp::Tekst("Lista parametrów:\n") + parametry + STyp::Tekst("\n");
	}

	const STyp::Tekst& NiepoprawneParametryFunkcji::getParametry() const{
		return parametry;
	}

	void NiepoprawneParametryFunkcji::setParametry(const STyp::Tekst& wwTresc){
		parametry = wwTresc;
	}

	std::string NiepoprawneParametryFunkcji::napis() const{
		SLog::Logger str(NAZWAKLASY(NiepoprawneParametryFunkcji));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(parametry), parametry);
		return str.napis();
	}
}
