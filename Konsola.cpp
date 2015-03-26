#include "Konsola.h"
#include "TGUI\TGUI.hpp"
#include <Windows.h>
#include "Aplikacja.h"

namespace SpEx{

	void function(const tgui::Callback& callback, tgui::ChatBox::Ptr chatbox){
		std::string polecenie = ((tgui::EditBox*)callback.widget)->getText();
		chatbox->addLine(SLog::Log::pobierzInstancje().pobierzDateCzas() + " -> " + polecenie, sf::Color(0x0a, 0xd7, 0xb8, 255));
		((tgui::EditBox*)callback.widget)->setText("");
		Aplikacja::pobierzInstancje().wykonajPolecenie(polecenie);
	}

	Konsola::Konsola(SLog::Log& log)
		: Watek(true)
	{
		log.dodajGniazdoWyjsciowe([this](SLog::Log::TypLogow typ, const std::string& czas, const std::string& komunikat)->void{
			std::string sTyp;
			sf::Color kolor;
			switch (typ)
			{
			case SLog::Log::Debug: sTyp = " [DEBUG] ";
				kolor = sf::Color::White;
				break;
			case SLog::Log::Info: sTyp = " [INFO] ";
				kolor = sf::Color::Green;
				break;
			case SLog::Log::Warning: sTyp = " [WARNING] ";
				kolor = sf::Color::Yellow;
				break;
			case SLog::Log::Error: sTyp = " [ERROR] ";
				kolor = sf::Color::Red;
				break;
			case SLog::Log::All:
			default:
				break;
			}
			this->dodajKomunikat(czas + sTyp + komunikat, kolor);
		});
		odblokuj();
	}

	void Konsola::dodajKomunikat(const std::string& komunikat, const sf::Color& kolor){
		std::lock_guard<std::mutex> lock(muxLista_);
		lista_.emplace_back(Komunikat({ komunikat, kolor }));
	}

	void Konsola::wykonuj(){
		sf::RenderWindow window(sf::VideoMode(650, 400), "Konsola",sf::Style::Titlebar);
		tgui::Gui gui(window);

		if (gui.setGlobalFont("resource/consola.ttf") == false){
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE,STyp::Tekst(),STyp::Tekst(),-1,STyp::Tekst("Blad inicjalizacji."),STyp::Tekst("Nie udalo sie ustawic czcionki")));
			return;
		}

		tgui::ChatBox::Ptr chatbox(gui);
		chatbox->load("widgets/Black.conf");
		chatbox->setPosition(0, 0);
		chatbox->setSize(650, 372);
		chatbox->setTextSize(14);
		chatbox->setLineLimit(100);

		tgui::EditBox::Ptr editBox(gui);
		editBox->load("widgets/Black.conf");
		editBox->setPosition(0, 372);
		editBox->setSize(650, 28);
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

			{
				std::lock_guard<std::mutex> lock(muxLista_);
				if (!lista_.empty()){
					auto& element = lista_.front();
					chatbox->addLine(element.komunikat_,element.kolor_);
					lista_.pop_front();
				}
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