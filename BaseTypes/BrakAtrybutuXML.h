#pragma once
#include "WyjatekParseraXML.h"

/**
* Wyj¹tek s³u¿y do informowania, ¿e w pliku xml w aktualnej ga³êzi nie ma podanego atrybutu.
*/
class BASETYPES_API BrakAtrybutuXML :
	virtual public LoggerInterface,
	public WyjatekParseraXML
{
public:
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

