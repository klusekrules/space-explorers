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
	* \brief Klasa przechowuj�ca ustawienia
	*
	* Klasa s�u�aca do wczytywania, przechowywyania, zarz�dzania i zapisywania ustawie� aplikacji.
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
		* Domy�lny konstruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		UstawieniaAplikacji() = default;

		/**
		* \brief Destruktor.
		*
		* Domy�lny destruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		virtual ~UstawieniaAplikacji() = default;

		/**
		* \brief Metoda wczytuj�ca dane z pliku.
		*
		* Metoda wczytuj�ca ustawienia w pliku, kt�rego adres jest podany w parametrze.
		* \param[in] plik - Adres pliku.
		* \return Zwracana jest warto�� true, je�eli wszystko si� powiedzie. Zwracana jest warto�c false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool zaladuj(const std::string& plik);

		/**
		* \brief Metoda zwracaj�ca j�zyk aplikacji.
		*
		* Metoda zwraca j�zyka aplikacji jaki zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy j�zyk aplikacji.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzJezykAplikacji() const;

		/**
		* \brief Metoda zwracaj�ca adres pliku danych.
		*
		* Metoda zwraca adres pliku danych, kt�ry to adres zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy adres pliku danych.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzPlikDanych() const;

		/**
		* \brief Metoda zwracaj�ca adres folderu z pluginami.
		*
		* Metoda zwraca adres folderu z pluginami, kt�ry to adres zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy adres folderu z pluginami.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzFolderPlugin() const;

		/**
		* \brief Metoda zwracaj�ca format daty log�w.
		*
		* Metoda zwraca format daty log�w jaki zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest format daty log�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		SLog::Log::FormatCzasu pobierzFormatDatyLogow() const;

		/**
		* \brief Metoda zwracaj�ca przedrostek w nazwie pliku log�w.
		*
		* Metoda zwraca przedrostek w nazwie pliku log�w jaki zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy przedrostek w nazwie pliku log�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzPrzedrostekPlikuLogow() const;

		/**
		* \brief Metoda zwracaj�ca format daty w nazwie pliku log�w.
		*
		* Metoda zwraca format daty w nazwie pliku log�w jaki zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy format daty w nazwie pliku log�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzFormatDatyPlikuLogow() const;

		/**
		* \brief Metoda zwracaj�ca list� zablokowanych poziom�w log�w.
		*
		* Metoda zwraca list� zablokowanych poziom�w log�w jaka zosta�a wczytana z pliku z ustawieniami.
		* \return Zwracana jest lista zablokowanych poziom�w log�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::vector< SLog::Log::TypLogow >& pobierzZablokowaneLogi() const;

		/**
		* \brief Metoda zwracaj�ca list� odblokowanych poziom�w log�w.
		*
		* Metoda zwraca list� odblokowanych poziom�w log�w jaka zosta�a wczytana z pliku z ustawieniami.
		* \return Zwracana jest lista odblokowanych poziom�w log�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::vector< SLog::Log::TypLogow >& pobierzOdblokowaneLogi() const;

		/**
		* \brief Metoda zwracaj�ca adres pliku z list� planet, uk�ad�w i galaktyk obecnych w grze.
		*
		* Metoda zwraca adres pliku z list� planet, uk�ad�w i galaktyk obecnych w grze, kt�ry to adres zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy adres pliku z list� planet, uk�ad�w i galaktyk obecnych w grze.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzAdresPlikuGry() const;

		/**
		* \brief Metoda zwracaj�ca adres pliku z opisem stanu.
		*
		* Metoda zwraca adres pliku z opisem stanu, kt�ry to adres zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy adres pliku z opisem stanu.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzAdresPlikuStanow() const;

		/**
		* \brief Metoda zwracaj�ca adres pliku z opisem okien.
		*
		* Metoda zwraca adres pliku z opisem okien, kt�ry to adres zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy adres pliku z opisem okien.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzAdresPlikuOkien() const;

		/**
		* \brief Metoda zwracaj�ca adres folderu z plikami u�ytkownika.
		*
		* Metoda zwraca adres pliku folderu z plikami u�ytkownika, kt�ry to adres zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy adres pliku folderu z plikami u�ytkownika.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzFolderPlikuUzytkownika() const;

		/**
		* \brief Metoda zwracaj�ca adres folderu z plikami opisuj�cymi planety.
		*
		* Metoda zwraca adres pliku folderu z plikami opisuj�cymi planety, kt�ry to adres zosta� wczytany z pliku z ustawieniami.
		* \return Zwracany jest napis zawieraj�cy adres pliku folderu z plikami opisuj�cymi planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		const std::string& pobierzFolderPlikuUkladu() const;
		
	private:
		std::string jezykAplikacji_; /// Atrybut przechowuj�cy napis z nazw� u�ywanego j�zyka aplikacji.

		/**
		* \brief Metoda wczytuj�ca do obiektu nazw� j�zyka u�ywanego w aplikacji.
		*
		* Metoda wczytuj�ca do obiektu nazw� j�zyka, kt�ry jest u�ywany w aplikacji, z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawJezykAplikacji(XmlBO::ElementWezla wezel);

		std::string plikDanych_; /// Atrybut przechowuj�cy napis z adresem pliku z opisem obiekt�w w grze.

		/**
		* \brief Metoda wczytuj�ca do obiektu adres pliku danych aplikacji.
		*
		* Metoda wczytuj�ca do obiektu nazw� pliku z opisem obiekt�w gry z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawPlikDanych(XmlBO::ElementWezla wezel);

		std::string folderPlugin_; /// Atrybut przechowuj�cy napis z adresem folderu z pluginami.

		/**
		* \brief Metoda wczytuj�ca do obiektu adres folderu plugin�w.
		*
		* Metoda wczytuj�ca do obiektu nazw� pliku z opisem obiekt�w gry z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFolderPlugin(XmlBO::ElementWezla wezel);

		SLog::Log::FormatCzasu formatDatyLogow_; /// Atrybut przechowuj�cy format daty u�ywany w pliku log�w.

		/**
		* \brief Metoda wczytuj�ca do obiektu format daty w pliku log�w.
		*
		* Metoda wczytuj�ca do obiektu format daty u�ywany w pliku log�w z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFormatDatyLogow(XmlBO::ElementWezla wezel);

		std::string przedrostekPlikuLogow_; /// Atrybut przechowuj�cy napis zawieraj�cy przedrostek nazwy pliku log�w.

		/**
		* \brief Metoda wczytuj�ca do obiektu przedrostek pliku log�w.
		*
		* Metoda wczytuj�ca do obiektu przedrostek pliku log�w z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawPrzedrostekPlikuLogow(XmlBO::ElementWezla wezel);

		std::string formatDatyPlikuLogow_; /// Atrybut przechowuj�cy napis z formatem daty u�ytym w nazwie pliku log�w.

		/**
		* \brief Metoda wczytuj�ca do obiektu format daty nazwy pliku log�w.
		*
		* Metoda wczytuj�ca do obiektu format daty u�ywany w nazwie pliku log�w z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFormatDatyPlikuLogow(XmlBO::ElementWezla wezel);

		std::vector< SLog::Log::TypLogow > zablokowaneLogi_; /// Atrybut przechowuj�cy list� zablokowanych poziom�w log�w.

		/**
		* \brief Metoda wczytuj�ca do obiektu list� zablokowanych poziom�w log�w.
		*
		* Metoda wczytuj�ca do obiektu list� zablokowanych poziom�w log�w z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawZablokowaneLogi(XmlBO::ElementWezla wezel);

		std::vector< SLog::Log::TypLogow > odblokowaneLogi_; /// Atrybut przechowuj�cy list� odblokowanych poziom�w log�w.

		/**
		* \brief Metoda wczytuj�ca do obiektu list� odblokowanych poziom�w log�w.
		*
		* Metoda wczytuj�ca do obiektu list� odblokowanych poziom�w log�w z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawOdblokowaneLogi(XmlBO::ElementWezla wezel);

		std::string adresPlikuGry_; /// Atrybut przechowuj�cy napis z adresem pliku zawieraj�cego list� planet, uk�ad�w i galaktyk.

		/**
		* \brief Metoda wczytuj�ca do obiektu adres pliku zawieraj�cego list� planet, uk�ad�w i galaktyki.
		*
		* Metoda wczytuj�ca do obiektu adres pliku zawieraj�cego list� planet, uk�ad�w i galaktyki z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawAdresPlikuGry(XmlBO::ElementWezla wezel);

		std::string adresPlikuStanow_; /// Atrybut przechowuj�cy napis z adresem pliku opisuj�cym stany aplikacji.

		/**
		* \brief Metoda wczytuj�ca do obiektu adres pliku zawieraj�cego opis stan�w aplikacji.
		*
		* Metoda wczytuj�ca do obiektu adres pliku zawieraj�cego opis stan�w aplikacji z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawAdresPlikuStanow(XmlBO::ElementWezla wezel);

		std::string adresPlikuOkien_; /// Atrybut przechowuj�cy napis z adresem pliku opusuj�cego okna u�yte w aplikacji.

		/**
		* \brief Metoda wczytuj�ca do obiektu adres pliku zawieraj�cego list� okien aplikacji.
		*
		* Metoda wczytuj�ca do obiektu adres pliku zawieraj�cego list� okien aplikacji z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawAdresPlikuOkien(XmlBO::ElementWezla wezel);

		std::string folderPlikuUzytkownika_; /// Atrybut przechowuj�cy napis z adresem folderu, w kt�rym znajduj� si� pliki u�ytkownika.

		/**
		* \brief Metoda wczytuj�ca do obiektu adres folderu zawieraj�cego pliki u�ytkownik�w.
		*
		* Metoda wczytuj�ca do obiektu adres folderu zawieraj�cego pliki u�ytkownik�w z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFolderPlikuUzytkownika(XmlBO::ElementWezla wezel);

		std::string folderPlikuUkladu_; /// Atrybut przechowuj�cy napis z adresem folderu, w kt�rym s� dok�adne opisy planet.

		/**
		* \brief Metoda wczytuj�ca do obiektu adres folderu zawieraj�cego pliki z opisem planet.
		*
		* Metoda wczytuj�ca do obiektu adres folderu zawieraj�cego pliki z opisem planet z w�z�a przekazanego w parametrze.
		* \param[in] wezel - W�ze� zawieraj�cy informacje o danej opcji.
		* \return Zwracany jest warto�� true, je�eli uda si� poprawnie wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		bool ustawFolderPlikuUkladu(XmlBO::ElementWezla wezel);

	};
};
