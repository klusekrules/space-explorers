#pragma once
#include "stdafx.h"
#include "EkranSzablon.h"

class EkranMenu:
	public EkranSzablon
{
public:
	EkranMenu( sf::RenderWindow& okno );
	virtual ~EkranMenu(void);

	void uaktualnij( StanGry& stan ) override;

	void odbierz( StanGry& stan, const sf::Event& zdarzenie ) override;

	bool dodajPrzycisk( const std::string&, StanGry::StanyGry stan, int numerSpecjalny );

	virtual void podlacz( sf::Window& );
	
	virtual void odlacz( sf::Window& );

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void callback( int id );

private:
	sf::Texture obrazTla_;
	sf::Sprite tlo_;
	sf::Texture obrazLogo_;
	sf::Sprite tloLogo_;
	mutable tgui::Gui interfejs_;
	StanGry* aktualnyStan_;
	sf::Font czcionka_;
	std::vector< std::pair< StanGry::StanyGry , int > > zdarzenia_;
};

