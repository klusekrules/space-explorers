#include "Wyjatek.h"
#include "Logger\LoggerNazwaKlasy.h"
#include "Logger\Logger.h"

namespace STyp{

	Wyjatek::Wyjatek(const Tekst& plik, const Tekst& funkcja, const Ilosc& linia, const Tekst& sladStosu, const Tekst& debug, const Identyfikator& id, const Tekst& tytul, const Tekst& tresc)
		: identyfikator_(id), tytul_(tytul), tresc_(tresc), plik_(plik), funkcja_(funkcja), linia_(linia), stack_(sladStosu), data_(Tekst(__DATE__) + Tekst(", ") + Tekst(__TIME__)), debug_(debug)
	{
	}

	Tekst Wyjatek::generujKomunikat()const
	{
		return std::move(Tekst("Tytul: ") + tytul_ +
			Tekst("\nID: ") + identyfikator_.napis() +
			Tekst("\nPlik: ") + plik_ +
			Tekst("\nFunkcja: ") + funkcja_ +
			Tekst("\nLinia: ") + linia_.napis() +
			Tekst("\nData kompilacji: ") + data_ +
			Tekst("\nTresc: ") + tresc_ +
			Tekst("\nStos wywo³añ: ") + stack_ + Tekst("\n"));
	}

	const Identyfikator& Wyjatek::getNumerWyjaku() const{
		return identyfikator_;
	}

	const Tekst& Wyjatek::getTytul() const{
		return tytul_;
	}

	const Tekst& Wyjatek::getTresc() const{
		return tresc_;
	}

	const Tekst& Wyjatek::getDebug() const{
		return debug_;
	}

	std::string Wyjatek::napis() const{
		SLog::Logger str(NAZWAKLASY(Wyjatek));
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator_);
		str.dodajPole(NAZWAPOLA(tytul_), tytul_);
		str.dodajPole(NAZWAPOLA(tresc_), tresc_);
		str.dodajPole(NAZWAPOLA(funkcja_), funkcja_);
		str.dodajPole(NAZWAPOLA(plik_), plik_);
		str.dodajPole(NAZWAPOLA(linia_), linia_);
		str.dodajPole(NAZWAPOLA(data_), data_);
		str.dodajPole(NAZWAPOLA(stack_), stack_);
		str.dodajPole(NAZWAPOLA(debug_), debug_);
		return std::move(str.napis());
	}

	const char * Wyjatek::what()const{
		komunikat_ = std::move(generujKomunikat());
		return komunikat_().c_str();
	}
}
