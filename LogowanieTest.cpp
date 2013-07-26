#include "LogowanieTest.h"
#include "Aplikacja.h"

LogowanieTest::LogowanieTest(void)
{
}

void LogowanieTest::zaloguj(){	
	UNIT_TEST_ASSERT_EQUAL(true,Aplikacja::getInstance().getGra().logowanie("",""));
}

LogowanieTest::~LogowanieTest(void)
{
}

