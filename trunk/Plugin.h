#pragma once
#include "Logger\LoggerInterface.h"
#include "Zmiana\ZmianaFabryka.h"
#include "UstawieniaAplikacji.h"
#include "SumaKontrolnaPliku.h"
#include <list>
#define ATRYBUT_FOLDER_PLUGINOW "plugins"

namespace SpEx{
	class Plugin :
		public virtual SLog::LoggerInterface
	{
	private:
		SZmi::ZmianaFabryka& fabryka_; /// Referencja na fabrykê zmian.
		SLog::Log& log_; /// Referencja na obiekt logów.
		std::string folderPluginow_; /// Œcie¿ka do folderu zawierajacy pluginy.
		std::list < SumaKontrolnaPliku::SharedPtr > lista_;
	public:
		Plugin() = delete;
		virtual ~Plugin() = default;
		/**
		* Konstruktor klasy Plugin
		* \param[in] ustawienia - Obiekt ustawieñ aplikacji.
		* \param[in] fabryka - Referencja na fabrykê zmian.
		* \param[in] log - Referencja na obiekt logów.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		Plugin(const UstawieniaAplikacji& ustawienia, SZmi::ZmianaFabryka& fabryka, SLog::Log& log);

		/**
		* Metoda wywo³uj¹ca funkcje rejestruj¹ce domyœlne Zminay zaimplementowane w aplikcji w pliku ftrans.dll.
		* \return Metoda zwraca wartoœæ true, je¿eli uda siê poprawnie zarejestrowaæ wszystkie zmiany. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		bool zaladujDomyslneKlasyZmian();

		/**
		* Metoda wywo³uj¹ca funkcje rejestruj¹ce zmiany z dodatkowych bibliotek do³aczonych do aplikacji.
		* \return Metoda zawsze zwraca wartoœæ true.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		bool zaladujZewnetrzneKlasyZmian(ZarzadcaZasobow & zarzadcaZasobow_);

		/**
		* Funkcja s³u¿¹ca do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-11-2014
		*/
		std::string napis() const override;
	};
}
