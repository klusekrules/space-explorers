#pragma once
#include "OgolnyWyjatek.h"

/**
* Klasa bazowa nadbudowuj¹ca wyj¹tki z biblioteki stl.
*/
class WyjatekSTL :
	public LoggerInterface<WyjatekSTL> ,
	public OgolnyWyjatek
{
public:
	typedef LoggerInterface<WyjatekSTL> LogWyjSTL;

	static const IdType idWyjatekSTL;
	
	WyjatekSTL( const Tekst& tPlik, const IdType& iLinia, const std::exception&, const Tekst& = Tekst() );
	WyjatekSTL( const WyjatekSTL& );
	virtual ~WyjatekSTL();

	const Tekst& getPowod() const;
	void setPowod( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst powod;

	static const Tekst tytulWyjatekSTL;
	static const Tekst trescWyjatekSTL;
};

