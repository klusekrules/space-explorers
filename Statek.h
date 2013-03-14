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
	public LoggerInterface<Statek>
{
	friend class StatekInfo;
public:
	typedef LoggerInterface<Statek> LogStatek;
	virtual ~Statek();

	ZuzyciePaliwa WyliczZuzyciePaliwa( const Dystans& d , const Predkosc& p ) const override;
		
	Statek* Kopia() const override;

	Statek* Podziel( const Ilosc& ) override;

	Obrazenia Atak() const override;

	Obrazenia Pancerz( const Obrazenia& o ) const override;

	Obrazenia Oslona( const Obrazenia& o ) const override;

	Objetosc getPojemnoscMax() const override;

	string toString() const override;
private:

	Statek( const Ilosc& ,const StatekInfo& );

protected:

	const StatekInfo& statekinfo;

};
