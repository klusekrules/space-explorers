#pragma once
#include "Logger\LoggerInterface.h"

/**
* \brief Klasa bazowa zawieraj�ca interfejs dla wykonywanych operacji.
*/
class Operacja:
	virtual public LoggerInterface
{
public:
	/**
	* \brief Konstruktor domy�lny.
	*/
	Operacja(void);

	/**
	* \brief Destruktor.
	*/
	virtual ~Operacja(void);

	/**
	* \brief Metoda wykonuj�ca operacje tranzakcyjn�.
	*
	* \return Metoda klasy bazowej zawsze zwraca false.
	*/
	virtual bool wykonaj();

	/**
	* \brief Metoda wykonuj�ca operacje odwrotn� do tranzakcyjnej.
	*
	* \return Metoda klasy bazowej zawsze zwraca false.
	*/
	virtual bool cofnij();

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;
};
