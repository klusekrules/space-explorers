#pragma once
#include "Main.h"
#include "Bazowa.h"
#include "Tekst.h"
#include "Identyfikator.h"
#include "Wymagania.h"
#include "WyjatekParseraXML.h"

class Info:
	public Bazowa,
	public Wymagania,
	virtual public LoggerInterface
{
public:
	Info( const Tekst& , const Tekst& , const Identyfikator&, const Wymagania& ) throw();
	explicit Info( TiXmlElement * ) throw(WyjatekParseraXML);
	virtual ~Info();

	const Tekst& getNazwa() const;
	void setNazwa( const Tekst& );

	const Tekst& getOpis() const;
	void setOpis( const Tekst& );
	
	string napis() const override;

private:

	Tekst nazwa;
	Tekst opis;
};

