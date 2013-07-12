#pragma once
#include "Main.h"
#include <vector>
#include <memory>
#include "parser\ticpp.h"
#include "Identyfikator.h"
#include "FuncTransf\ZmianaInterfejs.h"
#include "Poziom.h"
#include "PodstawoweParametry.h"

class ObiektBaseInfo;
class WyjatekParseraXML;

class Warunek :
	virtual public LoggerInterface
{
public:
	typedef pair < shared_ptr< ObiektBaseInfo > , shared_ptr< ZmianaInterfejs > > Item;
	typedef vector< Item > ListaWarunkow;
	typedef vector< shared_ptr< ObiektBaseInfo > > PrzetworzoneWarunki;

	explicit Warunek( TiXmlElement* n ) throw(WyjatekParseraXML);
	explicit Warunek(const Warunek& w);
	Warunek& operator=(const Warunek& w);

	PrzetworzoneWarunki listaWarunkow( const PodstawoweParametry& ) const;

	bool czySpelniaWarunki( const PodstawoweParametry& ) const;

	string napis() const override;

private:
	
	bool dodajWarunek( Item& o );

	shared_ptr< ObiektBaseInfo > przeliczWarunek( Item& o, const PodstawoweParametry& ) const;

	ListaWarunkow warunki;
};

