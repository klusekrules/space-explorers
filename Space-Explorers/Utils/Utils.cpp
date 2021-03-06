#include "Utils.h"
#include <direct.h>
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Zarzadca\Fabrykator.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Model\GeneratorUkladow.h"
#include "Narzedzia\Stale.h"
#include "Eksport\IProxyBO.h"

namespace SpEx{

	const STyp::Fluktuacja Utils::FMAX = 1.0;
	const STyp::Fluktuacja Utils::FMIN = 0.0;

	void Utils::generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel){
		SPar::ParserUtils::generujWyjatekBleduStruktury(wezel,pobierzDebugInfo());
	}

	std::string Utils::pobierzDebugInfo(){
		return std::move(Aplikacja::pobierzInstancje().pobierzDebugInfo());
	}

	__int64 Utils::pobierzLiczbeLosowa(){
		return Aplikacja::pobierzInstancje().pobierzNumerLosowy();
	}
	
	std::shared_ptr<SZmi::ZmianaInterfejs> Utils::TworzZmiane(XmlBO::ElementWezla wezel){
		if (!wezel)
			return nullptr;
		auto zmiana = Aplikacja::pobierzInstancje().pobierzFabrykator().tworzZmiane(wezel);
		if (!zmiana)
			Utils::generujWyjatekBleduStruktury(wezel);
		return zmiana;
	}

	std::string Utils::konwersja(const STyp::Czas& czas){
		auto sekundy = static_cast <__int64>(round(czas()));
		char temp[64];
		sprintf_s(temp, 64, "%02lli:%02lli:%02lli", sekundy / 3600, (sekundy % 3600) / 60, (sekundy % 3600) % 60);
		return temp;
	}
	
	bool Utils::pobierzRozszezenie(const std::string & adres, std::string& rozszezenie){
		auto pos = adres.find_last_of('.');
		if (pos == std::string::npos)
			return false;
		auto end = adres.substr(pos+1);
		if (end.empty())
			return false;
		rozszezenie = std::move(end);
		return true;
	}

	std::vector < SLog::Log::TypLogow > Utils::dekodujListeTypowLogow(const std::string& str){
		std::vector < SLog::Log::TypLogow > ret;
		if (str.empty())
			return ret;
		size_t pos = 0;
		size_t start = 0;
		std::string sub;
		while (pos != std::string::npos){
			pos = str.find_first_of(',', pos);
			if (pos == std::string::npos){
				sub = std::move(str.substr(start));
			}
			else{
				sub = std::move(str.substr(start, pos - start));
				start = ++pos;
			}
			if (sub.empty())
				break;
			int i = stoi(sub);
			switch (i)
			{
			case SLog::Log::All: ret.emplace_back(SLog::Log::All);
				break;
			case SLog::Log::Debug: ret.emplace_back(SLog::Log::Debug);
				break;
			case SLog::Log::Info: ret.emplace_back(SLog::Log::Info);
				break;
			case SLog::Log::Warning: ret.emplace_back(SLog::Log::Warning);
				break;
			case SLog::Log::Error: ret.emplace_back(SLog::Log::Error);
				break;
			}
		}
		return ret;
	}

	bool Utils::tworzSciezke(const std::string& path){
		std::string::size_type pos = 0;
		do{
			// Pomijianie backslash i slash
			for (; pos < path.size() && (path[pos] == '\\' || path[pos] == '/'); ++pos);

			// Pobieranie kolejnego stopnia �cie�ki
			pos = path.find_first_of("\\/", pos);
			if (pos == std::string::npos)
				return true;
			std::string folder = path.substr(0, pos);

			// Tworzenie �cie�ki
			if (_mkdir(folder.c_str()) && errno != EEXIST){
				return false;
			}
		} while (pos != std::string::npos);
		return true;
	}

	void Utils::generujSzablonPlikuGry(std::shared_ptr<SPar::ParserDokument>& ptr){
		auto generator = ptr->tworzElement(WEZEL_XML_ROOT)->tworzElement(WEZEL_XML_GRA)->tworzElement(WEZEL_XML_ZARZADCA)->tworzElement(WEZEL_XML_GENERATOR_UKLADOW);
		
		auto licznik_planeta = generator->tworzElement(WEZEL_XML_LICZNIK);
		licznik_planeta->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR,"")->ustawWartoscLongLong(GeneratorUkladow::LICZNIK_PLANET_ID());
		licznik_planeta->tworzAtrybut(ATRYBUT_XML_ILOSC, "0");		

		auto licznik_uklad = generator->tworzElement(WEZEL_XML_LICZNIK);
		licznik_uklad->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, "")->ustawWartoscLongLong(GeneratorUkladow::LICZNIK_UKLADOW_ID());
		licznik_uklad->tworzAtrybut(ATRYBUT_XML_ILOSC, "0");

		auto licznik_galaktyka = generator->tworzElement(WEZEL_XML_LICZNIK);
		licznik_galaktyka->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, "")->ustawWartoscLongLong(GeneratorUkladow::LICZNIK_GALAKTYK_ID());
		licznik_galaktyka->tworzAtrybut(ATRYBUT_XML_ILOSC, "0");
	}

	std::string Utils::adresPliku(const std::string & identyfikator){
		if (identyfikator == ATRYBUT_PLIK_DANYCH) {
			std::string adres;
			std::string plikDanych;
			std::string glownyFolder = Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()[ATRYBUT_GLOWNY_FOLDER_GRY];
			if (!glownyFolder.empty())
				adres += glownyFolder + "\\";

			plikDanych = Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()[ATRYBUT_PLIK_DANYCH];
			if (plikDanych.empty()) {
				if (Aplikacja::pobierzInstancje().proxy_->pobierzTrybAplikacji() == TrybAplikacji::Serwer) {
					return std::string();
				} else {
					plikDanych = "daneGry.xml";
				}
			}

			adres += plikDanych;
			return std::move(adres);
		}
		return std::string();
	}
}
