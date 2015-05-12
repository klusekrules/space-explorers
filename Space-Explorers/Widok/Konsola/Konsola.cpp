#include "Konsola.h"
#include "TGUI\TGUI.hpp"
#include <Windows.h>
#include "Kontroler\Aplikacja.h"
#include "Utils\Utils.h"

namespace SpEx{

	void Konsola::callback(const tgui::Callback& callback, tgui::ChatBox::Ptr chatbox) const{
		std::string polecenie = ((tgui::EditBox*)callback.widget)->getText();
		chatbox->addLine(SLog::Log::pobierzInstancje().pobierzDateCzas() + " -> " + polecenie, sf::Color(0x0a, 0xd7, 0xb8, 255));
		((tgui::EditBox*)callback.widget)->setText("");
		wykonajPolecenie(polecenie);
	}
	
	void Konsola::wykonajPolecenie(const std::string& polecenie) const{
		auto sPolecenie = Utils::trim(polecenie);
		auto iter = std::find_if(sPolecenie.begin(), sPolecenie.end(), [](unsigned char i){ return ::isspace(i); });
		std::string nazwa(sPolecenie.begin(), iter);
		sPolecenie.erase(sPolecenie.begin(), iter);
		auto parametry = Utils::trim(sPolecenie);
		if (log_.czyLogiOdblokowane(SLog::Log::Debug)){
			log_.loguj(SLog::Log::Debug, "Polecenie: \"" + nazwa + "\" - Parametry: \"" + parametry + "\"");
		}
		if (!nazwa.empty()){
			auto metoda = poleceniaKonsoli_.find(nazwa);
			if (metoda != poleceniaKonsoli_.end()){
				metoda->second.funkcja_(parametry);
			} else{
				if (log_.czyLogiOdblokowane(SLog::Log::Warning)){
					log_.loguj(SLog::Log::Warning, "Nierozpoznane polecenie: " + nazwa);
				}
			}
		}
	}

	void Konsola::rejestrujPolecenie(const std::string& nazwa, const OpcjePolecenia& polecenie){
		poleceniaKonsoli_.emplace(nazwa, polecenie);
	}

	void Konsola::logujListePolecen() const{
		if (poleceniaKonsoli_.empty()){
			log_.loguj(SLog::Log::Info, "Brak polecen konsoli.");
		} else{

			log_.loguj(SLog::Log::Info, "Lista dostêpnych poleceñ konsoli:");
			for (auto & wpis : poleceniaKonsoli_){
				log_.loguj(SLog::Log::Info, wpis.first + " - " + wpis.second.opisPolecenia_);
			}
		}
	}

	Konsola::Konsola(SLog::Log& log)
		: Watek(true), log_(log)
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
		inicjalizacjaWynik_ = inicjalizacja_.get_future();
		odblokuj();
	}

	void Konsola::dodajKomunikat(const std::string& komunikat, const sf::Color& kolor){
		std::lock_guard<std::mutex> lock(muxLista_);
		lista_.emplace_back(Komunikat({ komunikat, kolor }));
	}

	bool Konsola::czekajNaInicjalizacje(){
		inicjalizacjaWynik_.wait();
		return inicjalizacjaWynik_.get();
	}

	void Konsola::wykonuj(){
		sf::RenderWindow window(sf::VideoMode(650, 400), "Konsola",sf::Style::Titlebar);
		tgui::Gui gui(window);

		if (gui.setGlobalFont("resource/consola.ttf") == false){
			inicjalizacja_.set_value(false);
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
		editBox->bindCallbackEx(std::bind(&SpEx::Konsola::callback, this, std::placeholders::_1, chatbox), tgui::EditBox::ReturnKeyPressed);
		
		inicjalizacja_.set_value(true);

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