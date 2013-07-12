#pragma once
#include "Main.h"
#include "parser\ticpp.h"
#include "FuncTransf\ZmianaInterfejs.h"
#include "Ilosc.h"
#include "Poziom.h"
#include "IdType.h"
#include "PodstawoweParametry.h"

class Surowce;
class WyjatekParseraXML;

class Cena :
	virtual public LoggerInterface
{
public:
	typedef Surowce Item;
	explicit Cena( TiXmlElement* ) throw(WyjatekParseraXML);
	Cena( const Cena& );

	Cena& operator=(const Cena&);
	
	Cena* Kopia() const;

	shared_ptr<Item> PobierzKoszty( const Ilosc&, const PodstawoweParametry& param) const;

	bool czySpelniaKoszty( const Ilosc& i, const PodstawoweParametry& param ) const;

	const Item& getKoszty() const;
	void setKoszty( const Item& );

	string napis() const override;

private:
	shared_ptr<Item> obiekty;
	shared_ptr<ZmianaInterfejs> zmiana;
};

