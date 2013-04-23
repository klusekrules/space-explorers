#pragma once
#include "OgolnyWyjatek.h"
#include "Ilosc.h"

/**
* Wyj¹tek informuje, ze przekazana iloœæ obiektów jest nie poprawna dla danej operacji.
*/
class NiepoprawnaIloscObiektow :
	public LoggerInterface<NiepoprawnaIloscObiektow>,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<NiepoprawnaIloscObiektow> LogNiepoprawnaIloscObiektow;

	static const IdType idNiepoprawnaIloscObiektow;
	
	NiepoprawnaIloscObiektow( const Tekst& tPlik, const IdType& iLinia, const Ilosc& ilosc );
	virtual ~NiepoprawnaIloscObiektow(void);
	
	const Ilosc& getIlosc() const;
	void setIlosc( const Ilosc& ilosc );
	
	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Ilosc i;
	
	static const Tekst tytulNiepoprawnaIloscObiektow;
	static const Tekst trescNiepoprawnaIloscObiektow;
};

