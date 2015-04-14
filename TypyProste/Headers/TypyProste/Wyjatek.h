#pragma once
#include "TypyProste.h"

namespace STyp{

	//Makro wstawiajace nazwe pliku i liniê i datê pliku.
	#define EXCEPTION_PLACE STyp::Tekst(__FILE__) , STyp::Tekst(__func__) , STyp::Ilosc(__LINE__) 

	/**
	* \brief Klasa wyj¹tku parsera.
	*
	* Podstawowa klasa wyj¹tku. S³u¿¹ca jako klasa bazowa dla pozosta³ych wyj¹tków
	* lub jako klasa do tworzenia wyj¹tków nie posiadaj¹cych w³asnego typu.
	* \author Daniel Wojdak
	* \version 1
	* \date 25-06-2014
	*/
	class TYPY_PROSTE_LIB Wyjatek :
		public std::exception,
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* \brief Konstruktor wyj¹tku.
		*
		* Konstruktor ogólnego wyj¹tku.
		* \param[in] plik - Plik w którym wyst¹pi³ wyj¹tek.
		* \param[in] funkcja - Funkcja w której wyst¹pi³ wyj¹tek.
		* \param[in] linia - Linia w pliku w której wyst¹pi³ wyj¹tek.
		* \param[in] sladStosu - Œlad stosu w momencie wyst¹pienia wyj¹tku.
		* \param[in] id - Identyfikator wyj¹tku.
		* \param[in] tytul - Tytu³ wyj¹tku.
		* \param[in] tresc - Opis Wyj¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-06-2014
		*/
		Wyjatek(
			const Tekst& plik,
			const Tekst& funkcja,
			const Ilosc& linia,
			const Tekst& sladStosu,
			const Identyfikator& id = Identyfikator(),
			const Tekst& tytul = Tekst(),
			const Tekst& tresc = Tekst()
			);

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Domyœlny konstruktor kopiuj¹cy.
		* \param[in] obiekt - Obiekt Ÿród³owy.
		*/
		Wyjatek(const Wyjatek& obiekt) = default;

		/**
		* \brief Destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Wyjatek() = default;

		/**
		* \brief Metoda generuj¹ca komunikat.
		*
		* Metoda generuj¹ca komunikat opisuj¹cy sytuacje wyst¹pienia wyj¹tku.
		* \return Tekst opisuj¹cy wyj¹tek.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-06-2014
		*/
		virtual Tekst generujKomunikat() const;

		/**
		* \brief Metoda pobieraj¹ca identyfikator.
		*
		* Metoda pobiera identyfikator wyj¹tku.
		* \return Identyfikator wyj¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-06-2014		
		*/
		const Identyfikator& getNumerWyjaku() const;

		/**
		* \brief Metoda pobieraj¹ca tytu³.
		*
		* Metoda pobiera tytu³ wyj¹tku.
		* \return Tytu³ wyj¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-06-2014
		*/
		const Tekst& getTytul() const;

		/**
		* \brief Metoda pobieraj¹ca opis.
		*
		* Metoda pobiera opis wyj¹tku.
		* \return Opis wyj¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-06-2014
		*/
		const Tekst& getTresc() const;

		/**
		* \brief Metoda zwracaj¹ca opis obiektu.
		*
		* Metoda zwraca opis obiektu.
		* \return Tekst opisuj¹cy ca³y obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-06-2014
		*/
		std::string napis() const override;

		/**
		* \brief Metoda zwracaj¹ca komunikat wyj¹tku.
		*
		* Metoda zwraca komunikat wyj¹tku.
		* \return Tekst opisuj¹cy wyj¹tek.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-06-2014
		*/
		const char * what() const override;

	protected:
		Identyfikator identyfikator_; /// Identyfikator wyj¹tku.
		Tekst tytul_; /// Tytu³ wyj¹tku.
		Tekst tresc_; /// Opis wyj¹tku.
		Tekst plik_; /// Plik, w którym wyst¹pi³ wyj¹tek. 
		Tekst funkcja_; /// Funkcja, w której wyst¹pi³ wyj¹tek.
		Ilosc linia_; /// Linia, w której wyst¹pi³ wyj¹tek.
		Tekst data_; /// Data kompilacji klasy.
		Tekst stack_; /// Œlad stosu w momencie wyst¹pienia wyj¹tku.

		mutable Tekst komunikat_; /// Obiekt przechowuj¹cy komunikat.
	};
}
