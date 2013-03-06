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
	virtual public Base,
	public ObiektBase,
	public LoggerInterface<Obiekt>
{
public:
	typedef LoggerInterface<Obiekt> LogObiekt;

	Obiekt();
	explicit Obiekt( const ObiektBase& );
	explicit Obiekt( const ObiektInfo& );
	Obiekt( const Obiekt& );
	Obiekt( const Fluktuacja& , const Fluktuacja& , const Fluktuacja& , const ObiektBase& );
	Obiekt( const Fluktuacja& , const Fluktuacja& , const Fluktuacja& , const ObiektInfo& );
	virtual ~Obiekt();

	Obiekt* Kopia() const override;

	Obiekt* Podziel( const Ilosc& ) override;
	
	Powierzchnia getPowierzchnia() const;

	Objetosc getObjetosc() const;

	Masa getMasa() const;
		
	const Fluktuacja& getZmianaPowierzchnia() const;

	void setZmianaPowierzchnia( const Fluktuacja& pPrzyrostPowierzchnia );

	const Fluktuacja& getZmianaObjetosc() const;

	void setZmianaObjetosc( const Fluktuacja& pPrzyrostObjetosc );

	const Fluktuacja& getZmianaMasa() const;

	void setZmianaMasa( const Fluktuacja& pPrzyrostMasa );

	string toString() const override;

protected:
	Fluktuacja zmPowierzchnia;
	Fluktuacja zmObjetosc;
	Fluktuacja zmMasa;
};

