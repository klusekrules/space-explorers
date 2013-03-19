#pragma once
#include "Main.h"
#include "CenaInterfejs.h"
#include "LoggerInterface.h"
#include "parser\ticpp.h"
#include <vector>

class Cennik:
	public LoggerInterface < Cennik >
{
public:
	typedef LoggerInterface < Cennik > LogCennik;
	
	typedef vector< CenaInterfejs* > Zbiornik;

	explicit Cennik( ticpp::Node* );
	virtual ~Cennik();

	bool czySpelniaWymagania( const Ilosc&, const IdType& ) const;

	string toString()const override;
private:
	Zbiornik elementy;
};

