#pragma once
#include "NieznalezionoObiektu.h"
#include "NiepoprawnaIloscObiektow.h"
#include "Objetosc.h"
#include "Klucz.h"
#include "Ilosc.h"
#include "Obiekt.h"
#include "Fluktuacja.h"
#include "Masa.h"
#include "ListaObiektow.hpp"
#include "PodstawoweParametry.h"

class Surowce;
class LadowniaInfo;
class Statek;
/**
* \brief Klasa preprezentuj�ca �adownie statku.
*
* Klasa s�u�y do przechowywania i zarz�dzania obiektami w �adowni.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class Ladownia:
	virtual public PodstawoweParametry,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	typedef Obiekt Item;
	typedef ListaObiektow< Item > Zbiornik;
	typedef vector < Klucz > ListaKluczy;

	/**
	* \brief Konstruktor.
	*
	* \param[in] poziom - Poziom tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] ladowniaInfo - Referencja do obiektu opisuj�cego.
	*/
	Ladownia( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const LadowniaInfo& ladowniaInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
	* \param[in] ladowniaInfo - Referencja do obiektu opisuj�cego.
	*/
	Ladownia( const PodstawoweParametry& podstawoweParametry, const LadowniaInfo& ladowniaInfo );

	/**
	* \brief Destruktor.
	*/
	virtual ~Ladownia();
	
	/**
	* \brief Metoda wyliczaj�ca procent wolnego miejsca.
	*
	* \return Procentowa warto�� wolnego miejsca w �adowni.
	*/
	virtual Fluktuacja wolneMiejsce() const;

	/**
	* \brief Metoda dodaj�ca obiekt do �adowni.
	*
	* \param[in] obiekt - Obiekt dodawany do �adowni.
	* \return true je�eli dodano obiekt, false w przeciwnym wypadku.
	* \remark Metoda tworzy kopie elementu. Metoda tranzakcyjna.
	*/
	bool dodajObiektDoLadowni( const Item& obiekt );

	/**
	* \brief Metoda dodaj�ca obiekt do �adowni.
	*
	* \param[in] obiekt - Obiekt dodawany do �adowni.
	* \return true je�eli dodano obiekt, false w przeciwnym wypadku.
	* \remark Metoda nie tworzy kopii elementu. Metoda tranzakcyjna.
	*/
	bool dodajObiektDoLadowni( shared_ptr<Item> obiekt );

	/**
	* \brief Metoda wylicza obj�to�� maksymaln� �adowni.
	* \return Obj�to�� maksymalna �adowni.
	*/
	virtual Objetosc pobierzPojemnoscMaksymalna() const;

	/**
	* \brief Metoda ��czy obiekty �adowni.
	* 
	* Metoda przenosi obiekty z �adowni przekazanej przez parametr do obiektu docelowego.
	* \param[in] ladownia - �adownia �r�d�owa.
	* \return true je�eli uda si� przenie��, false w przeciwnym wypadku.
	* \remark Metoda tranzakcyjna.
	*/
	bool polacz( Ladownia& ladownia );

	/**
	* \brief Metoda ��czy obiekty �adowni.
	* 
	* Metoda przenosi obiekty z �adowni przekazanej przez parametr do obiektu docelowego.
	* \param[in] ladownia - �adownia �r�d�owa.
	* \return true je�eli uda si� przenie��, false w przeciwnym wypadku.
	* \remark Metoda tranzakcyjna.
	*/
	bool polacz( Zbiornik zbiornik );

	/**
	* \brief Metoda pobiera ilo�� obiekt�w o podanym kluczu.
	* 
	* \param[in] klucz - Klucz identyfikuj�cy obiekt.
	* \return Ilo�� obiekt�w o podanym kluczu znajduj�ca si� w �adowni.
	*/
	Ilosc pobierzIloscObiektow( const Klucz& klucz ) const;	

	/**
	* \brief Metoda wyjmuje z �adowni obietk o podanym kluczu i podanej ilo�ci
	* 
	* \param[in] klucz - Klucz identyfikuj�cy obiekt.
	* \param[in] ilosc - Ilo�� obiekt�w o podanym kluczu.
	* \return Wska�nik na wyj�ty obiekt. nullptr je�eli wystapi� b�ad.
	*/
	shared_ptr<Item> wyjmijObiekt( const Klucz& klucz , const Ilosc& ilosc );

	/**
	* \brief Metoda zwraca list� kluczy obiekt�w.
	*
	* \return Lista kluczy obiekt�w znajduj�cych sie w �adowni.
	*/
	ListaKluczy pobierzListeIdentyfikatorowObiektow() const;

	/**
	* \brief Metoda zwraca list� obiekt�w znajduj�cych si� w �adowni.
	*
	* \return Lista obiekt�w znajduj�cych si� w �adowni.
	*/
	const Zbiornik& pobierzPrzewozoneObiekty() const;

	/**
	* \brief Metoda dzieli �adownie.
	* 
	* Metoda dzieli �adownie w taki spos�b, aby obj�to�� odzielonej cz�ci �adowni zawiera� si� w przedziale \<minimum,maksimum\>.
	* \param[in] minimum - Minimalna obj�to�� wydzielanej cze�ci.
	* \param[in] maksimum - Maksymalna obj�to�� wydzielanej cze�ci.
	* \return Zbiornik z elementami.
	*/
	Zbiornik podzielLadownie( const Objetosc& minimum , const Objetosc& maksimum );

	/**
	* \brief Metoda zwraca obj�to�� wszystkich element�w w zbiorniku.
	*
	* \return Obj�to�� element�w w �adowni.
	*/
	const Objetosc& pobierzZajeteMiejsce() const;

	/**
	* \brief Metoda informuje o mo�liwo�ci biznesowej dodania obiektu do �adowni.
	*
	* \param[in] statek - nieu�ywane.
	* \return Zawsze zwraca true.
	*/
	bool czMoznaDodacDoLadownii( const Statek& statek ) const;

	/**
	* \brief Metoda informuje o mo�liwo�ci biznesowej dodania obiektu do �adowni.
	*
	* \param[in] surowce - Surowiec poddawany sprawdzeniu.
	* \return true je�eli mo�na doda� obiekt, false w przeciwnym wypadku.
	*/
	bool czMoznaDodacDoLadownii( const Surowce& surowce ) const;

	/**
	* \brief Metoda opr�nia �adownie.
	*
	* Metoda zwraca wszystkie obiekty znajduj�ce si� w �adowni. Pozostawia �adownie pust�.
	* \return Zbiornik zawieraj�cy obiekty.
	*/
	Zbiornik oproznijLadownie();

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
	* \brief Metoda przeliczaj�ca zaj�te miejsce w �adowni.
	*/
	void przeliczZajeteMiejsce();

	/**
	* \brief Metoda pobieraj�ca mas� obiekt�w znajduj�cych si� w �adowni.
	* \return Masa obiekt�w w �adowni.
	*/
	Masa pobierzMaseZawartosciLadowni()const;

	Zbiornik obiekty_; /// Lista element�w w �adowni.
	Objetosc zajete_; /// Zaj�te miejsce.

private:
	const LadowniaInfo& ladowniaInfo_; /// Referencja do obiektu opisuj�cego.
};
