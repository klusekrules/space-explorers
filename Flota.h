#pragma once
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"
#include "Base.h"
#include "Statek.h"
#include "Klucz.h"

class Flota : 
	public Base,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class Planeta;
public:
	typedef map< Klucz , shared_ptr<Statek> > ListaStatkow;
	Flota(const IdType&);
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

