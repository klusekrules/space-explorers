#pragma once
#include "ExportSymbol.h"
#include "..\Logger\LoggerInterface.h"
/**
* \brief G³ówny interfejs klas zmian
*
* Klasa zwieraj¹ca interfejs dla klas typu zmiana.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
class FUNCTRANSF_API ZmianaInterfejs: 
	virtual public LoggerInterface
{
public:
	/**
	* Metoda czysto wirtualna s³u¿aca do wyliczania wartoœci parametru przekazan¹ do metody, zale¿n¹ od poziomu i planety na której znajdzuje siê obiekt.
	* \param[in] wartosc - Wartoœæ atrybutu obiektu do przeliczenia.
	* \param[in] poziom - Poziom obiektu, dla którego wyliczana jest wartoœæ atrybutu.
	* \param[in] identyfikatorPlanety - Identyfikator planety, na której znajduje siê obiekt.
	* \return Nowa wyliczona wartoœæ atrybutu obiektu.
	*/
	virtual long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const = 0;

	/**
	* Metoda czysto wirtualna tworz¹ca kopiê obiektu.
	* \return WskaŸnik na kopiê obiektu.
	* \remark Obiekt nie zarz¹dza i nie u¿ywa kopii, które utworzy³. Pamiêæ musi zostaæ zwolniona na zewn¹trz, za pomoca operatora delete.
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
