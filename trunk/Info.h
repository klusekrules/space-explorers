#pragma once
#include "Main.h"
#include "Base.h"
#include "Tekst.h"
#include "ObiektBase.h"

class Info:
	virtual public Base,
	public LoggerInterface<Info>
{
public:
	Info();
	Info( const Tekst& , const Tekst& );
	Info( const Info& );
	virtual ~Info();

	const Tekst& getNazwa() const;
	void setNazwa( const Tekst& );

	const Tekst& getOpis() const;
	void setOpis( const Tekst& );
	
	string toString() const override;

private:
	typedef LoggerInterface<Info> LogInfo;

	Tekst nazwa;
	Tekst opis;
};

