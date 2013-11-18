#include "EkranMenu.h"
#include "Logger\Log.h"

EkranMenu::EkranMenu(sf::RenderWindow& okno)
	: aktualnyStan_(nullptr), interfejs_(okno)
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
}

EkranMenu::~EkranMenu()
{
}

void EkranMenu::uaktualnij( StanGry& stan ){
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
		auto para = zdarzenia_.at(id);
		aktualnyStan_->ustawNastepnyStan(para.first);
		aktualnyStan_->ustawNumerSpecjalny(para.second);
	}
}

bool EkranMenu::dodajPrzycisk( const std::string& napis, StanGry::StanyGry stan, int numerSpecjalny ){
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
	zdarzenia_.push_back( std::make_pair( stan, numerSpecjalny ) );
}

void EkranMenu::podlacz( sf::Window& ){
}
	
void EkranMenu::odlacz( sf::Window& ){
}
