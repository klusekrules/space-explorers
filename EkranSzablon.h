#pragma once
#include "stdafx.h"
#include "Stan.h"
#include "Identyfikator.h"

class EkranSzablon: 
	public sf::Drawable,
	public sf::Transformable
{
public:
	EkranSzablon( tinyxml2::XMLElement* wezel );

	virtual ~EkranSzablon(void);
	
	virtual void uaktualnij( Stan& stan );

	virtual void odbierz( Stan& stan, const sf::Event& zdarzenie );

	virtual void podlacz( sf::RenderWindow& );
	
	virtual void odlacz( sf::RenderWindow& );

	const Identyfikator& pobierzId() const;

protected:

	void callback( const tgui::Callback& callback, unsigned int funkcja );

	bool wczytajDaneKontrolki( tinyxml2::XMLElement* wezel , tgui::Widget::Ptr kontrolka );

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Identyfikator id_;
	Identyfikator idStanu_;
	mutable tgui::Gui interfejs_;
};

