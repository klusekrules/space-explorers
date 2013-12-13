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
* Klasa odpowiada za ladowanie plugin�w i wywo�anie funkcji rejestruj�cych plugin w aplikacji.
* \author Daniel Wojdak
* \version 1
* \date 11-07-2013
*/
class PLUGIN_API Cplugin {
private:
	ZmianaFabryka& fabryka_; /// Referencja na fabryk� zmian.
	Log& log_; /// Referencja na obiekt log�w.
	std::string folderPluginow_; /// �cie�ka do folderu zawierajacy pluginy.
public:
	/**
	* Konstruktor klasy Cplugin
	* \param[in] folderPluginow - �cie�ka do folderu zawierajacy pluginy.
	* \param[in] fabryka - Referencja na fabryk� zmian.
	* \param[in] log - Referencja na obiekt log�w.
	*/
	Cplugin( const std::string& folderPluginow, ZmianaFabryka& fabryka , Log& log );

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
