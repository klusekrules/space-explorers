#include "BladKonfiguracjiAplikacji.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"

namespace SpEx{
	BladKonfiguracjiAplikacji::BladKonfiguracjiAplikacji(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Tekst& komunikat)
		: Wyjatek(tPlik, funkcja, iLinia, debug, idBladKonfiguracjiAplikacji, STyp::Tekst("B³¹d konfigurowania aplikacji!")
		, STyp::Tekst("Podczas konfigurowania aplikacji wyst¹pi³ wyj¹tek. Komunikat b³êdu : ") + komunikat)
	{
	}

	std::string BladKonfiguracjiAplikacji::napis() const{
		SLog::Logger str(NAZWAKLASY(BladKonfiguracjiAplikacji));
		str.dodajKlase(Wyjatek::napis());
		return str.napis();
	}
};
