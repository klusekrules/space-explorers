#include "UtilsGui.h"
#include "Widok\Tgui\SurowiecGui.h"
#include "Widok\Tgui\ListaSurowcowGui.h"
#include "Model\SurowceInfo.h"
#include "Widok\Tgui\KontrolkaObiektu.h"
#include "Testy\Szkielet\TestyUtilsBO.h"
#include "Parser\ParserDokumentXml.h"
#include "Parser\ParserElementXml.h"
#include "Widok\Tgui\LogListGui.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Gra.h"
#include "Model\Planeta.h"

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

	void UtilsGui::bindCallbackEvent(const tgui::Widget::Ptr widzet, unsigned int zdarzenie, unsigned int numer, const std::string& akcje){
		if (!(akcje.empty() || zdarzenie == 0) && widzet != nullptr){
			widzet->connectEx(akcje, std::bind(&UtilsGui::callback, std::placeholders::_1, zdarzenie, numer));
		}
	}

	void UtilsGui::oknotestowe(){

		sf::RenderWindow window{ { 800, 600 }, "Okno Testowe" };
		tgui::Gui gui{ window }; // Create the gui and attach it to the window

		auto& app = SpEx::Aplikacja::pobierzInstancje();
		
		//app.pobierzGre().generujNowaGalaktyke();

		auto ptrPlaneta = app.pobierzGre().pobierzPlanete(0);

		/*if (ptrPlaneta) {
			auto ptrA = std::shared_ptr<SpEx::Surowce>(app.pobierzGre().pobierzObiektInfo<SpEx::SurowceInfo>(1).tworzEgzemplarz(STyp::Ilosc(500)));
			ptrPlaneta->dodajObiekt<SpEx::Surowce>(ptrA);
			auto ptrB = std::shared_ptr<SpEx::Surowce>(app.pobierzGre().pobierzObiektInfo<SpEx::SurowceInfo>(2).tworzEgzemplarz(STyp::Ilosc(1500)));
			ptrPlaneta->dodajObiekt<SpEx::Surowce>(ptrB);
			auto ptrC = std::shared_ptr<SpEx::Surowce>(app.pobierzGre().pobierzObiektInfo<SpEx::SurowceInfo>(3).tworzEgzemplarz(STyp::Ilosc(5500)));
			ptrPlaneta->dodajObiekt<SpEx::Surowce>(ptrC);
		}*/

		//app.zapiszGre();

		gui.setFont("resource/consola.ttf");

		//tgui::Theme::Ptr theme = std::make_shared<tgui::Theme>("widgets/Black.txt");
		
		//gui.loadWidgetsFromFile("resource\\temp2.txt");

		auto lista = std::make_shared<tgui::ListaSurowcowGui>();

		lista->aktualizacjaDanych(*ptrPlaneta);
		
		gui.add(lista, "ListaSurowcow");
		
		//gui.saveWidgetsToFile("resource\\temp2.txt");

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				gui.handleEvent(event); // Pass the event to the widgets
			}

			window.clear();
			gui.draw(); // Draw all widgets
			window.display();
		}

	}
}