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
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:

	Obiekt( const Ilosc&, const Poziom& p, const IdType&, const ObiektInfo& ) throw();
	Obiekt( const Ilosc&, const PodstawoweParametry& , const ObiektInfo& ) throw();
	virtual ~Obiekt();

	Obiekt* Kopia() const override;

	Obiekt* Podziel( const Ilosc& ) override;

	virtual bool czMoznaDodacDoLadownii( const Ladownia& c ) const;
	
	virtual Powierzchnia getPowierzchnia() const;

	virtual Objetosc getObjetosc() const;

	virtual Masa getMasa() const;

	bool zapisz( TiXmlElement* e) const override;
	bool odczytaj (TiXmlElement* e) override;

	string napis() const override;
protected:

	const ObiektInfo& obiektInfoClass; 
};

