#pragma once
#include "stdafx.h"
#include "Watek.h"
#include "Logger\Log.h"

class OknoGry :
	public Watek
{
public:
	OknoGry( bool wstrzymany );
	virtual ~OknoGry(void);
private:
	sf::RenderWindow oknoGlowne_;
	tgui::Gui gui_;

	sf::Texture obrazTla_;
	sf::Sprite tlo_;
	sf::Font czcionka_;
	sf::Shader testShadera_;
	
	tgui::ChatBox::Ptr chatbox_;
	tgui::Button::Ptr button_;

	void OknoGry::dodajKomunikatLogow( Log::TypLogow typ, const std::string& komunikat );

	void wykonuj() override;
	bool inicjalizacja( tgui::Gui& );
};

