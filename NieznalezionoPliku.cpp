#include "NieznalezionoPliku.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	NieznalezionoPliku::NieznalezionoPliku(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& stos, const STyp::Tekst& plik)
		: Wyjatek(tPlik, funkcja, iLinia, stos, idNieznalezionoPliku, STyp::Tekst("B³¹d powtórzenia obiektu!")
		, STyp::Tekst("Wyst¹pi³o powtórzenie obiektu o id: " + plik.napis() + ". Komunikat b³êdu : ") + plik),
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
