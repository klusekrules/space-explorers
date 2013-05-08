#pragma once
#include "Main.h"
#include "Cena.h"
#include "Logger\LoggerInterface.h"
#include "parser\ticpp.h"
#include <vector>
#include "BaseTypes\Ilosc.h"
#include "BaseTypes\Poziom.h"
#include "BaseTypes\IdType.h"

class Cennik:
	virtual public LoggerInterface
{
public:
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

