#include "EkranSzablon.h"
#include "definicjeWezlowXML.h"
#include "BladKonfiguracjiEkranu.h"
#include "UtilsGui.h"
#include "Utils.h"

#define KOMUNIKAT_BRAK_PLIKU STyp::Tekst("Brak pliku konfiguracyjengo dla okna szablonowego, nie zaimplementowano innego sposobu opisu okna.")
#define KOMUNIKAT_BLAD_PLIKU(plik) STyp::Tekst("Nie powiod³o sie konfigurowanie okna na podstawie pliku konfiguracyjnego o nazwie: " + (plik))
#define KOMUNIKAT_BLAD_WLASCIWOSCI(nazwa,wartosc) STyp::Tekst("Nie uda³o siê ustawiæ w³aœciwoœci: " + (nazwa) + " = " + (wartosc) + ".")

namespace SpEx{
	EkranSzablon::EkranSzablon(XmlBO::ElementWezla wezel){
		if (wezel){
			XmlBO::WczytajAtrybut<SpEx::STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, id_);
			std::string konfiguracja = XmlBO::WczytajAtrybut(wezel, ATRYBUT_XML_KONFIGURACJA, std::string());
			std::string czcionka = XmlBO::WczytajAtrybut(wezel, ATRYBUT_XML_CZCIONKA, std::string());
			if (konfiguracja.empty()){
				throw SpEx::BladKonfiguracjiEkranu(EXCEPTION_PLACE, id_, KOMUNIKAT_BRAK_PLIKU);
			}
			else{
				if (!czcionka.empty()){
					sf::Font czcionka_;
					czcionka_.loadFromFile(czcionka);
					interfejs_.setGlobalFont(czcionka_);
				}

				if (!interfejs_.loadWidgetsFromFile(konfiguracja)){
					throw SpEx::BladKonfiguracjiEkranu(EXCEPTION_PLACE, id_, KOMUNIKAT_BLAD_PLIKU(konfiguracja) );
				}

				std::string nazwaOknaKomunikatow = XmlBO::WczytajAtrybut(wezel, ATRYBUT_XML_OKNO_KOMUNIKATOW, std::string());

				if (!nazwaOknaKomunikatow.empty()){
					oknoKomunikatow_ = interfejs_.get<tgui::LogListGui>(nazwaOknaKomunikatow);
				}

				XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_KONTROLKA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
					std::string nazwa = XmlBO::WczytajAtrybut(element, ATRYBUT_XML_NAZWA, std::string());
					if (!nazwa.empty()){
						auto kontrolka = interfejs_.get(nazwa);
						if (kontrolka != nullptr){
							wczytajDaneKontrolki(element, kontrolka);
						}
					}
					return true;
				}));
			}
		}
	}

	void EkranSzablon::uaktualnij(Stan& stan){
	}
	
	void EkranSzablon::clear(){
		interfejs_.removeAllWidgets();
		interfejs_.setGlobalFont(sf::Font());
	}

	void EkranSzablon::odbierz(Stan& stan, const sf::Event& zdarzenie){
		interfejs_.handleEvent(zdarzenie);
	}

	void EkranSzablon::podlacz(sf::RenderWindow& okno){
		interfejs_.setWindow(okno);
	}

	void EkranSzablon::odlacz(sf::RenderWindow&){
	}

	const STyp::Identyfikator& EkranSzablon::pobierzId() const{
		return id_;
	}

	bool EkranSzablon::wczytajDaneKontrolki(XmlBO::ElementWezla wezel, tgui::Widget::Ptr kontrolka){
		if (wezel){
			XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_ATRYBUT, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
				std::string nazwa = XmlBO::WczytajAtrybut(element, ATRYBUT_XML_NAZWA, std::string());
				std::string wartosc = XmlBO::WczytajAtrybut(element, ATRYBUT_XML_WARTOSC, std::string());
				if (!(nazwa.empty() || wartosc.empty())){
					if (!kontrolka->setProperty(nazwa, wartosc)){
						throw SpEx::BladKonfiguracjiEkranu(EXCEPTION_PLACE, id_, KOMUNIKAT_BLAD_WLASCIWOSCI(nazwa,wartosc));
					}
				}
				return true;
			}));
			XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_AKCJA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
				unsigned int akcja = XmlBO::WczytajAtrybut<unsigned int>(element, ATRYBUT_XML_IDENTYFIKATOR, 0);
				unsigned int numer = XmlBO::WczytajAtrybut<unsigned int>(element, ATRYBUT_XML_NUMER, 0);
				unsigned int zdarzenie = XmlBO::WczytajAtrybut<unsigned int>(element, ATRYBUT_XML_ID_ZDARZENIA, 0);
				UtilsGui::bindCallbackEvent(kontrolka, zdarzenie, numer, akcja);				
				return true;
			}));
		}
		return true;
	}

	void EkranSzablon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		interfejs_.draw();
	}
	
	tgui::Gui& EkranSzablon::pobierzGUI(){
		return interfejs_;
	}
};
