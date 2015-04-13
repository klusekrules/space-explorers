#include "UtilsGui.h"
namespace SpEx{

	void UtilsGui::wyswietlWiadomoscWGUI(unsigned int typ, const std::string& tresc){
		auto ptr = SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry();
		if (ptr)
			ptr->wyswietlWiadomoscWGUI(typ, tresc);
	}
	
	void UtilsGui::callback(const tgui::Callback& callback, unsigned int idZdarzenia, unsigned int numer){
		Zdarzenie zdarzenie;
		zdarzenie.idStanu_ = MaszynaStanow::pobierzInstancje().pobierzStan().id_;
		zdarzenie.idZdarzenia_ = STyp::Identyfikator(idZdarzenia);
		zdarzenie.numer_ = numer;
		zdarzenie.zdarzenieGui_ = callback;
		MaszynaStanow::pobierzInstancje().kolejkujZdarzenie(zdarzenie);
	}

	void UtilsGui::bindCallbackEvent(const tgui::Widget::Ptr widzet, unsigned int zdarzenie, unsigned int numer, unsigned int akcja){
		if (!(akcja == 0 || zdarzenie == 0) && widzet != nullptr){
			widzet->bindCallbackEx(std::bind(&UtilsGui::callback, std::placeholders::_1, zdarzenie, numer), akcja);
		}
	}
}