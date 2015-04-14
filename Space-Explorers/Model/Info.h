#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste\TypyProste.h"
#include "Parser\XmlBO.h"
#include "Utils\NonCopyable.h"
#include "Utils\NonMoveable.h"

namespace SpEx{
	/**
	* \brief Klasa bazowa obiektu opisuj¹cego.
	*
	* Klasa bazowa dla obiektu opisuj¹cego. Zawiera podstawowy opis obiektu. Zawiera wymagania obiektu.
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
		* \brief Wyliczenie wszystkich typów obiektów.
		*
		* Wszystkie typy obiektów.
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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Info() = default;

		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \param[in] typ - Typ obiektu opisuj¹cego.
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
		* \deprecated Metoda przeznaczona do usuniêcia.
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
		* \deprecated Metoda przeznaczona do usuniêcia.
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
		* \deprecated Metoda przeznaczona do usuniêcia.
		*/
		void ustawOpis(const STyp::Tekst& opis);

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda pobieraj¹ca adres obrazka.
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
		STyp::Identyfikator idObrazka_; /// Identyfikator do obrazka wyœwietlonego w GUI.

	private:
		STyp::Tekst nazwa_; /// Nazwa obiektu.
		STyp::Tekst opis_; /// Opis obiektu.
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
	};
}