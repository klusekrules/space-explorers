#pragma once
#include "ObiektBase.h"
#include "Logger.h"

class Technologia :
	public ObiektBase,
	virtual public LoggerInterface
{
	friend class TechnologiaInfo;
protected:
	const TechnologiaInfo& technologiaInfo;
public:
	explicit Technologia( const Poziom&, const TechnologiaInfo& );
	~Technologia(void);

	Technologia* Kopia() const override;

	Technologia* Podziel( const Ilosc& ilosc) override;

	bool Polacz( const ObiektBase& obiektBase) override;
	
	bool czyMoznaPolaczyc( const ObiektBase& obiektBase) const override;

	bool czyMoznaPodzielic( const Ilosc& ilosc) const override;

	string toString() const override;
};
