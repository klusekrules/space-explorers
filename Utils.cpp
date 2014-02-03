#include "Utils.h"
#include "Aplikacja.h"
#include "WyjatekParseraXML.h"
#include "keccak.h"
namespace SpEx{

	std::shared_ptr<SZmi::ZmianaInterfejs> Utils::TworzZmiane(XmlBO::ElementWezla wezel){
		if (!wezel)
			return nullptr;
		auto zmiana = Aplikacja::pobierzInstancje().pobierzGre().pobierzFabrykeZmian().Tworz(wezel);
		if (!zmiana)
			SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
		return zmiana;
	}

	/*void Utils::generujWyjatekBleduStruktury(const Tekst& plik, const Ilosc& linia, tinyxml2::XMLElement* wezel)
	{
		std::string komunikat("B³¹d struktry pliku xml. Niepoprawny wêze³: ");
		tinyxml2::XMLPrinter printer;
		wezel->Accept(&printer);
		komunikat.append(printer.CStr());
		throw WyjatekParseraXML(plik, linia, exception(komunikat.c_str()), Tekst("B³¹d struktry pliku xml."));
	}*/

	void Utils::ascii2hex(std::string& str, unsigned char c){
		char pierwszy = (c >> 4) & 0x0F, drugi = c & 0x0F;
		if (pierwszy < 10){
			pierwszy += 0x30;
		}
		else{
			pierwszy += 55;
		}

		if (drugi < 10){
			drugi += 0x30;
		}
		else{
			drugi += 55;
		}
		str.push_back(pierwszy);
		str.push_back(drugi);
	}

	void Utils::sha3(std::string& str){
		uint8_t md[64];
		memset(md, 0, 64);
		keccak(reinterpret_cast<const uint8_t*>(str.c_str()), static_cast<int>(str.size()), md, 64);
		str.clear();
		str.reserve(128);
		for (int a = 0; a < 64; ++a){
			Utils::ascii2hex(str, md[a]);
		}
	}
}