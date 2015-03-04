#include "HangarInfo.h"
#include "Logger\Logger.h"
#include "Statek.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include "StackThrow.h"

namespace SpEx{
	HangarInfo::HangarInfo(const STyp::Powierzchnia& maksymalnaObjetosc) throw()
		: pojemnoscMaksymalna_(maksymalnaObjetosc), przyrostPojemnosciMaksymalnej_(nullptr)
	{
	}

	HangarInfo::HangarInfo(const HangarInfo& obiekt)
		: pojemnoscMaksymalna_(obiekt.pojemnoscMaksymalna_), przyrostPojemnosciMaksymalnej_(Utils::Kopiuj(obiekt.przyrostPojemnosciMaksymalnej_))
	{
	}

	HangarInfo::HangarInfo(XmlBO::ElementWezla wezel)
		: przyrostPojemnosciMaksymalnej_(nullptr)
	{
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POJEMNOSC_MAKSYMALNA, pojemnoscMaksymalna_);
		if (pojemnoscMaksymalna_ < STyp::Powierzchnia(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		przyrostPojemnosciMaksymalnej_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_POJEMNOSC_MAKSYMALNA));
	}
	
	STyp::Powierzchnia HangarInfo::pobierzMaksymalnaIloscPrzewozonychStatkow(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(przyrostPojemnosciMaksymalnej_, pojemnoscMaksymalna_, parametry);
	}

	std::string HangarInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(HangarInfo));
		str.dodajPole(NAZWAPOLA(pojemnoscMaksymalna_), pojemnoscMaksymalna_);
		if (przyrostPojemnosciMaksymalnej_)
			str.dodajPole(NAZWAPOLA(przyrostPojemnosciMaksymalnej_), *przyrostPojemnosciMaksymalnej_);
		return str.napis();
	}
}