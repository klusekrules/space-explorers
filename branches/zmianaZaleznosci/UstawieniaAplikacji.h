#pragma once
#include "Parser\XmlBO.h"
#include "Logger\Log.h"

#define XML_WEZEL_GLOWNY "SpaceGame"
#define XML_WEZEL_PLIK_DANYCH "data"
#define XML_WEZEL_JEZYK_APLIKACJI "locale"
#define XML_WEZEL_FOLDER_PLUGIN "plugins"
#define XML_WEZEL_USTAWIENIA_LOGOW "logi"
#define XML_WEZEL_ZARZADCA_PAMIECI "zarzadca"

#define XML_ATRYBUT_NUMER_FORMATU_DATY "numerFormatuDaty"
#define XML_ATRYBUT_PREFIX_PLIKU_LOGOW "prefixPlikuLogow"
#define XML_ATRYBUT_FORMAT_DATY_NAZWY_PLIKU_LOGOW "formatDatyWNazwiePliku"
#define XML_ATRYBUT_ZABLOKOWANE_LOGI "zablokowaneLogi"
#define XML_ATRYBUT_ODBLOKOWANE_LOGI "odblokowaneLogi"

#define XML_ATRYBUT_PLIK_GRY "plikGry"
#define XML_ATRYBUT_PLIK_STANOW "plikStanow"
#define XML_ATRYBUT_PLIK_OKIEN "plikOkien"
#define XML_ATRYBUT_FOLDER_UZYTKOWNIKA "folderPlikowUzytkownikow"
#define XML_ATRYBUT_FOLDER_UKLADU "folderPlikowOpisuUkladow"

#define USTAWIENIA_DOMYSLNE_JEZYK_APLIKACJI "Polish"

namespace SpEx{
	class UstawieniaAplikacji
	{
	public:
		UstawieniaAplikacji() = default;
		bool zaladuj(const std::string& plik);
		const std::string& pobierzJezykAplikacji() const;
		const std::string& pobierzPlikDanych() const;
		const std::string& pobierzFolderPlugin() const;
		SLog::Log::FormatCzasu pobierzFormatDatyLogow() const;
		const std::string& pobierzPrzedrostekPlikuLogow() const;
		const std::string& pobierzFormatDatyPlikuLogow() const;

		const std::vector< SLog::Log::TypLogow >& pobierzZablokowaneLogi() const;
		const std::vector< SLog::Log::TypLogow >& pobierzOdblokowaneLogi() const;

		const std::string& pobierzAdresPlikuGry() const;
		const std::string& pobierzAdresPlikuStanow() const;
		const std::string& pobierzAdresPlikuOkien() const;
		const std::string& pobierzFolderPlikuUzytkownika() const;
		const std::string& pobierzFolderPlikuUkladu() const;

		~UstawieniaAplikacji() = default;

	private:
		std::string jezykAplikacji_;
		bool ustawJezykAplikacji(XmlBO::ElementWezla wezel);

		std::string plikDanych_;
		bool ustawPlikDanych(XmlBO::ElementWezla wezel);

		std::string folderPlugin_;
		bool ustawFolderPlugin(XmlBO::ElementWezla wezel);

		SLog::Log::FormatCzasu formatDatyLogow_;
		bool ustawFormatDatyLogow(XmlBO::ElementWezla wezel);

		std::string przedrostekPlikuLogow_;
		bool ustawPrzedrostekPlikuLogow(XmlBO::ElementWezla wezel);

		std::string formatDatyPlikuLogow_;
		bool ustawFormatDatyPlikuLogow(XmlBO::ElementWezla wezel);

		std::vector< SLog::Log::TypLogow > zablokowaneLogi_;
		bool ustawZablokowaneLogi(XmlBO::ElementWezla wezel);

		std::vector< SLog::Log::TypLogow > odblokowaneLogi_;
		bool ustawOdblokowaneLogi(XmlBO::ElementWezla wezel);

		std::string adresPlikuGry_;
		bool ustawAdresPlikuGry(XmlBO::ElementWezla wezel);

		std::string adresPlikuStanow_;
		bool ustawAdresPlikuStanow(XmlBO::ElementWezla wezel);

		std::string adresPlikuOkien_;
		bool ustawAdresPlikuOkien(XmlBO::ElementWezla wezel);

		std::string folderPlikuUzytkownika_;
		bool ustawFolderPlikuUzytkownika(XmlBO::ElementWezla wezel);

		std::string folderPlikuUkladu_;
		bool ustawFolderPlikuUkladu(XmlBO::ElementWezla wezel);

	};
};
