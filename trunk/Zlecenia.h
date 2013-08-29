#pragma once
#include "Zlecenie.h"
#include "Identyfikator.h"
#include "PodstawoweParametry.h"
#include <functional>

using namespace std::placeholders;
class ZlecenieUstawIdentyfikatorPlanety:
	public Zlecenie < Identyfikator, shared_ptr< PodstawoweParametry > >,
	virtual public LoggerInterface
{
private:
	Identyfikator staryIdentyfikator;
	
	bool ustawIdentyfikator( Identyfikator& id , shared_ptr< PodstawoweParametry >& obiekt ){
		staryIdentyfikator = obiekt->pobierzIdentyfikatorPlanety();
		obiekt->ustawIdentyfikatorPlanety(id);
		return true;
	}

	bool cofnijUstawIdentyfikator( Identyfikator& id , shared_ptr< PodstawoweParametry >& obiekt ){
		obiekt->ustawIdentyfikatorPlanety(staryIdentyfikator);
		return true;
	}
public:
	ZlecenieUstawIdentyfikatorPlanety( Identyfikator& identyfikator, shared_ptr< PodstawoweParametry >& obiekt )
		: Zlecenie( identyfikator, obiekt, bind(&ZlecenieUstawIdentyfikatorPlanety::ustawIdentyfikator,this,_1,_2), bind(&ZlecenieUstawIdentyfikatorPlanety::cofnijUstawIdentyfikator,this,_1,_2))
	{}
	~ZlecenieUstawIdentyfikatorPlanety(){}

	string napis() const override{
		Logger str(NAZWAKLASY(ZlecenieUstawIdentyfikatorPlanety));
		str.dodajKlase(Zlecenie::napis());
		str.dodajPole("StaryIdentyfikator",staryIdentyfikator);
		return str.napis();
	}
};
