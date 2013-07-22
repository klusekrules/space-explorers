#pragma once
#include "Logger\LoggerInterface.h"
#include "Identyfikator.h"
#include "Serializacja.h"
#include "parser\ticpp.h"

/**
* \brief Klasa bazowa dla klas obiekt�w.
* 
* Klasa gromadzi podstawowy interfejs oraz zawiera identyfikator obiektu.
* \author Daniel Wojdak
* \version 1
* \date 22-07-2013
*/
class Bazowa:
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:	
			
	/**
	* Konstruktor tworz�cy obiekt na podstawie identyfikatora.
	* \param[in] identyfikator - Identyfikator jaki ma zosta� przypisany do obiektu.
	*/
	explicit Bazowa( const Identyfikator& identyfikator ) throw();

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit Bazowa( TiXmlElement * wezel );
	
	/**
	* Destruktor.
	*/
	virtual ~Bazowa();

	/**
	* Metoda zwracaj�ca Identyfikator obiektu.
	* \return Identyfikator obiektu.
	*/
	const Identyfikator& pobierzIdentyfikator() const;

	/**
	* Metoda ustawiaj�ca identyfikator obiektu.
	* \param[in] identyfikator - Nowa warto�� identyfikatora obiektu.
	*/
	void ustawIdentyfikator( const Identyfikator& identyfikator );

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

	Identyfikator identyfikator_; /// Identyfikator obiektu.
};
