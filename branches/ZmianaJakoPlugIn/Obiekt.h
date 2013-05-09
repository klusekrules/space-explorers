#pragma once
#include "Main.h"
#include "BaseTypes\BaseTypes.h"
#include "BaseTypes\Wyjatki.h"
#include "ObiektBase.h"

class ObiektInfo;
class Ladownia;

class Obiekt:
	public ObiektBase,
	virtual public LoggerInterface
{
public:

	Obiekt( const Ilosc&, const ObiektInfo& ) throw();
	virtual ~Obiekt();

	Obiekt* Kopia() const override;

	Obiekt* Podziel( const Ilosc& ) override;

	virtual bool czMoznaDodacDoLadownii( const Ladownia& c ) const;
	
	Powierzchnia getPowierzchnia() const;

	Objetosc getObjetosc() const;

	Masa getMasa() const;

	string toString() const override;
protected:
	const ObiektInfo& obiektInfoClass; 
};

