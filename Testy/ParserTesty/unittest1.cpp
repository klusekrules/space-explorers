#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser\XmlBO.h"
#include "Parser\ParserDokumentXml.h"
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
		std::string nazwaPliku_ = "plik.xml";
		static SLog::Log& log;
		SPar::ParserDokumentXml dokument_;

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
			FILE *fp;
			Assert::IsTrue(fopen_s(&fp, nazwaPliku_.c_str(), "w+")==0, L"Nie uda³o siê otworzyæ pliku do zapisu.", LINE_INFO());
			fprintf(fp, "<root> <Element atrybut=\"Napis\"> <Dziecko id=\"1\"/> <Dziecko id=\"2\"/> <Dziecko id=\"3\"/> </Element> </root>");
			fclose(fp);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(WczytywaniePliku)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(1)
			TEST_MY_TRAIT(L"thisTraitValue")
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(WczytywaniePliku){
			bool ret = dokument_.odczytaj(nazwaPliku_.c_str());
			if (!ret){
				log.loguj(SLog::Log::Error, dokument_.error());
			}
			Assert::IsTrue(ret, L"Nie uda³o siê wczytaæ pliku.", LINE_INFO());
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(SprawdzanieZawartosciPliku)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(SprawdzanieZawartosciPliku){
			Assert::IsTrue(dokument_.odczytaj(nazwaPliku_.c_str()), L"Nie uda³o siê wczytaæ pliku.", LINE_INFO());
			auto root = dokument_.pobierzElement(nullptr);
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

		BEGIN_TEST_METHOD_ATTRIBUTE(ZapisDoPliku)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(ZapisDoPliku){
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
			Assert::IsTrue(dokument.zapisz(nazwaPliku_.c_str()), L"Nie uda³o siê zapisaæ pliku.", LINE_INFO());
			log.loguj(SLog::Log::Debug, root->error());
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(XmlBOTest)
			TEST_OWNER(L"Parser")
			TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(XmlBOTest){
			Assert::IsTrue(dokument_.odczytaj(nazwaPliku_.c_str()), L"Nie uda³o siê wczytaæ pliku.", LINE_INFO());
			auto root = dokument_.pobierzElement(nullptr);
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
		}

		//TODO: Dodac test dla metody XmlBO::ForEach iterujacej po atrybutach.
		TEST_METHOD_CLEANUP(Czyszczenie){
			Assert::IsTrue(remove(nazwaPliku_.c_str())==0, L"Nie uda³o siê usun¹æ pliku.", LINE_INFO());
		}
	};

	SLog::Log& ParserTesty::ParserTest::log = SLog::Log::pobierzInstancje();
}