#pragma once
#include "Main.h"
#include "ObiektList.hpp"
#include "Surowce.h"
#include "LoggerInterface.h"

class CenaInterfejs :
	public LoggerInterface < CenaInterfejs >
{
public:
	typedef Surowce Item;
	typedef ObiektList< Item > Zbiornik;

	virtual Zbiornik PobierzKoszty( ) const = 0;

	virtual CenaInterfejs* Kopia() const = 0 ;

	virtual bool czySpelniaWymagania( const Zbiornik& ) const = 0 ;

	virtual ~CenaInterfejs(){}

	string toString() const override{
		Logger str(className());
		return str.toString();
	}

};

