#pragma once
#include "OgolnyWyjatek.h"
/**
* Wyj¹tek informuje, ¿e nie uda³o siê podzieliæ ³adowni wed³ug podanych wymagañ.
*/
class BladDzieleniaLadowni :
	public LoggerInterface<BladDzieleniaLadowni>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<BladDzieleniaLadowni> LogBladDzieleniaLadowni;

	static const IdType idBladDzieleniaLadowni;
	
	BladDzieleniaLadowni( const Tekst& tPlik, const IdType& iLinia, const Tekst& tLadownia );
	virtual ~BladDzieleniaLadowni(void);
		
	const Tekst& getLadownia() const;
	void setLadownia ( const Tekst& tLadownia );
	
	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst ladownia;
	static const Tekst tytulBladDzieleniaLadowni;
	static const Tekst trescBladDzieleniaLadowni;
};

