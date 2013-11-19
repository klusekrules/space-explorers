#include "OknoGry.h"
#include "MaszynaStanow.h"
#include <SFML\OpenGL.hpp>
#include "EkranStartowy.h"
#include "EkranMenu.h"
#include "definicjeWezlowXML.h"
#include "XmlBO.h"

#define GL_SHADING_LANGUAGE_VERSION       0x8B8C

OknoGry::OknoGry( bool wstrzymany )
	: Watek(wstrzymany)
{
}

OknoGry::~OknoGry(void)
{
}

StanGry::KrokCzasu OknoGry::obliczZmianeCzasu ( std::chrono::high_resolution_clock::time_point punkt ){
	static std::chrono::high_resolution_clock::time_point punktCzasu = std::chrono::high_resolution_clock::now();
	auto ret = punkt - punktCzasu;
	punktCzasu = punkt;
	return ret;
}

void OknoGry::wykonuj(){
	
	if(!inicjalizacja())
		return;
	
	//TODO: Przeniesc do inicjalizacji
	/*EkranMenu ekranMenu_(oknoGlowne_,nullptr);
	ekranMenu_.dodajPrzycisk("Nothing", StanGry::Menu, 1);
	ekranMenu_.dodajPrzycisk("Testowanie", StanGry::Testowanie, 1);
	ekranMenu_.dodajPrzycisk("Nothing", StanGry::Menu, 1);
	ekranMenu_.dodajPrzycisk("Nothing", StanGry::Menu, 1);
	ekranMenu_.dodajPrzycisk("Zamknij", StanGry::Wylacznie, 1);*/

	StanGry::KrokCzasu accumulator;
	oknoGlowne_.setVisible(true);

	while(oknoGlowne_.isOpen())
	{
		StanGry stan = MaszynaStanow::pobierzInstancje().pobierzStan();
		accumulator += obliczZmianeCzasu(std::chrono::high_resolution_clock::now());
		
		stan.ustawCzasKroku(accumulator);

		obslugaZdarzen( stan );
		uaktualnianie( stan );

		accumulator = stan.pobierzKrok();

		odmaluj();
		
		if(stan == StanGry::Wylacznie){
			oknoGlowne_.close();
		}

		MaszynaStanow::pobierzInstancje().scalStan(stan);
		
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

	oknoGlowne_.create(sf::VideoMode(800,500),"Space-Explorers",sf::Style::None);
	oknoGlowne_.setVisible(false);
	oknoGlowne_.setVerticalSyncEnabled(true);
	SetWindowLong(oknoGlowne_.getSystemHandle(), GWL_EXSTYLE, GetWindowLong(oknoGlowne_.getSystemHandle(), GWL_EXSTYLE) | WS_EX_LAYERED);
	if(!SetLayeredWindowAttributes(oknoGlowne_.getSystemHandle(), NULL, 0, LWA_ALPHA)){
		Log::pobierzInstancje().loguj(Log::Info,"Nie dziala przezroczstosc.");
	}
	//ekranStartowy_ = std::make_shared<EkranStartowy>(oknoGlowne_.getSystemHandle());
	TiXmlElement* wezel = nullptr;
	TiXmlDocument dokument;
	dokument.LoadFile("resource\\Menu.xml");
	wezel = dokument.RootElement();
	if(wezel){
		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_EKRAN_STARTOWY); element ; element = element->NextSiblingElement(WEZEL_XML_EKRAN_STARTOWY)){
			auto ptr = std::make_shared<EkranStartowy>(oknoGlowne_.getSystemHandle(),element);
			listaEkranow_.insert( std::make_pair(ptr->pobierzId(),ptr));
		}

		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_EKRAN_MENU); element ; element = element->NextSiblingElement(WEZEL_XML_EKRAN_MENU)){
			auto ptr = std::make_shared<EkranMenu>(oknoGlowne_,element);
			listaEkranow_.insert( std::make_pair(ptr->pobierzId(),ptr));
		}
	}

	
	if(!testShadera_.loadFromFile("resource\\simple.frag",sf::Shader::Type::Fragment))
		Log::pobierzInstancje().loguj(Log::Error,"Nie uda³o siê wczytaæ shadera");
	
	testShadera_.setParameter("texture", sf::Shader::CurrentTexture);
	
	
	return true;
}


void OknoGry::obslugaZdarzen( StanGry& stan ){

	sf::Event zdarzenie;
	// Obs³uga zdarzeñ
	while(oknoGlowne_.pollEvent(zdarzenie))
	{
		if(zdarzenie.type == sf::Event::EventType::KeyReleased){
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

		for( auto ekran : stosEkranow_)
			ekran->odbierz( stan, zdarzenie );
	}

}

void OknoGry::uaktualnianie( StanGry& stan ){
	static const StanGry::KrokCzasu krok(30);
	//Uaktualnianie okien
	StanGry::KrokCzasu accumulator = stan.pobierzKrok();
	while(accumulator > krok ){
		for( auto ekran : stosEkranow_)
			ekran->uaktualnij(stan);
		accumulator -=krok;
	}
	if(stan == StanGry::ZmianaEkranu){
		auto ptr = listaEkranow_[stan.pobierzIdEkranu()];
		if(ptr){
			stosEkranow_.clear();
			stosEkranow_.push_back(ptr);
			ptr->uaktualnij(stan);
		}
	}
	stan.ustawCzasKroku(accumulator);
}

void OknoGry::odmaluj(){
	//Odmalowanie okna
	static float balans = 0.0f;
	sf::RenderStates states;
	oknoGlowne_.clear(sf::Color(255,255,255,0));

	testShadera_.setParameter("time",balans+=0.001f);
	states.shader = &testShadera_;
							
	for( auto ekran : stosEkranow_)
		oknoGlowne_.draw(*ekran);
		
	oknoGlowne_.display();
}