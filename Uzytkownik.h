#pragma once
#include "Logger\LoggerInterface.h"
#include "Planeta.h"
class Uzytkownik:
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	typedef map<IdType, shared_ptr<Planeta> > ListaPlanet;
	Uzytkownik();
	~Uzytkownik();

	Planeta& getPlaneta( const IdType& ) const;

	bool dodajPlanete( shared_ptr<Planeta> );

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	string toString() const override;

private:
	ListaPlanet listaPlanet;
};

