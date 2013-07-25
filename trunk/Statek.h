#pragma once
#include "JednostkaAtakujaca.h"
#include "JednostkaLatajaca.h"
#include "Obiekt.h"
#include "Ladownia.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa obiektu statku
*
* Klasa gromadzi wszytkie niezb�dne klasy bazowe dla obiektu biznesowego typu statek.
* Nadpisuje metody potrzebne do poprawnego dzia�ania.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class Statek :
	public JednostkaAtakujaca,
	public JednostkaLatajaca,
	public Ladownia,
	public Obiekt,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class StatekInfo;
public:

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - ilo�� tworzonych obiekt�w.
	* \param[in] poziom - Poziom tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] statekInfo - Referencja do obiektu opisuj�cego.
	*/
	Statek( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const StatekInfo& statekInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - ilo�� tworzonych obiekt�w.
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
	* \param[in] statekInfo - Referencja do obiektu opisuj�cego.
	*/
	Statek( const Ilosc& ilosc, const PodstawoweParametry& podstawoweParametry, const StatekInfo& statekInfo );

	
	/**
	* \brief Destruktor.
	*/
	virtual ~Statek();

	/**
	* \brief Metoda pobiera obiekt opisuj�cy statek.
	* \return Obiekt opisuj�cy.
	*/
	const StatekInfo& pobierzStatekInfo() const;

	/**
	* \brief Metoda wyliczaj�ca zy�ycie paliwa przez statek.
	*
	* Metoda wylicza zy�ycie paliwa przez statek na okre�lonym dystansie i przy okre�lonej pr�ko�ci.
	* \param[in] dystans - Dystans, na kt�rym ma porusza� si� statek.
	* \param[in] predkosc - Pr�dko��, kt�r� ma lecie� statek.
	* \return Paliwo zu�yte przez statek.
	*/
	ZuzyciePaliwa wyliczZuzyciePaliwa( const Dystans& dystans , const Predkosc& predkosc ) const override;
	
	/**
	* Metoda kopiuj�ca obiekt. 
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	Statek* kopia() const override;

	/**
	* Metoda dziel�ca klas� wzdl�dem ilo�ci podanej przez argument.
	* Zwr�cony obiekt ma ilo�� r�wn� podan� przez parametr.
	* Obiekt bazowy ma ilo�� zmniejszon� o podan� przez parametr warto��.
	* \param[in] ilosc - Ilo�� obiekt�w wzgl�dem, kt�rego jest podzielony obiekt.
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na podzielony obiekt. Je�eli nie mo�na by�o podzieli� obiektu, zostaje zwr�cony nullptr.
	* \remark Metoda jest tranzakcyjna.
	*/
	Statek* podziel( const Ilosc& ilosc ) override;

	/**
	* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
	* \param[in] obiektbazowy - Obiekt do po��czenia.
	* \warning Metoda nie zwalnia pami�ci przekazanego obiektu.
	* \return Kiedy obiekty zostan� po��czone, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
	* \remark Metoda jest tranzakcyjna.
	*/
	bool polacz( const ObiektBazowy& obiektbazowy ) override;

	/**
	* \brief Metoda wyliczaj�ca mas�.
	*
	* Metoda wylicza mas� jak� zajmuj� obiekty reprezentowane przez dan� instancj� klasy.
	* Metoda uwzgl�dnia zmiany zale�ne od poziomu i planety.
	* \return Wyliczona masa obiekt�w.
	*/
	Masa pobierzMase( ) const override;

	/**
	* Metoda atak s�u�y do wyliczania obra�e� zadawanych przez obiekt.
	* \return Obra�enia zadane przez obiekt.
	*/
	Obrazenia pobierzAtak( ) const override;

	/**
	* Metoda obliczaj�ca obra�enia mo�liwe do przyj�cia przez pancerz.
	* \return Obra�enia, kt�re mo�e przyj�� pancerz.
	*/
	Obrazenia pobierzPancerz( ) const override;

	/**
	* Metoda obliczaj�ca obra�enia mo�liwe do przyj�cia przez oslone.
	* \return Obra�enia, kt�re mo�e przyj�� os�ona.
	*/
	Obrazenia pobierzOslone( ) const override;

	/**
	* \brief Metoda wylicza obj�to�� maksymaln� �adowni.
	* \return Obj�to�� maksymalna �adowni.
	*/
	Objetosc pobierzPojemnoscMaksymalna( ) const override;

	/**
	* \brief Metoda wyliczaj�ca jednostkowe zu�ycie paliwa.
	*
	* \return Paliwo zu�yte przez statek.
	*/
	ZuzyciePaliwa pobierzJednostkoweZuzyciePaliwa( )const override;

	/**
	* \brief Metoda wyliczaj�ca mas� silnika.
	*
	* \return Masa silnika.
	*/
	Masa pobierzMasaSilnika( )const override;

	/**
	* \brief Metoda sparawdzaj�ca teorertyczn� mo�liwo�� dodania do �adowni.
	* 
	* Metoda sprawdza czy obiekt spe�nia wymagane za�o�enia oby m�g�by by� rozpatrywany jako mo�liwy dodania do �adowni.
	* \param[in] ladownia - �adownia do kt�rej ma zosta� dodany obiekt.
	* \return true je�eli mo�na doda�. False w przeciwnym wypadku.
	*/
	bool czyMoznaDodacDoLadownii( const Ladownia& ladownia ) const override;

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
	string napis()const override;
protected:

	/**
	* \brief Metoda zwracaj�ca ca�kowit� mas� statku w raz z mas� �adowni.
	*
	* \return Ca�kowita masa statku.
	*/
	Masa calkowitaMasaJednostki() const override;

	const StatekInfo& statekinfo_; /// Referencja do obiektu opisuj�cego.

};
