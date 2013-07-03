#pragma once
#include "Main.h"
#include "Cena.h"
#include "parser\ticpp.h"
#include <vector>
#include "Ilosc.h"
#include "Poziom.h"
#include "IdType.h"
#include "PodstawoweParametry.h"

class Cennik:
	virtual public LoggerInterface
{
public:
	typedef vector< shared_ptr<Cena> > Zbiornik;
	typedef vector< shared_ptr<Surowce> > ListaSurowcow;
	explicit Cennik( ticpp::Node* ) throw(WyjatekParseraXML);
	Cennik( const Cennik& );
	Cennik& operator=( const Cennik& );

	ListaSurowcow PobierzKoszty(const Ilosc&, const PodstawoweParametry& ) const;

	bool czySpelniaKoszty( const Ilosc&, const PodstawoweParametry& ) const;

	string toString()const override;
private:
	Zbiornik elementy;
};

