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
		SZmi::ZmianaFabryka& fabryka_; /// Referencja na fabryk� zmian.
		SLog::Log& log_; /// Referencja na obiekt log�w.
		std::string folderPluginow_; /// �cie�ka do folderu zawierajacy pluginy.
		std::list < SumaKontrolnaPliku::SharedPtr > lista_;
	public:
		Plugin() = delete;
		virtual ~Plugin() = default;
		/**
		* Konstruktor klasy Plugin
		* \param[in] ustawienia - Obiekt ustawie� aplikacji.
		* \param[in] fabryka - Referencja na fabryk� zmian.
		* \param[in] log - Referencja na obiekt log�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		Plugin(const UstawieniaAplikacji& ustawienia, SZmi::ZmianaFabryka& fabryka, SLog::Log& log);

		/**
		* Metoda wywo�uj�ca funkcje rejestruj�ce domy�lne Zminay zaimplementowane w aplikcji w pliku ftrans.dll.
		* \return Metoda zwraca warto�� true, je�eli uda si� poprawnie zarejestrowa� wszystkie zmiany. Zwraca false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		bool zaladujDomyslneKlasyZmian();

		/**
		* Metoda wywo�uj�ca funkcje rejestruj�ce zmiany z dodatkowych bibliotek do�aczonych do aplikacji.
		* \return Metoda zawsze zwraca warto�� true.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		bool zaladujZewnetrzneKlasyZmian(ZarzadcaZasobow & zarzadcaZasobow_);

		/**
		* Funkcja s�u��ca do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-11-2014
		*/
		std::string napis() const override;
	};
}
