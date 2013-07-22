#pragma once
#include "Bazowa.h"
#include "Ilosc.h"

class Licznik:
	public Bazowa,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	Licznik(const Identyfikator&, const Ilosc& );
	Licznik(const Identyfikator& id);
	Licznik();
	virtual ~Licznik(void);

	Ilosc operator()();

	Ilosc pobierzWartosc()const;

	void resetujWartosc();

	void ustawWartosc( const Ilosc& );

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	string napis()const override;

private:
	Ilosc wartoscLicznika;
};
