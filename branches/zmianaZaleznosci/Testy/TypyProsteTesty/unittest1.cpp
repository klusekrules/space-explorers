#include "stdafx.h"
#include "CppUnitTest.h"
#include "TypyProste\TypyProste.h"

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
		
		TEST_METHOD(KlasaIlosc)
		{
			STyp::Ilosc ilosc(15.0);
			Assert::AreEqual<STyp::Ilosc::nazwa_typu>( 15.0, ilosc(), L"message", LINE_INFO() );
		}

	};
}