#pragma once
#include "Main.h"
#include "CenaDekorator.h"
#include "parser\ticpp.h"

class CenaLiniowyDekorator :
	public CenaDekorator,
	public LoggerInterface < CenaLiniowyDekorator >
{
public:
	typedef LoggerInterface <CenaLiniowyDekorator> LogCenaLiniowyDekorator;
	CenaLiniowyDekorator( ticpp::Node* n );
	virtual ~CenaLiniowyDekorator(void);

	string toString()const override;
};

