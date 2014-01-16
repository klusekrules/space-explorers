#pragma once
#include "ObiektBazowyInfo.h"
#include "Obiekt.h"
#include "NiezainicjalizowanaKlasa.h"
#include "FuncTransf\ZmianaInterfejs.h"

/**
* \brief Klasa opisowa obiektu.
*
* Klasa zawieraj�ca elementy opisowe obiektu gry.
* \author Daniel Wojdak
* \version 1
* \date 22-07-2013
*/
class ObiektInfo :
	public ObiektBazowyInfo,
	virtual public LoggerInterface
{
private:
	Powierzchnia powierzchnia_; /// Powierzchnia obiektu.
	shared_ptr<ZmianaInterfejs> zmianaPowierzchni_; /// Zmiana powierzchni obiektu.

	Objetosc objetosc_; /// Obj�to�� obiektu.
	shared_ptr<ZmianaInterfejs> zmianaObjetosci_; /// Zmiana obj�to�ci obiektu.

	Masa masa_; /// Masa obiektu.
	shared_ptr<ZmianaInterfejs> zmianaMasy_; /// Zmiana masy obiektu.

public:

	/**
	* \brief Konstruktor.
	* 
	* \param[in] masa - Masa obiektu.
	* \param[in] objetosc - Objeto�� obiektu.
	* \param[in] powierzchnia - Powierzchnia obiektu.
	* \param[in] obiektBazowyInfo - Referencja do obiektu bazowego.
	*/
	ObiektInfo( const Masa& masa, const Objetosc& objetosc, const Powierzchnia& powierzchnia, const ObiektBazowyInfo& obiektBazowyInfo ) throw();

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit ObiektInfo( tinyxml2::XMLElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Destruktor.
	*/
	virtual ~ObiektInfo();

	/**
	* \brief Metoda wyliczaj�ca powierzchni� obiektu.
	*
	* Metoda liczy powierzchni� dla podanego poziomu i identyfikatora planety.
	* Je�eli dla powierzchni nie ma klasy zmiany, zawsze zwracana jest podstawowa warto�� powierzchni dla obiektu.
	* \param[in] poziom - Poziom obiektu.
	* \param[in] identyfikatorPlanety - Identyfikator planety obiektu.
	* \return Wyliczona warto�� powierzchni.
	*/
	Powierzchnia pobierzPowierzchnie(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const;

	/**
	* \brief Metoda wyliczaj�ca obj�to�� obiektu.
	*
	* Metoda liczy obj�to�� dla podanego poziomu i identyfikatora planety.
	* Je�eli dla obj�to��i nie ma klasy zmiany, zawsze zwracana jest podstawowa warto�� obj�to�ci dla obiektu.
	* \param[in] poziom - Poziom obiektu.
	* \param[in] identyfikatorPlanety - Identyfikator planety obiektu.	
	* \return Wyliczona warto�� obj�to�ci.
	*/
	Objetosc pobierzObjetosc(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const;

	/**
	* \brief Metoda wyliczaj�ca mas� obiektu.
	*
	* Metoda liczy mas� dla podanego poziomu i identyfikatora planety.
	* Je�eli dla masy nie ma klasy zmiany, zawsze zwracana jest podstawowa warto�� masy dla obiektu.
	* \param[in] poziom - Poziom obiektu.
	* \param[in] identyfikatorPlanety - Identyfikator planety obiektu.
	* \return Wyliczona warto�� masy.
	*/
	Masa pobierzMase(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const;

	/**
	* \brief Metoda tworz�ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu o podanej ilo�ci i dla podanej planety.
	* \param[in] ilosc - Ilo�� tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Metoda zwraca wska�nika na obiekt.
	*/
	Obiekt* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;
};
