#pragma once
#include "stdafx.h"
#include "MaszynaStanow.h"

class EkranStartowy: 
	public sf::Drawable,
	public sf::Transformable
{
public:
	EkranStartowy(void);
	virtual ~EkranStartowy(void);

	void uaktualnij( MaszynaStanow::StanGry& );

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Texture obrazTla_;
	sf::Sprite tlo_;
	sf::Color kolor_;

	const MaszynaStanow::StanGry::KrokCzasu czasWlaczania_;
	MaszynaStanow::StanGry::KrokCzasu czasChwilowy_;
};

