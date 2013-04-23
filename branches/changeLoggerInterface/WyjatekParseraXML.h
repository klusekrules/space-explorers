#pragma once
#include "OgolnyWyjatek.h"
/**
* Klasa bazowa dla wyj�tk�w generowanych przez modu� parsuj�cy xml.
*/
class WyjatekParseraXML :	
	public LoggerInterface<WyjatekParseraXML> ,
	public OgolnyWyjatek
{
public:	
	typedef LoggerInterface<WyjatekParseraXML> LogWyjBibTICPP;

	static const IdType idWyjatekParseraXML;
	static const Tekst trescBladStrukturyXml;

	WyjatekParseraXML( const WyjatekParseraXML& );
	WyjatekParseraXML( const Tekst& tPlik, const IdType& iLinia, const std::exception&, const Tekst& = Tekst() );
	virtual ~WyjatekParseraXML();

	const Tekst& getPowod() const;
	void setPowod( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst powod;
	
	static const Tekst tytulWyjatekParseraXML;
	static const Tekst trescWyjatekParseraXML;
};

