#pragma once
#include "OgolnyWyjatek.h"
#include "Klucz.h"

class NiezgodnyTypSurowca :
	public LoggerInterface<NiezgodnyTypSurowca>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<NiezgodnyTypSurowca> LogNieTypSur;

	static const IdType idNiezgodnyTypSurowca;
	
	NiezgodnyTypSurowca( const Tekst& tPlik, const IdType& iLinia );
	NiezgodnyTypSurowca( const Tekst& tPlik, const IdType& iLinia, const Klucz& , const Klucz& );
	NiezgodnyTypSurowca( const NiezgodnyTypSurowca& );
	virtual ~NiezgodnyTypSurowca();

	string toString() const override;

private:
	static const Tekst tytulNiezgodnyTypSurowcaDomyslny;
	static const Tekst trescNiezgodnyTypSurowcaDomyslny;

};

