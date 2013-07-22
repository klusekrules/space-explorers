#pragma once
#include "ObiektBazowy.h"
#include "Ilosc.h"
#include "Powierzchnia.h"
#include "Objetosc.h"
#include "Masa.h"

class ObiektInfo;
class Ladownia;


/**
* \brief Klasa obiektu
*
* Klasa bazowa dla obiektów w grze. Poszerza interfejs o metody sprawdzaj¹ce powierzchniê, objêtoœæ i masê.
* Rozsze¿a tak¿e interfejs o metodê sprawdzaj¹c¹ mo¿liwoœæ dodania obiektu do ³adowni.
*/
class Obiekt:
	public ObiektBazowy,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - Iloœæ tworzonych obiektów.
	* \param[in] poziom - Poziom tworzonych obiektów.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] obiektInfo - Referencja do obiektu opisuj¹cego.
	*/
	Obiekt( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObiektInfo& obiektInfo ) throw();

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - Iloœæ tworzonych obiektów.
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
	* \param[in] obiektInfo - Referencja do obiektu opisuj¹cego.
	*/
	Obiekt( const Ilosc& ilosc, const PodstawoweParametry& podstawoweParametry, const ObiektInfo& obiektInfo ) throw();

	/**
	* \brief Destruktor.
	*/
	virtual ~Obiekt();

	/**
	* \brief Metoda sparawdzaj¹ca teorertyczn¹ mo¿liwoœæ dodania do ³adowni.
	* 
	* Metoda sprawdza czy obiekt spe³nia wymagane za³o¿enia oby móg³by byæ rozpatrywany jako mo¿liwy dodania do ³adowni.
	* \param[in] ladownia - £adownia do której ma zostaæ dodany obiekt.
	* \return true je¿eli mo¿na dodaæ. False w przeciwnym wypadku.
	*/
	virtual bool czMoznaDodacDoLadownii( const Ladownia& ladownia ) const;
	
	/**
	* \brief Metoda wyliczaj¹ca powierzchniê.
	*
	* Metoda wylicza powierzchniê jak¹ zajmuj¹ obiekty reprezentowane przez dan¹ instancjê klasy.
	* Metoda uwzglêdnia zmiany zale¿ne od poziomu i planety.
	* \return Wyliczona powierzchnia obiektów.
	*/
	virtual Powierzchnia pobierzPowierzchnie() const;

	/**
	* \brief Metoda wyliczaj¹ca objêtoœæ.
	*
	* Metoda wylicza objêtoœæ jak¹ zajmuj¹ obiekty reprezentowane przez dan¹ instancjê klasy.
	* Metoda uwzglêdnia zmiany zale¿ne od poziomu i planety.
	* \return Wyliczona objêtoœæ obiektów.
	*/
	virtual Objetosc pobierzObjetosc() const;

	/**
	* \brief Metoda wyliczaj¹ca masê.
	*
	* Metoda wylicza masê jak¹ zajmuj¹ obiekty reprezentowane przez dan¹ instancjê klasy.
	* Metoda uwzglêdnia zmiany zale¿ne od poziomu i planety.
	* \return Wyliczona masa obiektów.
	*/
	virtual Masa pobierzMase() const;

	/**
	* Metoda kopiuj¹ca obiekt. 
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	Obiekt* kopia() const override;

	/**
	* Metoda dziel¹ca klasê wzdlêdem iloœci podanej przez argument.
	* Zwrócony obiekt ma iloœæ równ¹ podan¹ przez parametr.
	* Obiekt bazowy ma iloœæ zmniejszon¹ o podan¹ przez parametr wartoœæ.
	* \param[in] ilosc - Iloœæ obiektów wzglêdem, którego jest podzielony obiekt.
	* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
	* \return Wskazanie na podzielony obiekt. Je¿eli nie mo¿na by³o podzieliæ obiektu, zostaje zwrócony nullptr.
	*/
	Obiekt* podziel( const Ilosc& ilosc ) override;
	
	/**
	* \brief Metoda zapisuj¹ca.
	*
	* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
	* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
	* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj¹ca.
	*
	* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
	* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
	* \warning Metoda nie modyfikuje wêz³a.
	* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;

protected:
	const ObiektInfo& obiektInfo_; /// Referencja do obiektu opisowego.
};
