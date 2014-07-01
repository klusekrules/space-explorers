#pragma once
#include "NonMoveable.h"
#include "NonCopyable.h"
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
	/**
	* \brief Klasa przechowuj¹ca ustawienia
	*
	* Klasa s³u¿aca do wczytywania, przechowywyania, zarz¹dzania i zapisywania ustawieñ aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 01-07-2014
	*/
	class UstawieniaAplikacji : 
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:
		/**
		* \brief Konstruktor.
		*
		* Domyœlny konstruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		UstawieniaAplikacji() = default;

		/**
		* \brief Destruktor.
		*
		* Domyœlny destruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		virtual ~UstawieniaAplikacji() = default;

		/**
		* \brief Metoda wczytuj¹ca dane z pliku.
		*
		* Metoda wczytuj¹ca ustawienia w pliku, którego adres jest podany w parametrze.
		* \param[in] plik - Adres pliku.
		* \return Zwracana jest wartoœæ true, je¿eli wszystko siê powiedzie. Zwracana jest wartoœc false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool zaladuj(const std::string& plik);

		/**
		* \brief Metoda zwracaj¹ca jêzyk aplikacji.
		*
		* Metoda zwraca jêzyka aplikacji jaki zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy jêzyk aplikacji.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzJezykAplikacji() const;

		/**
		* \brief Metoda zwracaj¹ca adres pliku danych.
		*
		* Metoda zwraca adres pliku danych, który to adres zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy adres pliku danych.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzPlikDanych() const;

		/**
		* \brief Metoda zwracaj¹ca adres folderu z pluginami.
		*
		* Metoda zwraca adres folderu z pluginami, który to adres zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy adres folderu z pluginami.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzFolderPlugin() const;

		/**
		* \brief Metoda zwracaj¹ca format daty logów.
		*
		* Metoda zwraca format daty logów jaki zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest format daty logów.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		SLog::Log::FormatCzasu pobierzFormatDatyLogow() const;

		/**
		* \brief Metoda zwracaj¹ca przedrostek w nazwie pliku logów.
		*
		* Metoda zwraca przedrostek w nazwie pliku logów jaki zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy przedrostek w nazwie pliku logów.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzPrzedrostekPlikuLogow() const;

		/**
		* \brief Metoda zwracaj¹ca format daty w nazwie pliku logów.
		*
		* Metoda zwraca format daty w nazwie pliku logów jaki zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy format daty w nazwie pliku logów.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzFormatDatyPlikuLogow() const;

		/**
		* \brief Metoda zwracaj¹ca listê zablokowanych poziomów logów.
		*
		* Metoda zwraca listê zablokowanych poziomów logów jaka zosta³a wczytana z pliku z ustawieniami.
		* \return Zwracana jest lista zablokowanych poziomów logów.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::vector< SLog::Log::TypLogow >& pobierzZablokowaneLogi() const;

		/**
		* \brief Metoda zwracaj¹ca listê odblokowanych poziomów logów.
		*
		* Metoda zwraca listê odblokowanych poziomów logów jaka zosta³a wczytana z pliku z ustawieniami.
		* \return Zwracana jest lista odblokowanych poziomów logów.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::vector< SLog::Log::TypLogow >& pobierzOdblokowaneLogi() const;

		/**
		* \brief Metoda zwracaj¹ca adres pliku z list¹ planet, uk³adów i galaktyk obecnych w grze.
		*
		* Metoda zwraca adres pliku z list¹ planet, uk³adów i galaktyk obecnych w grze, który to adres zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy adres pliku z list¹ planet, uk³adów i galaktyk obecnych w grze.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzAdresPlikuGry() const;

		/**
		* \brief Metoda zwracaj¹ca adres pliku z opisem stanu.
		*
		* Metoda zwraca adres pliku z opisem stanu, który to adres zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy adres pliku z opisem stanu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzAdresPlikuStanow() const;

		/**
		* \brief Metoda zwracaj¹ca adres pliku z opisem okien.
		*
		* Metoda zwraca adres pliku z opisem okien, który to adres zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy adres pliku z opisem okien.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzAdresPlikuOkien() const;

		/**
		* \brief Metoda zwracaj¹ca adres folderu z plikami u¿ytkownika.
		*
		* Metoda zwraca adres pliku folderu z plikami u¿ytkownika, który to adres zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy adres pliku folderu z plikami u¿ytkownika.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzFolderPlikuUzytkownika() const;

		/**
		* \brief Metoda zwracaj¹ca adres folderu z plikami opisuj¹cymi planety.
		*
		* Metoda zwraca adres pliku folderu z plikami opisuj¹cymi planety, który to adres zosta³ wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj¹cy adres pliku folderu z plikami opisuj¹cymi planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzFolderPlikuUkladu() const;
		
	private:
		std::string jezykAplikacji_; /// Atrybut przechowuj¹cy napis z nazw¹ u¿ywanego jêzyka aplikacji.

		/**
		* \brief Metoda wczytuj¹ca do obiektu nazwê jêzyka u¿ywanego w aplikacji.
		*
		* Metoda wczytuj¹ca do obiektu nazwê jêzyka, który jest u¿ywany w aplikacji, z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawJezykAplikacji(XmlBO::ElementWezla wezel);

		std::string plikDanych_; /// Atrybut przechowuj¹cy napis z adresem pliku z opisem obiektów w grze.

		/**
		* \brief Metoda wczytuj¹ca do obiektu adres pliku danych aplikacji.
		*
		* Metoda wczytuj¹ca do obiektu nazwê pliku z opisem obiektów gry z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawPlikDanych(XmlBO::ElementWezla wezel);

		std::string folderPlugin_; /// Atrybut przechowuj¹cy napis z adresem folderu z pluginami.

		/**
		* \brief Metoda wczytuj¹ca do obiektu adres folderu pluginów.
		*
		* Metoda wczytuj¹ca do obiektu nazwê pliku z opisem obiektów gry z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFolderPlugin(XmlBO::ElementWezla wezel);

		SLog::Log::FormatCzasu formatDatyLogow_; /// Atrybut przechowuj¹cy format daty u¿ywany w pliku logów.

		/**
		* \brief Metoda wczytuj¹ca do obiektu format daty w pliku logów.
		*
		* Metoda wczytuj¹ca do obiektu format daty u¿ywany w pliku logów z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFormatDatyLogow(XmlBO::ElementWezla wezel);

		std::string przedrostekPlikuLogow_; /// Atrybut przechowuj¹cy napis zawieraj¹cy przedrostek nazwy pliku logów.

		/**
		* \brief Metoda wczytuj¹ca do obiektu przedrostek pliku logów.
		*
		* Metoda wczytuj¹ca do obiektu przedrostek pliku logów z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawPrzedrostekPlikuLogow(XmlBO::ElementWezla wezel);

		std::string formatDatyPlikuLogow_; /// Atrybut przechowuj¹cy napis z formatem daty u¿ytym w nazwie pliku logów.

		/**
		* \brief Metoda wczytuj¹ca do obiektu format daty nazwy pliku logów.
		*
		* Metoda wczytuj¹ca do obiektu format daty u¿ywany w nazwie pliku logów z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFormatDatyPlikuLogow(XmlBO::ElementWezla wezel);

		std::vector< SLog::Log::TypLogow > zablokowaneLogi_; /// Atrybut przechowuj¹cy listê zablokowanych poziomów logów.

		/**
		* \brief Metoda wczytuj¹ca do obiektu listê zablokowanych poziomów logów.
		*
		* Metoda wczytuj¹ca do obiektu listê zablokowanych poziomów logów z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawZablokowaneLogi(XmlBO::ElementWezla wezel);

		std::vector< SLog::Log::TypLogow > odblokowaneLogi_; /// Atrybut przechowuj¹cy listê odblokowanych poziomów logów.

		/**
		* \brief Metoda wczytuj¹ca do obiektu listê odblokowanych poziomów logów.
		*
		* Metoda wczytuj¹ca do obiektu listê odblokowanych poziomów logów z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawOdblokowaneLogi(XmlBO::ElementWezla wezel);

		std::string adresPlikuGry_; /// Atrybut przechowuj¹cy napis z adresem pliku zawieraj¹cego listê planet, uk³adów i galaktyk.

		/**
		* \brief Metoda wczytuj¹ca do obiektu adres pliku zawieraj¹cego listê planet, uk³adów i galaktyki.
		*
		* Metoda wczytuj¹ca do obiektu adres pliku zawieraj¹cego listê planet, uk³adów i galaktyki z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawAdresPlikuGry(XmlBO::ElementWezla wezel);

		std::string adresPlikuStanow_; /// Atrybut przechowuj¹cy napis z adresem pliku opisuj¹cym stany aplikacji.

		/**
		* \brief Metoda wczytuj¹ca do obiektu adres pliku zawieraj¹cego opis stanów aplikacji.
		*
		* Metoda wczytuj¹ca do obiektu adres pliku zawieraj¹cego opis stanów aplikacji z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawAdresPlikuStanow(XmlBO::ElementWezla wezel);

		std::string adresPlikuOkien_; /// Atrybut przechowuj¹cy napis z adresem pliku opusuj¹cego okna u¿yte w aplikacji.

		/**
		* \brief Metoda wczytuj¹ca do obiektu adres pliku zawieraj¹cego listê okien aplikacji.
		*
		* Metoda wczytuj¹ca do obiektu adres pliku zawieraj¹cego listê okien aplikacji z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawAdresPlikuOkien(XmlBO::ElementWezla wezel);

		std::string folderPlikuUzytkownika_; /// Atrybut przechowuj¹cy napis z adresem folderu, w którym znajduj¹ siê pliki u¿ytkownika.

		/**
		* \brief Metoda wczytuj¹ca do obiektu adres folderu zawieraj¹cego pliki u¿ytkowników.
		*
		* Metoda wczytuj¹ca do obiektu adres folderu zawieraj¹cego pliki u¿ytkowników z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFolderPlikuUzytkownika(XmlBO::ElementWezla wezel);

		std::string folderPlikuUkladu_; /// Atrybut przechowuj¹cy napis z adresem folderu, w którym s¹ dok³adne opisy planet.

		/**
		* \brief Metoda wczytuj¹ca do obiektu adres folderu zawieraj¹cego pliki z opisem planet.
		*
		* Metoda wczytuj¹ca do obiektu adres folderu zawieraj¹cego pliki z opisem planet z wêz³a przekazanego w parametrze.
		* \param[in] wezel - Wêze³ zawieraj¹cy informacje o danej opcji.
		* \return Zwracany jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFolderPlikuUkladu(XmlBO::ElementWezla wezel);

	};
};
