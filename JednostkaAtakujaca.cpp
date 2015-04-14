#include "JednostkaAtakujaca.h"
#include "Logger\Logger.h"

namespace SpEx{
	JednostkaAtakujaca::JednostkaAtakujaca(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const JednostkaAtakujacaInfo& jInfo)
		: PodstawoweParametry(wpisPoziom(poziom), POZIOM, identyfikatorPlanety), jednostkaAtakujacaInfo_(jInfo)
	{
	}

	JednostkaAtakujaca::JednostkaAtakujaca(const PodstawoweParametry& parametry, const JednostkaAtakujacaInfo& jInfo)
		: PodstawoweParametry(parametry), jednostkaAtakujacaInfo_(jInfo)
	{
	}

	STyp::Obrazenia JednostkaAtakujaca::pobierzAtak() const {
		return jednostkaAtakujacaInfo_.pobierzAtak(*this);
	}

	STyp::Obrazenia JednostkaAtakujaca::pobierzPancerz() const{
		return jednostkaAtakujacaInfo_.pobierzPancerz(*this);
	}

	STyp::Obrazenia JednostkaAtakujaca::pobierzOslone() const{
		return jednostkaAtakujacaInfo_.pobierzOslone(*this);
	}

	std::string JednostkaAtakujaca::napis() const{
		SLog::Logger str(NAZWAKLASY(JednostkaAtakujaca));
		str.dodajPole(NAZWAPOLA(jednostkaAtakujacaInfo_), jednostkaAtakujacaInfo_);
		return str.napis();
	}
}
