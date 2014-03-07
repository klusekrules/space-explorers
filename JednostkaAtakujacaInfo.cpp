#include "JednostkaAtakujacaInfo.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"

namespace SpEx{

	JednostkaAtakujacaInfo::JednostkaAtakujacaInfo( const STyp::Obrazenia& oAtak, const STyp::Obrazenia& oPancerz, const STyp::Obrazenia& oOslona) throw()
		: atak_(oAtak), zmianaAtaku_(nullptr), pancerz_(oPancerz), zmianaPancerza_(nullptr), oslona_(oOslona), zmianaOslony_(nullptr)
	{
	}

	JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(XmlBO::ElementWezla wezel)
		: zmianaAtaku_(nullptr), zmianaPancerza_(nullptr), zmianaOslony_(nullptr)
	{
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ATAK, atak_);
		if (atak_ < STyp::Obrazenia(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		zmianaAtaku_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<STACKTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_ATAK));

		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_PANCERZ, pancerz_);
		if (pancerz_ < STyp::Obrazenia(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		zmianaPancerza_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<STACKTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_PANCERZ));

		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_OSLONA, oslona_);
		if (oslona_ < STyp::Obrazenia(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		zmianaOslony_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<STACKTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_OSLONA));
	}

	JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(const JednostkaAtakujacaInfo& obiekt)
		: atak_(obiekt.atak_), pancerz_(obiekt.pancerz_), oslona_(obiekt.oslona_),
		zmianaAtaku_(Utils::Kopiuj(obiekt.zmianaAtaku_)),
		zmianaPancerza_(Utils::Kopiuj(obiekt.zmianaPancerza_)),
		zmianaOslony_(Utils::Kopiuj(obiekt.zmianaOslony_))
	{
	}

	STyp::Obrazenia JednostkaAtakujacaInfo::pobierzAtak(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(zmianaAtaku_, atak_, parametry);
	}

	STyp::Obrazenia JednostkaAtakujacaInfo::pobierzPancerz(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(zmianaPancerza_, pancerz_, parametry);
	}

	STyp::Obrazenia JednostkaAtakujacaInfo::pobierzOslone(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(zmianaOslony_, oslona_, parametry);
	}

	std::string JednostkaAtakujacaInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(JednostkaAtakujacaInfo));
		str.dodajPole(NAZWAPOLA(atak_), atak_);
		str.dodajPole(NAZWAPOLA(pancerz_), pancerz_);
		str.dodajPole(NAZWAPOLA(oslona_), oslona_);
		if (zmianaAtaku_)
			str.dodajPole(NAZWAPOLA(zmianaAtaku_), *zmianaAtaku_);
		if (zmianaPancerza_)
			str.dodajPole(NAZWAPOLA(zmianaPancerza_), *zmianaPancerza_);
		if (zmianaOslony_)
			str.dodajPole(NAZWAPOLA(zmianaOslony_), *zmianaOslony_);
		return str.napis();
	}
}
