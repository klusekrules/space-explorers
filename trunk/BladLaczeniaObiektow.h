#pragma once
#include "OgolnyWyjatek.h"

/**
* Wyj¹tek informuje, ¿e nie uda³o sie po³¹czyæ obiektów.
*/
class BladLaczeniaObiektow :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const Identyfikator idBladLaczeniaObiektow;
	
	BladLaczeniaObiektow( const Tekst& tPlik, const Ilosc& iLinia, const Tekst& obiektA , const Tekst& obiektB );
	virtual ~BladLaczeniaObiektow();
	
	const Tekst& getObiektA() const;
	void setObiektA( const Tekst& );

	const Tekst& getObiektB() const;
	void setObiektB( const Tekst& );

	Tekst generujKomunikat() const override;

	string napis() const override;

private:
	Tekst obiektA;
	Tekst obiektB;

	static const Tekst tytulBladLaczeniaObiektow;
	static const Tekst trescBladLaczeniaObiektow;
};

