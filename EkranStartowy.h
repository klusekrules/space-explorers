#pragma once
#include "stdafx.h"
#include "EkranSzablon.h"

class EkranStartowy: 
	public EkranSzablon
{
public:
	EkranStartowy( const sf::WindowHandle& );
	virtual ~EkranStartowy(void);

	void uaktualnij( StanGry& stan ) override;
	
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Texture obrazTla_;
	sf::Sprite tlo_;
	sf::Color kolor_;
	sf::WindowHandle okno_;
	const StanGry::KrokCzasu czasWlaczania_;
	const StanGry::KrokCzasu czasTrwalosci_;
	StanGry::KrokCzasu czasChwilowy_;
};

