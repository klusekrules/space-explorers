#pragma once
#include "Serializacja.h"
#include "Logger\LoggerInterface.h"
#include "PodstawoweParametry.h"
#include "ListaObiektow.hpp"
#include "Objetosc.h"

class HangarInfo;
class Statek;
/**
* \brief Klasa reprezentuj�ca hangar.
*
* Klasa reprezentuje hangar statku. Mo�na w nim przewozi� inne statki.
*/
class Hangar:
	virtual public PodstawoweParametry,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:

	typedef Statek Item;
	typedef ListaObiektow< Item > Zbiornik;
	typedef vector < Klucz > ListaKluczy;

	/**
	* \brief Konstruktor.
	*
	* \param[in] poziom - Poziom tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] hangarInfo - Referencja do obiektu opisuj�cego.
	*/
	Hangar( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const HangarInfo& hangarInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
	* \param[in] hangarInfo - Referencja do obiektu opisuj�cego.
	*/
	Hangar( const PodstawoweParametry& podstawoweParametry, const HangarInfo& hangarInfo );

	/**
	* \brief Destruktor.
	*/
	virtual ~Hangar();

	/**
	* \brief Metoda wyliczaj�ca procent wolnego miejsca.
	*
	* \return Procentowa warto�� wolnego miejsca w hangarze.
	*/
	Fluktuacja wolneMiejsceHangaru() const;

	/**
	* \brief Metoda dodaj�ca statek do hangaru
	*
	* \param[in] obiekt - Statek dodawany do hangaru.
	* \return true je�eli dodano obiekt, false w przeciwnym wypadku.
	* \remark Metoda tworzy kopie elementu. Metoda tranzakcyjna.
	*/
	bool dodajStatekDoHangaru( const Item& obiekt );

	/**
	* \brief Metoda dodaj�ca statek do hangaru
	*
	* \param[in] obiekt - Statek dodawany do hangaru.
	* \return true je�eli dodano obiekt, false w przeciwnym wypadku.
	* \remark Metoda nie tworzy kopii elementu. Metoda tranzakcyjna.
	*/
	bool dodajStatekDoHangaru( shared_ptr<Item> obiekt );

	/**
	* \brief Metoda wylicza obj�to�� maksymaln� hangaru.
	* \return Obj�to�� maksymalna hangaru.
	*/
	virtual Objetosc pobierzPojemnoscMaksymalnaHangaru() const;

	/**
	* \brief Metoda pobieraj�ca pojemno�� jednostkow�
	* \return Obj�to�� jednostkowa hangaru.
	*/
	Objetosc pobierzPojemnoscJednostkowaHangaru() const;

	/**
	* \brief Metoda ��czy obiekty hangaru.
	* 
	* Metoda przenosi obiekty z hangaru przekazanej przez parametr do obiektu docelowego.
	* \param[in] hangar - Hangar �r�d�owy.
	* \return true je�eli uda si� przenie��, false w przeciwnym wypadku.
	* \remark Metoda tranzakcyjna.
	*/
	bool polaczHangar( Hangar& hangar );

	/**
	* \brief Metoda ��czy obiekty hangaru.
	* 
	* Metoda przenosi obiekty z hangaru przekazanej przez parametr do obiektu docelowego.
	* \param[in] zbiornik - Hangar �r�d�owy.
	* \return true je�eli uda si� przenie��, false w przeciwnym wypadku.
	* \remark Metoda tranzakcyjna.
	*/
	bool polaczHangar( Zbiornik zbiornik );

	/**
	* \brief Metoda pobiera ilo�� obiekt�w o podanym kluczu.
	* 
	* \param[in] klucz - Klucz identyfikuj�cy obiekt.
	* \return Ilo�� obiekt�w o podanym kluczu znajduj�ca si� w hangarze.
	*/
	Ilosc pobierzIloscStatkow( const Klucz& klucz ) const;	

	/**
	* \brief Metoda wyjmuje z hangaru statek o podanym kluczu i podanej ilo�ci
	* 
	* \param[in] klucz - Klucz identyfikuj�cy obiekt.
	* \param[in] ilosc - Ilo�� obiekt�w o podanym kluczu.
	* \return Wska�nik na wyj�ty obiekt. nullptr je�eli wystapi� b�ad.
	*/
	shared_ptr<Item> wyjmijStatek( const Klucz& klucz , const Ilosc& ilosc );

	/**
	* \brief Metoda zwraca list� kluczy obiekt�w.
	*
	* \return Lista kluczy obiekt�w znajduj�cych sie w hangarze.
	*/
	ListaKluczy pobierzListeIdentyfikatorowStatkow() const;

	/**
	* \brief Metoda zwraca list� obiekt�w znajduj�cych si� w hangarze.
	*
	* \return Lista obiekt�w znajduj�cych si� w hangarze.
	*/
	const Zbiornik& pobierzPrzewozoneStatki() const;

	/**
	* \brief Metoda dzieli hangar.
	* 
	* Metoda dzieli hangar w taki spos�b, aby obj�to�� odzielonej cz�ci hangaru zawiera� si� w przedziale \<minimum,maksimum\>.
	* \param[in] minimum - Minimalna obj�to�� wydzielanej cze�ci.
	* \param[in] maksimum - Maksymalna obj�to�� wydzielanej cze�ci.
	* \return Zbiornik z elementami.
	*/
	Zbiornik podzielHangar( const Objetosc& minimum , const Objetosc& maksimum );

	/**
	* \brief Metoda zwraca obj�to�� wszystkich element�w w hangarze.
	*
	* \return Obj�to�� element�w w hangarze.
	*/
	const Objetosc& pobierzZajeteMiejsceHangaru() const;

	/**
	* \brief Metoda zwraca dost�pn� przestrze� hangaru.
	*
	* \return Dost�pna przestrze� hangaru.
	*/
	Objetosc pobierzDostepneMiejsceHangaru() const;

	/**
	* \brief Metoda opr�nia hangar.
	*
	* Metoda zwraca wszystkie obiekty znajduj�ce si� w hangarze. Pozostawia hangar pusty.
	* \return Zbiornik zawieraj�cy obiekty.
	*/
	Zbiornik oproznijHangar();

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
	* \brief Metoda przeliczaj�ca zaj�te miejsce w hangarze.
	*/
	void przeliczZajeteMiejsceHangaru();

	Zbiornik obiekty_; /// Lista element�w w hangarze.
	Objetosc zajete_; /// Zaj�te miejsce.

private:

	const HangarInfo& hangarInfo_; /// Referencja do obiektu opisowego.
};
