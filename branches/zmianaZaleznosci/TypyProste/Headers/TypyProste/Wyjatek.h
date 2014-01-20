#pragma once
#include "TypyProste.h"


#pragma warning(disable: 4251)

#ifdef _WIN32
#   ifdef TYPY_PROSTE_EXPORT
#       define TYPY_PROSTE_LIB __declspec(dllexport)
#   elif defined(TYPY_PROSTE_IMPORT)
#       define TYPY_PROSTE_LIB __declspec(dllimport)
#   else
#       define TYPY_PROSTE_LIB
#   endif
#else
#   define TYPY_PROSTE_LIB
#endif


namespace STyp{

	//Makro wstawiajace nazwe pliku i liniê i datê pliku.
	#define EXCEPTION_PLACE STyp::Tekst(__FILE__) , STyp::Ilosc(__LINE__)

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
		Ilosc linia_;
		Tekst data_;
		Tekst stack_;

		mutable Tekst komunikat_;
	};
}
