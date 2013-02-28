#pragma once
#include "OgolnyWyjatek.h"

class WyjatekParseraXML :	
	public LoggerInterface<WyjatekParseraXML> ,
	public OgolnyWyjatek
{
public:	
	typedef LoggerInterface<WyjatekParseraXML> LogWyjBibTICPP;

	static const IdType idWyjatekParseraXML;

	WyjatekParseraXML( const Tekst& tPlik, const IdType& iLinia );
	WyjatekParseraXML( const WyjatekParseraXML& );
	WyjatekParseraXML( const Tekst& tPlik, const IdType& iLinia, const Tekst&, const std::exception& );
	WyjatekParseraXML( const Tekst& tPlik, const IdType& iLinia, const std::exception& );
	virtual ~WyjatekParseraXML();

	Tekst getPowod() const;
	void setPowod( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst powod;
	
	static const Tekst tytulWyjatekParseraXML;
	static const Tekst trescWyjatekParseraXML;
};

