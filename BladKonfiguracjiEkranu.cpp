#include "BladKonfiguracjiEkranu.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	BladKonfiguracjiEkranu::BladKonfiguracjiEkranu(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Identyfikator& ekran, const STyp::Tekst& komunikat)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), debug, idBladKonfiguracjiEkranu, STyp::Tekst("B³¹d konfigurowania okna!")
		, STyp::Tekst("Podczas konfigurowania okna o id: " + std::to_string(ekran()) + " wyst¹pi³ wyj¹tek. Komunikat b³êdu : ") + komunikat),
		identyfikatorEkranu_(ekran)
	{
	}
	
	const STyp::Identyfikator& BladKonfiguracjiEkranu::pobierzIdEkranu() const{
		return identyfikatorEkranu_;
	}

	std::string BladKonfiguracjiEkranu::napis() const{
		SLog::Logger str(NAZWAKLASY(BladKonfiguracjiEkranu));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(identyfikatorEkranu_), identyfikatorEkranu_);
		return str.napis();
	}
};
