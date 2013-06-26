#pragma once
#include "Main.h"
#include "JednostkaAtakujaca.h"
#include "JednostkaLatajaca.h"
#include "Obiekt.h"
#include "Ladownia.h"


class Statek :
	public JednostkaAtakujaca,
	public JednostkaLatajaca,
	public Ladownia,
	public Obiekt,
	virtual public LoggerInterface
{
	friend class StatekInfo;
public:
	virtual ~Statek();

	ZuzyciePaliwa WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p , const Poziom& pz = Poziom() ) const override;
		
	Statek* Kopia() const override;

	Statek* Podziel( const Ilosc& ) override;

	Masa getMasa( ) const override;

	Obrazenia Atak( const Poziom& pz = Poziom() ) const override;

	Obrazenia Pancerz( const Obrazenia& o , const Poziom& pz = Poziom()  ) const override;

	Obrazenia Oslona( const Obrazenia& o , const Poziom& pz = Poziom()  ) const override;

	Obrazenia getAtak( const Poziom& pz = Poziom() ) const override;

	Obrazenia getPancerz( const Poziom& pz = Poziom()  ) const override;

	Obrazenia getOslona( const Poziom& pz = Poziom() ) const override;

	Objetosc getPojemnoscMax(  const Poziom& pz = Poziom() ) const override;

	ZuzyciePaliwa getJednostkoweZuzyciePaliwa( const Poziom& pz = Poziom() )const override;

	Masa getMasaSilnika( const Poziom& pz = Poziom() )const override;

	Fluktuacja WolneMiejsce( const Poziom& pz = Poziom() ) const override;

	bool DodajObiektDoLadowni( const Item& , const Poziom& pz = Poziom() ) override;

	MocSilnika getMocSilnika( const Poziom& pz = Poziom() )const override;
	
	Fluktuacja getSprawnoscSilnika( const Poziom& pz = Poziom() )const override;

	bool czMoznaDodacDoLadownii( const Ladownia& c ) const override;

	const StatekInfo& getStatekInfo() const;

	string toString() const override;
private:

	Statek( const Ilosc& ,const StatekInfo& );

protected:

	const StatekInfo& statekinfo;

};
