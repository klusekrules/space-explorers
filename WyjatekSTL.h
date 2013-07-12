#pragma once
#include "OgolnyWyjatek.h"

/**
* Klasa bazowa nadbudowuj¹ca wyj¹tki z biblioteki stl.
*/
class WyjatekSTL :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const IdType idWyjatekSTL;
	
	WyjatekSTL( const Tekst& tPlik, const Ilosc& iLinia, const std::exception&, const Tekst& = Tekst() );
	WyjatekSTL( const WyjatekSTL& );
	virtual ~WyjatekSTL();

	const Tekst& getPowod() const;
	void setPowod( const Tekst& );

	Tekst generujKomunikat() const override;

	string napis() const override;

private:
	Tekst powod;

	static const Tekst tytulWyjatekSTL;
	static const Tekst trescWyjatekSTL;
};

