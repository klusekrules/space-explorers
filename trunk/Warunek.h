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

	Warunek();
	Warunek( ticpp::Node* n );
	Warunek(const Warunek& w);
	const Warunek& operator=(const Warunek& w);
	~Warunek();

	bool czySpelniaWarunki( const IdType& idPlanety ) const;

	string toString() const override;

private:
	
	bool dodajWarunek( Item o );

	ListaWarunkow warunki;
};

