#include "Fabrykator.h"
#include "LuaSkrypt.h"
#include "DllSkrypt.h"

namespace SpEx{
	Fabrykator::Fabrykator(){
		LuaSkrypt::Rejestruj(fabrykaSkryptow_);
		DllSkrypt::Rejestruj(fabrykaSkryptow_);
	}

	std::shared_ptr<Skrypt> Fabrykator::TworzSkrypt(XmlBO::ElementWezla wezel) const{
		return fabrykaSkryptow_.Tworz(wezel);
	}

	std::shared_ptr<Skrypt> Fabrykator::TworzSkrypt(const FabrykaSkryptow::Identyfikator& identyfikator, XmlBO::ElementWezla wezel) const{
		return fabrykaSkryptow_.Tworz(identyfikator, wezel);
	}

	std::shared_ptr<SZmi::ZmianaInterfejs> Fabrykator::TworzZmiane(XmlBO::ElementWezla wezel) const{
		return fabrykaZmian_.Tworz(wezel);
	}

	SZmi::ZmianaFabryka& Fabrykator::pobierzFabrykeZmian(){
		return fabrykaZmian_;
	}
};