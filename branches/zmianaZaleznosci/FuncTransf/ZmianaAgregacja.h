#pragma once
#include "ExportSymbol.h"
#include <vector>
#include <memory>
#include "tinyxml2.h"
#include "..\Logger\LoggerInterface.h"
#include "ZmianaFabryka.h"

/**
* \brief Klasa zmiany agreguj¹cej. 
*
* Sposób dzia³ania metod policzWartosc klasy zmiana agregacja:
*	- Je¿eli nastepna_ jest równa nullptr klasa zwraca wartosc.
*	- Je¿eli nastepna_ jest ró¿na od nullptr
*		-# Wywo³ywana jest metoda policzWartosc na rzecz obiektu nastepna_.
*		-# Wywo³ywane s¹ metody policzWartosc na rzecz obiektów listaZmian_ i jako parametr wartosc przekazywana jest liczba zwrócona przez obiekt nastepny_.
*		-# Sumowane s¹ wszytkie wartoœci zwrócone przez obiekty listaZmian_ i zwracane z funkcji.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
class FUNCTRANSF_API ZmianaAgregacja :
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static ZmianaFabryka* fabryka_; ///  WskaŸnik na fabrykê zmian.
	static const int identyfikator_; /// Identyfikator klasy przekazywany do fabryki.

	/**
	* Metoda tworz¹ca obiekt a podstawie wêz³a.
	* \param[in] wezel - Wêze³ na podstawie którego tworzony jest obiekt.
	* \return WskaŸnika na obiekt utworzonej zmiany.
	*/
	static ZmianaInterfejs* TworzZmianaAgregacja( tinyxml2::XMLElement* wezel );

	std::shared_ptr < ZmianaInterfejs > nastepna_; /// Nastêpna zmiana
	std::vector<std::shared_ptr < ZmianaInterfejs > > listaZmian_; /// Lista zmian, których wartoœci bêd¹ zsumowane.

public:

	/**
	* Metoda rejestruj¹ca klasê w fabryce.
	* \param[in] fabryka - Referencja do globalnej fabryki.
	* \return Metoda zwraca wartoœæ true, je¿eli uda siê zarejestrowaæ klasê. Je¿eli wyst¹pi³ b³¹d zwrócona jest wartoœæ false.
	* \sa ZmianaFabryka
	*/
	static bool RejestrujZmianaAgregacja( ZmianaFabryka &fabryka );

	/**
	* Metoda wyliczaj¹ca wartoœæ.
	* Sposób dzia³ania metod policzWartosc klasy zmiana agregacja:
	*	- Je¿eli nastepna_ jest równa nullptr klasa zwraca wartosc.
	*	- Je¿eli nastepna_ jest ró¿na od nullptr
	*		-# Wywo³ywana jest metoda policzWartosc na rzecz obiektu nastepna_.
	*		-# Wywo³ywane s¹ metody policzWartosc na rzecz obiektów listaZmian_ i jako parametr wartosc przekazywana jest liczba zwrócona przez obiekt nastepny_.
	*		-# Sumowane s¹ wszytkie wartoœci zwrócone przez obiekty listaZmian_ i zwracane z funkcji.
	* \param[in] wartosc - podstawowa wartoœæ parametru, dla kótrego bêdzie wyliczana modyfikacja wartoœci.
	* \param[in] poziom - poziom obiektu, dla którego bêdzie wyliczana modyfikacja wartoœci.
	* \param[in] identyfikatorPlanety - identyfikator planety, na której znajduje siê obiekt.
	* \return Przeliczona wartoœæ atryutu.
	*/
	long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety)const override;

	/**
	* Konstruktor obiektu na podstawie wêz³a XML.
	* \param[in] wezel - Wezel drzewa xml.
	* \pre Wêze³ musi zawieraæ nastêpuj¹c¹ strukturê
	* \code {.xml}
	*	<Zmiana id="n">
	*		<Zmiana id="x" for="nastepny">
	*		  <Param id="0" wspolczynnik="3.0"/>
	*		</Zmiana>
	*		<Zmiana id="y" for="brat">
	*		  <Param id="0" wspolczynnik="5.0"/>
	*		</Zmiana>
	*	</Zmiana>
	* \endcode
	* gdzie elementów \<Zmiana id="y" for="brat"\> mo¿e byæ wiele.
	*/
	explicit ZmianaAgregacja( tinyxml2::XMLElement* wezel );

	/**
	* Konstruktor kopiujacy
	* \param[in] obiekt - Obiekt na podstawie, którego bêdzie utworzona kopia.
	*/
	ZmianaAgregacja( const ZmianaAgregacja& obiekt );

	/**
	* Operator przypisania
	* \param[in] obiekt - Obiekt na podstawie, którego bêdzie utworzona kopia.
	* \return Referencje do obiektu.
	*/
	ZmianaAgregacja& operator=( const ZmianaAgregacja& obiekt );

	/**
	* Metoda tworzy kopiê obiektu.
	* \return WskaŸnik do kopii obiektu.
	* \warning Zwrócony wskaŸnik musi zostac zwolniony operatorem delete. 
	*/
	ZmianaAgregacja* Kopia()const override;

	/**
	* Destruktor
	*/
	virtual ~ZmianaAgregacja();

	/**
	* Metoda tworz¹ca napis zawieraj¹cy opis obiektu.
	* \return Opis obiektu.
	*/
	std::string&& napis() const override;
};
