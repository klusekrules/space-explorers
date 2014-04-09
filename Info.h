#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste\TypyProste.h"
#include "Parser\XmlBO.h"
#include "NonCopyable.h"
#include "NonMoveable.h"

namespace SpEx{
	/**
	* \brief Klasa bazowa obiektu opisuj�cego.
	*
	* Klasa bazowa dla obiektu opisuj�cego. Zawiera podstawowy opis obiektu. Zawiera wymagania obiektu.
	* \author Daniel Wojdak
	* \version 1
	* \date 22-07-2013
	*/
	class Info :
		virtual public SLog::LoggerInterface,
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:

		enum TYPY_OBIEKTOW {
			NIEZNANY = 0,
			BUDYNEK,
			SUROWIEC,
			TECHNOLOGIA,
			STATEK,
			OBRONA
		};

		virtual ~Info() = default;

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit Info(const STyp::Identyfikator& typ, XmlBO::ElementWezla wezel);

		/**
		* Metoda zwracaj�ca Identyfikator obiektu.
		* \return Identyfikator obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* Metoda ustawiaj�ca identyfikator obiektu.
		* \param[in] identyfikator - Nowa warto�� identyfikatora obiektu.
		*/
		void ustawIdentyfikator(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca nazw� obiektu.
		*/
		const STyp::Tekst& pobierzNazwe() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] nazwa - Nowa warto�� nazwy obiektu.
		*/
		void ustawNazwe(const STyp::Tekst& nazwa);

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca opis obiektu.
		*/
		const STyp::Tekst& pobierzOpis() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] opis - Nowa warto�� opisu obiektu.
		*/
		void ustawOpis(const STyp::Tekst& opis);

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

		const STyp::Identyfikator typ_ = NIEZNANY; /// Typ obiektu.

		const STyp::Tekst& pobierzAdresObrazka() const;

	protected:
		STyp::Tekst adresObrazka_; /// Adres do obrazka wy�wietlonego w GUI.

	private:
		STyp::Tekst nazwa_; /// Nazwa obiektu.
		STyp::Tekst opis_; /// Opis obiektu.
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
	};
}