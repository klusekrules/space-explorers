#pragma once
#include "stdafx.h"
#include "StanGry.h"
#include "Identyfikator.h"
#include "parser\ticpp.h"

class EkranSzablon: 
	public sf::Drawable,
	public sf::Transformable
{
public:
	EkranSzablon( TiXmlElement* wezel );

	virtual ~EkranSzablon(void);
	
	virtual void uaktualnij( StanGry& stan );

	virtual void odbierz( StanGry& stan, const sf::Event& zdarzenie );

	virtual void podlacz( sf::Window& );
	
	virtual void odlacz( sf::Window& );

	const Identyfikator& pobierzId() const;

protected:
	Identyfikator id_;
	StanGry::StanyGry stanWejsciowy_;
	//int numerWejsciowy_;
};

