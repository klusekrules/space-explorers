#pragma once
#include "Logger\LoggerInterface.h"
#include "IdType.h"
#include "Poziom.h"

class PodstawoweParametry :	
	virtual public LoggerInterface
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

	void ustawKontekst( const PodstawoweParametry& p );

private:
	Poziom poziom;
	IdType idPlanety;
};

