#pragma once
#include "ObiektBase.h"
#include "Logger.h"

class Technologia :
	public ObiektBase,
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

	bool Polacz( ObiektBase& obiektBase) override;
	
	bool czyMoznaPolaczyc( const ObiektBase& obiektBase) const override;

	bool czyMoznaPodzielic( const Ilosc& ilosc) const override;

	void wybuduj(const Ilosc&) override;

	bool zapisz( TiXmlElement* e) const override;
	bool odczytaj (TiXmlElement* e) override;

	string napis() const override;
};

