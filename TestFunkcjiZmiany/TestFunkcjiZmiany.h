#ifdef TESTFUNKCJIZMIANY_EXPORTS
#define TESTFUNKCJIZMIANY_API __declspec(dllexport)
#else
#define TESTFUNKCJIZMIANY_API __declspec(dllimport)
#endif

#include "..\FuncTransf\ZmianaFabryka.h"
#include "..\FuncTransf\ZmianaParametr.h"

/**
* \brief Klasa s�u�aca do test�w zmiany.
*
* Domy�nie nie b�dzie si� zawiera� w wersji release.
* Spos�b dzia�ania metody wyliczajacej:
*	- Warto�� atrybutu mno�ona jest przez wsp�czynik pobrany z parametru i to mno�one jest przez poziom przekazany w parametrze, ca�o�� mno�ona jest przez 10. ( wartosc * parametr_ * poziom * 10 )
* \author Daniel Wojdak
* \version 1
* \date 11-07-2013
*/
class TESTFUNKCJIZMIANY_API ZmianaTest:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int identyfikator_; /// Identyfikator klasy przekazywany do fabryki.

	/**
	* Metoda tworz�ca obiekt a podstawie w�z�a.
	* \param[in] wezel - W�ze� na podstawie kt�rego tworzony jest obiekt.
	* \return Wska�nika na obiekt utworzonej zmiany.
	*/
	static ZmianaInterfejs* TworzZmianaTest( TiXmlElement* wezel );

	ZmianaParametr parametr_; /// Wsp�czynnik o jaki zmienia si� warto�� atrybutu.
public:

	/**
	* Metoda rejestruj�ca klas� w fabryce.
	* \param[in] fabryka - Referencja do globalnej fabryki.
	* \return Metoda zwraca warto�� true, je�eli uda si� zarejestrowa� klas�. Je�eli wyst�pi� b��d zwr�cona jest warto�� false.
	* \sa ZmianaFabryka
	*/
	static bool RejestrujZmianaTest( ZmianaFabryka &fabryka );

	/**
	* Metoda wyliczaj�ca warto��.
	* Spos�b dzia�ania metod policzWartosc klasy zmiana agregacja:
	*	- Warto�� atrybutu mno�ona jest przez wsp�czynik pobrany z parametru i to mno�one jest przez poziom przekazany w parametrze, ca�o�� mno�ona jest przez 10. ( wartosc * parametr_ * poziom * 10 )
	* \param[in] wartosc - podstawowa warto�� parametru, dla k�trego b�dzie wyliczana modyfikacja warto�ci.
	* \param[in] poziom - poziom obiektu, dla kt�rego b�dzie wyliczana modyfikacja warto�ci.
	* \param[in] identyfikatorPlanety - identyfikator planety, na kt�rej znajduje si� obiekt.
	* \return Przeliczona warto�� atryutu.
	*/
	long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const override;

	/**
	* Metoda tworzy kopi� obiektu.
	* \return Wska�nik do kopii obiektu.
	* \warning Zwr�cony wska�nik musi zostac zwolniony operatorem delete. 
	*/
	ZmianaTest* Kopia()const override;

	/**
	* Konstruktor obiektu na podstawie w�z�a XML.
	* \param[in] wezel - Wezel drzewa xml.
	* \pre W�ze� musi zawiera� nast�puj�c� struktur�
	* \code {.xml}
	*	<Zmiana id="n">
	*		<Param wspolczynnik="3.0"/>
	*	</Zmiana>
	* \endcode
	*/
	explicit ZmianaTest( TiXmlElement * wezel );

	/**
	* Destruktor
	*/
	virtual ~ZmianaTest();

	/**
	* Metoda tworz�ca napis zawieraj�cy opis obiektu.
	* \return Opis obiektu.
	*/
	std::string napis () const override;

};

/**
* Funkcja eksportowana s�u��ca do rejestracji zmiany w fabryce.
* \param[in,out] fabryka - Referencja do fabryki, w kt�rej ma zosta� zarejestrowana klasa.
* \param[in] logger - referencja do loggera, dla komunikacji o b��dach.
* \return Funkcja zwraca true, je�eli uda si� zarejestrowa� klas� lub false w przeciwnym wypadku.
*/
extern "C" bool TESTFUNKCJIZMIANY_API RejestrujZmiany ( ZmianaFabryka& fabryka , Log& logger );
