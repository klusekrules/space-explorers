#pragma once
#include "WyjatekParseraXML.h"

class BrakMaski :
	public LoggerInterface<BrakMaski>,
	public WyjatekParseraXML
{
public:
	typedef LoggerInterface<BrakMaski> LogBrakMaski;

	static const IdType idBrakMaski;

	BrakMaski( const Tekst& tPlik, const IdType& iLinia );
	BrakMaski( const Tekst& tPlik, const IdType& iLinia, const Tekst& );
	BrakMaski( const BrakMaski& );
	virtual ~BrakMaski();

	Tekst getNazwaMaski() const;
	void setNazwaMaski( const Tekst& );

	Tekst generujKomunikat() const override;

	string toString() const override;

private:
	Tekst nazwaMaski;
	
	static const Tekst tytulBrakMaski;
	static const Tekst trescBrakMaski;
};

