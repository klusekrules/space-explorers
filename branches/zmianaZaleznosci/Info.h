#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste\TypyProste.h"
#include "Parser\XmlBO.h"
#include "NonCopyable.h"
#include "NonMoveable.h"

namespace SpEx{
	/**
	* \brief Klasa bazowa obiektu opisuj¹cego.
	*
	* Klasa bazowa dla obiektu opisuj¹cego. Zawiera podstawowy opis obiektu. Zawiera wymagania obiektu.
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
		virtual ~Info() = default;

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
		
		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		*/
		explicit Info(XmlBO::ElementWezla wezel);

		/**
		* Metoda zwracaj¹ca Identyfikator obiektu.
		* \return Identyfikator obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* Metoda ustawiaj¹ca identyfikator obiektu.
		* \param[in] identyfikator - Nowa wartoœæ identyfikatora obiektu.
		*/
		void ustawIdentyfikator(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca nazwê obiektu.
		*/
		const STyp::Tekst& pobierzNazwe() const;

		/**
		* \brief Metoda ustawiaj¹ca atrybut.
		*
		* Metoda ustawiaj¹ca atrybut obiektu.
		* \param[in] nazwa - Nowa wartoœæ nazwy obiektu.
		*/
		void ustawNazwe(const STyp::Tekst& nazwa);

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca opis obiektu.
		*/
		const STyp::Tekst& pobierzOpis() const;

		/**
		* \brief Metoda ustawiaj¹ca atrybut.
		*
		* Metoda ustawiaj¹ca atrybut obiektu.
		* \param[in] opis - Nowa wartoœæ opisu obiektu.
		*/
		void ustawOpis(const STyp::Tekst& opis);

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Tekst nazwa_; /// Nazwa obiektu.
		STyp::Tekst opis_; /// Opis obiektu.
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
	};
}