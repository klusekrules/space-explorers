#pragma once
#include "parser\ticpp.h"

class Serializacja
{
public:

	Serializacja(){
	}

	virtual ~Serializacja(){
	}

	virtual bool zapisz( TiXmlElement* n ) const = 0;
	virtual bool odczytaj( TiXmlElement* n ) = 0;
};

