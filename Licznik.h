#pragma once
#include "Base.h"
#include "Ilosc.h"

class Licznik:
	public Base,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	Licznik(const IdType&, const Ilosc& );
	Licznik(const IdType& id);
	Licznik();
	virtual ~Licznik(void);

	Ilosc operator()();

	Ilosc pobierzWartosc()const;

	void resetujWartosc();

	void ustawWartosc( const Ilosc& );

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	string toString()const override;

private:
	Ilosc wartoscLicznika;
};

