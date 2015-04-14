#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste\TypyProste.h"
#include "Parser\XmlBO.h"
#include "Utils\NonCopyable.h"
#include "Utils\NonMoveable.h"

namespace SpEx{
	/**
	* \brief Klasa bazowa obiektu opisuj�cego.
	*
	* Klasa bazowa dla obiektu opisuj�cego. Zawiera podstawowy opis obiektu. Zawiera wymagania obiektu.
	* \author Daniel Wojdak
	* \version 2
	* \date 14-07-2014
	*/
	class Info :
		virtual public SLog::LoggerInterface,
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:
		/**
		* \brief Wyliczenie wszystkich typ�w obiekt�w.
		*
		* Wszystkie typy obiekt�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		enum TYPY_OBIEKTOW {
			NIEZNANY = 0,
			BUDYNEK,
			SUROWIEC,
			TECHNOLOGIA,
			STATEK,
			OBRONA
		};

		Info() = delete;

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Info() = default;

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \param[in] typ - Typ obiektu opisuj�cego.
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
		* \deprecated Metoda przeznaczona do usuni�cia.
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
		* \deprecated Metoda przeznaczona do usuni�cia.
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
		* \deprecated Metoda przeznaczona do usuni�cia.
		*/
		void ustawOpis(const STyp::Tekst& opis);

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda pobieraj�ca adres obrazka.
		*
		* Metoda pobiera adres obrazka.
		* \return Adres do obrazka obiektu.
		* \author Daniel Wojdak
		* \version 2
		* \date 09-09-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikatorObrazka() const;

		const STyp::Identyfikator typ_ = NIEZNANY; /// Typ obiektu.

	protected:
		STyp::Identyfikator idObrazka_; /// Identyfikator do obrazka wy�wietlonego w GUI.

	private:
		STyp::Tekst nazwa_; /// Nazwa obiektu.
		STyp::Tekst opis_; /// Opis obiektu.
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
	};
}