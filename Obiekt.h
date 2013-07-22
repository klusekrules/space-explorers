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
* Klasa bazowa dla obiekt�w w grze. Poszerza interfejs o metody sprawdzaj�ce powierzchni�, obj�to�� i mas�.
* Rozsze�a tak�e interfejs o metod� sprawdzaj�c� mo�liwo�� dodania obiektu do �adowni.
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
	* \param[in] ilosc - Ilo�� tworzonych obiekt�w.
	* \param[in] poziom - Poziom tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] obiektInfo - Referencja do obiektu opisuj�cego.
	*/
	Obiekt( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObiektInfo& obiektInfo ) throw();

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - Ilo�� tworzonych obiekt�w.
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
	* \param[in] obiektInfo - Referencja do obiektu opisuj�cego.
	*/
	Obiekt( const Ilosc& ilosc, const PodstawoweParametry& podstawoweParametry, const ObiektInfo& obiektInfo ) throw();

	/**
	* \brief Destruktor.
	*/
	virtual ~Obiekt();

	/**
	* \brief Metoda sparawdzaj�ca teorertyczn� mo�liwo�� dodania do �adowni.
	* 
	* Metoda sprawdza czy obiekt spe�nia wymagane za�o�enia oby m�g�by by� rozpatrywany jako mo�liwy dodania do �adowni.
	* \param[in] ladownia - �adownia do kt�rej ma zosta� dodany obiekt.
	* \return true je�eli mo�na doda�. False w przeciwnym wypadku.
	*/
	virtual bool czMoznaDodacDoLadownii( const Ladownia& ladownia ) const;
	
	/**
	* \brief Metoda wyliczaj�ca powierzchni�.
	*
	* Metoda wylicza powierzchni� jak� zajmuj� obiekty reprezentowane przez dan� instancj� klasy.
	* Metoda uwzgl�dnia zmiany zale�ne od poziomu i planety.
	* \return Wyliczona powierzchnia obiekt�w.
	*/
	virtual Powierzchnia pobierzPowierzchnie() const;

	/**
	* \brief Metoda wyliczaj�ca obj�to��.
	*
	* Metoda wylicza obj�to�� jak� zajmuj� obiekty reprezentowane przez dan� instancj� klasy.
	* Metoda uwzgl�dnia zmiany zale�ne od poziomu i planety.
	* \return Wyliczona obj�to�� obiekt�w.
	*/
	virtual Objetosc pobierzObjetosc() const;

	/**
	* \brief Metoda wyliczaj�ca mas�.
	*
	* Metoda wylicza mas� jak� zajmuj� obiekty reprezentowane przez dan� instancj� klasy.
	* Metoda uwzgl�dnia zmiany zale�ne od poziomu i planety.
	* \return Wyliczona masa obiekt�w.
	*/
	virtual Masa pobierzMase() const;

	/**
	* Metoda kopiuj�ca obiekt. 
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	Obiekt* kopia() const override;

	/**
	* Metoda dziel�ca klas� wzdl�dem ilo�ci podanej przez argument.
	* Zwr�cony obiekt ma ilo�� r�wn� podan� przez parametr.
	* Obiekt bazowy ma ilo�� zmniejszon� o podan� przez parametr warto��.
	* \param[in] ilosc - Ilo�� obiekt�w wzgl�dem, kt�rego jest podzielony obiekt.
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na podzielony obiekt. Je�eli nie mo�na by�o podzieli� obiektu, zostaje zwr�cony nullptr.
	*/
	Obiekt* podziel( const Ilosc& ilosc ) override;
	
	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;

protected:
	const ObiektInfo& obiektInfo_; /// Referencja do obiektu opisowego.
};
