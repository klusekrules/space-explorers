#include "BladKonfiguracjiEkranu.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	const STyp::Identyfikator BladKonfiguracjiEkranu::idBladKonfiguracjiEkranu(0x7);

	BladKonfiguracjiEkranu::BladKonfiguracjiEkranu(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Identyfikator& ekran, const STyp::Tekst& komunikat)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), idBladKonfiguracjiEkranu, STyp::Tekst("B³¹d konfigurowania okna!")
		, STyp::Tekst("Podczas konfigurowania okna o id: "+ ekran.napis() + " wyst¹pi³ wyj¹tek. Komunikat b³êdu : ") + komunikat),
		identyfikator_(ekran)
	{
	}
	
	const STyp::Identyfikator& BladKonfiguracjiEkranu::pobierzIdEkranu() const{
		return identyfikator_;
	}

	std::string BladKonfiguracjiEkranu::napis() const{
		SLog::Logger str(NAZWAKLASY(BladKonfiguracjiEkranu));
		str.dodajKlase(Wyjatek::napis());
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator_);
		return str.napis();
	}
};
