#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste\TypyProste.h"
#include "Parser\XmlBO.h"

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
		virtual public SLog::LoggerInterface
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* Podstawowy konstruktor obiektu.
		* \param[in] nazwa - Nazwa obiektu.
		* \param[in] opis - Opis obiektu.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \param[in] wymagania - Wymagania obiektu.
		*/
		Info(const STyp::Tekst& nazwa, const STyp::Tekst& opis, const STyp::Identyfikator& identyfikator);

		Info(const Info&) = delete;
		Info& operator=(const Info&) = delete;

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit Info(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~Info() = default;

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

	private:
		STyp::Tekst nazwa_; /// Nazwa obiektu.
		STyp::Tekst opis_; /// Opis obiektu.
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
	};
}