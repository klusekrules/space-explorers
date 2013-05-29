#pragma once
#include "OgolnyWyjatek.h"
#include "Klucz.h"
/**
* Porównywane surowce maj¹ ró¿ne typy.
*/
class NiezgodnyTypSurowca :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:

	static const IdType idNiezgodnyTypSurowca;
	
	NiezgodnyTypSurowca( const Tekst& tPlik, const IdType& iLinia, const Klucz& , const Klucz& );
	NiezgodnyTypSurowca( const NiezgodnyTypSurowca& );
	virtual ~NiezgodnyTypSurowca();

	string toString() const override;

private:
	static const Tekst tytulNiezgodnyTypSurowcaDomyslny;
	static const Tekst trescNiezgodnyTypSurowcaDomyslny;

};

