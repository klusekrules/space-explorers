#pragma once
#include "Main.h"
#include <vector>
#include <memory>
#include "parser\ticpp.h"
#include "IdType.h"
#include "ZmianaInterfejs.h"

class ObiektBaseInfo;

class Warunek :
	public LoggerInterface< Warunek >
{
public:
	typedef pair < shared_ptr< ObiektBaseInfo > , shared_ptr< ZmianaInterfejs > > Item;
	typedef vector< Item > ListaWarunkow;
	typedef vector< shared_ptr< ObiektBaseInfo > > PrzetworzoneWarunki;

	Warunek();
	Warunek( ticpp::Node* n );
	Warunek(const Warunek& w);
	const Warunek& operator=(const Warunek& w);
	~Warunek();

	PrzetworzoneWarunki listaWarunkow( const Poziom& p ) const;

	bool czySpelniaWarunki( const IdType& idPlanety ) const;

	string toString() const override;

private:
	
	bool dodajWarunek( Item& o );

	shared_ptr< ObiektBaseInfo > przeliczWarunek( Item& o, const Poziom& p  ) const;

	ListaWarunkow warunki;
};

