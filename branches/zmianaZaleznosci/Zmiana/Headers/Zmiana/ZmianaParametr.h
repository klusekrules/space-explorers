#pragma once
#include "ZmianaSymbol.h"
#include "Logger\LoggerInterface.h"
#include "Parser\XmlBO.h"
#include "TypyProste\TypyProste.h"

namespace SZmi{
	/**
	* \brief Klasa reprezentuj�ca parametr zmiany.
	*
	* Zalecana do przechowywania parametru we w�asnych dopisanych danych. Posiada zaimplemetowany konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \author Daniel Wojdak
	* \version 1
	* \date 10-07-2013
	*/
	class ZMIANA_API ZmianaParametr :
		virtual public SLog::LoggerInterface
	{
	private:
		STyp::Identyfikator idObiektu_ = 0; /// Identyfikatro obiektu.
		STyp::Wartosc wspolczynnikObiektu_ = 0.0; /// Wsp�czynnik przechowywany przez parametr.
	public:
		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a.
		* \param[in] wezel - W�ze� drzewa XML.
		* \pre W�ze� powinien posiada� poprawne atrybuty o nazwach zdefiniowanych przez ATRYBUT_XML_IDENTYFIKATOR oraz ATRYBUT_XML_WSPOLCZYNNIK.
		* \sa ATRYBUT_XML_IDENTYFIKATOR, ATRYBUT_XML_WSPOLCZYNNIK
		*/
		ZmianaParametr(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~ZmianaParametr() = default;

		/**
		* Metoda zwracaj�ca identyfikator obiektu.
		* \return Identyfikator obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikatorObiektu()const;

		/**
		* Metoda zwracaj�ca wsp�czynnik obiektu.
		* \return Wsp�czynnik obiektu.
		*/
		const STyp::Wartosc& pobierzWspolczynnik()const;

		/**
		* Metoda tworz�ca napis zawieraj�cy opis obiektu.
		* \return Opis obiektu.
		*/
		std::string napis() const override;
	};
}
