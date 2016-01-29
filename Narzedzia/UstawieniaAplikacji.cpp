#include "UstawieniaAplikacji.h"
#include "Parser\ParserDokumentXml.h"
#include "Parser\XmlBO.h"
#include "Logger\Logger.h"

#define XML_WEZEL_GLOWNY "Space-Explorers"
#define XML_WEZEL_OPCJA "opcja"

#define XML_OPCJA_ATRYBUT_NAZWA "nazwa"
#define XML_OPCJA_ATRYBUT_WARTOSC "wartosc"

#define USTAWIENIA_DOMYSLNE_JEZYK_APLIKACJI "Polish"

namespace SpEx{

	bool UstawieniaAplikacji::zaladuj(const std::string& plik){
		SPar::ParserDokumentXml dokument;
		if (!dokument.odczytaj(plik.c_str()))
			return false;
		auto root_data = dokument.pobierzElement(XML_WEZEL_GLOWNY);
		if (root_data){
			return XmlBO::ForEach<THROW>(root_data, XML_WEZEL_OPCJA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla wezel)->bool {
				auto nazwa = XmlBO::WczytajAtrybut(wezel, XML_OPCJA_ATRYBUT_NAZWA, std::string());
				auto wartosc = XmlBO::WczytajAtrybut(wezel, XML_OPCJA_ATRYBUT_WARTOSC, std::string());
				if (nazwa.empty())
					return false;
				opcje_[nazwa] = wartosc;
				return true;
			}));
		}
		return false;
	}

	const std::string& UstawieniaAplikacji::operator[](const std::string& nazwa) const{
		return opcje_[nazwa];
	}

	std::string& UstawieniaAplikacji::operator[](const std::string& nazwa){
		return opcje_[nazwa];
	}

	std::string UstawieniaAplikacji::napis() const{
		SLog::Logger str(NAZWAKLASY(UstawieniaAplikacji));
		str.rozpocznijPodKlase(NAZWAPOLA(opcje_), "std::map<std::string, std::string>");
		for (auto& element : opcje_){
			str.rozpocznijPodKlase("Para");
			str.dodajPole("first", "std::string", element.first);
			str.dodajPole("second", "std::string", element.second);
			str.zakonczPodKlase();
		}
		str.zakonczPodKlase();
		return str.napis();
	}
};
