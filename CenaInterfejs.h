#pragma once
#include "Main.h"
#include "Surowce.h"
#include "LoggerInterface.h"

class CenaInterfejs :
	public LoggerInterface < CenaInterfejs > 
{
public:
	typedef LoggerInterface < CenaInterfejs > LogCenaInterface;
	typedef Surowce Item;

	virtual Item PobierzKoszty( ) const = 0;

	virtual CenaInterfejs* Kopia() const = 0 ;

	virtual bool czySpelniaWymagania( const Ilosc&, const IdType& ) const = 0 ;

	virtual ~CenaInterfejs();

	string toString()const override;
	
};

