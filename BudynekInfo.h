#pragma once
#include "Budynek.h"
#include "parser\ticpp.h"
#include "ObiektInfo.h"
#include "PodstawoweParametry.h"

class BudynekInfo :
	public ObiektInfo,
	virtual public LoggerInterface
{
protected:
	Wymagania::ListaCen zapotrzebowanie;
	Wymagania::ListaCen produkcja;

public:
	BudynekInfo( TiXmlElement* );
	~BudynekInfo(void);
	Budynek* tworzEgzemplarz( const Ilosc&, const Identyfikator& ) const override;

	Wymagania::PrzetworzonaCena PobierzZapotrzebowanie( const PodstawoweParametry& param)const;

	Wymagania::PrzetworzonaCena PobierzProdukcje( const PodstawoweParametry& param )const;

	string napis()const override;
private:
	bool tworz( const Gra& g, Planeta& p , const Ilosc& i ) const override;
};

