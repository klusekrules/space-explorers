#pragma once
#include "Main.h"
#include "LoggerInterface.h"
#include "parser\ticpp.h"
#include "ZmianaInterfejs.h"
#include "Ilosc.h"
#include "Poziom.h"
#include "IdType.h"

class Surowce;
class WyjatekParseraXML;

class Cena :
	virtual public LoggerInterface
{
public:
	typedef Surowce Item;
	explicit Cena( ticpp::Node* ) throw(WyjatekParseraXML);
	explicit Cena( const Item& ) throw();
	Cena( const Cena& );

	Cena& operator=(const Cena&);

	virtual ~Cena();

	Cena* Kopia() const;

	shared_ptr<Item> PobierzKoszty( const Ilosc&, const Poziom& ) const;

	bool czySpelniaKoszty( const Ilosc& i, const Poziom& p, const IdType& idPlanety ) const;

	const Item& getKoszty() const;
	void setKoszty( const Item& );

	string toString() const override;

private:
	shared_ptr<Item> obiekty;
	shared_ptr<ZmianaInterfejs> zmiana;
};

