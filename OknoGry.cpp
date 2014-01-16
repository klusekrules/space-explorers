#include "OknoGry.h"
#include "MaszynaStanow.h"
#include <SFML\OpenGL.hpp>
#include "EkranStartowy.h"
#include "definicjeWezlowXML.h"
#include "XmlBO.h"

#define GL_SHADING_LANGUAGE_VERSION       0x8B8C

OknoGry::OknoGry( bool wstrzymany )
	: Watek(wstrzymany)
{
	przetwarzanie_ = false;
	inicjalizacjaWynik_ = inicjalizacja_.get_future();
}

bool OknoGry::zainicjalizowe(){
	std::lock_guard<std::mutex> blokada(mutexInicjalizacja_);
	return przetwarzanie_;
}

OknoGry::~OknoGry(void)
{
}

bool OknoGry::czekajNaInicjalizacje(){
	inicjalizacjaWynik_.wait();
	return inicjalizacjaWynik_.get();
}

void OknoGry::zatrzymajPoInicjalizacji(){
	mutexUruchom_.lock();
}

void OknoGry::uruchom(){
	mutexUruchom_.try_lock();
	mutexUruchom_.unlock();
}

OknoGry::EkranPtr OknoGry::pobierzEkran( const Identyfikator& ekranId ){
	auto iter = listaEkranow_.find(ekranId);
	if(iter != listaEkranow_.end()){
		return iter->second;
	}
	return nullptr;
}

Stan::KrokCzasu OknoGry::obliczZmianeCzasu ( std::chrono::high_resolution_clock::time_point punkt ){
	static std::chrono::high_resolution_clock::time_point punktCzasu = std::chrono::high_resolution_clock::now();
	auto ret = punkt - punktCzasu;
	punktCzasu = punkt;
	return ret;
}

void OknoGry::wykonuj(){
	try{
		if(!inicjalizacja()){
			inicjalizacja_.set_value(false);
			Log::pobierzInstancje().loguj(Log::Error,"B��d inicjalizacji.");
			return;
		}
	}catch(...){
		inicjalizacja_.set_value(false);
		throw;
	}
	std::lock_guard<std::mutex> blokada(mutexUruchom_);

	Stan::KrokCzasu accumulator;
	oknoGlowne_.setVisible(true);

	while(przetwarzanie_)
	{
		Stan stan = MaszynaStanow::pobierzInstancje().pobierzStan(stosEkranow_);
		accumulator += obliczZmianeCzasu(std::chrono::high_resolution_clock::now());

		stan.dt_ = accumulator;

		obslugaZdarzen( stan );
		uaktualnianie( stan );

		accumulator = stan.dt_;

		odmaluj();
	}
	oknoGlowne_.close();
}

bool OknoGry::inicjalizacja( ){
	std::lock_guard<std::mutex> blokada(mutexInicjalizacja_);
	przetwarzanie_ = false;
	logujInfo();

	oknoGlowne_.create(sf::VideoMode(800,500),"Space-Explorers",sf::Style::None);
	oknoGlowne_.setVisible(false);
	oknoGlowne_.setVerticalSyncEnabled(true);

	oknoGlowne_.setVisible(false);
	
	SetWindowLong(oknoGlowne_.getSystemHandle(), GWL_EXSTYLE, GetWindowLong(oknoGlowne_.getSystemHandle(), GWL_EXSTYLE) | WS_EX_LAYERED);
	if(!SetLayeredWindowAttributes(oknoGlowne_.getSystemHandle(), NULL, 0, LWA_ALPHA)){
		Log::pobierzInstancje().loguj(Log::Info,"Nie dziala przezroczstosc.");
	}

	if(!wczytajEkrany()){
		Log::pobierzInstancje().loguj(Log::Error,"Nieuda�o si� wczyta� ekran�w.");
		return false;
	}
	/*
	if(!testShadera_.loadFromFile("resource\\simple.frag",sf::Shader::Type::Fragment))
		Log::pobierzInstancje().loguj(Log::Error,"Nie uda�o si� wczyta� shadera");
	
	testShadera_.setParameter("texture", sf::Shader::CurrentTexture);*/
	inicjalizacja_.set_value(true);
	przetwarzanie_ = true;
	return true;
}

void OknoGry::logujInfo(){
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
}

bool OknoGry::wczytajEkrany(){
	tinyxml2::XMLDocument dokument;
	dokument.LoadFile("resource\\Menu.xml");
	tinyxml2::XMLElement* wezel = dokument.RootElement();
	if(wezel){
		for(tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_EKRAN_STARTOWY); element ; element = element->NextSiblingElement(WEZEL_XML_EKRAN_STARTOWY)){
			auto ptr = std::make_shared<EkranStartowy>(oknoGlowne_,element);
			listaEkranow_.insert( std::make_pair(ptr->pobierzId(),ptr));
		}
		for(tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_EKRAN); element ; element = element->NextSiblingElement(WEZEL_XML_EKRAN)){
			auto ptr = std::make_shared<EkranSzablon>(element);
			ptr->podlacz(oknoGlowne_);
			listaEkranow_.insert( std::make_pair(ptr->pobierzId(),ptr));
		}
	}
	return !listaEkranow_.empty();
}


void OknoGry::obslugaZdarzen( Stan& stan ){
	sf::Event zdarzenie;
	while(oknoGlowne_.pollEvent(zdarzenie))
	{
		if(zdarzenie.type == sf::Event::EventType::Closed){
			MaszynaStanow::pobierzInstancje().inicjujZamykanie();
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

void OknoGry::uaktualnianie( Stan& stan ){
	static const Stan::KrokCzasu krok(30);
	Stan::KrokCzasu accumulator = stan.dt_;
	while(accumulator > krok ){
		for( auto ekran : stosEkranow_)
			ekran->uaktualnij(stan);
		accumulator -=krok;
	}
	stan.dt_ = accumulator;
}

void OknoGry::odmaluj(){
	static float balans = 0.0f;
	sf::RenderStates states;
	oknoGlowne_.clear(sf::Color(255,255,255,0));

	/*testShadera_.setParameter("time",balans+=0.001f);
	states.shader = &testShadera_;*/
							
	for( auto ekran : stosEkranow_)
		oknoGlowne_.draw(*ekran);
	
	oknoGlowne_.display();
}

void OknoGry::zakmnij(){
	przetwarzanie_=false;
}