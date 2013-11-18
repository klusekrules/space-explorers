#pragma once
#include "stdafx.h"
#include "MaszynaStanow.h"

class EkranSzablon: 
	public sf::Drawable,
	public sf::Transformable
{
public:
	EkranSzablon(void);
	virtual ~EkranSzablon(void);
	
	virtual void uaktualnij( StanGry& stan );

	virtual void odbierz( StanGry& stan, const sf::Event& zdarzenie );

	virtual void podlacz( sf::Window& );
	
	virtual void odlacz( sf::Window& );

};

