#include "EkranMenu.h"
#include "Logger\Log.h"
#include "definicjeWezlowXML.h"
#include "XmlBO.h"

EkranMenu::EkranMenu(sf::RenderWindow& okno  , TiXmlElement* wezel)
	: EkranSzablon(wezel), aktualnyStan_(nullptr), interfejs_(okno)
{
	obrazTla_.loadFromFile("resource\\space.jpg");
	tlo_.setTexture(obrazTla_);
	obrazLogo_.loadFromFile("resource\\SpaceExplorers_logo_640x348.png");
	obrazLogo_.setSmooth(true);
	tloLogo_.setTexture(obrazLogo_);
	tloLogo_.move(10,10);
	tloLogo_.scale(0.3,0.3);

	czcionka_.loadFromFile("resource\\arial.ttf");
	interfejs_.setGlobalFont(czcionka_);

	if(wezel){
		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_EKRAN_MENU_PRZYCISK); element ; element = element->NextSiblingElement(WEZEL_XML_EKRAN_MENU_PRZYCISK)){
			if(!dodajPrzycisk(element))
				throw OgolnyWyjatek(EXCEPTION_PLACE);
		}
	}
}

bool EkranMenu::dodajPrzycisk( TiXmlElement* wezel ){
	if(wezel){
		Identyfikator id;
		std::string napis = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_EKRAN_MENU_PRZYCISK_NAPIS,std::string());
		unsigned int uStan = XmlBO::WczytajAtrybut<unsigned int>(wezel,ATRYBUT_XML_EKRAN_MENU_PRZYCISK_STAN,StanGry::Niezainicjalizowana);
		int numerSpecjalny = XmlBO::WczytajAtrybut<int>(wezel,ATRYBUT_XML_EKRAN_MENU_PRZYCISK_NUMER,0);
		XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_EKRAN_MENU_PRZYCISK_EKRAN,id);
		if(!dodajPrzycisk(napis,StanGry::konwertuj(uStan),numerSpecjalny,id))
			return false;
	}
	return true;
}

EkranMenu::~EkranMenu()
{
}

void EkranMenu::uaktualnij( StanGry& stan ){
	EkranSzablon::uaktualnij(stan);
}

void EkranMenu::odbierz( StanGry& stan, const sf::Event& zdarzenie ){
	aktualnyStan_ = &stan;
	interfejs_.handleEvent(zdarzenie);
}

void EkranMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(tlo_,states);
	target.draw(tloLogo_,states);
	interfejs_.draw();
}

void EkranMenu::callback( int id ){
	if(aktualnyStan_){
		auto przycisk = zdarzenia_.at(id);
		aktualnyStan_->ustawNastepnyStan(przycisk.stan_);
		aktualnyStan_->ustawNumerSpecjalny(przycisk.numer_);
		aktualnyStan_->ustawIdEkranu(przycisk.ekran_);
	}
}

bool EkranMenu::dodajPrzycisk( const std::string& napis, StanGry::StanyGry stan, int numerSpecjalny, Identyfikator id ){
	tgui::Button::Ptr przycisk;
	unsigned int rozmiarTablicy = static_cast<unsigned int>( zdarzenia_.size() );
	if(!przycisk->load("widgets\\Black.conf")){
		Log::pobierzInstancje().loguj(Log::Error,"Nieudalo sie wczytac stylu kontrolki.");
		return false;
	}
	interfejs_.add(przycisk);
	przycisk->setSize(150,30);
	przycisk->setPosition( 630 , 30 + ( 40 * rozmiarTablicy ) );
	przycisk->setText(napis);
	przycisk->setTextSize(15);
	przycisk->bindCallback(std::bind(&EkranMenu::callback, std::ref(*this), rozmiarTablicy ), tgui::Button::LeftMouseClicked);
	zdarzenia_.push_back( Przycisk(stan,numerSpecjalny,id) );
	return true;
}

void EkranMenu::podlacz( sf::Window& ){
}
	
void EkranMenu::odlacz( sf::Window& ){
}

EkranMenu::Przycisk::Przycisk( StanGry::StanyGry stan , int numer , Identyfikator ekran)
	: stan_(stan), numer_(numer), ekran_(ekran)
{
}
