#pragma once
#include "Main.h"
#include "CenaInterfejs.h"
#include "LoggerInterface.h"
#include "NiezainicjalizowanaKlasa.h"
#include "parser\ticpp.h"

class CenaDekorator:
	public CenaInterfejs,
	public LoggerInterface < CenaDekorator >
{
public:	
	typedef LoggerInterface < CenaDekorator > LogCenaDekorator;

	static CenaDekorator* TworzDekorator( ticpp::Node* n );
	
	explicit CenaDekorator( ticpp::Node* n );
	
	explicit CenaDekorator( CenaInterfejs* );

	CenaDekorator( const CenaDekorator& );

	CenaDekorator& operator=( const CenaDekorator& );

	virtual ~CenaDekorator();

	CenaDekorator* Kopia() const override;

	Item PobierzKoszty( ) const override;

	bool czySpelniaWymagania( const Ilosc&, const IdType& ) const override;

	virtual string toString() const override;

private:
	CenaInterfejs* dekorator;

};

