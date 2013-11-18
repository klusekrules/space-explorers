#include "EkranStartowy.h"
#include <Windows.h>

EkranStartowy::EkranStartowy( const sf::WindowHandle& uchwyt )
	: kolor_(255,255,255,0),czasWlaczania_(3000),czasTrwalosci_(2000), czasChwilowy_(0), okno_(uchwyt)
{
	obrazTla_.loadFromFile("resource\\Space_start_screen.png");
	tlo_.setTexture(obrazTla_);
	tlo_.setColor(kolor_);
}


EkranStartowy::~EkranStartowy(void)
{
}

void EkranStartowy::uaktualnij( StanGry& stan ){
	czasChwilowy_+=stan.pobierzKrok();
	if( czasChwilowy_ >= czasWlaczania_){
		kolor_.a=255;
		SetLayeredWindowAttributes(okno_, NULL, kolor_.a, LWA_ALPHA);
		if( czasChwilowy_ >= czasWlaczania_ + czasTrwalosci_)
			stan.ustawNastepnyStan(StanGry::StanyGry::MenuGlowne);
	}else{
		kolor_.a=static_cast<sf::Uint8>(255.f*(czasChwilowy_/czasWlaczania_));
		SetLayeredWindowAttributes(okno_, NULL, kolor_.a, LWA_ALPHA);
	}
	tlo_.setColor(kolor_);
}

void EkranStartowy::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	
	states.transform *= getTransform();
	target.draw(tlo_, states);
}