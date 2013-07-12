#pragma once
#include "OgolnyWyjatek.h"
/**
* Klasa bazowa dla wyj¹tków generowanych przez modu³ parsuj¹cy xml.
*/
class WyjatekParseraXML :	
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const Identyfikator idWyjatekParseraXML;
	static const Tekst trescBladStrukturyXml;

	WyjatekParseraXML( const WyjatekParseraXML& );
	WyjatekParseraXML( const Tekst& tPlik, const Ilosc& iLinia, const std::exception&, const Tekst& = Tekst() );
	virtual ~WyjatekParseraXML();

	const Tekst& getPowod() const;
	void setPowod( const Tekst& );

	Tekst generujKomunikat() const override;

	string napis() const override;

private:
	Tekst powod;
	
	static const Tekst tytulWyjatekParseraXML;
	static const Tekst trescWyjatekParseraXML;
};

