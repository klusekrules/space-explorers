#pragma once
#include "Main.h"
#include "Info.h"
#include "MocSilnika.h"
#include "ZuzyciePaliwa.h"
#include "Masa.h"


/**
* Klasa opisuj�ca statek pod k�tem przemieszczania si�.
* Przechowuje informacje odno�nie mocy silnika, zu�ycia paliwa przez statek, rodzaju nap�du statku, uk�adu nap�dowego statku.
*/
class JednostkaLatajacaInfo :
	public Info,
	public LoggerInterface<JednostkaLatajacaInfo>
{
public:
	typedef LoggerInterface<JednostkaLatajacaInfo> LogJednostkaLatajacaInfo; ///  Typ loggera klasy

	/**
	* Konstruktor domy�lny
	*/
	JednostkaLatajacaInfo();

	/**
	* Konstruktor parametryczny
	* \param k - Rodzaj nap�du ( silnika )
	* \param moc - Moc silnika
	* \param z - Zu�ycia paliwa przez silnik
	* \param masa - Masa uk�adu nap�dowego
	*/
	JednostkaLatajacaInfo( const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa );
	
	/**
	* Domy�lny konstruktor kopiuj�cy
	* \param a - Obiekt na podstawie kt�rego zostanie utworzona kopia.
	*/
	JednostkaLatajacaInfo( const JednostkaLatajacaInfo& a );
	
	/**
	* Destruktor domy�lny
	*/
	virtual ~JednostkaLatajacaInfo();

	/**
	* Metoda zwracaj�ca rodzaj nap�du jednostki.
	* \return Rodzaj nap�du jednostki.
	*/
	Klucz getRodzajNapedu() const;

	/**
	* Metoda ustawiaj�ca rodzaj nap�du jednostki.
	* \param k - Rodzaj nap�du jednostki.
	*/
	void setRodzajNapedu( const Klucz& k );

	/**
	* Metoda zwracaj�ca moc silnika jednostki.
	* \return Moc silnika jednostki.
	*/
	MocSilnika	getMocSilnika() const;

	/**
	* Metoda ustawiaj�ca moc silnika jednostki.
	* \param m - Moc silnika jednostki.
	*/
	void setMocSilnika( const MocSilnika& m );

	/**
	* Metoda zwracaj�ca zu�ycie paliwa jednostki.
	* \return Zu�ycie paliwa jednostki.
	*/
	ZuzyciePaliwa getZuzyciePaliwa() const;

	/**
	* Metoda ustawiaj�ca zu�ycie paliwa jednostki.
	* \param k - Zu�ycie paliwa jednostki.
	*/
	void setZuzyciePaliwa( const ZuzyciePaliwa& z );

	/**
	* Metoda zwracaj�ca mas� nap�du jednostki.
	* \return Masa nap�du jednostki.
	*/
	Masa getMasaNapedu() const;

	/**
	* Metoda ustawiaj�ca mas� nap�du jednostki.
	* \param k - Masa nap�du jednostki.
	*/
	void setMasaNapedu( const Masa& m );

	/**
	* Metoda opisuj�ca zawarto�� klasy.
	* \return CI�g znak�w opisuj�cy klas�.
	*/
	string toString() const override;
private:
	
	Klucz				rodzajNapedu; /// Rodzaj nap�dy statku
	MocSilnika			mocSilnika; /// Moc silnika statku
	ZuzyciePaliwa		zuzyciePaliwa; /// Zu�ycie paliwa przez statek
	Masa				masaNapedu; /// Masa uk�adu nap�dowego
};

