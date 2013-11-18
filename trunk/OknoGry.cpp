#include "OknoGry.h"
#include "MaszynaStanow.h"
#include <SFML\OpenGL.hpp>
#include "EkranStartowy.h"
#include "EkranMenu.h"

#define GL_SHADING_LANGUAGE_VERSION       0x8B8C

OknoGry::OknoGry( bool wstrzymany )
	: Watek(wstrzymany)
{
}

OknoGry::~OknoGry(void)
{
}

void OknoGry::wykonuj(){
	
	if(!inicjalizacja())
		return;
	
	//TODO: Przeniesc do inicjalizacji
	EkranStartowy ekranStartowy_(oknoGlowne_.getSystemHandle());
	EkranMenu ekranMenu_(oknoGlowne_);
	ekranMenu_.dodajPrzycisk("Nothing", StanGry::MenuGlowne, 1);
	ekranMenu_.dodajPrzycisk("Testowanie", StanGry::Testowanie, 1);
	ekranMenu_.dodajPrzycisk("Nothing", StanGry::MenuGlowne, 1);
	ekranMenu_.dodajPrzycisk("Nothing", StanGry::MenuGlowne, 1);
	ekranMenu_.dodajPrzycisk("Zamknij", StanGry::Wylacznie, 1);
	EkranSzablon* ptr = nullptr;

	sf::Event zdarzenie;
	sf::RenderStates states;

	std::chrono::high_resolution_clock::time_point punktCzasu = std::chrono::high_resolution_clock::now();

	StanGry::KrokCzasu dt;
	StanGry::KrokCzasu accumulator;
	const StanGry::KrokCzasu krok(30);
	const StanGry::KrokCzasu maxAccTime(1000);

	StanGry& stan= MaszynaStanow::pobierzInstancje().pobierzStan();
	stan.ustawCzasKroku(krok);

	oknoGlowne_.setVisible(true);
	float balans = 0.0f;
	while(oknoGlowne_.isOpen())
	{
		//TODO: Do przeprojektowania
		if(stan != StanGry::EkranStartowy){

			ptr = &ekranMenu_;
		}else{
			ptr = &ekranStartowy_;
		}

		//Wylacz okno je¿eli odkryto odpowiadaj¹cy stan
		if(stan == StanGry::Wylacznie){
			oknoGlowne_.close();
		}
		
		//Pomiar czasu
		std::chrono::high_resolution_clock::time_point punkt = std::chrono::high_resolution_clock::now();
		accumulator += punkt - punktCzasu;
		punktCzasu = punkt;

		// Obs³uga zdarzeñ
		while(oknoGlowne_.pollEvent(zdarzenie))
		{
			if(zdarzenie.type == sf::Event::EventType::KeyReleased)
			{
				stan.ustawNastepnyStan( StanGry::StanyGry::Testowanie );
			}
			
			if(zdarzenie.type == sf::Event::EventType::Closed){
				stan.ustawNastepnyStan( StanGry::StanyGry::Wylacznie );
				oknoGlowne_.close();
			}

			if (zdarzenie.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, static_cast<float>(zdarzenie.size.width), static_cast<float>(zdarzenie.size.height));
				oknoGlowne_.setView(sf::View(visibleArea));
			}

			if(ptr)
				ptr->odbierz( stan, zdarzenie );
		}

		//Uaktualnianie okien
		while(accumulator > krok ){
			if(ptr)
				ptr->uaktualnij(stan);
			accumulator -=krok;
		}

		//Odmalowanie okna
		oknoGlowne_.clear(sf::Color(255,255,255,0));

		testShadera_.setParameter("time",balans+=0.001f);
		states.shader = &testShadera_;
							
		if(ptr)
			oknoGlowne_.draw(*ptr);
		
		oknoGlowne_.display();


	}
	
}

bool OknoGry::inicjalizacja( ){
	
	if(sf::Shader::isAvailable())
		Log::pobierzInstancje().loguj(Log::Info,"Shadery dostepne");
	else
		Log::pobierzInstancje().loguj(Log::Info,"Shadery niedostepne");

	char* p = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	Log::pobierzInstancje().loguj(Log::Info,p?p:"");
	p = (char*)glGetString(GL_VERSION);
	Log::pobierzInstancje().loguj(Log::Info,p?p:"");
	p = (char*)glGetString(GL_VENDOR);
	Log::pobierzInstancje().loguj(Log::Info,p?p:"");

	if(!testShadera_.loadFromFile("resource\\simple.frag",sf::Shader::Type::Fragment))
		Log::pobierzInstancje().loguj(Log::Error,"Nie uda³o siê wczytaæ shadera");
	
	testShadera_.setParameter("texture", sf::Shader::CurrentTexture);
	
	oknoGlowne_.create(sf::VideoMode(800,500),"Space-Explorers",sf::Style::None);
	oknoGlowne_.setVerticalSyncEnabled(true);
	oknoGlowne_.setVisible(false);
	SetWindowLong(oknoGlowne_.getSystemHandle(), GWL_EXSTYLE, GetWindowLong(oknoGlowne_.getSystemHandle(), GWL_EXSTYLE) | WS_EX_LAYERED);
	if(!SetLayeredWindowAttributes(oknoGlowne_.getSystemHandle(), NULL, 0, LWA_ALPHA)){
		Log::pobierzInstancje().loguj(Log::Info,"Nie dziala przezroczstosc.");
	}
	return true;
}
