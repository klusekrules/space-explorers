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
	bool czekajNaInicjalizacje();
	void uruchom();
	EkranPtr pobierzEkran( const STyp::Identyfikator& ekranId );

	virtual ~OknoGry(void) = default;
private:
	sf::RenderWindow oknoGlowne_;
	sf::Shader testShadera_;
	
	std::atomic_bool przetwarzanie_;
	std::promise<bool> inicjalizacja_;
	std::future<bool> inicjalizacjaWynik_;
	mutable std::mutex mutexUruchom_;
	mutable std::mutex mutexInicjalizacja_;
	std::map< STyp::Identyfikator, EkranPtr > listaEkranow_;
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

