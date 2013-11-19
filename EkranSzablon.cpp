#include "EkranSzablon.h"
#include "definicjeWezlowXML.h"
#include "XmlBO.h"

EkranSzablon::EkranSzablon(TiXmlElement* wezel){
	if(wezel){
		XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,id_);
		//numerWejsciowy_ = XmlBO::WczytajAtrybut<int>(wezel,ATRYBUT_XML_EKRAN_MENU_PRZYCISK_NUMER,0);
		stanWejsciowy_ = StanGry::konwertuj(XmlBO::WczytajAtrybut<unsigned int>(wezel,ATRYBUT_XML_EKRAN_STAN_WEJSCIOWY,StanGry::Niezainicjalizowana));
	}
}

EkranSzablon::~EkranSzablon(void){
}

void EkranSzablon::uaktualnij( StanGry& stan ){
	if(stan==StanGry::ZmianaEkranu && stan.pobierzIdEkranu()==id_ ){
		stan.ustawNastepnyStan(stanWejsciowy_);
		//stan.ustawNumerSpecjalny(numerWejsciowy_);
	}
}

void EkranSzablon::odbierz( StanGry& stan, const sf::Event& zdarzenie ){
}

void EkranSzablon::podlacz( sf::Window& ){
}
	
void EkranSzablon::odlacz( sf::Window& ){
}

const Identyfikator& EkranSzablon::pobierzId() const{
	return id_;
}
