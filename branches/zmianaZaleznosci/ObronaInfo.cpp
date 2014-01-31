#include "ObronaInfo.h"
#include "Logger\Logger.h"
#include "Gra.h"

namespace SpEx{
	ObronaInfo::ObronaInfo(const ObiektInfo& obiektInfo, const JednostkaAtakujacaInfo& jednostkaAtakujacaInfo)
		: ObiektInfo(obiektInfo), JednostkaAtakujacaInfo(jednostkaAtakujacaInfo)
	{
	}
	
	ObronaInfo::ObronaInfo(XmlBO::ElementWezla wezel) throw(WyjatekParseraXML)
		: ObiektInfo(wezel),
		JednostkaAtakujacaInfo(XmlBO::ZnajdzWezel<THROW>(wezel, WEZEL_XML_JEDNOSTKA_ATAKUJACA_INFO))
	{
	}
	
	Obrona* ObronaInfo::tworzEgzemplarz(const PodstawoweParametry& parametry) const{
		return new Obrona(parametry, *this);
	}

	bool ObronaInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const{
		return false;//TODO: dokoñczyæ metodê. gra.wybudujNaPlanecie(planeta, *this, ilosc, poziom);
	}

	std::string ObronaInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(ObronaInfo));
		str.dodajKlase(ObiektInfo::napis());
		str.dodajKlase(JednostkaAtakujacaInfo::napis());
		return str.napis();
	}
}