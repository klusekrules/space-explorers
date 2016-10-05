#include "Konsola.h"
#include "TGUI\TGUI.hpp"
#include <Windows.h>
#include "Kontroler\Aplikacja.h"
#include "Utils\Utils.h"
#include "Kontroler\MaszynaStanow\MaszynaStanow.h"

#define KOMUNIKAT_BLAD_POBIERANIA_EKRANOW(editbox,chatbox) STyp::Tekst("Nie znaleziono conajmniej jednej z kontrolek: Editbox = " + editbox + " , Chatbox = " + chatbox)

#define PLIK_WDG "plikWdgKonsoli"
#define PLIK_FONT "plikCzcionkiKonsoli"
#define NAZWA_EDITBOX "nazwaKontrolkiEditboxKonsoli"
#define NAZWA_CHATBOX "nazwaKontrolkiChatboxKonsoli"
#define TYTUL_OKNA "tytulOknaKonsoli"
#define SZEROKOSC_OKNA "szerokoscOknaKonsoli"
#define WYSOKOSC_OKNA "wysokoscOknaKonsoli"
#define POZYCJA_X_OKNA "pozycjaXOknaKonsoli"
#define POZYCJA_Y_OKNA "pozycjaYOknaKonsoli"

namespace SpEx{

	void Konsola::callback(tgui::ChatBox::Ptr chatbox, const tgui::Callback& callback) const{
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
				try {
					metoda->second.funkcja_(parametry);
				}catch (STyp::Wyjatek& e) {
					log_.loguj(SLog::Log::Error, std::string("Wykryto wyj¹tek (STyp::Wyjatek): ") + e.what());
				}
				catch (tgui::Exception& e) {
					log_.loguj(SLog::Log::Error, std::string("Wykryto wyj¹tek (tgui::Exception): ") + e.what());
				}
				catch (std::exception& e) {
					log_.loguj(SLog::Log::Error, std::string("Wykryto wyj¹tek (std::exception): ") + e.what());
				}
				catch (...) {
					log_.loguj(SLog::Log::Error, std::string("Wykryto nieznany wyj¹tek!"));
				}
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

	Konsola::Konsola(SLog::Log& log, UstawieniaAplikacji& ustawienia)
		: Watek("Konsola", true), log_(log)
	{

		plikWdg_ = ustawienia[PLIK_WDG];
		plikCzcionki_ = ustawienia[PLIK_FONT];
		nazwaEditbox_ = ustawienia[NAZWA_EDITBOX];
		nazwaChatbox_ = ustawienia[NAZWA_CHATBOX];
		tytulOkna_ = ustawienia[TYTUL_OKNA];
		szerokoscOkna_ = std::stoul(ustawienia[SZEROKOSC_OKNA]);
		wysokoscOkna_ = std::stoul(ustawienia[WYSOKOSC_OKNA]);
		pozycjaX_ = std::stoi(ustawienia[POZYCJA_X_OKNA]);
		pozycjaY_ = std::stoi(ustawienia[POZYCJA_Y_OKNA]);

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
				kolor = sf::Color(255,51,51);
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

	bool Konsola::przesunNaWierch() const{
		if (ptrWindow) {
			return BringWindowToTop(ptrWindow->getSystemHandle()) == TRUE;
		}
		return false;
	}

	void Konsola::wykonuj(){
		try {
			std::unique_ptr<tgui::Gui> ptrGUI = nullptr;
			tgui::ChatBox::Ptr chatbox = nullptr;
			try {
				ptrWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(szerokoscOkna_, wysokoscOkna_), tytulOkna_, sf::Style::Titlebar);
				ptrWindow->setPosition(sf::Vector2i(pozycjaX_,pozycjaY_));
				ptrGUI = std::make_unique<tgui::Gui>(*ptrWindow);
				ptrGUI->setFont(plikCzcionki_);
				ptrGUI->loadWidgetsFromFile(plikWdg_);
				tgui::EditBox::Ptr editBox = ptrGUI->get<tgui::EditBox>(nazwaEditbox_);
				chatbox = ptrGUI->get<tgui::ChatBox>(nazwaChatbox_);

				if (editBox == nullptr || chatbox == nullptr) {
					zakoncz();
					ustawKodPowrotu(WDG_WIDGETS_DONT_FIND);
					ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(WDG_WIDGETS_DONT_FIND), STyp::Tekst("Brak kontrolek"),KOMUNIKAT_BLAD_POBIERANIA_EKRANOW(nazwaEditbox_, nazwaChatbox_)));
					inicjalizacja_.set_value(false);
				}else{
					editBox->connectEx("ReturnKeyPressed", &SpEx::Konsola::callback, this, chatbox);
					ptrGUI->focusWidget(editBox);
					inicjalizacja_.set_value(true);
				}
			}catch (...) {
				inicjalizacja_.set_value(false);
				throw;
			}

			while (ptrWindow->isOpen() && !czyZakonczyc())
			{
				sf::Event event;
				while (ptrWindow->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						ptrWindow->close();

					if (event.type == sf::Event::MouseButtonPressed)
						SetActiveWindow(ptrWindow->getSystemHandle());

					ptrGUI->handleEvent(event);
				}

				{
					std::lock_guard<std::mutex> lock(muxLista_);
					if (!lista_.empty()) {
						auto& element = lista_.front();
						chatbox->addLine(element.komunikat_, element.kolor_);
						lista_.pop_front();
					}
				}

				ptrWindow->clear();
				ptrGUI->draw();
				ptrWindow->display();
			}

			ustawKodPowrotu(ERROR_SUCCESS);
		}
		catch (STyp::Wyjatek& e) {
			ustawBlad(e);
			ustawKodPowrotu(WDG_THROW_STYP);
		}
		catch (tgui::Exception& e) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE,STyp::Tekst(),STyp::Identyfikator(WDG_THROW_TGUI), STyp::Tekst("tgui::Exception"), STyp::Tekst(e.what())));
			ustawKodPowrotu(WDG_THROW_TGUI);
		}
		catch (std::exception& e) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(WDG_THROW_STD), STyp::Tekst("std::exception"), STyp::Tekst(e.what())));
			ustawKodPowrotu(WDG_THROW_STD);
		}
		catch (...) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(WDG_THROW_UNKNOWN), STyp::Tekst("Critical!!"), STyp::Tekst("Unrecognize Exception!")));
			ustawKodPowrotu(WDG_THROW_UNKNOWN);
		}
	}
}