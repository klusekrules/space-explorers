#pragma once
#include "Logger\LoggerInterface.h"
#include "IdType.h"
#include "Poziom.h"
#include "Serializacja.h"

class PodstawoweParametry :	
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	PodstawoweParametry( const Poziom&, const IdType& );
	virtual ~PodstawoweParametry(void);

	string toString()const override;

	const Poziom& getPoziom() const;

	void wzrostPoziomu();

	void setPoziom(const Poziom&);

	const IdType& getIdPlanety() const;

	void setIdPlanety( const IdType& id );

	bool zapisz( TiXmlElement* ) const override;

	bool odczytaj( TiXmlElement* ) override;

	void ustawKontekst( const PodstawoweParametry& p );

private:
	Poziom poziom;
	IdType idPlanety;
};

