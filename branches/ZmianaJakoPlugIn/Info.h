#pragma once
#include "Main.h"
#include "Base.h"
#include "BaseTypes\Tekst.h"
#include "BaseTypes\IdType.h"
#include "Wymagania.h"
#include "BaseTypes\WyjatekParseraXML.h"

class Info:
	public Base,
	public Wymagania,
	virtual public LoggerInterface
{
public:
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

