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

	string toString() const override;
private:

	Statek( const Ilosc& ,const StatekInfo& );

};
