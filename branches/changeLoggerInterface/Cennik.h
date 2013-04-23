#pragma once
#include "Main.h"
#include "Cena.h"
#include "LoggerInterface.h"
#include "parser\ticpp.h"
#include <vector>
#include "Ilosc.h"
#include "Poziom.h"
#include "IdType.h"

class Cennik:
	public LoggerInterface < Cennik >
{
public:
	typedef LoggerInterface < Cennik > LogCennik;
	
	typedef vector< shared_ptr<Cena> > Zbiornik;
	typedef vector< shared_ptr<Surowce> > ListaSurowcow;
	explicit Cennik( ticpp::Node* ) throw(WyjatekParseraXML);
	virtual ~Cennik();

	Cennik& operator=( const Cennik& );

	ListaSurowcow PobierzKoszty(const Ilosc&, const Poziom&) const;

	//IdType - id planety w kontekœcie której maj¹ byæ sprawdzane wymagania.
	bool czySpelniaKoszty( const Ilosc&, const Poziom&, const IdType& ) const;

	string toString()const override;
private:
	Zbiornik elementy;
};

