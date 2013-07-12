#pragma once
#include "Main.h"
#include "Cena.h"
#include "parser\ticpp.h"
#include <vector>
#include "Ilosc.h"
#include "Poziom.h"
#include "IdType.h"
#include "PodstawoweParametry.h"
#include "Czas.h"

class Cennik:
	virtual public LoggerInterface
{
public:
	typedef vector< shared_ptr<Cena> > Zbiornik;
	typedef vector< shared_ptr<Surowce> > ListaSurowcow;
	explicit Cennik( TiXmlElement* ) throw(WyjatekParseraXML);
	Cennik( const Cennik& );
	Cennik& operator=( const Cennik& );

	virtual Czas pobierzCzasBudowy( const PodstawoweParametry& )const;

	ListaSurowcow PobierzKoszty(const Ilosc&, const PodstawoweParametry& ) const;

	bool czySpelniaKoszty( const Ilosc&, const PodstawoweParametry& ) const;

	string napis()const override;
private:
	Zbiornik elementy;

	shared_ptr <ZmianaInterfejs> zmCzasuBudowy;
};

