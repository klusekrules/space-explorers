#pragma once
#include "OgolnyWyjatek.h"
class NiepoprawneParametryFunkcji :
	public LoggerInterface<NiepoprawneParametryFunkcji>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<NiepoprawneParametryFunkcji> LogNiepoprawneParametryFunkcji;

	static const IdType idNiepoprawneParametryFunkcji;
	
	NiepoprawneParametryFunkcji( const Tekst& tPlik, const IdType& iLinia, const Tekst& tNazwa );
	virtual ~NiepoprawneParametryFunkcji(void);

	Tekst getFuncName() const;
	void setFuncName ( const Tekst& wwTresc );
	
	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst funcName;
	static const Tekst tytulNiepoprawneParametryFunkcji;
	static const Tekst trescNiepoprawneParametryFunkcji;
};

