#include "LogowanieTest.h"
#include "Aplikacja.h"

LogowanieTest::LogowanieTest(void)
{
}

void LogowanieTest::zaloguj(){	
	UNIT_TEST_ASSERT_EQUAL(true,Aplikacja::pobierzInstancje().pobierzGre().logowanie("",""));
}

LogowanieTest::~LogowanieTest(void)
{
}

