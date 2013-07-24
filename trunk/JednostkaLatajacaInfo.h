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
* \brief Klasa opisuj¹ca statek pod k¹tem przemieszczania siê.
*
* Przechowuje informacje odnoœnie mocy silnika, zu¿ycia paliwa przez statek, rodzaju napêdu statku, uk³adu napêdowego statku.
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
	* \param[in] klucz - Rodzaj napêdu ( silnika )
	* \param[in] mocSilnika - Moc silnika
	* \param[in] zuzyciePaliwa - Zu¿ycia paliwa przez silnik
	* \param[in] masa - Masa uk³adu napêdowego
	*/
	JednostkaLatajacaInfo(const Info& info, const Klucz& klucz, const MocSilnika& mocSilnika, const ZuzyciePaliwa& zuzyciePaliwa, const Masa& masa ) throw();
	
	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit JednostkaLatajacaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Konstruktor kopiuj¹cy.
	* 
	* \param[in] obiekt - Obiekt Ÿród³owy.
	*/
	JednostkaLatajacaInfo( const JednostkaLatajacaInfo& obiekt );

	/**
	* \brief Destruktor.
	*/
	virtual ~JednostkaLatajacaInfo();

	/**
	* \brief Metoda zwracaj¹ca rodzaj napêdu jednostki.
	*
	* \return Rodzaj napêdu jednostki.
	*/
	const Klucz& pobierzRodzajNapedu() const;

	/**
	* \brief Metoda wyliczaj¹ca moc silnika jednostki.
	*
	* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
	* \return Moc silnika jednostki.
	*/
	MocSilnika pobierzMocSilnika(const PodstawoweParametry& parametry ) const;

	/**
	* \brief Metoda wyliczaj¹ca zu¿ycie paliwa jednostki.
	*
	* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
	* \return Zu¿ycie paliwa jednostki.
	*/
	ZuzyciePaliwa pobierzZuzyciePaliwa(const PodstawoweParametry& parametry ) const;
	
	/**
	* Metoda wyliczaj¹ca masê napêdu jednostki.
	*
	* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
	* \return Masa napêdu jednostki.
	*/
	Masa pobierzMasaNapedu(const PodstawoweParametry& parametry ) const;
	
	/**
	* Metoda wyliczaj¹ca sprawnoœæ silnika jednostki.
	*
	* \param[in] parametry - Parametry wymagane do policzenia atrybutu.
	* \return Sprawnoœæ silnika jednostki.
	*/
	Fluktuacja pobierzSprawnoscSilnika(const PodstawoweParametry& parametry ) const;
	
	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;
private:
	
	Klucz				rodzajNapedu_; /// Rodzaj napêdy statku
	MocSilnika			mocSilnika_; /// Moc silnika statku
	ZuzyciePaliwa		zuzyciePaliwa_; /// Zu¿ycie paliwa przez statek
	Masa				masaNapedu_; /// Masa uk³adu napêdowego
	Fluktuacja			sprawnoscSilnika_; /// Sprawnoœæ silnika.

	
	shared_ptr<ZmianaInterfejs>	przyrostMocySilnika_; /// Obiekt wyliczaj¹cy zmianê mocy silnika
	shared_ptr<ZmianaInterfejs>	przyrostSprawnosciSilnika_; /// Obiekt wyliczaj¹cy zmianê sprawnoœci silnika
	shared_ptr<ZmianaInterfejs>	przyrostZuzyciaPaliwa_; /// Obiekt wyliczaj¹cy zmianê zu¿ycia paliwa
	shared_ptr<ZmianaInterfejs>	przyrostMasyNapedu_; /// Obiekt wyliczaj¹cy zmianê masy napêdu
};
