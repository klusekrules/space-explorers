#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"

MaszynaStanow::MaszynaStanow()
	: aktualnyStan_(StanyGry::Niezainicjalizowana,0,std::chrono::milliseconds(0))
{
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
		aktualnyStan_.ustawStan( StanyGry::Wylacznie );
		break;
	default:
		break;
	}
}

void MaszynaStanow::pokazEkranStartowy(){

	sf::Texture obrazTla;
	obrazTla.loadFromFile("resource\\background.jpg");
	sf::Sprite tlo(obrazTla);
	sf::Font czcionka;
	czcionka.loadFromFile("resource\\arial.ttf");
	gui.setGlobalFont(czcionka);
	tgui::Button::Ptr button(gui);
	if(!button->load("widgets\\Black.conf")){
		aktualnyStan_.ustawStan( StanyGry::Wylacznie );
		return;
	}
    button->setSize(260, 60);
    button->setPosition(270, 530);
    button->setText("Zamknij");
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(1);

	tgui::ChatBox::Ptr chatbox(gui);
    chatbox->load("widgets\\Black.conf");
    chatbox->setSize(780, 510);
    chatbox->setTextSize(15);
    chatbox->setPosition(10, 10);
    chatbox->addLine("Nacisnij dowolny klawisz aby rozpocz¹æ testy.", sf::Color::White);
    chatbox->addLine("Line 1", sf::Color::Red);
    chatbox->addLine("Line 2", sf::Color::Blue);
    chatbox->addLine("Line 3", sf::Color::Green);
    chatbox->addLine("Line 4", sf::Color::Yellow);
    chatbox->addLine("Line 5", sf::Color::Cyan);
    chatbox->addLine("Line 6", sf::Color::Magenta);
	//przycisk.dopasujRozmiarPrzyciskuDoTekstu();
	sf::Event zdarzenie;
	while(true)
	{
		while(oknoGlowne_.pollEvent(zdarzenie))
		{
			if(zdarzenie.type == sf::Event::EventType::KeyPressed )
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
				// update the view to the new size of the window
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

		oknoGlowne_.draw(tlo);
		gui.draw();
		oknoGlowne_.display();
	}
}

/*
#pragma once
#include <SFML/Graphics.hpp>
#include "Przycisk.h"

class GlowneOkno :
	public sf::Drawable,
	public sf::Transformable
{
public:
	GlowneOkno(void);
	void setEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);
	void loop();
	virtual ~GlowneOkno(void);

private:

	sf::RenderWindow okno_;
	sf::Clock zegar_;
	sf::Texture teksturaTla_;
	sf::Sprite tlo_;
	sf::Font czcionka_;
	sf::Text tekst_;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// przyklad

	struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(unsigned int index);

    std::vector<Particle> v_czastki_;
    sf::VertexArray v_obiekty_;
    sf::Time m_czasZycia_;
    sf::Vector2f m_pozycja_;	
	sf::Vector2f m_pozycja_prev_;
	//sf::Vector2f m_vector_;
	Przycisk przycisk_;
	float kat;
};

#include "GlowneOkno.h"


GlowneOkno::GlowneOkno(void)
	: okno_(sf::VideoMode(800,600),"Space-Explorers"),
	v_czastki_( 1000 ), v_obiekty_( sf::Points , 1000), m_czasZycia_(sf::seconds(3)), m_pozycja_ (1,0), m_pozycja_prev_(0,0), kat(0),
	przycisk_(sf::FloatRect(300,10,300,100),"Zamknij",sf::Color(150, 50, 50))
{
	okno_.setVerticalSyncEnabled(true);
	czcionka_.loadFromFile("resource\\arial.ttf");
	teksturaTla_.loadFromFile("resource\\background.jpg");
	tekst_.setFont(czcionka_);
	przycisk_.ustawCzcionke(czcionka_);
	przycisk_.ustawRozmiarCzcionki(18);
	tekst_.setString(L"Hello World");
	tekst_.setColor(sf::Color::Red);
	tekst_.setStyle(sf::Text::Style::Regular);
	tlo_.setTexture(teksturaTla_);
	przycisk_.dopasujRozmiarPrzyciskuDoTekstu();
	//tlo_.setColor(sf::Color(255,255,255,128));
}

void GlowneOkno::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(tlo_);
	target.draw(tekst_);
	target.draw(przycisk_);
	target.draw(v_obiekty_, states);
}

void GlowneOkno::loop(){

	while(okno_.isOpen()){
		sf::Event zdarzenie;
		sf::Vector2i mouse = sf::Mouse::getPosition(okno_);
		while( okno_.pollEvent(zdarzenie) ){
			if(zdarzenie.type == sf::Event::Closed ){
				okno_.close();
			}
			if (zdarzenie.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, static_cast<float>(zdarzenie.size.width), static_cast<float>(zdarzenie.size.height));
				okno_.setView(sf::View(visibleArea));
			}
			if(zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
			{
				//If we clicked within the exit rectangle, then exit!
				if(przycisk_.czyZawiera(mouse))
				{
					przycisk_.klikniecie(zdarzenie);
					okno_.close();
				}
				//If we clicked within another button's rectangle, then do that button's function.
				if(DifferentButtonRectangle.Contains(zdarzenie.mouseMove.x, zdarzenie.mouseMove.y) == true)
				{
					//...
				}
			}
			
			if(zdarzenie.type == sf::Event::MouseMoved)
			{
				//If hovered over the button, change it's color.
				if(przycisk_.czyZawiera(zdarzenie.mouseMove))
				{
					//Change the color of the text.
					przycisk_.ustawKolorTla(sf::Color(250, 20, 20));
				}
				else
				{
					przycisk_.ustawKolorTla(sf::Color(150, 50, 50));
				}
				
			}
		}

		this->setEmitter(okno_.mapPixelToCoords(mouse));
		sf::Time elapsed = zegar_.restart();
        this->update(elapsed);

		okno_.clear(sf::Color(0,0,128,255));
		okno_.draw(*this);
		okno_.display();
		//Do testów
		if(zegar.getElapsedTime() >= sf::seconds(3)){
			oknoGlowne.close();
		}
	}
}

GlowneOkno::~GlowneOkno(void)
{
}

void GlowneOkno::setEmitter(sf::Vector2f position)
{
	if(m_pozycja_ ==position)
		return;
	sf::Vector2f last = m_pozycja_ - position;
	if(std::sqrtf(last.x * last.x + last.y * last.y) <=2.f)
		return;
	m_pozycja_prev_ = m_pozycja_;
    m_pozycja_ = position;
	sf::Vector2f m_vector_e =  m_pozycja_prev_ - m_pozycja_;
	float lenght = std::sqrtf(m_vector_e.x * m_vector_e.x + m_vector_e.y * m_vector_e.y);
	if(lenght!=0.f){
		m_vector_e /= lenght;
	}
	if(m_vector_e.y>=0.f){
		kat = std::acosf(m_vector_e.x);
	}else{
		if(m_vector_e.x < 0.f) 
			kat = -std::acosf(m_vector_e.y);
		else
			kat = std::asinf(m_vector_e.y);
	}
	tekst_.setString(std::to_string(kat) + std::string(" x:") + (m_vector_e.x>=0.f ? "+" : "-" ) + std::string(" y:") + (m_vector_e.y>=0.f ? "+" : "-")  );
}

void GlowneOkno::update(sf::Time elapsed)
{
	for (unsigned int i = 0; i < v_czastki_.size(); ++i)
    {
        // update the particle lifetime
        Particle& p = v_czastki_[i];
        p.lifetime -= elapsed;

        // if the particle is dead, respawn it
        if (p.lifetime <= sf::Time::Zero)
            resetParticle(i);

        // update the position of the corresponding vertex
        v_obiekty_[i].position += p.velocity * elapsed.asSeconds();

        // update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_czasZycia_.asSeconds();
        v_obiekty_[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		v_obiekty_[i].color.r = static_cast<sf::Uint8>(255);
		v_obiekty_[i].color.g = static_cast<sf::Uint8>(0);
		v_obiekty_[i].color.b = static_cast<sf::Uint8>(0);
    }
}

void GlowneOkno::resetParticle(unsigned int index)
{
    // give a random velocity and lifetime to the particle
	float angle = ((((std::rand() / static_cast<float>(RAND_MAX) )* 60.f)-30.f) * 3.14f / 180.f) + kat;
    float speed = (std::rand() % 30) + 30.f;
    v_czastki_[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    v_czastki_[index].lifetime = sf::milliseconds((std::rand() % 3000) + 1000);

    // reset the position of the corresponding vertex
    v_obiekty_[index].position = m_pozycja_;
}

*/
