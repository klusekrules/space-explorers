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
		bool processing = true;
		while (processing){
			pos = logi.find_first_of(',', pos);
			if (pos == std::string::npos){
				sub = std::move(logi.substr(start));
				processing = false;
			}else{
				sub = std::move(logi.substr(start, pos - start));
			}
			if (sub.empty())
				break;
			int i = stoi(sub);
			start = ++pos;
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
		bool processing = true;
		while (processing){
			pos = logi.find_first_of(',', pos);
			if (pos == std::string::npos){
				sub = std::move(logi.substr(start));
				processing = false;
			}
			else{
				sub = std::move(logi.substr(start, pos - start));
			}
			if (sub.empty())
				break;
			int i = stoi(sub);
			start = ++pos;
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
};
