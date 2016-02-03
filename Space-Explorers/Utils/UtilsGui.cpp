#include "UtilsGui.h"
#include "Widok\Tgui\SurowiecGui.h"
#include "Model\SurowceInfo.h"
#include "Widok\Tgui\KontrolkaObiektu.h"
#include "Testy\Szkielet\TestyUtilsBO.h"
#include "Parser\ParserDokumentXml.h"
#include "Parser\ParserElementXml.h"
#include "Widok\Tgui\LogListGui.h"

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
/*
		SPar::ParserDokumentXml root;
		auto surowiec = TestyUtilsBO::tworzSurowiec(*root.tworzElement("test"),
			STyp::Identyfikator(1),
			STyp::Tekst("Metal"),
			STyp::Tekst("BrakObrazka"),
			STyp::Tekst("Opis metalu."),
			STyp::Masa(3),
			STyp::Objetosc(1),
			STyp::Bool(true));

		SurowceInfo info(surowiec);
		auto ptr = info.tworzEgzemplarz(STyp::Ilosc(1500));

		tgui::SurowiecGui::Ptr button = std::make_shared<tgui::SurowiecGui>();
		gui.add(button,"MojPrzycisk");
		
		tgui::KontrolkaObiektu::Ptr kontrolka = std::make_shared<tgui::KontrolkaObiektu>();
		gui.add(kontrolka, "MojaKontrolka");
		gui.setFont("resource\\consola.ttf");
		kontrolka->setPosition(150, 150);
		button->ustawDane(*ptr);
		button->setPosition(10,20);*/
		gui.setFont("resource/consola.ttf");

		//tgui::Theme::Ptr theme = std::make_shared<tgui::Theme>("widgets/Black.txt");
		
		gui.loadWidgetsFromFile("resource\\temp2.txt");
		/*
		tgui::ChatBox::Ptr chatbox = theme->load("ChatBox");
		chatbox->setPosition(200, 0);
		chatbox->setTextSize(14);
		chatbox->setLineLimit(4);
		chatbox->setLinesStartFromTop();
		gui.add(chatbox);*/

		tgui::LogListGui::Ptr ptr_= gui.get<tgui::LogListGui>("Log");
		ptr_->addMessage(0, "Napis1");
		ptr_->addMessage(0, "Napis2");
		ptr_->addMessage(0, "Napis3");
		ptr_->addMessage(0, "Napis4");

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