#pragma once
#include "stdafx.h"
#include "Watek.h"
#include "Logger\Log.h"
#include "EkranSzablon.h"

class OknoGry :
	public Watek
{
public:
	typedef std::shared_ptr< EkranSzablon > EkranPtr;
	typedef std::vector< EkranPtr > StosEkranow;

	OknoGry( bool wstrzymany );
	void zakmnij();
	void zatrzymajPoInicjalizacji();
	bool zainicjalizowe();
	void uruchom();
	EkranPtr pobierzEkran( const Identyfikator& ekranId );

	virtual ~OknoGry(void);
private:
	sf::RenderWindow oknoGlowne_;
	sf::Shader testShadera_;
	
	std::atomic_bool przetwarzanie_;
	mutable std::mutex mutexUruchom_;
	mutable std::mutex mutexInicjalizacja_;
	std::map< Identyfikator, EkranPtr > listaEkranow_;
	StosEkranow stosEkranow_;
	
	void wykonuj() override;
	bool inicjalizacja();
	void obslugaZdarzen( Stan& stan );
	void uaktualnianie( Stan& stan );
	void odmaluj();

	Stan::KrokCzasu obliczZmianeCzasu ( std::chrono::high_resolution_clock::time_point );

	bool wczytajEkrany();

	void logujInfo();
};

