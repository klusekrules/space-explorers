#pragma once
#include "ExportSymbol.h"
#include "..\parser\ticpp.h"
#include "ZmianaInterfejs.h"
#include <map>
#include <memory>
#include "..\Logger\Log.h"
using std::shared_ptr;
using std::map;

/**
* \brief Fabryka klas zmian
*
* Klasa tworz¹ca instacje klas zmian. Klasa implementuje wzorzec singleton.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
class FUNCTRANSF_API ZmianaFabryka
{
public:
	/**
	* Prototyp funkcji tworz¹cej instacjê obiektu danej klasy.
	* \param[in] wezel - Wezel na podstawie, którego tworzony jest obiekt.
	* \return WskaŸnik na obiekt pochodny po ZmianaInterfejs.
	*/
	typedef ZmianaInterfejs* (*KreatorZmiany)( TiXmlElement* wezel );

	/**
	* Prototyp funkcji rejestruj¹cej klasê zmiany w fabryce.
	* \param[in,out] fabryka - Instacja fabryki, w której nale¿y zarejestrowaæ zmianê, aby aplikacja potrafi³a utworzyæ obiekt zmiany.
	* \param[in,out] logger - Instacja loggera do wyœwietlania komunikatów o b³êdach.
	* \return Funkcja powinna zwracaæ true, jeœli rejestracja siê powiedzie lub false w przeciwnym wypadku.
	* \warning Funkcja powonna wywo³ywaæ na rzecz obiektu fabryka metodê RejestracjaZmiany.
	* \sa RejestracjaZmiany()
	*/
	typedef bool (*RejestrujZmiane)( ZmianaFabryka& fabryka , Log& logger );

	/**
	* Metoda pobieraj¹ca instancjê klasy ZmianaFabryka.
	* \return Obiekt klasy ZmianaFabryka.
	*/
	static ZmianaFabryka& pobierzInstancje();
	
	/**
	* Metoda tworz¹ca obiekt klasy zmiana zarejestrownej w fabryce, na podstawie wêz³a przekazanego przez parametr wezel. Wywo³uje ona funckjê zarejestrowan¹ przez metodê rejestracjaZmiany i przekazuje jej wezel.
	* \param[in] wezel - Wêze³ na podstawie, którego tworzony jest obiekt klasy zmiana.
	* \return Metoda zwraca inteligenty wskaŸnik na utworzony obiekt. Je¿eli operacja siê nie powiedzie zwracany jest wska¿nik na nullptr.
	* \warning Metoda wymaga, aby w wêŸle by³ atrybut o nazwie zdefiniowanej przez ATRYBUT_XML_IDENTYFIKATOR zawieraj¹cy identyfikator podany podczas rejestracji w funkcji rejestracjaZmiany.
	* \sa rejestracjaZmiany(), ATRYBUT_XML_IDENTYFIKATOR
	*/
	shared_ptr<ZmianaInterfejs> Tworz( TiXmlElement* wezel ) const;

	/**
	* Metoda rejestruj¹ca funkcjê tworz¹c¹ obiekt pochodny po ZmianaInterfejs.
	* \param[in] identyfikator - Identyfikator funckji.
	* \param[in] funkcja - Funkcja tworz¹ca.
	* \return Metoda zwraca true, je¿eli rejestracja siê powiedzie lub false w przeciwnym wypadku.
	* \warning Zabronionym identyfikatorem jest 0. Je¿eli poda siê taki identyfikator to metoda zawsze zwróci wartoœæ false. Jest to podyktowane implementaj¹ metody. Inne warunki kiedy metoda zwróci false to: funkcja wskazuje na nullptr lub identyfikator zosta³ ju¿ u¿yty.
	*/
	bool rejestracjaZmiany(int identyfikator, KreatorZmiany funkcja );

private:

	/**
	* Typ zbioru funkcji tworz¹cych obiekt.
	*/
	typedef map<int, KreatorZmiany> Callbacks;
	Callbacks callbacks_; // S³ownik funkcji tworz¹cych obiekty pochodzne po ZmianaInterfejs.

	/**
	* Konstruktor bezparametrowy.
	*/
	ZmianaFabryka();

	/**
	* Konstruktor kopiuj¹cy.
	* \param[in] obiekt - Obiekt klasy ZmianaFabryka, z którego zostanie utworzony kolejny obiekt.
	*/
	ZmianaFabryka( const ZmianaFabryka& obiekt );

	/**
	* Operator przypisania.
	* \param[in] obiekt - Obiekt klasy ZmianaFabryka, z którego zostanie utworzona kopia.
	* \return Referencja do obiektu klasy ZmianaFabryka.
	*/
	ZmianaFabryka& operator=(const ZmianaFabryka& obiekt );
};
