// TestFunkcjiZmiany.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TestFunkcjiZmiany.h"
#include "..\XmlBO.h"
#include "..\Logger.h"

ZmianaTest::ZmianaTest( const ticpp::Element* e )
	: parametr(XmlBO::IterateChildrenElement<NOTHROW>(e,"Param"))
{
}

ZmianaTest::~ZmianaTest(void)
{
}

long double ZmianaTest::value(const long double& d, const int& p) const{
	return d * parametr.getWspolczynnik() * p * 10 ;
}

ZmianaTest* ZmianaTest::Kopia()const{
	return new ZmianaTest(*this);
}

bool ZmianaTest::RejestrujZmianaTest(  ZmianaFabryka &ref ){
	return ref.RejestracjaZmiany(idKlasy,ZmianaTest::TworzZmianaTest);
}

string ZmianaTest::toString()const{
	Logger str(CLASSNAME(ZmianaTest));
	str.addField("Parametr",parametr);
	return str.toString();
}

const int ZmianaTest::idKlasy(5);

bool RejestrujZmiany ( ZmianaFabryka& fabryka , Log& logger ){
	if(ZmianaTest::RejestrujZmianaTest(fabryka))
		logger.info("Zaladowano ZmianaTest.");
	else
		logger.info("Nie zaladowano ZmianaTest.");
	return true;
}
