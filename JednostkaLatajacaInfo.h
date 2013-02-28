#pragma once
#include "Main.h"
#include "Info.h"
#include "MocSilnika.h"
#include "ZuzyciePaliwa.h"
#include "Masa.h"


/**
* Klasa opisuj¹ca statek pod k¹tem przemieszczania siê.
* Przechowuje informacje odnoœnie mocy silnika, zu¿ycia paliwa przez statek, rodzaju napêdu statku, uk³adu napêdowego statku.
*/
class JednostkaLatajacaInfo :
	public Info,
	public LoggerInterface<JednostkaLatajacaInfo>
{
public:
	typedef LoggerInterface<JednostkaLatajacaInfo> LogJednostkaLatajacaInfo; ///  Typ loggera klasy

	/**
	* Konstruktor domyœlny
	*/
	JednostkaLatajacaInfo();

	/**
	* Konstruktor parametryczny
	* \param k - Rodzaj napêdu ( silnika )
	* \param moc - Moc silnika
	* \param z - Zu¿ycia paliwa przez silnik
	* \param masa - Masa uk³adu napêdowego
	*/
	JednostkaLatajacaInfo( const Klucz& k, const MocSilnika& moc, const ZuzyciePaliwa& z, const Masa& masa );
	
	/**
	* Domyœlny konstruktor kopiuj¹cy
	* \param a - Obiekt na podstawie którego zostanie utworzona kopia.
	*/
	JednostkaLatajacaInfo( const JednostkaLatajacaInfo& a );
	
	/**
	* Destruktor domyœlny
	*/
	virtual ~JednostkaLatajacaInfo();

	/**
	* Metoda zwracaj¹ca rodzaj napêdu jednostki.
	* \return Rodzaj napêdu jednostki.
	*/
	Klucz getRodzajNapedu() const;

	/**
	* Metoda ustawiaj¹ca rodzaj napêdu jednostki.
	* \param k - Rodzaj napêdu jednostki.
	*/
	void setRodzajNapedu( const Klucz& k );

	/**
	* Metoda zwracaj¹ca moc silnika jednostki.
	* \return Moc silnika jednostki.
	*/
	MocSilnika	getMocSilnika() const;

	/**
	* Metoda ustawiaj¹ca moc silnika jednostki.
	* \param m - Moc silnika jednostki.
	*/
	void setMocSilnika( const MocSilnika& m );

	/**
	* Metoda zwracaj¹ca zu¿ycie paliwa jednostki.
	* \return Zu¿ycie paliwa jednostki.
	*/
	ZuzyciePaliwa getZuzyciePaliwa() const;

	/**
	* Metoda ustawiaj¹ca zu¿ycie paliwa jednostki.
	* \param k - Zu¿ycie paliwa jednostki.
	*/
	void setZuzyciePaliwa( const ZuzyciePaliwa& z );

	/**
	* Metoda zwracaj¹ca masê napêdu jednostki.
	* \return Masa napêdu jednostki.
	*/
	Masa getMasaNapedu() const;

	/**
	* Metoda ustawiaj¹ca masê napêdu jednostki.
	* \param k - Masa napêdu jednostki.
	*/
	void setMasaNapedu( const Masa& m );

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
};

