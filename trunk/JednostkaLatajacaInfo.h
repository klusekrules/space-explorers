#pragma once
#include "Main.h"
#include "Info.h"
#include "MocSilnika.h"
#include "ZuzyciePaliwa.h"
#include "Masa.h"
#include "Klucz.h"
#include "ZmianaInterfejs.h"
#include "WyjatekParseraXML.h"

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
	* Konstruktor parametryczny
	* \param k - Rodzaj nap�du ( silnika )
	* \param moc - Moc silnika
	* \param z - Zu�ycia paliwa przez silnik
	* \param masa - Masa uk�adu nap�dowego
	*/
	JednostkaLatajacaInfo(const Info& info, const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa );
	
	JednostkaLatajacaInfo( ticpp::Node* );
	/**
	* Destruktor domy�lny
	*/
	virtual ~JednostkaLatajacaInfo();

	/**
	* Metoda zwracaj�ca rodzaj nap�du jednostki.
	* \return Rodzaj nap�du jednostki.
	*/
	const Klucz& getRodzajNapedu() const;

	/**
	* Metoda zwracaj�ca moc silnika jednostki.
	* \return Moc silnika jednostki.
	*/
	MocSilnika getMocSilnika() const;

	/**
	* Metoda zwracaj�ca zu�ycie paliwa jednostki.
	* \return Zu�ycie paliwa jednostki.
	*/
	ZuzyciePaliwa getZuzyciePaliwa() const;
	
	/**
	* Metoda zwracaj�ca mas� nap�du jednostki.
	* \return Masa nap�du jednostki.
	*/
	Masa getMasaNapedu() const;
	
	/**
	* Metoda zwracaj�ca Sprawnosc Silnika jednostki.
	* \return Sprawnosc Silnika jednostki.
	*/
	Fluktuacja getSprawnoscSilnika() const;
	
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
	Fluktuacja			sprawnoscSilnika; /// Sprawno�� silnika.

	
	ZmianaInterfejs*	przyrostMocySilnika; /// Klasa dekoratora wyliczaj�ca zmian� mocy silnika
	ZmianaInterfejs*	przyrostSprawnosciSilnika; /// Klasa dekoratora wyliczaj�ca zmian� sprawno�ci silnika
	ZmianaInterfejs*	przyrostZuzyciaPaliwa; /// Klasa dekoratora wyliczaj�ca zmian� zu�ycia paliwa
	ZmianaInterfejs*	przyrostMasyNapedu; /// Klasa dekoratora wyliczaj�ca zmian� masy nap�du
};

