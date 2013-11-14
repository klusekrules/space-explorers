#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"
#include <SFML\OpenGL.hpp>

#define GL_SHADING_LANGUAGE_VERSION       0x8B8C




MaszynaStanow::MaszynaStanow()
	: gui(),aktualnyStan_(StanyGry::Niezainicjalizowana,0,std::chrono::milliseconds(0))
{
	obrazTla_.loadFromFile("resource\\background.jpg");
	tlo_.setTexture(obrazTla_);
	czcionka_.loadFromFile("resource\\arial.ttf");
	gui.setGlobalFont(czcionka_);
	gui.add(button_,"Zamknij");
	if(!button_->load("widgets\\Black.conf")){
		aktualnyStan_.ustawStan( StanyGry::Wylacznie );
		return;
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
    button_->setPosition(270, 530);
    button_->setText("Zamknij");
	button_->bindCallback(tgui::Button::LeftMouseClicked);
	button_->setCallbackId(1);

	gui.add(chatbox_,"Log");
    chatbox_->load("widgets\\Black.conf");
    chatbox_->setSize(780, 510);
    chatbox_->setTextSize(15);
    chatbox_->setPosition(10, 10);
    chatbox_->addLine("Nacisnij dowolny klawisz aby rozpocz¹æ testy.", sf::Color::White);

	Log::pobierzInstancje().dodajGniazdoWyjsciowe([this](Log::TypLogow typ, const std::string& komunikat)->void{
		pobierzInstancje().dodajKomunikatLogow( typ, komunikat );
	});
    /*chatbox->addLine("Line 1", sf::Color::Red);
    chatbox->addLine("Line 2", sf::Color::Blue);
    chatbox->addLine("Line 3", sf::Color::Green);
    chatbox->addLine("Line 4", sf::Color::Yellow);
    chatbox->addLine("Line 5", sf::Color::Cyan);
    chatbox->addLine("Line 6", sf::Color::Magenta);*/
	//przycisk.dopasujRozmiarPrzyciskuDoTekstu();
}

void MaszynaStanow::dodajKomunikatLogow( Log::TypLogow typ, const std::string& komunikat ){
	string kopia(komunikat);
	kopia.pop_back();
	switch(typ){
	case Log::TypLogow::Debug: chatbox_->addLine(kopia,sf::Color::White); break;
	case Log::TypLogow::Info: chatbox_->addLine(kopia,sf::Color::Green); break;
	case Log::TypLogow::Warning: chatbox_->addLine(kopia,sf::Color::Yellow); break;
	case Log::TypLogow::Error: chatbox_->addLine(kopia,sf::Color::Red); break;
	default: chatbox_->addLine(kopia,sf::Color::White); break;
	}
}
MaszynaStanow::MaszynaStanow( const MaszynaStanow& o )
	: aktualnyStan_(o.aktualnyStan_)
{
}

MaszynaStanow::MaszynaStanow( MaszynaStanow&& o )
	: aktualnyStan_(o.aktualnyStan_)
{
}

MaszynaStanow& MaszynaStanow::operator=(const MaszynaStanow& o){
	aktualnyStan_ = o.aktualnyStan_;
	return *this;
}

MaszynaStanow::~MaszynaStanow(){
}

MaszynaStanow::StanGry& MaszynaStanow::pobierzStan(){
	return aktualnyStan_;
}

MaszynaStanow& MaszynaStanow::pobierzInstancje(){
	static MaszynaStanow maszyna;
	return maszyna;
}

void MaszynaStanow::start(){
	if(aktualnyStan_ != StanyGry::Niezainicjalizowana)
		return;

	oknoGlowne_.create(sf::VideoMode(800,600),"Space-Explorers");
	gui.setWindow(oknoGlowne_);
	aktualnyStan_.ustawStan( StanyGry::EkranStartowy );

	while(aktualnyStan_ != StanyGry::Wylacznie)
	{
		petlaGlowna();
	}

	oknoGlowne_.close();
}

void MaszynaStanow::petlaGlowna(){
	switch(aktualnyStan_.pobierzStan())
	{
	case StanyGry::EkranStartowy:
		pokazEkranStartowy();
		break;
	case StanyGry::Testowanie :	
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
		aktualnyStan_.ustawStan( StanyGry::EkranStartowy );
		break;
	default:
		break;
	}
}

void MaszynaStanow::pokazEkranStartowy(){
	sf::Event zdarzenie;
	sf::RenderStates states;
	sf::Clock zegar;
	float balans = 0.0f;
	while(true)
	{
		
		while(oknoGlowne_.pollEvent(zdarzenie))
		{
			if(zdarzenie.type == sf::Event::EventType::KeyReleased)
			{
				aktualnyStan_.ustawStan( StanyGry::Testowanie );
				return;
			}
			
			if(zdarzenie.type == sf::Event::EventType::Closed){
				aktualnyStan_.ustawStan( StanyGry::Wylacznie );
				return;
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
				aktualnyStan_.ustawStan( StanyGry::Wylacznie );
				return;
			}
		}
		testShadera_.setParameter("time",balans+=0.001f);
		states.shader = &testShadera_;
		oknoGlowne_.draw(tlo_,states);
		gui.draw();
		oknoGlowne_.display();
	}
}
