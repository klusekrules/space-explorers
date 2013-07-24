#pragma once
#include "Main.h"
#include "JednostkaAtakujaca.h"
#include "JednostkaLatajaca.h"
#include "Obiekt.h"
#include "Ladownia.h"
#include "PodstawoweParametry.h"

class Statek :
	public JednostkaAtakujaca,
	public JednostkaLatajaca,
	public Ladownia,
	public Obiekt,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class StatekInfo;
public:
	ZuzyciePaliwa wyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const override;
		
	Statek* kopia() const override;

	Statek* podziel( const Ilosc& ) override;

	bool polacz( const ObiektBazowy& ) override;

	Masa pobierzMase( ) const override;

	Obrazenia pobierzAtak( ) const override;

	Obrazenia pobierzPancerz( ) const override;

	Obrazenia pobierzOslone( ) const override;

	Objetosc getPojemnoscMax( ) const override;

	ZuzyciePaliwa pobierzJednostkoweZuzyciePaliwa( )const override;

	Masa pobierzMasaSilnika( )const override;

	Fluktuacja WolneMiejsce( ) const override;

	bool DodajObiektDoLadowni( Item& ) override;

	MocSilnika pobierzMocSilnika( )const override;
	
	Fluktuacja pobierzSprawnoscSilnika( )const override;

	bool czMoznaDodacDoLadownii( const Ladownia& c ) const override;

	const StatekInfo& getStatekInfo() const;

	bool zapisz( TiXmlElement* e) const override;

	bool odczytaj (TiXmlElement* e) override;

	string napis() const override;
private:

	Statek( const Ilosc&, const Poziom& p, const Identyfikator& idP, const StatekInfo& );

	Statek( const Ilosc&, const PodstawoweParametry& idP, const StatekInfo& );

protected:

	/**
	* \brief Metoda zwracaj¹ca ca³kowit¹ masê statku w raz z mas¹ ³adowni.
	*
	* \return Ca³kowita masa statku.
	*/
	Masa calkowitaMasaJednostki() const override;

	const StatekInfo& statekinfo;

};
