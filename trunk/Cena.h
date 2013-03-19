#pragma once
#include "Main.h"
#include "CenaInterfejs.h"
#include "LoggerInterface.h"
#include "parser\ticpp.h"

class Cena :
	public CenaInterfejs,
	public LoggerInterface < Cena >
{
public:
	typedef LoggerInterface < Cena > LogCena;

	explicit Cena( ticpp::Node* );
	explicit Cena( const Item& );
	Cena( const Cena& );

	Cena& operator=(const Cena&);

	virtual ~Cena();

	Cena* Kopia() const override;

	Item PobierzKoszty( ) const override;

	bool czySpelniaWymagania( const Ilosc& i, const IdType& idPlanety ) const override;

	const Item& getKoszty() const;
	void setKoszty( const Item& );

	string toString() const override;

private:
	Item* obiekty;
};

