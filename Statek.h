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
	virtual public LoggerInterface
{
	friend class StatekInfo;
public:
	ZuzyciePaliwa WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const override;
		
	Statek* Kopia() const override;

	Statek* Podziel( const Ilosc& ) override;

	Masa getMasa( ) const override;

	Obrazenia Atak( ) const override;

	Obrazenia Pancerz( const Obrazenia& o ) const override;

	Obrazenia Oslona( const Obrazenia& o ) const override;

	Obrazenia getAtak( ) const override;

	Obrazenia getPancerz( ) const override;

	Obrazenia getOslona( ) const override;

	Objetosc getPojemnoscMax( ) const override;

	ZuzyciePaliwa getJednostkoweZuzyciePaliwa( )const override;

	Masa getMasaSilnika( )const override;

	Fluktuacja WolneMiejsce( ) const override;

	bool DodajObiektDoLadowni( const Item& ) override;

	MocSilnika getMocSilnika( )const override;
	
	Fluktuacja getSprawnoscSilnika( )const override;

	bool czMoznaDodacDoLadownii( const Ladownia& c ) const override;

	const StatekInfo& getStatekInfo() const;

	string toString() const override;
private:

	Statek( const Ilosc&, const Poziom& p, const IdType& idP, const StatekInfo& );
	Statek( const Ilosc&, const PodstawoweParametry& idP, const StatekInfo& );

protected:

	const StatekInfo& statekinfo;

};
