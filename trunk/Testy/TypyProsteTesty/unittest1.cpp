#include "stdafx.h"
#include "CppUnitTest.h"
#include "TypyProste\TypyProste.h"
#include "TypyProste\Wyjatek.h"

namespace Microsoft{
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<long double>(long double* t)                      { RETURN_WIDE_STRING(t); }
			template<> static std::wstring ToString<long double>(const long double* t)                { RETURN_WIDE_STRING(t); }
			template<> static std::wstring ToString<long double>(const long double& t)                { RETURN_WIDE_STRING(t); }
		}
	}
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TypyProsteTesty
{		
	TEST_CLASS(TypyProsteTest)
	{
	public:
		
		TEST_METHOD(KlasaIloscKonstruowanie)
		{
			STyp::Ilosc::nazwa_typu wartoscA = 15.0;
			STyp::Ilosc ilosc(wartoscA);
			STyp::Ilosc liczba(ilosc);

			Assert::AreEqual<STyp::Ilosc::nazwa_typu>(wartoscA, ilosc(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			Assert::AreEqual<STyp::Ilosc::nazwa_typu>(wartoscA, liczba(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			STyp::Ilosc varA(std::move(ilosc));
			Assert::AreEqual<STyp::Ilosc::nazwa_typu>(wartoscA, varA(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			Assert::AreEqual<STyp::Ilosc::nazwa_typu>(wartoscA, ilosc(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			STyp::Ilosc varB;
			Assert::AreNotEqual<STyp::Ilosc::nazwa_typu>(wartoscA, varB(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			varB = varA;
			Assert::AreEqual<STyp::Ilosc::nazwa_typu>(wartoscA, varA(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			Assert::AreEqual<STyp::Ilosc::nazwa_typu>(wartoscA, varB(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			STyp::Ilosc varC;
			Assert::AreNotEqual<STyp::Ilosc::nazwa_typu>(wartoscA, varC(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			varC = std::move(varB);
			Assert::AreEqual<STyp::Ilosc::nazwa_typu>(wartoscA, varB(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
			Assert::AreEqual<STyp::Ilosc::nazwa_typu>(wartoscA, varC(), L"Nie poprawne dzia³anie klasy STyp::Ilosc.", LINE_INFO());
		}

		TEST_METHOD(KlasaTekstKonstruowanie)
		{
			STyp::Tekst::nazwa_typu wartoscA("Wynik");
			STyp::Tekst varA(wartoscA);
			STyp::Tekst varB(varA);

			Assert::AreEqual<STyp::Tekst::nazwa_typu>(wartoscA, varA(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			Assert::AreEqual<STyp::Tekst::nazwa_typu>(wartoscA, varB(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			STyp::Tekst varC(std::move(varA));
			Assert::AreNotEqual<STyp::Tekst::nazwa_typu>(wartoscA, varA(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			Assert::AreEqual<STyp::Tekst::nazwa_typu>(wartoscA, varC(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			STyp::Tekst varD;
			Assert::AreNotEqual<STyp::Tekst::nazwa_typu>(wartoscA, varD(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			varD = varB;
			Assert::AreEqual<STyp::Tekst::nazwa_typu>(wartoscA, varD(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			Assert::AreEqual<STyp::Tekst::nazwa_typu>(wartoscA, varB(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			STyp::Tekst varE;
			Assert::AreNotEqual<STyp::Tekst::nazwa_typu>(wartoscA, varE(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			varE = std::move(varB);
			Assert::AreEqual<STyp::Tekst::nazwa_typu>(wartoscA, varB(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			Assert::AreEqual<STyp::Tekst::nazwa_typu>(wartoscA, varE(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
		}

		TEST_METHOD(KlasaTekstPobieranieWartosci)
		{
			STyp::Tekst napis("Wynik");
			Assert::AreEqual<STyp::Tekst::nazwa_typu>("Wynik", napis(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
			//Assert::AreEqual<STyp::Tekst::nazwa_typu>("\"Wynik\"", napis.napis(), L"Nie poprawne dzia³anie klasy STyp::Tekst.", LINE_INFO());
		}

		TEST_METHOD(KlasaWyjatek)
		{
			STyp::Wyjatek wyjatek(EXCEPTION_PLACE, STyp::Tekst(__FUNCTION__));
			
			Assert::IsNotNull(wyjatek.what(), L"Nie poprawne dzia³anie klasy STyp::Wyjatek.", LINE_INFO());
			//Assert::AreEqual(wyjatek.generujKomunikat()().c_str(), wyjatek.what(), L"Nie poprawne dzia³anie klasy STyp::Wyjatek.", LINE_INFO());
		}

	};
}