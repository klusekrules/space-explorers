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
	Cennik::Zbiornik zapotrzebowanie;
	Cennik::Zbiornik produkcja;

public:
	BudynekInfo( TiXmlElement* );
	~BudynekInfo(void);
	Budynek* TworzEgzemplarz( const Ilosc&, const IdType& ) const override;

	Cennik::ListaSurowcow PobierzZapotrzebowanie( const PodstawoweParametry& param)const;

	Cennik::ListaSurowcow PobierzProdukcje( const PodstawoweParametry& param )const;

	string toString()const override;
private:
	bool Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const override;
};

