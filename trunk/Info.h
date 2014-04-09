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
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		*/
		explicit Info(const STyp::Identyfikator& typ, XmlBO::ElementWezla wezel);

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

		const STyp::Identyfikator typ_ = NIEZNANY; /// Typ obiektu.

		const STyp::Tekst& pobierzAdresObrazka() const;

	protected:
		STyp::Tekst adresObrazka_; /// Adres do obrazka wyœwietlonego w GUI.

	private:
		STyp::Tekst nazwa_; /// Nazwa obiektu.
		STyp::Tekst opis_; /// Opis obiektu.
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
	};
}