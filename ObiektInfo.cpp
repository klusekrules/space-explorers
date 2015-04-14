#include "ObiektInfo.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{

	ObiektInfo::ObiektInfo(const STyp::Identyfikator& typ, PodstawoweParametry::TypAtrybutu typAtrybutu, XmlBO::ElementWezla wezel)
		: Info(typ, wezel), Wymagania(wezel), typAtrybutu_(typAtrybutu)
	{
	}

	PodstawoweParametry::TypAtrybutu ObiektInfo::pobierzTypAtrybutu()const{
		return typAtrybutu_;
	}

	std::string ObiektInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(ObiektInfo));
		str.dodajKlase(Info::napis());
		str.dodajKlase(Wymagania::napis());
		return str.napis();
	}
}
