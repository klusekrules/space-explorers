#include "EkranStartowy.h"
#include <Windows.h>
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\StackThrow.h"
#include "Kontroler\MaszynaStanow\MaszynaStanow.h"

namespace SpEx{
	EkranStartowy::EkranStartowy(sf::RenderWindow& okno, XmlBO::ElementWezla wezel)
		: EkranSzablon(wezel), czasWlaczania_(3000), czasTrwalosci_(2000), czasChwilowy_(0), okno_(okno.getSystemHandle())
	{
		interfejs_.setWindow(okno);
		XmlBO::WczytajAtrybut<SpEx::STACKTHROW>(wezel, ATRYBUT_XML_EKRAN_STAN_WEJSCIOWY, idStanuWejscia_);
		XmlBO::WczytajAtrybut<SpEx::STACKTHROW>(wezel, ATRYBUT_XML_EKRAN_ZDARZENIE_WYJSCIA, idZdarzeniaWyjscia_);
	}

	void EkranStartowy::uaktualnij(Stan& stan){
		
		if (stan.id_ == idStanuWejscia_){
			czasChwilowy_ += stan.dt_;
			unsigned char kolor;
			if (czasChwilowy_ >= czasWlaczania_){
				kolor = 255;
				SetLayeredWindowAttributes(okno_, NULL, kolor, LWA_ALPHA);
				if (czasChwilowy_ >= czasWlaczania_ + czasTrwalosci_){
					Zdarzenie zdarzenie;
					zdarzenie.idStanu_ = stan.id_;
					zdarzenie.numer_ = stan.numer_;
					zdarzenie.idZdarzenia_ = idZdarzeniaWyjscia_;
					MaszynaStanow::pobierzInstancje().kolejkujZdarzenie(zdarzenie);
				}
			}
			else{
				kolor = static_cast<sf::Uint8>(255.f * (czasChwilowy_.count() / czasWlaczania_.count()));
				SetLayeredWindowAttributes(okno_, NULL, kolor, LWA_ALPHA);
			}
		}
		else{
			czasChwilowy_ = Stan::KrokCzasu(0);
		}

	}
};
