#pragma once
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"
#include "Bazowa.h"
#include "Statek.h"
#include "Klucz.h"

class Flota : 
	public Bazowa,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class Planeta;
public:
	typedef map< Klucz , shared_ptr<Statek> > ListaStatkow;
	Flota(const Identyfikator&);
	virtual ~Flota(void);
	bool dodajStatek( shared_ptr<Statek> );
	bool dodajLadunek( shared_ptr<Obiekt> );
	Objetosc pobierzDostepneMiejsce() const;
	bool zapisz( TiXmlElement* e ) const override;
	bool odczytaj( TiXmlElement* e ) override;
	string napis()const override;

private:
	ListaStatkow lista;
};

