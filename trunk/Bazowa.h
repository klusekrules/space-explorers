#pragma once
#include "Logger\LoggerInterface.h"
#include "Identyfikator.h"
#include "Serializacja.h"
#include "parser\ticpp.h"

/**
* \brief Klasa bazowa dla klas obiektów.
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
	* Konstruktor tworz¹cy obiekt na podstawie identyfikatora.
	* \param[in] identyfikator - Identyfikator jaki ma zostaæ przypisany do obiektu.
	*/
	explicit Bazowa( const Identyfikator& identyfikator ) throw();

	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit Bazowa( TiXmlElement * wezel );
	
	/**
	* Destruktor.
	*/
	virtual ~Bazowa();

	/**
	* Metoda zwracaj¹ca Identyfikator obiektu.
	* \return Identyfikator obiektu.
	*/
	const Identyfikator& pobierzIdentyfikator() const;

	/**
	* Metoda ustawiaj¹ca identyfikator obiektu.
	* \param[in] identyfikator - Nowa wartoœæ identyfikatora obiektu.
	*/
	void ustawIdentyfikator( const Identyfikator& identyfikator );

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

private:

	Identyfikator identyfikator_; /// Identyfikator obiektu.
};
