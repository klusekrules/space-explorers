#include "UstawieniaAplikacji.h"
#include "Parser\ParserDokumentXml.h"
#include "Aplikacja.h"
#include "Utils.h"

namespace SpEx{
	bool UstawieniaAplikacji::zaladuj(const std::string& plik){
		SPar::ParserDokumentXml dokument;
		if (!dokument.odczytaj(plik.c_str()))
			return false;
		auto root_data = dokument.pobierzElement("SpaceGame");
		if (root_data){
			if (!ustawJezykAplikacji(XmlBO::ZnajdzWezel<NOTHROW>(root_data, "locale")))
				return false;
			if (!ustawPlikDanych(XmlBO::ZnajdzWezel<THROW>(root_data, "data")))
				return false;
			if (!ustawFolderPlugin(XmlBO::ZnajdzWezel<NOTHROW>(root_data, "plugins")))
				return false;

			return true;
		}
		return false;
	}

	bool UstawieniaAplikacji::ustawJezykAplikacji(XmlBO::ElementWezla wezel){
		if (wezel){
			jezykAplikacji_ = wezel->pobierzTekst();
		}

		if (jezykAplikacji_.empty()){
			jezykAplikacji_ = "Polish";
		}
		return true;
	}

	const std::string& UstawieniaAplikacji::pobierzJezykAplikacji() const{
		return jezykAplikacji_;
	}

	bool UstawieniaAplikacji::ustawPlikDanych(XmlBO::ElementWezla wezel){
		if (wezel){
			auto temp = wezel->pobierzTekst();
			if (!temp){
				Utils::generujWyjatekBleduStruktury(wezel);
			}
			plikDanych_ = temp;
			if (plikDanych_.empty()){
				Utils::generujWyjatekBleduStruktury(wezel);
			}
			return true;
		}
		return false;
	}

	const std::string& UstawieniaAplikacji::pobierzPlikDanych() const{
		return plikDanych_;
	}
	
	bool UstawieniaAplikacji::ustawFolderPlugin(XmlBO::ElementWezla wezel){
		if (wezel){
			folderPlugin_ = wezel->pobierzTekst();
		}

		if (folderPlugin_.empty()){
			folderPlugin_ = "plugins\\";
		}
		return true;
	}
	
	const std::string& UstawieniaAplikacji::pobierzFolderPlugin() const{
		return folderPlugin_;
	}
};
