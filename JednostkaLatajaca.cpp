
#include "JednostkaLatajaca.h"
#include "Logger\Logger.h"

namespace SpEx{
	JednostkaLatajaca::JednostkaLatajaca(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const JednostkaLatajacaInfo& jInfo)
		: PodstawoweParametry(wpisPoziom(poziom),POZIOM ,identyfikatorPlanety), jednostkaLatajacaInfo_(jInfo)
	{
	}

	JednostkaLatajaca::JednostkaLatajaca(const PodstawoweParametry& p, const JednostkaLatajacaInfo& jInfo)
		: PodstawoweParametry(p), jednostkaLatajacaInfo_(jInfo)
	{
	}

	STyp::ZuzyciePaliwa JednostkaLatajaca::wyliczZuzyciePaliwa(const STyp::Dystans& d, const STyp::Predkosc& p) const{
		return STyp::ZuzyciePaliwa(jednostkaLatajacaInfo_.pobierzZuzyciePaliwa(*this)()* (d() / p()));
	}

	STyp::ZuzyciePaliwa JednostkaLatajaca::pobierzJednostkoweZuzyciePaliwa()const{
		return jednostkaLatajacaInfo_.pobierzZuzyciePaliwa(*this);
	}

	STyp::Moc JednostkaLatajaca::pobierzMocSilnika()const{
		return jednostkaLatajacaInfo_.pobierzMocSilnika(*this);
	}

	STyp::Masa JednostkaLatajaca::pobierzMasaSilnika()const{
		return jednostkaLatajacaInfo_.pobierzMasaNapedu(*this);
	}

	STyp::Fluktuacja JednostkaLatajaca::pobierzSprawnoscSilnika()const{
		return jednostkaLatajacaInfo_.pobierzSprawnoscSilnika(*this);
	}

	STyp::Predkosc JednostkaLatajaca::predkoscMaksymalna() const{
		long double eta_m = jednostkaLatajacaInfo_.pobierzSprawnoscSilnika(*this)();
		long double a = 0.01;
		long double P = jednostkaLatajacaInfo_.pobierzMocSilnika(*this)();
		return STyp::Predkosc((P * eta_m) / (calkowitaMasaJednostki()() * a));
	}

	STyp::Masa JednostkaLatajaca::calkowitaMasaJednostki() const{
		return STyp::Masa();
	}

	std::string JednostkaLatajaca::napis() const{
		SLog::Logger str(NAZWAKLASY(JednostkaLatajaca));
		str.dodajPole(NAZWAPOLA(jednostkaLatajacaInfo_), jednostkaLatajacaInfo_);
		return str.napis();
	}
}