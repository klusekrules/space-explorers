#pragma once
#include "Main.h"
#include "CenaInterfejs.h"
#include "LoggerInterface.h"

class CenaDekorator:
	public CenaInterfejs,
	public LoggerInterface < CenaDekorator >
{
public:	
	typedef LoggerInterface < CenaDekorator > LogCenaDekorator;

	explicit CenaDekorator( CenaInterfejs* );

	CenaDekorator( const CenaDekorator& );

	CenaDekorator& operator=( const CenaDekorator& );

	virtual ~CenaDekorator();

	CenaDekorator* Kopia() const override;

	Zbiornik PobierzKoszty( ) const override;

	bool czySpelniaWymagania( const Ilosc&, const IdType& ) const override;

	string toString() const override;
private:

	CenaInterfejs* dekorator;

};

