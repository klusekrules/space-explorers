#pragma once
#include "ExportSymbol.h"
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"
#include "ZmianaFabryka.h"
#include "..\parser\ticpp.h"

/**
* \brief Klasa reprezentuj¹ca zmianê liniow¹.
*
* Sposób dzia³ania metody wyliczajacej:
*	- Wartoœæ atrybutu mno¿ona jest przez wspó³czynik pobrany z parametru i to mno¿one jest przez poziom przekazany w parametrze. ( wartosc * parametr_ * poziom )
* \author Daniel Wojdak
* \version 1
* \date 11-07-2013
*/
class FUNCTRANSF_API ZmianaLiniowa:
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
	static ZmianaInterfejs* TworzZmianaLiniowa( TiXmlElement* wezel );

	ZmianaParametr parametr_; /// Wspó³czynnik o jaki zmienia siê wartoœæ atrybutu.

public:

	/**
	* Metoda rejestruj¹ca klasê w fabryce.
	* \param[in] fabryka - Referencja do globalnej fabryki.
	* \return Metoda zwraca wartoœæ true, je¿eli uda siê zarejestrowaæ klasê. Je¿eli wyst¹pi³ b³¹d zwrócona jest wartoœæ false.
	* \sa ZmianaFabryka
	*/
	static bool RejestrujZmianaLiniowa( ZmianaFabryka &fabryka );

	/**
	* Metoda wyliczaj¹ca wartoœæ.
	* Sposób dzia³ania metod policzWartosc klasy zmiana agregacja:
	*	- Wartoœæ atrybutu mno¿ona jest przez wspó³czynik pobrany z parametru i to mno¿one jest przez poziom przekazany w parametrze. ( wartosc * parametr_ * poziom )
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
	ZmianaLiniowa* Kopia()const override;

	/**
	* Konstruktor obiektu na podstawie wêz³a XML.
	* \param[in] wezel - Wezel drzewa xml.
	* \pre Wêze³ musi zawieraæ nastêpuj¹c¹ strukturê
	* \code {.xml}
	*	<Zmiana id="n">
	*		<Param wspolczynnik="3.0"/>
	*	</Zmiana>
	* \endcode
	*/
	explicit ZmianaLiniowa( TiXmlElement * wezel );

	/**
	* Destruktor
	*/
	virtual ~ZmianaLiniowa();

	/**
	* Metoda tworz¹ca napis zawieraj¹cy opis obiektu.
	* \return Opis obiektu.
	*/
	std::string napis () const override;

};
