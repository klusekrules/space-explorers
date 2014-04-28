#pragma once
#include "stdafx.h"
#include "Watek.h"
#include "Logger\Log.h"
#include "EkranSzablon.h"
#include "Zadanie.h"
#include "LogListGui.h"

namespace SpEx{
	class OknoGry :
		public Watek
	{
	public:
		typedef std::shared_ptr< EkranSzablon > EkranPtr;
		typedef std::vector< EkranPtr > StosEkranow;

		OknoGry(bool wstrzymany);
		void zakmnij();
		void zatrzymajPoInicjalizacji();
		bool zainicjalizowe();
		bool czekajNaInicjalizacje();
		void uruchom();
		EkranPtr pobierzEkran(const STyp::Identyfikator& ekranId);
		StosEkranow& pobierzStosEkranow();

		void przeladujEkran( const STyp::Identyfikator& id );
		
		void dodajZadanie(SpEx::Zadanie&);

		void pause();
		bool isPause() const;
		void unpause();

		void odlaczOknoKomunikatow();
		void logToGUI(unsigned int typ, const std::string& tresc);
		void ustawOknoKomunikatow(int, const char *);

		virtual ~OknoGry(void) = default;
	private:
		sf::RenderWindow oknoGlowne_;
		sf::Shader testShadera_;

		std::atomic_bool przetwarzanie_;
		std::promise<bool> inicjalizacja_;
		std::future<bool> inicjalizacjaWynik_;
		mutable std::mutex mutexUruchom_;
		mutable std::mutex mutexInicjalizacja_;

		std::atomic_bool boolPauza_;
		std::mutex mutexPauza_;

		mutable std::recursive_mutex mutexListaEkranow_;
		std::map< STyp::Identyfikator, EkranPtr > listaEkranow_;
		mutable std::mutex listaZadanMux_;
		std::list< SpEx::Zadanie > listaZadan_;
		StosEkranow stosEkranow_;

		tgui::LogListGui::Ptr oknoKomunikatow_;

		void wykonuj() override;
		bool inicjalizacja();
		void obslugaZdarzen(Stan& stan);
		void uaktualnianie(Stan& stan);
		void odmaluj();

		Stan::KrokCzasu obliczZmianeCzasu(std::chrono::high_resolution_clock::time_point);

		bool wczytajEkrany();
		void usunWszystkieEkrany();

		void logujInfo();
	};
};
