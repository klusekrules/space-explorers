#pragma once
#include "FuncTransf\ZmianaInterfejs.h"
#include "Info.h"
#include "MocSilnika.h"
#include "ZuzyciePaliwa.h"
#include "Masa.h"
#include "Klucz.h"
#include "WyjatekParseraXML.h"
#include "PodstawoweParametry.h"

/**
* \brief Klasa opisuj�ca statek pod k�tem przemieszczania si�.
*
* Przechowuje informacje odno�nie mocy silnika, zu�ycia paliwa przez statek, rodzaju nap�du statku, uk�adu nap�dowego statku.
* \author Daniel Wojdak
* \version 1
* \date 24-07-2013
*/
class JednostkaLatajacaInfo :
	public Info,
	virtual public LoggerInterface
{
public:
	/**
	* Konstruktor parametryczny
	* \param[in] info - referencja do obiektu opisowego.
	* \param[in] klucz - Rodzaj nap�du ( silnika )
	* \param[in] mocSilnika - Moc silnika
	* \param[in] zuzyciePaliwa - Zu�ycia paliwa przez silnik
	* \param[in] masa - Masa uk�adu nap�dowego
	*/
	JednostkaLatajacaInfo(const Info& info, const Klucz& klucz, const MocSilnika& mocSilnika, const ZuzyciePaliwa& zuzyciePaliwa, const Masa& masa ) throw();
	
	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit JednostkaLatajacaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Konstruktor kopiuj�cy.
	* 
	* \param[in] obiekt - Obiekt �r�d�owy.
	*/
	JednostkaLatajacaInfo( const JednostkaLatajacaInfo& obiekt );

	/**
	* \brief Destruktor.
	*/
	virtual ~JednostkaLatajacaInfo();

	/**
	* \brief Metoda zwracaj�ca rodzaj nap�du jednostki.
	*
	* \return Rodzaj nap�du jednostki.
	*/
	const Klucz& pobierzRodzajNapedu() const;

	/**
	* \brief Metoda wyliczaj�ca moc silnika jednostki.
	*
	* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
	* \return Moc silnika jednostki.
	*/
	MocSilnika pobierzMocSilnika(const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda wyliczaj�ca zu�ycie paliwa jednostki.
	*
	* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
	* \return Zu�ycie paliwa jednostki.
	*/
	ZuzyciePaliwa pobierzZuzyciePaliwa(const PodstawoweParametry& parametry ) const;
	
	/**
	* Metoda wyliczaj�ca mas� nap�du jednostki.
	*
	* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
	* \return Masa nap�du jednostki.
	*/
	Masa pobierzMasaNapedu(const PodstawoweParametry& parametry ) const;
	
	/**
	* Metoda wyliczaj�ca sprawno�� silnika jednostki.
	*
	* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
	* \return Sprawno�� silnika jednostki.
	*/
	Fluktuacja pobierzSprawnoscSilnika(const PodstawoweParametry& parametry ) const;
	
	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;
private:
	
	Klucz				rodzajNapedu_; /// Rodzaj nap�dy statku
	MocSilnika			mocSilnika_; /// Moc silnika statku
	ZuzyciePaliwa		zuzyciePaliwa_; /// Zu�ycie paliwa przez statek
	Masa				masaNapedu_; /// Masa uk�adu nap�dowego
	Fluktuacja			sprawnoscSilnika_; /// Sprawno�� silnika.

	
	shared_ptr<ZmianaInterfejs>	przyrostMocySilnika_; /// Obiekt wyliczaj�cy zmian� mocy silnika
	shared_ptr<ZmianaInterfejs>	przyrostSprawnosciSilnika_; /// Obiekt wyliczaj�cy zmian� sprawno�ci silnika
	shared_ptr<ZmianaInterfejs>	przyrostZuzyciaPaliwa_; /// Obiekt wyliczaj�cy zmian� zu�ycia paliwa
	shared_ptr<ZmianaInterfejs>	przyrostMasyNapedu_; /// Obiekt wyliczaj�cy zmian� masy nap�du
};
