#pragma once
#include "Main.h"
#include "Base.h"
#include "Tekst.h"
#include "IdType.h"
#include "Wymagania.h"

class Info:
	public Base,
	public LoggerInterface<Info>
{
public:
	typedef LoggerInterface<Info> LogInfo;

	Info( const Tekst& , const Tekst& , const IdType&, const Wymagania& );
	virtual ~Info();

	const Tekst& getNazwa() const;
	void setNazwa( const Tekst& );

	const Tekst& getOpis() const;
	void setOpis( const Tekst& );

	const Wymagania& getWymagania() const;

	bool sprawdzWymagania(const Ilosc& i , const IdType& idPlanety) const;
	
	string toString() const override;

private:
	
	Wymagania wymagania;

	Tekst nazwa;
	Tekst opis;
};

