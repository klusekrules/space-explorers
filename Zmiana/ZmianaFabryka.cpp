#include "ZmianaFabryka.h"
//#include "..\XmlBO.h"
//#include "..\definicjeWezlowXML.h"

namespace SZmi{
	bool ZmianaFabryka::rejestracjaZmiany(int id, KreatorZmiany funkcja){
		if (funkcja == nullptr || id == 0 || callbacks_.find(id) != callbacks_.end())
			return false;
		callbacks_[id] = funkcja;
		return true;
	}

	ZmianaFabryka& ZmianaFabryka::pobierzInstancje(){
		static ZmianaFabryka instancja;
		return instancja;
	}

	std::shared_ptr<ZmianaInterfejs> ZmianaFabryka::Tworz(SPar::ParserElement& wezel) const {
		if (wezel){
			//TODO: Do uzupelnienia.
			int id = 0; //XmlBO::WczytajAtrybut<int>(wezel, ATRYBUT_XML_IDENTYFIKATOR, 0);
			if (id == 0)
				return nullptr;
			auto iterator = callbacks_.find(id);
			if (iterator == callbacks_.end())
				return nullptr;
			return std::shared_ptr<ZmianaInterfejs>(iterator->second(wezel));
		}
		return nullptr;
	}
}
