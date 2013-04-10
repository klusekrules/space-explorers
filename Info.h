#pragma once
#include "Main.h"
#include "Base.h"
#include "Tekst.h"
#include "IdType.h"
#include "Wymagania.h"
#include "WyjatekParseraXML.h"

class Info:
	public Base,
	public Wymagania,
	public LoggerInterface<Info>
{
public:
	typedef LoggerInterface<Info> LogInfo;

	Info( const Tekst& , const Tekst& , const IdType&, const Wymagania& ) throw();
	explicit Info( ticpp::Node* ) throw(WyjatekParseraXML);
	virtual ~Info();

	const Tekst& getNazwa() const;
	void setNazwa( const Tekst& );

	const Tekst& getOpis() const;
	void setOpis( const Tekst& );
	
	string toString() const override;

private:

	Tekst nazwa;
	Tekst opis;
};

