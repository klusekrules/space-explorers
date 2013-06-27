#pragma once
#include "Budynek.h"
#include "parser\ticpp.h"
#include "ObiektInfo.h"

class BudynekInfo :
	public ObiektInfo,
	virtual public LoggerInterface
{
protected:
	Cennik::Zbiornik zapotrzebowanie;
	Cennik::Zbiornik produkcja;

public:
	BudynekInfo( ticpp::Node* );
	~BudynekInfo(void);
	Budynek* TworzEgzemplarz( const Ilosc& = Ilosc() ) const override;

	Cennik::ListaSurowcow PobierzZapotrzebowanie( const Poziom& )const;

	Cennik::ListaSurowcow PobierzProdukcje( const Poziom& )const;

	string toString()const override;
};

