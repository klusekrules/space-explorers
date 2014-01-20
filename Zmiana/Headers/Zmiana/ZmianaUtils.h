#pragma once
#include "ZmianaSymbol.h"
#include "Parser\XmlBO.h"
namespace SZmi{
	class ZMIANA_API ZmianaUtils
	{
	public:
		static void generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel);
	};
}
