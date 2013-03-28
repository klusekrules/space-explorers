#pragma once
#include "Main.h"
#include "LoggerInterface.h"
#include "parser\ticpp.h"
#include "ZmianaInterfejs.h"
#include "Surowce.h"

class Cena :
	public LoggerInterface < Cena >
{
public:
	typedef LoggerInterface < Cena > LogCena;
	typedef Surowce Item;
	explicit Cena( ticpp::Node* );
	explicit Cena( const Item& );
	Cena( const Cena& );

	Cena& operator=(const Cena&);

	virtual ~Cena();

	Cena* Kopia() const;

	shared_ptr<Item> PobierzKoszty( const Ilosc&, const Poziom& ) const;

	bool czySpelniaWymagania( const Ilosc& i, const Poziom& p, const IdType& idPlanety ) const;

	const Item& getKoszty() const;
	void setKoszty( const Item& );

	string toString() const override;

private:
	shared_ptr<Item> obiekty;
	shared_ptr<ZmianaInterfejs> zmiana;
};

