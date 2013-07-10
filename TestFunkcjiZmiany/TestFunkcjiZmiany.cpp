// TestFunkcjiZmiany.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TestFunkcjiZmiany.h"
#include "..\XmlBO.h"
#include "..\Logger.h"
#include "..\definicjeWezlowXML.h"

ZmianaTest::ZmianaTest( TiXmlElement* e )
	: parametr(XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,WEZEL_XML_PARAM,ATRYBUT_XML_IDENTYFIKATOR,"0"))
{
}

ZmianaTest::~ZmianaTest(void)
{
}

long double ZmianaTest::policzWartosc(long double d, int p, int) const{
	return d * parametr.pobierzWspolczynnik() * p * 10 ;
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
