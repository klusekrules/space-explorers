#pragma once
#include "Zmiana\ZmianaFabryka.h"
#include "Zmiana\ZmianaParametr.h"

namespace SpEx {
	/**
	* \brief Klasa reprezentuj�ca zmian� poziom obiektu.
	*
	* Spos�b dzia�ania metody wyliczajacej:
	*	- Zwraca poziom obiektu o id podanym w parametrze. Obiekt sprawdzany jest na planecie o id podanej jako 3 parametr funkcji.
	* \author Daniel Wojdak
	* \version 1
	* \date 11-07-2013
	*/
	class ZmianaPoziomObiektu :
		public SZmi::ZmianaInterfejs,
		virtual public SLog::LoggerInterface
	{
	private:
		static const STyp::Identyfikator identyfikator_; /// Identyfikator klasy przekazywany do fabryki.

		/**
		* \brief Metoda tworz�ca obiekt.
		*
		* Metoda tworz�ca obiekt a podstawie w�z�a.
		* \param[in] wezel - W�ze� na podstawie kt�rego tworzony jest obiekt.
		* \return Wska�nika na obiekt utworzonej zmiany.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		static SZmi::ZmianaInterfejs* TworzZmianaPoziomObiektu(XmlBO::ElementWezla wezel);

		SZmi::ZmianaParametr parametr_; /// Identyfikator obiektu.
	public:

		/**
		* \brief Metoda rejestruj�ca klas�.
		*
		* Metoda rejestruj�ca klas� w fabryce.
		* \param[in] fabryka - Referencja do globalnej fabryki.
		* \return Metoda zwraca warto�� true, je�eli uda si� zarejestrowa� klas�. Je�eli wyst�pi� b��d zwr�cona jest warto�� false.
		* \sa ZmianaFabryka
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		static bool RejestrujZmianaPoziomObiektu(SZmi::ZmianaFabryka &fabryka);

		/**
		* \brief Metoda wyliczaj�ca warto��.
		*
		* Metoda wyliczaj�ca warto��.
		* Spos�b dzia�ania metod policzWartosc klasy zmiana agregacja:
		*	- Zwraca poziom obiektu o id podanym w parametrze. Obiekt sprawdzany jest na planecie o id podanej jako 3 parametr funkcji.
		* \param[in] wartosc - podstawowa warto�� parametru, dla k�trego b�dzie wyliczana modyfikacja warto�ci.
		* \param[in] poziom - poziom obiektu, dla kt�rego b�dzie wyliczana modyfikacja warto�ci.
		* \param[in] identyfikatorPlanety - identyfikator planety, na kt�rej znajduje si� obiekt.
		* \return Przeliczona warto�� atryutu.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		STyp::Wartosc policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety) const override;

		/**
		* \brief Metoda tworz�ca kopi� obiektu.
		*
		* Metoda tworzy kopi� obiektu.
		* \return Wska�nik do kopii obiektu.
		* \warning Zwr�cony wska�nik musi zostac zwolniony operatorem delete.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		ZmianaPoziomObiektu* Kopia()const override;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor obiektu na podstawie w�z�a XML.
		* \param[in] wezel - Wezel drzewa xml.
		* \pre W�ze� musi zawiera� nast�puj�c� struktur�
		* \code {.xml}
		*	<Zmiana id="n">
		*		<Param id="0x3"/>
		*	</Zmiana>
		* \endcode
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		explicit ZmianaPoziomObiektu(XmlBO::ElementWezla wezel);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ZmianaPoziomObiektu() = default;

		/**
		* Metoda tworz�ca napis zawieraj�cy opis obiektu.
		* \return Opis obiektu.
		*/
		std::string napis() const override;

	};

	/**
	* \brief Funkcja rejestruj�ca klas�.
	*
	* Funkcja eksportowana s�u��ca do rejestracji zmiany w fabryce.
	* \param[inout] fabryka - Referencja do fabryki, w kt�rej ma zosta� zarejestrowana klasa.
	* \param[in] logger - referencja do loggera, dla komunikacji o b��dach.
	* \return Funkcja zwraca true, je�eli uda si� zarejestrowa� klas� lub false w przeciwnym wypadku.
	* \author Daniel Wojdak
	* \version 1
	* \date 11-07-2013
	*/
	bool RejestrujZmianaPoziomObiektu(SZmi::ZmianaFabryka& fabryka, SLog::Log& logger);
}