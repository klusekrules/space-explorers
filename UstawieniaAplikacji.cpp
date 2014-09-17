#include "UstawieniaAplikacji.h"
#include "Parser\ParserDokumentXml.h"
#include "Aplikacja.h"
#include "Utils.h"

namespace SpEx{
	bool UstawieniaAplikacji::zaladuj(const std::string& plik){
		SPar::ParserDokumentXml dokument;
		if (!dokument.odczytaj(plik.c_str()))
			return false;
		auto root_data = dokument.pobierzElement(XML_WEZEL_GLOWNY);
		if (root_data){
			if (!ustawJezykAplikacji(XmlBO::ZnajdzWezel<NOTHROW>(root_data, XML_WEZEL_JEZYK_APLIKACJI)))
				return false;
			if (!ustawPlikDanych(XmlBO::ZnajdzWezel<THROW>(root_data, XML_WEZEL_PLIK_DANYCH)))
				return false;
			if (!ustawFolderPlugin(XmlBO::ZnajdzWezel<NOTHROW>(root_data, XML_WEZEL_FOLDER_PLUGIN)))
				return false;
			if (!ustawPlikPowiazanZasobow(XmlBO::ZnajdzWezel<NOTHROW>(root_data, XML_WEZEL_POWIAZANIA_ZASOBOW)))
				return false;

			auto logi = XmlBO::ZnajdzWezel<THROW>(root_data, XML_WEZEL_USTAWIENIA_LOGOW);

			if (!ustawFormatDatyLogow(logi))
				return false;
			if (!ustawFormatDatyPlikuLogow(logi))
				return false;
			if (!ustawPrzedrostekPlikuLogow(logi))
				return false;
			if (!ustawZablokowaneLogi(logi))
				return false;
			if (!ustawOdblokowaneLogi(logi))
				return false;

			auto zarzadca = XmlBO::ZnajdzWezel<THROW>(root_data, XML_WEZEL_ZARZADCA_PAMIECI);

			if (!ustawAdresPlikuGry(zarzadca))
				return false;
			if (!ustawAdresPlikuOkien(zarzadca))
				return false;
			if (!ustawAdresPlikuStanow(zarzadca))
				return false;
			if (!ustawFolderPlikuUzytkownika(zarzadca))
				return false;
			if (!ustawFolderPlikuUkladu(zarzadca))
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
			jezykAplikacji_ = USTAWIENIA_DOMYSLNE_JEZYK_APLIKACJI;
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
				SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
			}
			plikDanych_ = temp;
			if (plikDanych_.empty()){
				SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
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
		return !folderPlugin_.empty();
	}

	const std::string& UstawieniaAplikacji::pobierzFolderPlugin() const{
		return folderPlugin_;
	}

	bool UstawieniaAplikacji::ustawFormatDatyLogow(XmlBO::ElementWezla wezel){
		int i = XmlBO::WczytajAtrybut<int>(wezel, XML_ATRYBUT_NUMER_FORMATU_DATY, -1);
		switch (i)
		{
		case SLog::Log::Data: formatDatyLogow_ = SLog::Log::Data;
			break;
		case SLog::Log::Czas: formatDatyLogow_ = SLog::Log::Czas;
			break;
		case SLog::Log::DataCzas: formatDatyLogow_ = SLog::Log::DataCzas;
			break;
		default:
			SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
			break;
		}
		return true;
	}

	SLog::Log::FormatCzasu UstawieniaAplikacji::pobierzFormatDatyLogow() const{
		return formatDatyLogow_;
	}

	bool UstawieniaAplikacji::ustawPrzedrostekPlikuLogow(XmlBO::ElementWezla wezel){
		przedrostekPlikuLogow_ = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_PREFIX_PLIKU_LOGOW, std::string());
		return !przedrostekPlikuLogow_.empty();
	}

	const std::string& UstawieniaAplikacji::pobierzPrzedrostekPlikuLogow() const{
		return przedrostekPlikuLogow_;
	}

	bool UstawieniaAplikacji::ustawFormatDatyPlikuLogow(XmlBO::ElementWezla wezel){
		formatDatyPlikuLogow_ = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_FORMAT_DATY_NAZWY_PLIKU_LOGOW, std::string());
		return !formatDatyPlikuLogow_.empty();
	}

	const std::string& UstawieniaAplikacji::pobierzFormatDatyPlikuLogow() const{
		return formatDatyPlikuLogow_;
	}

	bool UstawieniaAplikacji::ustawZablokowaneLogi(XmlBO::ElementWezla wezel){
		auto logi = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_ZABLOKOWANE_LOGI, std::string());
		if (logi.empty())
			return true;
		size_t pos = 0;
		size_t start = 0;
		std::string sub;
		while (pos != std::string::npos){
			pos = logi.find_first_of(',', pos);
			if (pos == std::string::npos){
				sub = std::move(logi.substr(start));
			}
			else{
				sub = std::move(logi.substr(start, pos - start));
				start = ++pos;
			}
			if (sub.empty())
				break;
			int i = stoi(sub);
			switch (i)
			{
			case SLog::Log::All: zablokowaneLogi_.emplace_back(SLog::Log::All);
				break;
			case SLog::Log::Debug: zablokowaneLogi_.emplace_back(SLog::Log::Debug);
				break;
			case SLog::Log::Info: zablokowaneLogi_.emplace_back(SLog::Log::Info);
				break;
			case SLog::Log::Warning: zablokowaneLogi_.emplace_back(SLog::Log::Warning);
				break;
			case SLog::Log::Error: zablokowaneLogi_.emplace_back(SLog::Log::Error);
				break;
			default: SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
				break;
			}
		}
		return true;
	}

	const std::vector< SLog::Log::TypLogow >& UstawieniaAplikacji::pobierzZablokowaneLogi() const{
		return zablokowaneLogi_;
	}

	bool UstawieniaAplikacji::ustawOdblokowaneLogi(XmlBO::ElementWezla wezel){
		auto logi = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_ODBLOKOWANE_LOGI, std::string());
		if (logi.empty())
			return true;
		size_t pos = 0;
		size_t start = 0;
		std::string sub;
		while (pos != std::string::npos){
			pos = logi.find_first_of(',', pos);
			if (pos == std::string::npos){
				sub = std::move(logi.substr(start));
			}
			else{
				sub = std::move(logi.substr(start, pos - start));
				start = ++pos;
			}
			if (sub.empty())
				break;
			int i = stoi(sub);
			switch (i)
			{
			case SLog::Log::All: odblokowaneLogi_.emplace_back(SLog::Log::All);
				break;
			case SLog::Log::Debug: odblokowaneLogi_.emplace_back(SLog::Log::Debug);
				break;
			case SLog::Log::Info: odblokowaneLogi_.emplace_back(SLog::Log::Info);
				break;
			case SLog::Log::Warning: odblokowaneLogi_.emplace_back(SLog::Log::Warning);
				break;
			case SLog::Log::Error: odblokowaneLogi_.emplace_back(SLog::Log::Error);
				break;
			default: SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
				break;
			}
		}
		return true;
	}

	const std::vector< SLog::Log::TypLogow >& UstawieniaAplikacji::pobierzOdblokowaneLogi() const{
		return odblokowaneLogi_;
	}

	bool UstawieniaAplikacji::ustawAdresPlikuGry(XmlBO::ElementWezla wezel){
		adresPlikuGry_ = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_PLIK_GRY, std::string());
		return !adresPlikuGry_.empty();
	}

	const std::string& UstawieniaAplikacji::pobierzAdresPlikuGry() const{
		return adresPlikuGry_;
	}

	bool UstawieniaAplikacji::ustawAdresPlikuStanow(XmlBO::ElementWezla wezel){
		adresPlikuStanow_ = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_PLIK_STANOW, std::string());
		return !adresPlikuStanow_.empty();
	}

	const std::string& UstawieniaAplikacji::pobierzAdresPlikuStanow() const{
		return adresPlikuStanow_;
	}

	bool UstawieniaAplikacji::ustawAdresPlikuOkien(XmlBO::ElementWezla wezel){
		adresPlikuOkien_ = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_PLIK_OKIEN, std::string());
		return !adresPlikuOkien_.empty();
	}

	const std::string& UstawieniaAplikacji::pobierzAdresPlikuOkien() const{
		return adresPlikuOkien_;
	}

	bool UstawieniaAplikacji::ustawFolderPlikuUzytkownika(XmlBO::ElementWezla wezel){
		folderPlikuUzytkownika_ = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_FOLDER_UZYTKOWNIKA, std::string());
		return !folderPlikuUzytkownika_.empty();
	}

	const std::string& UstawieniaAplikacji::pobierzFolderPlikuUzytkownika() const{
		return folderPlikuUzytkownika_;
	}

	bool UstawieniaAplikacji::ustawFolderPlikuUkladu(XmlBO::ElementWezla wezel){
		folderPlikuUkladu_ = XmlBO::WczytajAtrybut<std::string>(wezel, XML_ATRYBUT_FOLDER_UKLADU, std::string());
		return !folderPlikuUkladu_.empty();
	}

	const std::string& UstawieniaAplikacji::pobierzFolderPlikuUkladu() const{
		return folderPlikuUkladu_;
	}

	bool UstawieniaAplikacji::ustawPlikPowiazanZasobow(XmlBO::ElementWezla wezel){
		if (wezel){
			auto temp = wezel->pobierzTekst();
			if (!temp){
				SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
			}
			plikPowiazanZasobow_ = temp;
			if (plikPowiazanZasobow_.empty()){
				SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);
			}
			return true;
		}
		return false;
	}

	const std::string& UstawieniaAplikacji::pobierzAdresPlikuPowiazanZasobow() const{
		return plikPowiazanZasobow_;
	}
};
