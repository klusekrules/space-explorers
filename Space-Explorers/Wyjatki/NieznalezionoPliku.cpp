#include "NieznalezionoPliku.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"

namespace SpEx{
	NieznalezionoPliku::NieznalezionoPliku(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Tekst& plik)
		: Wyjatek(tPlik, funkcja, iLinia, debug, idNieznalezionoPliku, STyp::Tekst("Nieznaleziono pliku!")
		, STyp::Tekst("Nieuda³o siê otworzyæ pliku: " + plik() )),
		nazwaPliku_(plik)
	{
	}

	const STyp::Tekst& NieznalezionoPliku::pobierzNazwePliku() const{
		return nazwaPliku_;
	}

	std::string NieznalezionoPliku::napis() const{
		SLog::Logger str(NAZWAKLASY(NieznalezionoPliku));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(nazwaPliku_), nazwaPliku_);
		return str.napis();
	}
};
