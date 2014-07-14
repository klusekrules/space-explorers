#pragma once
#include "Zmiana\ZmianaFabryka.h"
#include "Zmiana\ZmianaParametr.h"

namespace SpEx {
	/**
	* \brief Klasa reprezentuj¹ca zmianê poziom obiektu.
	*
	* Sposób dzia³ania metody wyliczajacej:
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
		* \brief Metoda tworz¹ca obiekt.
		*
		* Metoda tworz¹ca obiekt a podstawie wêz³a.
		* \param[in] wezel - Wêze³ na podstawie którego tworzony jest obiekt.
		* \return WskaŸnika na obiekt utworzonej zmiany.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		static SZmi::ZmianaInterfejs* TworzZmianaPoziomObiektu(XmlBO::ElementWezla wezel);

		SZmi::ZmianaParametr parametr_; /// Identyfikator obiektu.
	public:

		/**
		* \brief Metoda rejestruj¹ca klasê.
		*
		* Metoda rejestruj¹ca klasê w fabryce.
		* \param[in] fabryka - Referencja do globalnej fabryki.
		* \return Metoda zwraca wartoœæ true, je¿eli uda siê zarejestrowaæ klasê. Je¿eli wyst¹pi³ b³¹d zwrócona jest wartoœæ false.
		* \sa ZmianaFabryka
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		static bool RejestrujZmianaPoziomObiektu(SZmi::ZmianaFabryka &fabryka);

		/**
		* \brief Metoda wyliczaj¹ca wartoœæ.
		*
		* Metoda wyliczaj¹ca wartoœæ.
		* Sposób dzia³ania metod policzWartosc klasy zmiana agregacja:
		*	- Zwraca poziom obiektu o id podanym w parametrze. Obiekt sprawdzany jest na planecie o id podanej jako 3 parametr funkcji.
		* \param[in] wartosc - podstawowa wartoœæ parametru, dla kótrego bêdzie wyliczana modyfikacja wartoœci.
		* \param[in] poziom - poziom obiektu, dla którego bêdzie wyliczana modyfikacja wartoœci.
		* \param[in] identyfikatorPlanety - identyfikator planety, na której znajduje siê obiekt.
		* \return Przeliczona wartoœæ atryutu.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		STyp::Wartosc policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety) const override;

		/**
		* \brief Metoda tworz¹ca kopiê obiektu.
		*
		* Metoda tworzy kopiê obiektu.
		* \return WskaŸnik do kopii obiektu.
		* \warning Zwrócony wskaŸnik musi zostac zwolniony operatorem delete.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		ZmianaPoziomObiektu* Kopia()const override;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor obiektu na podstawie wêz³a XML.
		* \param[in] wezel - Wezel drzewa xml.
		* \pre Wêze³ musi zawieraæ nastêpuj¹c¹ strukturê
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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ZmianaPoziomObiektu() = default;

		/**
		* Metoda tworz¹ca napis zawieraj¹cy opis obiektu.
		* \return Opis obiektu.
		*/
		std::string napis() const override;

	};

	/**
	* \brief Funkcja rejestruj¹ca klasê.
	*
	* Funkcja eksportowana s³u¿¹ca do rejestracji zmiany w fabryce.
	* \param[inout] fabryka - Referencja do fabryki, w której ma zostaæ zarejestrowana klasa.
	* \param[in] logger - referencja do loggera, dla komunikacji o b³êdach.
	* \return Funkcja zwraca true, je¿eli uda siê zarejestrowaæ klasê lub false w przeciwnym wypadku.
	* \author Daniel Wojdak
	* \version 1
	* \date 11-07-2013
	*/
	bool RejestrujZmianaPoziomObiektu(SZmi::ZmianaFabryka& fabryka, SLog::Log& logger);
}