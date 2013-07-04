#pragma once
#include "Base.h"
#include "Ilosc.h"

class Licznik:
	public Base,
	virtual public LoggerInterface
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

	string toString()const;

private:
	Ilosc wartoscLicznika;
};

