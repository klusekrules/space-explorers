#include "EkranStartowy.h"


EkranStartowy::EkranStartowy(void)
	: kolor_(255,255,255,0),czasWlaczania_(3000), czasChwilowy_(0)
{
	obrazTla_.loadFromFile("resource\\Space_start_screen.png");
	tlo_.setTexture(obrazTla_);
	tlo_.setColor(kolor_);
}


EkranStartowy::~EkranStartowy(void)
{
}

void EkranStartowy::uaktualnij( MaszynaStanow::StanGry& stan ){
	czasChwilowy_+=stan.pobierzKrok();
	if( czasChwilowy_ >= czasWlaczania_){
		kolor_.a=255;
		stan.ustawNastepnyStan(MaszynaStanow::StanyGry::MenuGlowne);
	}else{
		kolor_.a=static_cast<sf::Uint8>(255.f*(czasChwilowy_/czasWlaczania_));
	}
	tlo_.setColor(kolor_);
}

void EkranStartowy::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	
	states.transform *= getTransform();
	target.draw(tlo_, states);
}