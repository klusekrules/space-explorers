#pragma once
#include "stdafx.h"

class ObiektInterfejsuUzytkownika : 
	public sf::Drawable, 
	public sf::Transformable
{
public:
	ObiektInterfejsuUzytkownika( const sf::FloatRect& );
	virtual ~ObiektInterfejsuUzytkownika();
	
	virtual void ustawPozycje(float x, float y);
	virtual void ustawPozycje(const sf::FloatRect& pozycja);
	virtual void ustawTeksture(const sf::Texture& tlo);
	virtual void ustawKolorTla(const sf::Color& kolor);

	bool czyZawiera( const struct sf::Event::MouseMoveEvent punkt ) const;
	bool czyZawiera( const sf::Vector2i &punkt ) const;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RoundedRectangleShape tlo_;
	sf::Texture obrazTla_;
	sf::FloatRect obszar_;
};

