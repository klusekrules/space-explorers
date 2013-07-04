#pragma once
#include "Logger\LoggerInterface.h"
#include "Planeta.h"
class Uzytkownik:
	virtual public LoggerInterface
{
public:
	typedef map<IdType, shared_ptr<Planeta> > ListaPlanet;
	Uzytkownik();
	~Uzytkownik();

	Planeta& getPlaneta( const IdType& ) const;

	bool dodajPlanete( shared_ptr<Planeta> );

	string toString() const override;

private:
	ListaPlanet listaPlanet;
};

