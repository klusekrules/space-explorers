#ifdef PLUGIN_EXPORTS
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API __declspec(dllimport)
#endif

#include "..\FuncTransf\ZmianaFabryka.h"
#include "..\Logger\Log.h"

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
	ZmianaFabryka& fabryka_; /// Referencja na fabrykê zmian.
	Log& log_; /// Referencja na obiekt logów.
	std::string folderPluginow_; /// Œcie¿ka do folderu zawierajacy pluginy.
public:
	/**
	* Konstruktor klasy Cplugin
	* \param[in] folderPluginow - Œcie¿ka do folderu zawierajacy pluginy.
	* \param[in] fabryka - Referencja na fabrykê zmian.
	* \param[in] log - Referencja na obiekt logów.
	*/
	Cplugin( const std::string& folderPluginow, ZmianaFabryka& fabryka , Log& log );

	/**
	* Metoda wywo³uj¹ca funkcje rejestruj¹ce domyœlne Zminay zaimplementowane w aplikcji w pliku ftrans.dll.
	* \return Metoda zwraca wartoœæ true, je¿eli uda siê poprawnie zarejestrowaæ wszystkie zmiany. Zwraca false w przeciwnym wypadku.
	*/
	bool zaladujDomyslneKlasyZmian();

	/**
	* Metoda wywo³uj¹ca funkcje rejestruj¹ce zmiany z dodatkowych bibliotek do³aczonych do aplikacji.
	* \return Metoda zawsze zwraca wartoœæ true.
	*/
	bool zaladujZewnetrzneKlasyZmian();
};
