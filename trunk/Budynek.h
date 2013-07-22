#pragma once
#include "Obiekt.h"

class Budynek :
	public Obiekt,
	virtual public LoggerInterface
{
	friend class BudynekInfo;
protected:
	const BudynekInfo& budynekInfo;
public:
	Budynek(const Poziom& p, const Identyfikator& idP, const BudynekInfo&);
	Budynek(const PodstawoweParametry& p, const BudynekInfo& o);
	~Budynek(void);

	Budynek* Kopia() const override;

	Budynek* Podziel( const Ilosc& ilosc) override;

	bool Polacz( const ObiektBazowy& obiektBase) override;
	
	bool czyMoznaPolaczyc( const ObiektBazowy& obiektBase) const override;

	bool czyMoznaPodzielic( const Ilosc& ilosc) const override;

	Wymagania::PrzetworzonaCena PobierzZapotrzebowanie( )const;

	Wymagania::PrzetworzonaCena PobierzProdukcje( )const;

	void wybuduj(const Ilosc&) override;

	bool zapisz( TiXmlElement* e) const override;
	bool odczytaj (TiXmlElement* e) override;

	string napis()const override;
};

