#pragma once
#include "Logger\LoggerInterface.h"
#include "Planeta.h"
class Uzytkownik:
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	typedef map<Identyfikator, shared_ptr<Planeta> > ListaPlanet;
	Uzytkownik(Gra&);
	~Uzytkownik();

	Planeta& getPlaneta( const Identyfikator& ) const;

	bool dodajPlanete( shared_ptr<Planeta> );

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	string napis() const override;

private:
	ListaPlanet listaPlanet;
	Gra& instancjaGry;
};

