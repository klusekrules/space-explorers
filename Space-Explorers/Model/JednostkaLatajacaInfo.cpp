#include "JednostkaLatajacaInfo.h"
#include "Logger\Logger.h"
#include "Utils\Utils.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\StackThrow.h"

namespace SpEx{

	JednostkaLatajacaInfo::JednostkaLatajacaInfo(const STyp::Identyfikator& klucz, const STyp::Moc& mocSilnika, const STyp::ZuzyciePaliwa& zuzyciePaliwa, const STyp::Masa& masa)
		: rodzajNapedu_(klucz), mocSilnika_(mocSilnika), zuzyciePaliwa_(zuzyciePaliwa), masaNapedu_(masa),
		przyrostMocySilnika_(nullptr), przyrostSprawnosciSilnika_(nullptr), przyrostZuzyciaPaliwa_(nullptr), przyrostMasyNapedu_(nullptr)
	{
	}

	JednostkaLatajacaInfo::JednostkaLatajacaInfo(XmlBO::ElementWezla wezel)
		: przyrostMocySilnika_(nullptr), przyrostSprawnosciSilnika_(nullptr), przyrostZuzyciaPaliwa_(nullptr), przyrostMasyNapedu_(nullptr)
	{
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_RODZAJ_SILNIKA_ID, rodzajNapedu_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_MOC_SILNIKA, mocSilnika_);
		if (mocSilnika_ < STyp::Moc(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		przyrostMocySilnika_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_MOC_SILNIKA));

		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ZUZYCIE_PALIWA, zuzyciePaliwa_);
		if (zuzyciePaliwa_ < STyp::ZuzyciePaliwa(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		przyrostZuzyciaPaliwa_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_ZUZYCIE_PALIWA));

		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_MASA_SILNIKA, masaNapedu_);
		if (masaNapedu_ < STyp::Masa(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		przyrostMasyNapedu_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_MASA_SILNIKA));

		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_SPRAWNOSC_SILNIKA, sprawnoscSilnika_);
		if (sprawnoscSilnika_ < STyp::Fluktuacja(0))
			Utils::generujWyjatekBleduStruktury(wezel);
		przyrostSprawnosciSilnika_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_SPRAWNOSC_SILNIKA));
	}

	JednostkaLatajacaInfo::JednostkaLatajacaInfo(const JednostkaLatajacaInfo& obiekt)
		: przyrostMocySilnika_(Utils::Kopiuj(obiekt.przyrostMocySilnika_)),
		przyrostSprawnosciSilnika_(Utils::Kopiuj(obiekt.przyrostSprawnosciSilnika_)),
		przyrostZuzyciaPaliwa_(Utils::Kopiuj(obiekt.przyrostZuzyciaPaliwa_)),
		przyrostMasyNapedu_(Utils::Kopiuj(obiekt.przyrostMasyNapedu_)),
		rodzajNapedu_(obiekt.rodzajNapedu_), mocSilnika_(obiekt.mocSilnika_), zuzyciePaliwa_(obiekt.zuzyciePaliwa_), masaNapedu_(obiekt.masaNapedu_)
	{
	}

	const STyp::Identyfikator& JednostkaLatajacaInfo::pobierzRodzajNapedu() const{
		return rodzajNapedu_;
	}

	STyp::Moc JednostkaLatajacaInfo::pobierzMocSilnika(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(przyrostMocySilnika_, mocSilnika_, parametry);
	}

	STyp::ZuzyciePaliwa JednostkaLatajacaInfo::pobierzZuzyciePaliwa(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(przyrostZuzyciaPaliwa_, zuzyciePaliwa_, parametry);
	}

	STyp::Masa JednostkaLatajacaInfo::pobierzMasaNapedu(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(przyrostMasyNapedu_, masaNapedu_, parametry);
	}

	STyp::Fluktuacja JednostkaLatajacaInfo::pobierzSprawnoscSilnika(const PodstawoweParametry& parametry) const{
		return Utils::ObliczZmiane(przyrostSprawnosciSilnika_, sprawnoscSilnika_, parametry);
	}

	std::string JednostkaLatajacaInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(JednostkaLatajacaInfo));
		str.dodajPole(NAZWAPOLA(rodzajNapedu_), rodzajNapedu_);
		str.dodajPole(NAZWAPOLA(mocSilnika_), mocSilnika_);
		if (przyrostMocySilnika_){
			str.dodajPole(NAZWAPOLA(przyrostMocySilnika_), *przyrostMocySilnika_);
		}
		str.dodajPole(NAZWAPOLA(sprawnoscSilnika_), sprawnoscSilnika_);
		if (przyrostSprawnosciSilnika_){
			str.dodajPole(NAZWAPOLA(przyrostSprawnosciSilnika_), *przyrostSprawnosciSilnika_);
		}
		str.dodajPole(NAZWAPOLA(zuzyciePaliwa_), zuzyciePaliwa_);
		if (przyrostZuzyciaPaliwa_){
			str.dodajPole(NAZWAPOLA(przyrostZuzyciaPaliwa_), *przyrostZuzyciaPaliwa_);
		}
		str.dodajPole(NAZWAPOLA(masaNapedu_), masaNapedu_);
		if (przyrostMasyNapedu_){
			str.dodajPole(NAZWAPOLA(przyrostMasyNapedu_), *przyrostMasyNapedu_);
		}
		return str.napis();
	}
}
