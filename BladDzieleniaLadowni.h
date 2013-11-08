#pragma once
#include "OgolnyWyjatek.h"
/**
* Wyj�tek informuje, �e nie uda�o si� podzieli� �adowni wed�ug podanych wymaga�.
*/
class BladDzieleniaLadowni :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const Identyfikator idBladDzieleniaLadowni;
	
	BladDzieleniaLadowni( const Tekst& tPlik, const Ilosc& iLinia, const Tekst& tLadownia );
	virtual ~BladDzieleniaLadowni(void);
		
	const Tekst& getLadownia() const;
	void setLadownia ( const Tekst& tLadownia );
	
	Tekst generujKomunikat() const override;

	std::string napis() const override;

private:
	Tekst ladownia;
	static const Tekst tytulBladDzieleniaLadowni;
	static const Tekst trescBladDzieleniaLadowni;
};
