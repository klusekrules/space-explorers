#pragma once
#include "JednostkaAtakujaca.h"
#include "Obiekt.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa obiektu Obrony
*
* Klasa gromadzi wszytkie niezb�dne klasy bazowe dla obiektu biznesowego typu obrona.
* Nadpisuje metody potrzebne do poprawnego dzia�ania.
* \author Daniel Wojdak
* \version 1
* \date 29-08-2013
*/
class Obrona :
	public JednostkaAtakujaca,
	public Obiekt,
	virtual public LoggerInterface,
	virtual public Serializacja,
	virtual public PodstawoweParametry
{
	friend class ObronaInfo;
public:

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - ilo�� tworzonych obiekt�w.
	* \param[in] poziom - Poziom tworzonych obiekt�w.
	* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
	* \param[in] obronaInfo - Referencja do obiektu opisuj�cego.
	*/
	Obrona( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObronaInfo& obronaInfo );

	/**
	* \brief Konstruktor.
	*
	* \param[in] ilosc - ilo�� tworzonych obiekt�w.
	* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
	* \param[in] obronaInfo - Referencja do obiektu opisuj�cego.
	*/
	Obrona( const Ilosc& ilosc, const PodstawoweParametry& podstawoweParametry, const ObronaInfo& obronaInfo );

	/**
	* \brief Destruktor.
	*/
	virtual ~Obrona();

	/**
	* \brief Metoda pobiera obiekt opisuj�cy obron�.
	* \return Obiekt opisuj�cy.
	*/
	const ObronaInfo& pobierzObronaInfo() const;

	/**
	* Metoda kopiuj�ca obiekt. 
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na kopie obiektu.
	*/
	Obrona* kopia() const override;

	/**
	* Metoda dziel�ca klas� wzdl�dem ilo�ci podanej przez argument.
	* Zwr�cony obiekt ma ilo�� r�wn� podan� przez parametr.
	* Obiekt bazowy ma ilo�� zmniejszon� o podan� przez parametr warto��.
	* \param[in] ilosc - Ilo�� obiekt�w wzgl�dem, kt�rego jest podzielony obiekt.
	* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
	* \return Wskazanie na podzielony obiekt. Je�eli nie mo�na by�o podzieli� obiektu, zostaje zwr�cony nullptr.
	* \remark Metoda jest tranzakcyjna.
	*/
	Obrona* podziel( const Ilosc& ilosc ) override;
	
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
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( tinyxml2::XMLElement* wezel ) const override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( tinyxml2::XMLElement* wezel ) override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis()const override;

protected:
	
	const ObronaInfo& obronaInfo_; /// Referencja do obiektu opisuj�cego.
};