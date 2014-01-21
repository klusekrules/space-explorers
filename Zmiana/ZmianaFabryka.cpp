#include "ZmianaFabryka.h"
#include "ZmianaStaleXml.h"

namespace SZmi{
	bool ZmianaFabryka::rejestracjaZmiany(const STyp::Identyfikator& id, KreatorZmiany funkcja){
		if (funkcja == nullptr || id == 0 || callbacks_.find(id) != callbacks_.end())
			return false;
		callbacks_[id] = funkcja;
		return true;
	}

	ZmianaFabryka& ZmianaFabryka::pobierzInstancje(){
		static ZmianaFabryka instancja;
		return instancja;
	}

	std::shared_ptr<ZmianaInterfejs> ZmianaFabryka::Tworz(XmlBO::ElementWezla wezel) const {
		if (wezel){
			STyp::Identyfikator id;
			if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, XML_ATRYBUT_ZMIANA_ID, id))
				return nullptr;
			auto iterator = callbacks_.find(id());
			if (iterator == callbacks_.end())
				return nullptr;
			return std::shared_ptr<ZmianaInterfejs>(iterator->second(wezel));
		}
		return nullptr;
	}
}
