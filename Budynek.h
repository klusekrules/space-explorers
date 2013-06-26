#pragma once
#include "Obiekt.h"
#include "Cennik.h"

class Budynek :
	public Obiekt,
	virtual public LoggerInterface
{
	friend class BudynekInfo;
protected:
	const BudynekInfo& budynekInfo;
public:
	Budynek(const Poziom& p, const BudynekInfo&);
	~Budynek(void);

	Budynek* Kopia() const override;

	Budynek* Podziel( const Ilosc& ilosc) override;

	bool Polacz( const ObiektBase& obiektBase) override;
	
	bool czyMoznaPolaczyc( const ObiektBase& obiektBase) const override;

	bool czyMoznaPodzielic( const Ilosc& ilosc) const override;

	Cennik::ListaSurowcow PobierzZapotrzebowanie( )const;

	Cennik::ListaSurowcow PobierzProdukcje( )const;

	string toString()const override;
};

