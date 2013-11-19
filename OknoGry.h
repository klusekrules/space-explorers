#pragma once
#include "stdafx.h"
#include "Watek.h"
#include "Logger\Log.h"
#include "EkranMenu.h"

class OknoGry :
	public Watek
{
public:
	OknoGry( bool wstrzymany );
	virtual ~OknoGry(void);
private:
	sf::RenderWindow oknoGlowne_;
	sf::Shader testShadera_;
	
	std::map< Identyfikator, std::shared_ptr< EkranSzablon > > listaEkranow_;
	std::vector< std::shared_ptr< EkranSzablon > > stosEkranow_;
	
	void wykonuj() override;
	bool inicjalizacja();
	void obslugaZdarzen( StanGry& stan );
	void uaktualnianie( StanGry& stan );
	void odmaluj();

	StanGry::KrokCzasu obliczZmianeCzasu ( std::chrono::high_resolution_clock::time_point );
};

