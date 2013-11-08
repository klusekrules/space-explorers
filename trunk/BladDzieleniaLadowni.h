#pragma once
#include "OgolnyWyjatek.h"
/**
* Wyj¹tek informuje, ¿e nie uda³o siê podzieliæ ³adowni wed³ug podanych wymagañ.
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
