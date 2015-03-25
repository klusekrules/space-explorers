#include "Konsola.h"
#include "TGUI\TGUI.hpp"
#include <Windows.h>

namespace SpEx{

	void function(const tgui::Callback& callback, tgui::ChatBox::Ptr chatbox){
		chatbox->addLine( " -> " + ((tgui::EditBox*)callback.widget)->getText() , sf::Color::Blue);
		((tgui::EditBox*)callback.widget)->setText("");
	}

	Konsola::Konsola()
		: Watek(true)
	{
		odblokuj();
	}

	void Konsola::wykonuj(){
		sf::RenderWindow window(sf::VideoMode(600, 400), "Konsola",sf::Style::Titlebar);
		tgui::Gui gui(window);

		if (gui.setGlobalFont("resource/consola.ttf") == false){
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE,STyp::Tekst(),STyp::Tekst(),-1,STyp::Tekst("Blad inicjalizacji."),STyp::Tekst("Nie udalo sie ustawic czcionki")));
			return;
		}

		tgui::ChatBox::Ptr chatbox(gui);
		chatbox->load("widgets/Black.conf");
		chatbox->setPosition(0, 0);
		chatbox->setSize(600, 370);
		chatbox->setTextSize(14);
		chatbox->setLineLimit(500);

		tgui::EditBox::Ptr editBox(gui);
		editBox->load("widgets/Black.conf");
		editBox->setPosition(0, 370);
		editBox->setSize(600, 30);
		editBox->bindCallbackEx(std::bind(function,std::placeholders::_1,chatbox), tgui::EditBox::ReturnKeyPressed);
		
		while (window.isOpen() && !czyZakonczyc())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseButtonPressed)
					SetActiveWindow(window.getSystemHandle());

				gui.handleEvent(event);
			}

			window.clear();
			gui.draw();
			window.display();
		}
	}

	Konsola::~Konsola()
	{
	}
}