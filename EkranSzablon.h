#pragma once
#include "stdafx.h"
#include "Stan.h"

class EkranSzablon: 
	public sf::Drawable,
	public sf::Transformable
{
public:
	EkranSzablon( XmlBO::ElementWezla wezel );

	virtual ~EkranSzablon(void) = default;
	
	virtual void uaktualnij( Stan& stan );

	virtual void odbierz( Stan& stan, const sf::Event& zdarzenie );

	virtual void podlacz( sf::RenderWindow& );
	
	virtual void odlacz( sf::RenderWindow& );

	const STyp::Identyfikator& pobierzId() const;

protected:

	void callback( const tgui::Callback& callback, unsigned int funkcja );

	bool wczytajDaneKontrolki(XmlBO::ElementWezla wezel, tgui::Widget::Ptr kontrolka);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	STyp::Identyfikator id_;
	STyp::Identyfikator idStanu_;
	mutable tgui::Gui interfejs_;
};

