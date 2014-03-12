#pragma once
#include "Parser\XmlBO.h"
namespace SpEx{
	class UstawieniaAplikacji
	{
	public:
		UstawieniaAplikacji() = default;
		bool zaladuj(const std::string& plik);
		const std::string& pobierzJezykAplikacji() const;
		const std::string& pobierzPlikDanych() const;
		const std::string& pobierzFolderPlugin() const;
		~UstawieniaAplikacji() = default;
	private:
		std::string jezykAplikacji_;
		bool ustawJezykAplikacji(XmlBO::ElementWezla wezel);

		std::string plikDanych_;
		bool ustawPlikDanych(XmlBO::ElementWezla wezel);

		std::string folderPlugin_;
		bool ustawFolderPlugin(XmlBO::ElementWezla wezel);
	};
};
