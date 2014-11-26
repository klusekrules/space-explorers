#include "ZmianaFabryka.h"
#include "ZmianaStaleXml.h"
#include "Logger\Logger.h"

namespace SZmi{
	bool ZmianaFabryka::rejestracjaZmiany(const STyp::Identyfikator& id, KreatorZmiany funkcja){
		if (funkcja == nullptr || id == 0 || callbacks_.find(id) != callbacks_.end())
			return false;
		callbacks_[id] = funkcja;
		return true;
	}
	
	std::shared_ptr<ZmianaInterfejs> ZmianaFabryka::Tworz(XmlBO::ElementWezla wezel) const {
		if (wezel){
			STyp::Identyfikator id;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, XML_ATRYBUT_ZMIANA_ID, id))
				return nullptr;
			auto iterator = callbacks_.find(id());
			if (iterator == callbacks_.end())
				return nullptr;
			return std::shared_ptr<ZmianaInterfejs>(iterator->second(wezel));
		}
		return nullptr;
	}

	std::string ZmianaFabryka::napis() const {
		SLog::Logger logger(NAZWAKLASY(ZmianaFabryka));
		logger.rozpocznijPodKlase(NAZWAPOLA(callbacks_),"SZmi::ZmianaFabryka::Callbacks");
		for (auto& element : callbacks_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			std::stringstream streamKreator;
			streamKreator.imbue(std::locale("C"));
			streamKreator << "0x" << std::hex << (unsigned int)(element.second);
			logger.dodajPole("second", "SpEx::ZmianaFabryka::KreatorZmiany", streamKreator.str());
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();
		return logger.napis();
	}
}
