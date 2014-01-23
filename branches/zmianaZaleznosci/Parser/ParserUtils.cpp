#include "XmlBO.h"

#define ZMIANA_NAPIS_KOMUNIKAT_METODY_GENERUJACEJ_BLAD_STRUKTURY "W ni¿ej wyœwietlonym wêŸle wyst¹pi³ b³¹d struktury danych. "

namespace SPar{
	void ParserUtils::generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel)
	{
		throw SPar::WyjatekParser(EXCEPTION_PLACE, std::string(__FUNCTION__), wezel.get(), std::string(ZMIANA_NAPIS_KOMUNIKAT_METODY_GENERUJACEJ_BLAD_STRUKTURY));
	}
}
