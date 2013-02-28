#pragma once
#include "OgolnyWyjatek.h"
class BladLaczeniaObiektow :
	public LoggerInterface<BladLaczeniaObiektow>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<BladLaczeniaObiektow> LogBladLaczeniaObiektow;

	static const IdType idBladLaczeniaObiektow;
	
	BladLaczeniaObiektow( const Tekst& tPlik, const IdType& iLinia, const Tekst& obiektA , const Tekst& obiektB );
	virtual ~BladLaczeniaObiektow();
	
	Tekst getObiektA() const;
	void setObiektA( const Tekst& );

	Tekst getObiektB() const;
	void setObiektB( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst obiektA;
	Tekst obiektB;

	static const Tekst tytulBladLaczeniaObiektow;
	static const Tekst trescBladLaczeniaObiektow;
};

