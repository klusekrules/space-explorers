#pragma once
#include "Main.h"
#include "Fluktuacja.h"
#include "Ilosc.h"
#include "Base.h"
#include "ObiektBase.h"
#include "Powierzchnia.h"
#include "Objetosc.h"
#include "Masa.h"

class ObiektInfo;

class Obiekt:
	public ObiektBase,
	public LoggerInterface<Obiekt>
{
public:
	typedef LoggerInterface<Obiekt> LogObiekt;

	explicit Obiekt( const ObiektInfo& );
	virtual ~Obiekt();

	Obiekt* Kopia() const override;

	Obiekt* Podziel( const Ilosc& ) override;
	
	Powierzchnia getPowierzchnia() const;

	Objetosc getObjetosc() const;

	Masa getMasa() const;

	string toString() const override;
private:
	const ObiektInfo& obiektInfoClass; 
};
