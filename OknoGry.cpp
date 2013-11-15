#include "OknoGry.h"
#include "MaszynaStanow.h"
#include <SFML\OpenGL.hpp>
#include "EkranStartowy.h"

#define GL_SHADING_LANGUAGE_VERSION       0x8B8C

OknoGry::OknoGry( bool wstrzymany )
	: Watek(wstrzymany)
{
}


OknoGry::~OknoGry(void)
{
}


void OknoGry::wykonuj(){
	
	EkranStartowy ekranStartowy_;
	tgui::Gui gui;
	if(!inicjalizacja(gui))
		return;

	sf::Event zdarzenie;
	sf::RenderStates states;

	std::chrono::high_resolution_clock::time_point punktCzasu = std::chrono::high_resolution_clock::now();

	MaszynaStanow::StanGry::KrokCzasu dt;
	MaszynaStanow::StanGry::KrokCzasu accumulator;
	const MaszynaStanow::StanGry::KrokCzasu krok(30);
	const MaszynaStanow::StanGry::KrokCzasu maxAccTime(1000);

	MaszynaStanow::StanGry& stan= MaszynaStanow::pobierzInstancje().pobierzStan();
	stan.ustawCzasKroku(krok);

	float balans = 0.0f;
	while(oknoGlowne_.isOpen())
	{
		std::chrono::high_resolution_clock::time_point punkt = std::chrono::high_resolution_clock::now();
		accumulator += punkt - punktCzasu;
		punktCzasu = punkt;

		while(oknoGlowne_.pollEvent(zdarzenie))
		{
			if(zdarzenie.type == sf::Event::EventType::KeyReleased)
			{
				stan.ustawNastepnyStan( MaszynaStanow::StanyGry::Testowanie );
			}
			
			if(zdarzenie.type == sf::Event::EventType::Closed){
				stan.ustawNastepnyStan( MaszynaStanow::StanyGry::Wylacznie );
				oknoGlowne_.close();
			}

			if (zdarzenie.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, static_cast<float>(zdarzenie.size.width), static_cast<float>(zdarzenie.size.height));
				oknoGlowne_.setView(sf::View(visibleArea));
			}

			gui.handleEvent(zdarzenie);
		}

		tgui::Callback callback;
		while (gui.pollCallback(callback))
		{
			if (callback.id == 1)
			{
				stan.ustawNastepnyStan( MaszynaStanow::StanyGry::Wylacznie );
				oknoGlowne_.close();
			}
		}

		while(accumulator > krok ){
			ekranStartowy_.uaktualnij(stan);
			accumulator -=krok;
		}

		if(stan.pobierzStan() != MaszynaStanow::EkranStartowy){
			testShadera_.setParameter("time",balans+=0.001f);
			states.shader = &testShadera_;
			oknoGlowne_.draw(tlo_,states);
			gui.draw();
		}else{
			oknoGlowne_.draw(ekranStartowy_);
		}
		oknoGlowne_.display();
	}
	
}

bool OknoGry::inicjalizacja( tgui::Gui& gui ){

	obrazTla_.loadFromFile("resource\\Space_start_screen.png");
	tlo_.setTexture(obrazTla_);
	czcionka_.loadFromFile("resource\\arial.ttf");
	gui.setGlobalFont(czcionka_);
	gui.add (chatbox_,"Log");
	gui.add (button_,"Zamknij");

	if(!button_->load("widgets\\Black.conf")){
		MaszynaStanow::pobierzInstancje().pobierzStan().ustawStan( MaszynaStanow::StanyGry::Wylacznie );
		return false;
	}

	Log::pobierzInstancje().loguj(Log::Info,(char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	Log::pobierzInstancje().loguj(Log::Info,(char*)glGetString(GL_VERSION));
	Log::pobierzInstancje().loguj(Log::Info,(char*)glGetString(GL_VENDOR));

	if(sf::Shader::isAvailable())
		Log::pobierzInstancje().loguj(Log::Info,"Shadery dostepne");
	if(!testShadera_.loadFromFile("resource\\simple.frag",sf::Shader::Type::Fragment))
		Log::pobierzInstancje().loguj(Log::Error,"Nie uda³o siê wczytaæ shadera");
	
	testShadera_.setParameter("texture", sf::Shader::CurrentTexture);
	
	button_->setSize(260, 60);
    button_->setPosition(270, 430);
    button_->setText("Zamknij");
	button_->bindCallback(tgui::Button::LeftMouseClicked);
	button_->setCallbackId(1);

    chatbox_->load("widgets\\Black.conf");
    chatbox_->setSize(780, 410);
    chatbox_->setTextSize(15);
    chatbox_->setPosition(10, 10);
    chatbox_->addLine("Nacisnij dowolny klawisz aby rozpocz¹æ testy.", sf::Color::White);

	Log::pobierzInstancje().dodajGniazdoWyjsciowe([this](Log::TypLogow typ, const std::string& komunikat)->void{
		this->dodajKomunikatLogow( typ, komunikat );
	});

	oknoGlowne_.create(sf::VideoMode(800,500),"Space-Explorers");
	gui.setWindow(oknoGlowne_);
	
	return true;
}


void OknoGry::dodajKomunikatLogow( Log::TypLogow typ, const std::string& komunikat ){
	std::string kopia(komunikat);
	kopia.pop_back();

	switch(typ){
	case Log::TypLogow::Debug: chatbox_->addLine(kopia,sf::Color::White); break;
	case Log::TypLogow::Info: chatbox_->addLine(kopia,sf::Color::Green); break;
	case Log::TypLogow::Warning: chatbox_->addLine(kopia,sf::Color::Yellow); break;
	case Log::TypLogow::Error: chatbox_->addLine(kopia,sf::Color::Red); break;
	default: chatbox_->addLine(kopia,sf::Color::White); break;
	}
}
