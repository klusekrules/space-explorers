#include "ObiektInterfejsuUzytkownika.h"


ObiektInterfejsuUzytkownika::ObiektInterfejsuUzytkownika( const sf::FloatRect& obszar )
{
	ustawPozycje(obszar);
	tlo_.setCornerPointCount(40);
	tlo_.setCornersRadius(15);
}

ObiektInterfejsuUzytkownika::~ObiektInterfejsuUzytkownika(void)
{
}

bool ObiektInterfejsuUzytkownika::czyZawiera( const struct sf::Event::MouseMoveEvent punkt ) const{
	return obszar_.contains(static_cast<float>(punkt.x),static_cast<float>(punkt.y));
}

bool ObiektInterfejsuUzytkownika::czyZawiera( const sf::Vector2i &punkt ) const{
	return obszar_.contains(static_cast<float>(punkt.x),static_cast<float>(punkt.y));
}

void ObiektInterfejsuUzytkownika::ustawPozycje(float x, float y){
	tlo_.setPosition(x,y);
	obszar_ = tlo_.getGlobalBounds();
}

void ObiektInterfejsuUzytkownika::ustawPozycje(const sf::FloatRect& pozycja){
	tlo_.setPosition(pozycja.left,pozycja.top);
	tlo_.setSize(sf::Vector2f(pozycja.width,pozycja.height));
	obszar_ = pozycja;
}

void ObiektInterfejsuUzytkownika::ustawTeksture(const sf::Texture& tlo){
	obrazTla_ = tlo;
	tlo_.setTexture(&obrazTla_);
}

void ObiektInterfejsuUzytkownika::ustawKolorTla(const sf::Color& kolor){
	tlo_.setFillColor(kolor);
}

void ObiektInterfejsuUzytkownika::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(tlo_,states);
}

