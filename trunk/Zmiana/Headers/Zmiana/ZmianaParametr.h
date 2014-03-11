#pragma once
#include "ZmianaSymbol.h"
#include "Logger\LoggerInterface.h"
#include "Parser\XmlBO.h"
#include "TypyProste\TypyProste.h"

namespace SZmi{
	/**
	* \brief Klasa reprezentuj¹ca parametr zmiany.
	*
	* Zalecana do przechowywania parametru we w³asnych dopisanych danych. Posiada zaimplemetowany konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \author Daniel Wojdak
	* \version 1
	* \date 10-07-2013
	*/
	class ZMIANA_API ZmianaParametr :
		virtual public SLog::LoggerInterface
	{
	private:
		STyp::Identyfikator idObiektu_ = 0; /// Identyfikatro obiektu.
		STyp::Wartosc wspolczynnikObiektu_ = 0.0; /// Wspó³czynnik przechowywany przez parametr.
	public:
		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a.
		* \param[in] wezel - Wêze³ drzewa XML.
		* \pre Wêze³ powinien posiadaæ poprawne atrybuty o nazwach zdefiniowanych przez ATRYBUT_XML_IDENTYFIKATOR oraz ATRYBUT_XML_WSPOLCZYNNIK.
		* \sa ATRYBUT_XML_IDENTYFIKATOR, ATRYBUT_XML_WSPOLCZYNNIK
		*/
		ZmianaParametr(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~ZmianaParametr() = default;

		/**
		* Metoda zwracaj¹ca identyfikator obiektu.
		* \return Identyfikator obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikatorObiektu()const;

		/**
		* Metoda zwracaj¹ca wspó³czynnik obiektu.
		* \return Wspó³czynnik obiektu.
		*/
		const STyp::Wartosc& pobierzWspolczynnik()const;

		/**
		* Metoda tworz¹ca napis zawieraj¹cy opis obiektu.
		* \return Opis obiektu.
		*/
		std::string napis() const override;
	};
}
