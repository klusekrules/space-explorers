#include "ZmianaFabryka.h"

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

	std::shared_ptr<ZmianaInterfejs> ZmianaFabryka::Tworz(XmlBO::ElementWezla wezel) const {
		if (wezel){
			int id = XmlBO::WczytajAtrybut<int>(wezel, "id", 0); //TODO: U¿yæ sta³ej.
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
