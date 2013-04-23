#pragma once
#include "WyjatekParseraXML.h"

/**
* Wyj�tek s�u�y do informowania, �e w pliku xml w aktualnej ga��zi nie ma podanego atrybutu.
*/
class BrakAtrybutuXML :
	public LoggerInterface<BrakAtrybutuXML>,
	public WyjatekParseraXML
{
public:
	typedef LoggerInterface<BrakAtrybutuXML> LogBrakAtrXML;

	static const IdType idBrakAtrybutuXML;
	
	BrakAtrybutuXML( const Tekst& tPlik, const IdType& iLinia, const Tekst& = Tekst() );
	BrakAtrybutuXML( const BrakAtrybutuXML& );
	virtual ~BrakAtrybutuXML();

	const Tekst& getAtrybut() const;
	void setAtrybut( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst atrybut;

	static const Tekst tytulBrakAtrybutuXML;
	static const Tekst trescBrakAtrybutuXML;
};

