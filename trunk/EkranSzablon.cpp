#include "EkranSzablon.h"
#include "definicjeWezlowXML.h"
#include "XmlBO.h"
#include "Zdarzenie.h"
#include "Logger\Log.h"
#include "MaszynaStanow.h"

EkranSzablon::EkranSzablon(TiXmlElement* wezel){
	if(wezel){
		XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,id_);
		std::string konfiguracja = XmlBO::WczytajAtrybut(wezel,ATRYBUT_XML_KONFIGURACJA,std::string());
		std::string czcionka = XmlBO::WczytajAtrybut(wezel,ATRYBUT_XML_CZCIONKA,std::string());
		if( konfiguracja.empty() ){
			throw OgolnyWyjatek(EXCEPTION_PLACE);
		}else{
			if( !czcionka.empty() ){
				sf::Font czcionka_;
				czcionka_.loadFromFile(czcionka);
				interfejs_.setGlobalFont(czcionka_);
			}
			if( !interfejs_.loadWidgetsFromFile(konfiguracja) )
				throw OgolnyWyjatek(EXCEPTION_PLACE);
			for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_KONTROLKA); element ; element = element->NextSiblingElement(WEZEL_XML_KONTROLKA)){
				std::string nazwa = XmlBO::WczytajAtrybut(element,ATRYBUT_XML_NAZWA,std::string());
				if(  !nazwa.empty() ){
					auto kontrolka = interfejs_.get(nazwa);
					if( kontrolka!=nullptr ){
						wczytajDaneKontrolki(element,kontrolka);
					}
				}
			}
		}
	}
}

EkranSzablon::~EkranSzablon(void){
}

void EkranSzablon::uaktualnij( Stan& stan ){
}

void EkranSzablon::odbierz( Stan& stan, const sf::Event& zdarzenie ){
	idStanu_ = stan.id_;
	interfejs_.handleEvent(zdarzenie);
}

void EkranSzablon::podlacz( sf::RenderWindow& okno ){
	interfejs_.setWindow(okno);
}
	
void EkranSzablon::odlacz( sf::RenderWindow& ){
}

const Identyfikator& EkranSzablon::pobierzId() const{
	return id_;
}

void EkranSzablon::callback( const tgui::Callback& callback, unsigned int idZdarzenia ){
	Zdarzenie zdarzenie;
	zdarzenie.idStanu_ = idStanu_;
	zdarzenie.idZdarzenia_ = Identyfikator(idZdarzenia);
	zdarzenie.numer_=0;
	zdarzenie.zdarzenieGui_ = callback;
	MaszynaStanow::pobierzInstancje().kolejkujZdarzenie(zdarzenie);
}

bool EkranSzablon::wczytajDaneKontrolki( TiXmlElement* wezel , tgui::Widget::Ptr kontrolka ){
	if(wezel){
		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_ATRYBUT); element ; element = element->NextSiblingElement(WEZEL_XML_ATRYBUT)){
			std::string nazwa = XmlBO::WczytajAtrybut(element,ATRYBUT_XML_NAZWA,std::string());
			std::string wartosc = XmlBO::WczytajAtrybut(element,ATRYBUT_XML_WARTOSC,std::string());
			if( !( nazwa.empty() || wartosc.empty() ) ){
				kontrolka->setProperty(nazwa,wartosc);
			}
		}
		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_AKCJA); element ; element = element->NextSiblingElement(WEZEL_XML_AKCJA)){
			unsigned int akcja = XmlBO::WczytajAtrybut<unsigned int>(element,ATRYBUT_XML_IDENTYFIKATOR,0);
			unsigned int zdarzenie = XmlBO::WczytajAtrybut<unsigned int>(element,ATRYBUT_XML_ID_ZDARZENIA,0);
			if( !( akcja == 0 || zdarzenie == 0 ) ){
				kontrolka->bindCallbackEx(std::bind(&EkranSzablon::callback, std::ref(*this), std::placeholders::_1, zdarzenie ), akcja);
			}
		}
	}
	return true;
}


void EkranSzablon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	interfejs_.draw();
}