#pragma once
#include "ExportSymbol.h"
#include "..\Logger\LoggerInterface.h"
/**
* \brief G��wny interfejs klas zmian
*
* Klasa zwieraj�ca interfejs dla klas typu zmiana.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
class FUNCTRANSF_API ZmianaInterfejs: 
	virtual public LoggerInterface
{
public:
	/**
	* Metoda czysto wirtualna s�u�aca do wyliczania warto�ci parametru przekazan� do metody, zale�n� od poziomu i planety na kt�rej znajdzuje si� obiekt.
	* \param[in] wartosc - Warto�� atrybutu obiektu do przeliczenia.
	* \param[in] poziom - Poziom obiektu, dla kt�rego wyliczana jest warto�� atrybutu.
	* \param[in] identyfikatorPlanety - Identyfikator planety, na kt�rej znajduje si� obiekt.
	* \return Nowa wyliczona warto�� atrybutu obiektu.
	*/
	virtual long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const = 0;

	/**
	* Metoda czysto wirtualna tworz�ca kopi� obiektu.
	* \return Wska�nik na kopi� obiektu.
	* \remark Obiekt nie zarz�dza i nie u�ywa kopii, kt�re utworzy�. Pami�� musi zosta� zwolniona na zewn�trz, za pomoca operatora delete.
	*/
	virtual ZmianaInterfejs* Kopia() const = 0;

	/**
	* Konstruktor bezparametrowy
	*/
	ZmianaInterfejs();

	/**
	* Destruktor
	*/
	virtual ~ZmianaInterfejs();
};
