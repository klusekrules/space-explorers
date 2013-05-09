#pragma once
#include "Main.h"
#include "Info.h"
#include "BaseTypes\BaseTypes.h"
#include "BaseTypes\Wyjatki.h"
#include "FabrTransf\ZmianaInterfejs.h"

/**
* Klasa opisuj¹ca statek pod k¹tem przemieszczania siê.
* Przechowuje informacje odnoœnie mocy silnika, zu¿ycia paliwa przez statek, rodzaju napêdu statku, uk³adu napêdowego statku.
*/
class JednostkaLatajacaInfo :
	public Info,
	virtual public LoggerInterface
{
public:
	/**
	* Konstruktor parametryczny
	* \param k - Rodzaj napêdu ( silnika )
	* \param moc - Moc silnika
	* \param z - Zu¿ycia paliwa przez silnik
	* \param masa - Masa uk³adu napêdowego
	*/
	JednostkaLatajacaInfo(const Info& info, const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa ) throw();
	
	explicit JednostkaLatajacaInfo( ticpp::Node* ) throw(WyjatekParseraXML);
	/**
	* Destruktor domyœlny
	*/
	virtual ~JednostkaLatajacaInfo();

	/**
	* Metoda zwracaj¹ca rodzaj napêdu jednostki.
	* \return Rodzaj napêdu jednostki.
	*/
	const Klucz& getRodzajNapedu() const;

	/**
	* Metoda zwracaj¹ca moc silnika jednostki.
	* \return Moc silnika jednostki.
	*/
	MocSilnika getMocSilnika(const Poziom& p ) const;

	/**
	* Metoda zwracaj¹ca zu¿ycie paliwa jednostki.
	* \return Zu¿ycie paliwa jednostki.
	*/
	ZuzyciePaliwa getZuzyciePaliwa(const Poziom& p ) const;
	
	/**
	* Metoda zwracaj¹ca masê napêdu jednostki.
	* \return Masa napêdu jednostki.
	*/
	Masa getMasaNapedu(const Poziom& p ) const;
	
	/**
	* Metoda zwracaj¹ca Sprawnosc Silnika jednostki.
	* \return Sprawnosc Silnika jednostki.
	*/
	Fluktuacja getSprawnoscSilnika(const Poziom& p ) const;
	
	/**
	* Metoda opisuj¹ca zawartoœæ klasy.
	* \return CI¹g znaków opisuj¹cy klasê.
	*/
	string toString() const override;
private:
	
	Klucz				rodzajNapedu; /// Rodzaj napêdy statku
	MocSilnika			mocSilnika; /// Moc silnika statku
	ZuzyciePaliwa		zuzyciePaliwa; /// Zu¿ycie paliwa przez statek
	Masa				masaNapedu; /// Masa uk³adu napêdowego
	Fluktuacja			sprawnoscSilnika; /// Sprawnoœæ silnika.

	
	ZmianaInterfejs*	przyrostMocySilnika; /// Klasa dekoratora wyliczaj¹ca zmianê mocy silnika
	ZmianaInterfejs*	przyrostSprawnosciSilnika; /// Klasa dekoratora wyliczaj¹ca zmianê sprawnoœci silnika
	ZmianaInterfejs*	przyrostZuzyciaPaliwa; /// Klasa dekoratora wyliczaj¹ca zmianê zu¿ycia paliwa
	ZmianaInterfejs*	przyrostMasyNapedu; /// Klasa dekoratora wyliczaj¹ca zmianê masy napêdu
};

