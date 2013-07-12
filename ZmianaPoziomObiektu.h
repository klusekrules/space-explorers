#pragma once
#include "FuncTransf\ZmianaFabryka.h"
#include "FuncTransf\ZmianaParametr.h"
/**
* \brief Klasa reprezentuj¹ca zmianê poziom obiektu.
*
* Sposób dzia³ania metody wyliczajacej:
*	- Zwraca poziom obiektu o id podanym w parametrze. Obiekt sprawdzany jest na planecie o id podanej jako 3 parametr funkcji.
* \author Daniel Wojdak
* \version 1
* \date 11-07-2013
*/
class ZmianaPoziomObiektu:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int identyfikator_; /// Identyfikator klasy przekazywany do fabryki.

	/**
	* Metoda tworz¹ca obiekt a podstawie wêz³a.
	* \param[in] wezel - Wêze³ na podstawie którego tworzony jest obiekt.
	* \return WskaŸnika na obiekt utworzonej zmiany.
	*/
	static ZmianaInterfejs* TworzZmianaPoziomObiektu( TiXmlElement* wezel );

	ZmianaParametr parametr_; /// Identyfikator obiektu.
public:

	/**
	* Metoda rejestruj¹ca klasê w fabryce.
	* \param[in] fabryka - Referencja do globalnej fabryki.
	* \return Metoda zwraca wartoœæ true, je¿eli uda siê zarejestrowaæ klasê. Je¿eli wyst¹pi³ b³¹d zwrócona jest wartoœæ false.
	* \sa ZmianaFabryka
	*/
	static bool RejestrujZmianaPoziomObiektu( ZmianaFabryka &fabryka );

	/**
	* Metoda wyliczaj¹ca wartoœæ.
	* Sposób dzia³ania metod policzWartosc klasy zmiana agregacja:
	*	- Zwraca poziom obiektu o id podanym w parametrze. Obiekt sprawdzany jest na planecie o id podanej jako 3 parametr funkcji.
	* \param[in] wartosc - podstawowa wartoœæ parametru, dla kótrego bêdzie wyliczana modyfikacja wartoœci.
	* \param[in] poziom - poziom obiektu, dla którego bêdzie wyliczana modyfikacja wartoœci.
	* \param[in] identyfikatorPlanety - identyfikator planety, na której znajduje siê obiekt.
	* \return Przeliczona wartoœæ atryutu.
	*/
	long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const override;

	/**
	* Metoda tworzy kopiê obiektu.
	* \return WskaŸnik do kopii obiektu.
	* \warning Zwrócony wskaŸnik musi zostac zwolniony operatorem delete. 
	*/
	ZmianaPoziomObiektu* Kopia()const override;

	/**
	* Konstruktor obiektu na podstawie wêz³a XML.
	* \param[in] wezel - Wezel drzewa xml.
	* \pre Wêze³ musi zawieraæ nastêpuj¹c¹ strukturê
	* \code {.xml}
	*	<Zmiana id="n">
	*		<Param id="0x3"/>
	*	</Zmiana>
	* \endcode
	*/
	explicit ZmianaPoziomObiektu( TiXmlElement * wezel );

	/**
	* Destruktor
	*/
	virtual ~ZmianaPoziomObiektu();

	/**
	* Metoda tworz¹ca napis zawieraj¹cy opis obiektu.
	* \return Opis obiektu.
	*/
	string napis () const override;

};

/**
* Funkcja eksportowana s³u¿¹ca do rejestracji zmiany w fabryce.
* \param[in,out] fabryka - Referencja do fabryki, w której ma zostaæ zarejestrowana klasa.
* \param[in] logger - referencja do loggera, dla komunikacji o b³êdach.
* \return Funkcja zwraca true, je¿eli uda siê zarejestrowaæ klasê lub false w przeciwnym wypadku.
*/
bool RejestrujZmianaPoziomObiektu ( ZmianaFabryka& fabryka , Log& logger );
