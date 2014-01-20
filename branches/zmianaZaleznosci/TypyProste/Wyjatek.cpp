#include "Wyjatek.h"
#include "Logger\LoggerNazwaKlasy.h"
#include "Logger\Logger.h"

namespace STyp{

	Wyjatek::Wyjatek(const Tekst& plik, const Ilosc& linia, const Tekst& sladStosu, const Identyfikator& id, const Tekst& tytul, const Tekst& tresc)
		: identyfikator_(id), tytul_(tytul), tresc_(tresc), plik_(plik), linia_(linia), stack_(sladStosu), data_(Tekst(__DATE__) + Tekst(", ") + Tekst(__TIME__))
	{
	}

	Tekst Wyjatek::generujKomunikat()const
	{
		return std::move(Tekst("Tytul: ") + tytul_ +
			Tekst("\nID: ") + identyfikator_.napis() +
			Tekst("\nPlik: ") + plik_ +
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

	std::string Wyjatek::napis() const{
		SLog::Logger str(NAZWAKLASY(Wyjatek));
		str.dodajPole("ID", identyfikator_);
		str.dodajPole("Tytul", tytul_);
		str.dodajPole("Tresc", tresc_);
		str.dodajPole("Plik", plik_);
		str.dodajPole("Linia", linia_);
		str.dodajPole("Data", data_);
		str.dodajPole("StackTrace", stack_);
		return std::move(str.napis());
	}

	const char * Wyjatek::what()const{
		komunikat_ = std::move(generujKomunikat());
		return komunikat_().c_str();
	}
}
