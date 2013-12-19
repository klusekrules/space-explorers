#pragma once
#include "ObiektBazowyInfo.h"
#include "Obiekt.h"
#include "NiezainicjalizowanaKlasa.h"
#include "FuncTransf\ZmianaInterfejs.h"

/**
* \brief Klasa opisowa obiektu.
*
* Klasa zawieraj¹ca elementy opisowe obiektu gry.
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

	Objetosc objetosc_; /// Objêtoœæ obiektu.
	shared_ptr<ZmianaInterfejs> zmianaObjetosci_; /// Zmiana objêtoœci obiektu.

	Masa masa_; /// Masa obiektu.
	shared_ptr<ZmianaInterfejs> zmianaMasy_; /// Zmiana masy obiektu.

public:

	/**
	* \brief Konstruktor.
	* 
	* \param[in] masa - Masa obiektu.
	* \param[in] objetosc - Objetoœæ obiektu.
	* \param[in] powierzchnia - Powierzchnia obiektu.
	* \param[in] obiektBazowyInfo - Referencja do obiektu bazowego.
	*/
	ObiektInfo( const Masa& masa, const Objetosc& objetosc, const Powierzchnia& powierzchnia, const ObiektBazowyInfo& obiektBazowyInfo ) throw();

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit ObiektInfo( tinyxml2::XMLElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Destruktor.
	*/
	virtual ~ObiektInfo();

	/**
	* \brief Metoda wyliczaj¹ca powierzchniê obiektu.
	*
	* Metoda liczy powierzchniê dla podanego poziomu i identyfikatora planety.
	* Je¿eli dla powierzchni nie ma klasy zmiany, zawsze zwracana jest podstawowa wartoœæ powierzchni dla obiektu.
	* \param[in] poziom - Poziom obiektu.
	* \param[in] identyfikatorPlanety - Identyfikator planety obiektu.
	* \return Wyliczona wartoœæ powierzchni.
	*/
	Powierzchnia pobierzPowierzchnie(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const;

	/**
	* \brief Metoda wyliczaj¹ca objêtoœæ obiektu.
	*
	* Metoda liczy objêtoœæ dla podanego poziomu i identyfikatora planety.
	* Je¿eli dla objêtoœæi nie ma klasy zmiany, zawsze zwracana jest podstawowa wartoœæ objêtoœci dla obiektu.
	* \param[in] poziom - Poziom obiektu.
	* \param[in] identyfikatorPlanety - Identyfikator planety obiektu.	
	* \return Wyliczona wartoœæ objêtoœci.
	*/
	Objetosc pobierzObjetosc(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const;

	/**
	* \brief Metoda wyliczaj¹ca masê obiektu.
	*
	* Metoda liczy masê dla podanego poziomu i identyfikatora planety.
	* Je¿eli dla masy nie ma klasy zmiany, zawsze zwracana jest podstawowa wartoœæ masy dla obiektu.
	* \param[in] poziom - Poziom obiektu.
	* \param[in] identyfikatorPlanety - Identyfikator planety obiektu.
	* \return Wyliczona wartoœæ masy.
	*/
	Masa pobierzMase(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const;

	/**
	* \brief Metoda tworz¹ca egzemplarz obiektu.
	*
	*  Metoda tworzy egzemplarz obiektu o podanej iloœci i dla podanej planety.
	* \param[in] ilosc - Iloœæ tworzonych obiektów.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Metoda zwraca wskaŸnika na obiekt.
	*/
	Obiekt* tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;
};
