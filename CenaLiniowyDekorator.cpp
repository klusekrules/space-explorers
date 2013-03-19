#include "CenaLiniowyDekorator.h"
#include "XmlBO.h"
#include "Logger.h"

CenaLiniowyDekorator::CenaLiniowyDekorator( ticpp::Node* n )
	: CenaDekorator( n )
{
}


CenaLiniowyDekorator::~CenaLiniowyDekorator(void)
{
}

string CenaLiniowyDekorator::toString()const{
	Logger str(LogCenaLiniowyDekorator::className());
	str.addClass(CenaDekorator::toString());
	return str.toString();
}