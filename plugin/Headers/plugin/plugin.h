#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef _WIN32
#   ifdef PLUGIN_EXPORT
#       define PLUGIN_API __declspec(dllexport)
#		define PLUGIN_EXPIMP_TEMPLATE
#   elif defined(PLUGIN_IMPORT)
#       define PLUGIN_API __declspec(dllimport)
#		define PLUGIN_EXPIMP_TEMPLATE extern
#   else
#       define PLUGIN_API
#   endif
#else
#   define PLUGIN_API
#endif

#include "Zmiana\ZmianaFabryka.h"
#include "Logger\Log.h"
namespace SPlu{
	/**
	* \brief Klasa zarzadzajaca pluginami.
	*
	* Klasa odpowiada za ladowanie pluginów i wywo³anie funkcji rejestruj¹cych plugin w aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 11-07-2013
	*/
	class PLUGIN_API Cplugin {
	private:
		SZmi::ZmianaFabryka& fabryka_; /// Referencja na fabrykê zmian.
		SLog::Log& log_; /// Referencja na obiekt logów.
		std::string folderPluginow_; /// Œcie¿ka do folderu zawierajacy pluginy.
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
		* \param[in] folderPluginow - Œcie¿ka do folderu zawierajacy pluginy.
		* \param[in] fabryka - Referencja na fabrykê zmian.
		* \param[in] log - Referencja na obiekt logów.
		* \author Daniel Wojdak
		* \version 1
		* \date 11-07-2013
		*/
		Cplugin(const std::string& folderPluginow, SZmi::ZmianaFabryka& fabryka, SLog::Log& log);

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
		bool zaladujZewnetrzneKlasyZmian();
	};
}
