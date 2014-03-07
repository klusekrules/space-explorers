#include "LadowniaInfo.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "TypyProste\TypyProsteBO.h"

namespace SpEx{
	LadowniaInfo::LadowniaInfo(const STyp::Objetosc& maksymalnaObjetosc)
		: pojemnoscMaksymalna_(maksymalnaObjetosc), przyrostPojemnosciMaksymalnej_(nullptr)
	{
	}

	LadowniaInfo::LadowniaInfo(const LadowniaInfo& obiekt)
		: pojemnoscMaksymalna_(obiekt.pojemnoscMaksymalna_), przyrostPojemnosciMaksymalnej_(Utils::Kopiuj(obiekt.przyrostPojemnosciMaksymalnej_))
	{
	}

	LadowniaInfo::LadowniaInfo(XmlBO::ElementWezla wezel)
		: przyrostPojemnosciMaksymalnej_(nullptr)
	{
		XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_POJEMNOSC_MAKSYMALNA, pojemnoscMaksymalna_);
		if (pojemnoscMaksymalna_ < STyp::Objetosc(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		przyrostPojemnosciMaksymalnej_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<THROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_POJEMNOSC_MAKSYMALNA));
	}

	STyp::Objetosc LadowniaInfo::pobierzPojemnoscMaksymalna(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(przyrostPojemnosciMaksymalnej_, pojemnoscMaksymalna_, parametry);
	}

	std::string LadowniaInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(LadowniaInfo));
		str.dodajPole(NAZWAPOLA(pojemnoscMaksymalna_), pojemnoscMaksymalna_);
		if (przyrostPojemnosciMaksymalnej_)
			str.dodajPole(NAZWAPOLA(przyrostPojemnosciMaksymalnej_), *przyrostPojemnosciMaksymalnej_);
		return str.napis();
	}
}
