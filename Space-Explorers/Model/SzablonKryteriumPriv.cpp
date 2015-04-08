#include "SzablonKryterium.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\Utils.h"

namespace SpEx{
	std::shared_ptr<SZmi::ZmianaInterfejs> SzablonKryteriumPriv::TworzZmiane(XmlBO::ElementWezla wezel){
		return Utils::TworzZmiane(XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_ZMIANA));
	}
}