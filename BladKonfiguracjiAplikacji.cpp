#include "BladKonfiguracjiAplikacji.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	BladKonfiguracjiAplikacji::BladKonfiguracjiAplikacji(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& stos, const STyp::Tekst& komunikat)
		: Wyjatek(tPlik, funkcja, iLinia, stos, idBladKonfiguracjiAplikacji, STyp::Tekst("B��d konfigurowania aplikacji!")
		, STyp::Tekst("Podczas konfigurowania aplikacji wyst�pi� wyj�tek. Komunikat b��du : ") + komunikat)
	{
	}

	std::string BladKonfiguracjiAplikacji::napis() const{
		SLog::Logger str(NAZWAKLASY(BladKonfiguracjiAplikacji));
		str.dodajKlase(Wyjatek::napis());
		return str.napis();
	}
};
