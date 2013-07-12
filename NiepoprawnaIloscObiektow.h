#pragma once
#include "OgolnyWyjatek.h"
#include "Ilosc.h"

/**
* Wyj�tek informuje, ze przekazana ilo�� obiekt�w jest nie poprawna dla danej operacji.
*/
class NiepoprawnaIloscObiektow :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const Identyfikator idNiepoprawnaIloscObiektow;
	
	NiepoprawnaIloscObiektow( const Tekst& tPlik, const Ilosc& iLinia, const Ilosc& ilosc );
	virtual ~NiepoprawnaIloscObiektow(void);
	
	const Ilosc& getIlosc() const;
	void setIlosc( const Ilosc& ilosc );
	
	Tekst generujKomunikat() const override;

	string napis() const override;

private:
	Ilosc i;
	
	static const Tekst tytulNiepoprawnaIloscObiektow;
	static const Tekst trescNiepoprawnaIloscObiektow;
};

