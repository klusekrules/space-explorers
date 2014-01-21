#include "ZmianaUtils.h"
#include "Parser\WyjatekParser.h"
#include "ZmianaStaleNapisy.h"

namespace SZmi{
	void ZmianaUtils::generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel)
	{
		throw SPar::WyjatekParser(EXCEPTION_PLACE, std::string(__FUNCTION__), wezel.get(), std::string(ZMIANA_NAPIS_KOMUNIKAT_METODY_GENERUJACEJ_BLAD_STRUKTURY));
	}
}