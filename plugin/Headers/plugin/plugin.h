#ifdef PLUGIN_EXPORTS
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API __declspec(dllimport)
#endif

#include "Zmiana\ZmianaFabryka.h"
#include "Logger\Log.h"
namespace SPlu{
	/**
	* \brief Klasa zarzadzajaca pluginami.
	*
	* Klasa odpowiada za ladowanie plugin�w i wywo�anie funkcji rejestruj�cych plugin w aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 11-07-2013
	*/
	class PLUGIN_API Cplugin {
	private:
		SZmi::ZmianaFabryka& fabryka_; /// Referencja na fabryk� zmian.
		SLog::Log& log_; /// Referencja na obiekt log�w.
		std::string folderPluginow_; /// �cie�ka do folderu zawierajacy pluginy.
	public:
		/**
		* Konstruktor
		*/
		Cplugin() = delete;

		/**
		* Destruktor
		*/
		~Cplugin() = default;

		/**
		* Konstruktor klasy Cplugin
		* \param[in] folderPluginow - �cie�ka do folderu zawierajacy pluginy.
		* \param[in] fabryka - Referencja na fabryk� zmian.
		* \param[in] log - Referencja na obiekt log�w.
		*/
		Cplugin(const std::string& folderPluginow, SZmi::ZmianaFabryka& fabryka, SLog::Log& log);

		/**
		* Metoda wywo�uj�ca funkcje rejestruj�ce domy�lne Zminay zaimplementowane w aplikcji w pliku ftrans.dll.
		* \return Metoda zwraca warto�� true, je�eli uda si� poprawnie zarejestrowa� wszystkie zmiany. Zwraca false w przeciwnym wypadku.
		*/
		bool zaladujDomyslneKlasyZmian();

		/**
		* Metoda wywo�uj�ca funkcje rejestruj�ce zmiany z dodatkowych bibliotek do�aczonych do aplikacji.
		* \return Metoda zawsze zwraca warto�� true.
		*/
		bool zaladujZewnetrzneKlasyZmian();
	};
}
