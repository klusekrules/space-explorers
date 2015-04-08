#include "StackThrow.h"
#include "Kontroler\Aplikacja.h"
#include "Utils.h"

namespace SpEx{

	XmlBO::ElementWezla STACKTHROW::bladWezla(XmlBO::ElementWezla element, const std::string& nazwaWezla){
		return THROW::bladWezla(element, nazwaWezla, Aplikacja::pobierzInstancje().pobierzSladStosu(), Utils::pobierzDebugInfo());
	}

	bool STACKTHROW::bladAtrybutu(XmlBO::ElementWezla element, const std::string& nazwaAtrybutu){
		return THROW::bladAtrybutu(element, nazwaAtrybutu, Aplikacja::pobierzInstancje().pobierzSladStosu(), Utils::pobierzDebugInfo());
	}

}
