#include "UtilsGui.h"
namespace SpEx{

	void UtilsGui::logToGUI(unsigned int typ, const std::string& tresc){
		SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().logToGUI(typ, tresc);
	}

	void UtilsGui::ustawOknoKomunikatow(int idOkna, const char * kontrolkaNazwy){
		SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().ustawOknoKomunikatow(idOkna,kontrolkaNazwy);
	}

	void UtilsGui::odlaczOknoKomunikatow(){
		SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().odlaczOknoKomunikatow();
	}
}