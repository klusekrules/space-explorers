#pragma once
#include "Logger\LoggerInterface.h"
#include "Identyfikator.h"
#include "Poziom.h"
#include "Serializacja.h"

class PodstawoweParametry :	
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	PodstawoweParametry( const Poziom&, const Identyfikator& );
	virtual ~PodstawoweParametry(void);

	string napis()const override;

	const Poziom& getPoziom() const;

	void wzrostPoziomu();

	void setPoziom(const Poziom&);

	const Identyfikator& getIdPlanety() const;

	void setIdPlanety( const Identyfikator& id );

	bool zapisz( TiXmlElement* ) const override;

	bool odczytaj( TiXmlElement* ) override;

	void ustawKontekst( const PodstawoweParametry& p );

private:
	Poziom poziom;
	Identyfikator idPlanety;
};

