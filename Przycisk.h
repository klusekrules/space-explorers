#pragma once
#include <SFML\Graphics.hpp>
#include "ObiektInterfejsuUzytkownika.h"

class Przycisk : 
	public ObiektInterfejsuUzytkownika
{
public:
	
	Przycisk( const sf::FloatRect &obszar, const sf::String &napis, const sf::Color &tlo );
	Przycisk( const sf::FloatRect &obszar, const sf::String &napis, const sf::Texture &tekstura );
	virtual ~Przycisk();
	

	//Zmiana parametrow
	void ustawCzcionke( const sf::Font &czcionka );
	void ustawRozmiarCzcionki( unsigned int rozmiar );
	void dopasujRozmiarPrzyciskuDoTekstu();
	//Zdarzenia
	bool klikniecie( const sf::Event &zdarzenie );

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool zaznaczony_;
	sf::Text napis_;
	void wyrownajNapis();
};

