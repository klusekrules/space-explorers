#pragma once
#include "Logger\LoggerInterface.h"
#include "Planeta.h"

/**
* \brief Klasa reprezentuj�ca u�ytkownika.
*
* Klasa u�ytkownika przechowuje planety oraz wszystkie potrzebne dane
* \author Daniel Wojdak
* \version 1
* \date 26-07-2013
*/
class Uzytkownik:
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	typedef map<Identyfikator, shared_ptr<Planeta> > ListaPlanet;

	/**
	* \brief Konstruktor.
	*
	* \param[in] gra - instancja gry dla u�ytkownika..
	*/
	Uzytkownik( Gra& gra );

	/**
	* \brief Destruktor.
	*/
	virtual ~Uzytkownik();

	/**
	* \brief Metoda zwracaj�ca planet� nale��c� do u�ytkownika.
	*
	* Metoda pobiera planete nale��c� do u�ytkownika. Nie usuwa jej z listy jego planet.
	* \return Referencja do planety u�ytkownika.
	*/
	Planeta& pobierzPlanete( const Identyfikator& Identyfikator ) const;


	/**
	* \brief Metoda dodaje palanet� do listy planet u�ytkownika.
	* 
	*  Metoda ustawia w�a�ciciela planety na aktualnego u�ytkownika.
	* \param[in] planeta - Sprytny wska�nika na obiekt planety.
	* \return true je�eli uda si� doda� planet�, false je�eli operacja si� nie powiedzie.
	*/
	bool dodajPlanete( shared_ptr<Planeta> planeta );

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

private:
	ListaPlanet listaPlanet; /// Lista planet u�ytkownika.
	Gra& instancjaGry; /// Instancja gry do kt�rej nale�y u�ytkowni.
};
