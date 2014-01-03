#include "ParserTest.h"
#include "ParserDokumentXml.h"

ParserTest::ParserTest()
{
}

ParserTest::~ParserTest()
{
}

void ParserTest::tworzPlik()
{
	se::ParserDokumentXml dokument;
	auto element = dokument.tworzElement("root");
	UNIT_TEST_ASSERT_NOTNULL(element);
	auto wezel = element->tworzElement("element");
	UNIT_TEST_ASSERT_NOTNULL(wezel);
	UNIT_TEST_ASSERT_NOTNULL(element->tworzAtrybut("Nazwa","Element"));
	UNIT_TEST_ASSERT_NOTNULL(wezel->tworzAtrybut("Nazwa","Wezel"));
	UNIT_TEST_ASSERT_TRUE(dokument.zapisz("ParserTest.xml"));
}

void ParserTest::zapiszPlik()
{
	se::ParserDokumentXml dokument;
	UNIT_TEST_ASSERT_TRUE(dokument.odczytaj("ParserTest.xml"));
	auto element = dokument.pobierzElement("root");
	UNIT_TEST_ASSERT_NOTNULL(element);
	auto wezel = element->tworzElement("wezel");
	UNIT_TEST_ASSERT_NOTNULL(wezel);
	UNIT_TEST_ASSERT_NOTNULL(wezel->tworzAtrybut("Nazwa","NowyWezel"));
	UNIT_TEST_ASSERT_TRUE(dokument.zapisz("ParserTest.xml"));
}

void ParserTest::odczytajPlik()
{
	se::ParserDokumentXml dokument;
	UNIT_TEST_ASSERT_TRUE(dokument.odczytaj("ParserTest.xml"));
	auto root = dokument.pobierzElement("root");
	UNIT_TEST_ASSERT_NOTNULL(root);

	auto atrRoot = root->pobierzAtrybut("Nazwa");
	UNIT_TEST_ASSERT_NOTNULL(atrRoot);
	UNIT_TEST_ASSERT_TRUE(! strcmp( atrRoot->pobierzWartosc(), "Element" ));

	auto element = root->pobierzElement("element");
	UNIT_TEST_ASSERT_NOTNULL(element);

	auto atrElement = element->pobierzAtrybut("Nazwa");
	UNIT_TEST_ASSERT_NOTNULL(atrElement);
	UNIT_TEST_ASSERT_TRUE(! strcmp( atrElement->pobierzWartosc(), "Wezel" ));

	auto wezel = root->pobierzElement("wezel");
	UNIT_TEST_ASSERT_NOTNULL(wezel);

	auto atrWezel = wezel->pobierzAtrybut("Nazwa");
	UNIT_TEST_ASSERT_NOTNULL(atrWezel);
	UNIT_TEST_ASSERT_TRUE(! strcmp( atrWezel->pobierzWartosc(), "NowyWezel" ));
	
}

void ParserTest::usunPlik()
{
	UNIT_TEST_ASSERT_TRUE(!remove("ParserTest.xml"));
}
