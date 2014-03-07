#pragma once
#include "TypyProste.h"

namespace STyp{

	//Makro wstawiajace nazwe pliku i liniê i datê pliku.
	#define EXCEPTION_PLACE STyp::Tekst(__FILE__) , STyp::Tekst(__func__) , STyp::Ilosc(__LINE__) 

	/**
	* Podstawowa klasa wyj¹tku. S³u¿¹ca jako klasa bazowa dla pozosta³ych wyj¹tków
	* lub jako klasa do tworzenia wyj¹tków nie posiadaj¹cych w³asnego typu.
	*/
	class TYPY_PROSTE_LIB Wyjatek :
		public std::exception,
		virtual public SLog::LoggerInterface
	{
	public:
		Wyjatek(
			const Tekst& plik,
			const Tekst& funkcja,
			const Ilosc& linia,
			const Tekst& sladStosu,
			const Identyfikator& id = Identyfikator(),
			const Tekst& tytul = Tekst(),
			const Tekst& tresc = Tekst()
			);
		Wyjatek(const Wyjatek&) = default;
		virtual ~Wyjatek() = default;

		virtual Tekst generujKomunikat() const;
		const Identyfikator& getNumerWyjaku() const;
		const Tekst& getTytul() const;
		const Tekst& getTresc() const;
		std::string napis() const override;
		const char * what() const override;
	protected:
		Identyfikator identyfikator_;
		Tekst tytul_;
		Tekst tresc_;
		Tekst plik_;
		Tekst funkcja_;
		Ilosc linia_;
		Tekst data_;
		Tekst stack_;

		mutable Tekst komunikat_;
	};
}
