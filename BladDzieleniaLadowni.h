#pragma once
#include "OgolnyWyjatek.h"
class BladDzieleniaLadowni :
	public LoggerInterface<BladDzieleniaLadowni>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<BladDzieleniaLadowni> LogBladDzieleniaLadowni;

	static const IdType idBladDzieleniaLadowni;
	
	BladDzieleniaLadowni( const Tekst& tPlik, const IdType& iLinia, const Tekst& tLadownia );
	virtual ~BladDzieleniaLadowni(void);
		
	Tekst getLadownia() const;
	void setLadownia ( const Tekst& tLadownia );
	
	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst ladownia;
	static const Tekst tytulBladDzieleniaLadowni;
	static const Tekst trescBladDzieleniaLadowni;
};

