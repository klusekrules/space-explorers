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
class Ladownia;

class Obiekt:
	public ObiektBase,
	virtual public LoggerInterface
{
public:

	Obiekt( const Ilosc&, const Poziom& p, const IdType&, const ObiektInfo& ) throw();
	virtual ~Obiekt();

	Obiekt* Kopia() const override;

	Obiekt* Podziel( const Ilosc& ) override;

	virtual bool czMoznaDodacDoLadownii( const Ladownia& c ) const;
	
	virtual Powierzchnia getPowierzchnia() const;

	virtual Objetosc getObjetosc() const;

	virtual Masa getMasa() const;

	string toString() const override;
protected:

	const ObiektInfo& obiektInfoClass; 
};

