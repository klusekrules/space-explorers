#pragma once
#include "OgolnyWyjatek.h"
#include "Klucz.h"
/**
* Por�wnywane surowce maj� r�ne typy.
*/
class NiezgodnyTypSurowca :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:

	static const IdType idNiezgodnyTypSurowca;
	
	NiezgodnyTypSurowca( const Tekst& tPlik, const Ilosc& iLinia, const Klucz& , const Klucz& );
	NiezgodnyTypSurowca( const NiezgodnyTypSurowca& );
	virtual ~NiezgodnyTypSurowca();

	string napis() const override;

private:
	static const Tekst tytulNiezgodnyTypSurowcaDomyslny;
	static const Tekst trescNiezgodnyTypSurowcaDomyslny;

};

