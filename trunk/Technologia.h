#pragma once
#include "ObiektBazowy.h"
#include "Logger.h"

class Technologia :
	public ObiektBazowy,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class TechnologiaInfo;
protected:
	const TechnologiaInfo& technologiaInfo;
public:
	Technologia( const Poziom&, const Identyfikator&, const TechnologiaInfo& );
	Technologia( const PodstawoweParametry& p, const TechnologiaInfo& t);
	~Technologia(void);

	Technologia* Kopia() const override;

	Technologia* Podziel( const Ilosc& ilosc) override;

	bool Polacz( const ObiektBazowy& obiektBase) override;
	
	bool czyMoznaPolaczyc( const ObiektBazowy& obiektBase) const override;

	bool czyMoznaPodzielic( const Ilosc& ilosc) const override;

	void wybuduj(const Ilosc&) override;

	bool zapisz( TiXmlElement* e) const override;
	bool odczytaj (TiXmlElement* e) override;

	string napis() const override;
};

