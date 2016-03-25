#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser\XmlBO.h"
#include "Parser\ParserDokumentXml.h"
#include "Parser\ParserDokumentJSON.h"
#include "Logger\Log.h"
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Parser\json\json.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define TEST_MY_TRAIT(traitValue) TEST_METHOD_ATTRIBUTE(L"MyTrait", traitValue)

namespace ParserTesty
{		
	TEST_CLASS(ParserTest)
	{
	public:
		std::string nazwaPlikuXml_ = "plik.xml";
		std::string nazwaPlikuJson_ = "plik.json";
		static SLog::Log& log;
		SPar::ParserDokumentXml dokumentXml_;
		SPar::ParserDokumentJSON dokumentJson_;

		TEST_CLASS_INITIALIZE(logger){
			struct tm timeinfo;
			time_t t = time(nullptr);
			localtime_s(&timeinfo, &t);
			char s[20];
			strftime(s, 20, "%Y-%m-%d", &timeinfo);
			std::stringstream sfile;
			sfile << "ParserTest-" << s << ".log";
			std::string filename = sfile.str();
#ifdef DEBUG
			log.odblokujLogi(SLog::Log::Debug);
#else
			log.zablokujLogi(SLog::Log::Debug);
#endif
			log.ustawFormatCzasu(SLog::Log::Czas);
			log.dodajGniazdoWyjsciowe([filename](SLog::Log::TypLogow typ, const std::string& czas, const std::string& komunikat)->void{
				static std::fstream plik(filename, std::ios_base::app); 
				std::string sTyp;
				switch (typ)
				{
				case SLog::Log::Debug: sTyp = " [DEBUG] ";
					break;
				case SLog::Log::Info: sTyp = " [INFO] ";
					break;
				case SLog::Log::Warning: sTyp = " [WARNING] ";
					break;
				case SLog::Log::Error: sTyp = " [ERROR] ";
					break;
				case SLog::Log::All:
				default:
					break;
				}
				plik << czas << sTyp << komunikat; 
			});
			log.dodajGniazdoWyjsciowe([](SLog::Log::TypLogow typ, const std::string& czas, const std::string& komunikat)->void{ 
				if (!komunikat.empty()){
					std::string sTyp;
					switch (typ)
					{
					case SLog::Log::Debug: sTyp = " [DEBUG] ";
						break;
					case SLog::Log::Info: sTyp = " [INFO] ";
						break;
					case SLog::Log::Warning: sTyp = " [WARNING] ";
						break;
					case SLog::Log::Error: sTyp = " [ERROR] ";
						break;
					case SLog::Log::All:
					default:
						break;
					}
					Logger::WriteMessage((czas + sTyp + komunikat).c_str());
				}
			});
		}

		TEST_METHOD_INITIALIZE(Inicjalizacja){
			FILE *fpXml;
			Assert::IsTrue(fopen_s(&fpXml, nazwaPlikuXml_.c_str(), "w+") == 0, L"Nie uda³o siê otworzyæ pliku do zapisu.", LINE_INFO());
			fprintf(fpXml, "<root> <Element atrybut=\"Napis\"> <Dziecko id=\"1\"/> <Dziecko id=\"2\"/> <Dziecko id=\"3\"/> <TestBool id=\"true\"/></Element> </root>");
			fclose(fpXml);
			bool ret = dokumentXml_.odczytaj(nazwaPlikuXml_.c_str());
			if (!ret){
				log.loguj(SLog::Log::Error, dokumentXml_.error());
			}
			Assert::IsTrue(ret, L"Nie uda³o siê wczytaæ pliku.", LINE_INFO());

			FILE *fpJson;
			Assert::IsTrue(fopen_s(&fpJson, nazwaPlikuJson_.c_str(), "w+") == 0, L"Nie uda³o siê otworzyæ pliku do zapisu.", LINE_INFO());
			fprintf(fpJson, "{\"test\":\"wartosc\"}");
			fclose(fpJson);

			ret = dokumentJson_.odczytaj(nazwaPlikuJson_.c_str());
			if (!ret){
				log.loguj(SLog::Log::Error, dokumentJson_.error());
			}
			Assert::IsTrue(ret, L"Nie uda³o siê wczytaæ pliku.", LINE_INFO());
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(STD_TEST)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(STD_TEST) {
			std::string sDouble = " 3.14";
			std::string invalidDouble = " n3.14";
			Assert::AreEqual(3.14, std::stod(sDouble));
			size_t index = 0;
			Assert::ExpectException<std::invalid_argument>([&]()->void { std::stod(invalidDouble, &index); });
			log.loguj(SLog::Log::Debug, std::to_string(index));
			Assert::ExpectException<std::invalid_argument>([&]()->void { std::stod("", &index); }); 
			log.loguj(SLog::Log::Debug, std::to_string(index));
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(Parser_XML_Sprawdzanie_Zawartosci)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(Parser_XML_Sprawdzanie_Zawartosci){
			Assert::IsTrue(dokumentXml_.odczytaj(nazwaPlikuXml_.c_str()), L"Nie uda³o siê wczytaæ pliku.", LINE_INFO());
			auto root = dokumentXml_.pobierzElement(nullptr);
			Assert::IsNotNull(root.get(), L"Nie uda³o siê wczytaæ elementu root.", LINE_INFO());
			Assert::IsTrue(root->operator bool(), L"Nie uda³o siê wczytaæ elementu root.", LINE_INFO());

			auto element = root->pobierzElement("Element");
			Assert::IsNotNull(element.get(), L"Nie uda³o siê wczytaæ elementu.", LINE_INFO());
			Assert::IsTrue(element->operator bool(), L"Nie uda³o siê wczytaæ elementu.", LINE_INFO());

			auto atrybut = element->pobierzAtrybut("atrybut");
			Assert::IsNotNull(atrybut.get(), L"Nie uda³o siê wczytaæ atrybutu elementu.", LINE_INFO());
			Assert::IsTrue(atrybut->operator bool(), L"Nie uda³o siê wczytaæ atrybutu elementu.", LINE_INFO());
			Assert::AreEqual("Napis",atrybut->pobierzWartosc(), L"Nie uda³o siê wczytaæ atrybutu elementu.", LINE_INFO());
			int iteracja = 0;
			Assert::IsTrue(XmlBO::ForEach<NOTHROW>(element, "Dziecko", XmlBO::OperacjaWezla([&iteracja](XmlBO::ElementWezla el)->bool{
				if (!el)
					return false;
				++iteracja;
				auto atrybut = el->pobierzAtrybut("id");
				Assert::IsNotNull(atrybut.get(), L"Nie uda³o siê wczytaæ atrybutu elementu Dziecko.", LINE_INFO());
				Assert::IsTrue(atrybut->operator bool(), L"Nie uda³o siê wczytaæ atrybutu elementu Dziecko.", LINE_INFO());
				Assert::AreEqual(iteracja, atrybut->pobierzWartoscInt(), L"Nie uda³o siê wczytaæ atrybutu elementu.", LINE_INFO());
				return true;
			})), L"Nie uda³o siê iterowaæ po elementach Dziecko.", LINE_INFO());
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(Parser_XML_Zapis_do_pliku)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(Parser_XML_Zapis_do_pliku){
			SPar::ParserDokumentXml dokument;
			auto root = dokument.tworzElement("root");
			Assert::IsNotNull(root.get(), L"Nie uda³o siê wczytaæ elementu root.", LINE_INFO());
			Assert::IsTrue(root->operator bool(), L"Nie uda³o siê wczytaæ elementu root.", LINE_INFO());

			auto element = root->tworzElement("Element");
			Assert::IsNotNull(element.get(), L"Nie uda³o siê wczytaæ elementu.", LINE_INFO());
			Assert::IsTrue(element->operator bool(), L"Nie uda³o siê wczytaæ elementu.", LINE_INFO());

			auto atrybut = element->tworzAtrybut("atrybut", "Napis");
			Assert::IsNotNull(atrybut.get(), L"Nie uda³o siê wczytaæ atrybutu elementu.", LINE_INFO());
			Assert::IsTrue(atrybut->operator bool(), L"Nie uda³o siê wczytaæ atrybutu elementu.", LINE_INFO());
			Assert::AreEqual("Napis", atrybut->pobierzWartosc(), L"Nie uda³o siê wczytaæ atrybutu elementu.", LINE_INFO());
			Assert::IsTrue(dokument.zapisz(nazwaPlikuXml_.c_str()), L"Nie uda³o siê zapisaæ pliku.", LINE_INFO());
			log.loguj(SLog::Log::Debug, root->error());
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(Parser_XML_XmlBO)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(Parser_XML_XmlBO){
			Assert::IsTrue(dokumentXml_.odczytaj(nazwaPlikuXml_.c_str()), L"Nie uda³o siê wczytaæ pliku.", LINE_INFO());
			auto root = dokumentXml_.pobierzElement(nullptr);
			Assert::IsNotNull(XmlBO::ZnajdzWezel<NOTHROW>(root, "Element").get());
			Assert::IsNotNull(XmlBO::ZnajdzWezelJezeli<NOTHROW>(root, "Element", "atrybut", "Napis").get());
			Assert::IsNull(XmlBO::ZnajdzWezel<NOTHROW>(root, "Dziecko").get());
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::ZnajdzWezel<THROW>(root, "Dziecko");  });
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::ZnajdzWezel<THROW>(root, ""); });
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::ZnajdzWezel<THROW>(nullptr, "Dziecko"); });
			auto element = XmlBO::ZnajdzWezel<NOTHROW>(root, "Element");
			auto dziecko = XmlBO::ZnajdzWezel<NOTHROW>(element, "Dziecko");
			Assert::IsNotNull(dziecko.get());
			Assert::IsNotNull(XmlBO::ZnajdzWezel<NOTHROW>(element, "Dziecko", dziecko).get());
			Assert::AreEqual(1, XmlBO::WczytajAtrybut<int>(dziecko, "id", 0));
			Assert::IsNotNull(XmlBO::ZnajdzWezelJezeli<NOTHROW>(element, "Dziecko","id","3", dziecko).get());
			Assert::IsNull(XmlBO::ZnajdzWezelJezeli<NOTHROW>(element, "Dziecko", "id", "4", dziecko).get());
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::ZnajdzWezelJezeli<THROW>(element, "Dziecko", "id", "4", dziecko); });
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::ZnajdzWezelJezeli<THROW>(element, "", "id", "4"); });
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::ZnajdzWezelJezeli<THROW>(element, "Dziecko", "", "4"); });
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::ZnajdzWezelJezeli<THROW>(nullptr, "Dziecko", "id", "4"); });
			auto dziecko3 = XmlBO::ZnajdzWezelJezeli<NOTHROW>(element, "Dziecko", "id", "3", dziecko);
			STyp::Identyfikator id;
			Assert::IsTrue(XmlBO::WczytajAtrybut<NOTHROW>(dziecko3, "id", id));
			Assert::AreEqual(3,id());
			STyp::Identyfikator id2;
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::WczytajAtrybut<THROW>(element, "id", id2); });
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::WczytajAtrybut<THROW>(nullptr, "id", id2); });
			Assert::ExpectException<SPar::WyjatekParser>([&]()->void { XmlBO::WczytajAtrybut<THROW>(dziecko3, "", id2); });
			Assert::AreNotEqual(3, id2());
			auto testBool = XmlBO::ZnajdzWezel<NOTHROW>(element, "TestBool");
			Assert::IsNotNull(testBool.get());
			Assert::IsTrue(XmlBO::WczytajAtrybut<bool>(testBool, "id", false));
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(JSON_Test)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(JSON_Test){
			Json::Value value;
			value["Node"] = "value";
			Json::FastWriter writer;
			auto node = writer.write(value);
			log.loguj(SLog::Log::Debug, node);
			Assert::AreEqual(node, std::string("{\"Node\":\"value\"}\n"));
			Assert::AreEqual(value["Node"].asString(), std::string("value"));
			for (auto& val : value.getMemberNames()){
				log.loguj(SLog::Log::Debug, val);
			}
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(JSON_Test_isNULL)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(JSON_Test_isNULL){
			Json::Value value;
			value["Node"] = "value";
			Assert::IsFalse(value["Node"].isNull());
			Assert::IsTrue(value["node"].isNull());
			Assert::IsFalse(!value["Node"]);
			Assert::IsTrue(!value["node"]);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(JSON_Test_iterator)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(JSON_Test_iterator){
			Json::Value value;
			value["Node"] = "value";
			value["Array"] = Json::Value(Json::arrayValue);
			value["Array"][0] = "first";
			value["Array"][1] = "second";
			Json::FastWriter writer;
			auto node = writer.write(value);
			log.loguj(SLog::Log::Debug, node);
			myPrint(value);
		}

		void myPrint(const Json::Value& value){
			for (auto iter = value.begin(); iter != value.end(); ++iter){
				if (iter->isArray() || iter->isObject()){
					std::stringstream ss;
					ss << "Member: " << iter.memberName() << " Key: " << iter.key() << " Index: " << iter.index();
					log.loguj(SLog::Log::Debug, ss.str());
					myPrint(*iter);
				}else{
					std::stringstream ss;
					ss << "Member: " << iter.memberName() << " Key: " << iter.key() << " Index: " << iter.index() << " Value: " << *iter;
					log.loguj(SLog::Log::Debug, ss.str());
				}
			}
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(JSON_Test_DoubleNode)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(JSON_Test_DoubleNode){
			Json::Value value;
			Json::Reader reader;
			Assert::IsTrue(reader.parse("{\"node\":\"value\",\"node\":{\"obj\":\"objval\"}}", value));
			Json::FastWriter writer;
			auto node = writer.write(value);
			log.loguj(SLog::Log::Debug, node);
			myPrint(value);
		}
		//TODO: Dodac test dla metody XmlBO::ForEach iterujacej po atrybutach.
		TEST_METHOD_CLEANUP(Czyszczenie){
			Assert::IsTrue(remove(nazwaPlikuXml_.c_str()) == 0, L"Nie uda³o siê usun¹æ pliku.", LINE_INFO());
			Assert::IsTrue(remove(nazwaPlikuJson_.c_str()) == 0, L"Nie uda³o siê usun¹æ pliku.", LINE_INFO());
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(Parser_JSON_Sprawdzanie_Zawartosci)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(Parser_JSON_Sprawdzanie_Zawartosci){
			auto element = dokumentJson_.pobierzElement("test");
			Assert::IsNotNull(element.get());
			Assert::AreEqual(std::string(element->pobierzTekst()),std::string("wartosc"));
		}
	};

	SLog::Log& ParserTesty::ParserTest::log = SLog::Log::pobierzInstancje();
}