#include "Przycisk.h"


Przycisk::Przycisk( const sf::FloatRect &obszar, const sf::String &napis, const sf::Color &tlo )	
	: ObiektInterfejsuUzytkownika(obszar), napis_(), zaznaczony_(false)
{
	ustawKolorTla(tlo);
	napis_.setString(napis);	
	wyrownajNapis();
}

Przycisk::Przycisk( const sf::FloatRect &obszar, const sf::String &napis, const sf::Texture &tekstura )
	: ObiektInterfejsuUzytkownika(obszar), napis_(), zaznaczony_(false)
{
	ustawTeksture(tekstura);
	napis_.setString(napis);	
	wyrownajNapis();
}


bool Przycisk::klikniecie( const sf::Event &zdarzenie ){
	return zaznaczony_ = !zaznaczony_;
}

void Przycisk::ustawCzcionke( const sf::Font &czcionka ){
	napis_.setFont(czcionka);
	wyrownajNapis();
}

void Przycisk::ustawRozmiarCzcionki( unsigned int rozmiar ){
	napis_.setCharacterSize(rozmiar);
	wyrownajNapis();
}

void Przycisk::wyrownajNapis(){
	sf::FloatRect textRect = napis_.getLocalBounds();
	napis_.setOrigin((textRect.width / 2) + textRect.left, ((textRect.height + textRect.top) / 2) + textRect.top );
	napis_.setPosition(obszar_.left + obszar_.width / 2 , obszar_.top + obszar_.height / 2 );
}

void Przycisk::dopasujRozmiarPrzyciskuDoTekstu(){
	sf::FloatRect textRect = napis_.getLocalBounds();
	sf::FloatRect pozycja = obszar_;
	pozycja.top += (obszar_.height - textRect.height - textRect.top)/2;
	pozycja.left += (obszar_.width - textRect.width - textRect.left)/2;
	pozycja.height = textRect.height + textRect.top;
	pozycja.width = textRect.width + textRect.left;
	ustawPozycje(pozycja);
	wyrownajNapis();
}

Przycisk::~Przycisk(void)
{
}

void Przycisk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect textRect = napis_.getGlobalBounds();
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(obszar_.left + obszar_.width / 2, obszar_.top)),
		sf::Vertex(sf::Vector2f(obszar_.left + obszar_.width / 2, obszar_.top + obszar_.height)),
		sf::Vertex(sf::Vector2f(obszar_.left , obszar_.top + obszar_.height / 2)),
		sf::Vertex(sf::Vector2f(obszar_.left + obszar_.width, obszar_.top + obszar_.height / 2)),
		sf::Vertex(sf::Vector2f(textRect.left,textRect.top)),
		sf::Vertex(sf::Vector2f(textRect.left+textRect.width,textRect.top+textRect.height))
	};
    // apply the entity's transform -- combine it with the one that was passed by the caller
	ObiektInterfejsuUzytkownika::draw(target,states);

    // apply the texture
	states.texture = &obrazTla_;

    // you may also override states.shader or states.blendMode if you want
	target.draw(line, 6, sf::Lines,states);
	target.draw(napis_,states);   
}