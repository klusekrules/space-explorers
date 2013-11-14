#pragma once
#include "stdafx.h"
#include "Logger\\Log.h"
#include "Watek.h"

class MaszynaStanow
{
public:
	enum StanyGry{
		Niezainicjalizowana,
		Testowanie,
		EkranStartowy,
		MenuGlowne,
		Uruchomiona,
		Wylacznie
	};

	class StanGry{
		friend class MaszynaStanow;
	public:
		typedef std::chrono::milliseconds KrokCzasu;

		StanGry(const StanGry& stan) : stan_(stan.stan_), krok_(stan.krok_), numerSpecjalny_(stan.numerSpecjalny_){}
		StanGry(StanGry&& stan) : stan_(stan.stan_), krok_(stan.krok_), numerSpecjalny_(stan.numerSpecjalny_){}

		StanGry& operator=(const StanGry& stan){ 
			stan_ = stan.stan_; 
			krok_ = stan.krok_;
			numerSpecjalny_ = stan.numerSpecjalny_;
			return *this;
		}

		~StanGry(){}

		int pobierzNumerSpecjalny() const { return numerSpecjalny_; }
		StanyGry pobierzStan() const { return stan_; }
		KrokCzasu pobierzKrok() const { return krok_; }

		void ustawNumerSpecjalny( int numerSpecjalny ){ numerSpecjalny_ = numerSpecjalny; }

		bool operator==( StanyGry stan ) const { return stan_==stan; }

		bool operator!=( StanyGry stan ) const { return stan_!=stan; }

		bool operator==( const StanGry &stan ) const { return stan_==stan.stan_ && krok_ == stan.krok_ && numerSpecjalny_ == stan.numerSpecjalny_; }

		bool operator!=( const StanGry &stan ) const { return stan_!=stan.stan_ || krok_ != stan.krok_ || numerSpecjalny_ != stan.numerSpecjalny_; }

	private:
		StanyGry stan_;
		int numerSpecjalny_;
		KrokCzasu krok_;

		void ustawCzasKroku ( KrokCzasu krok ){ krok_=krok; }
		void ustawStan ( StanyGry stan ){ stan_=stan; }

		StanGry(StanyGry stan, int numerSpecjalny, KrokCzasu krok )
			: stan_(stan), krok_(krok), numerSpecjalny_(numerSpecjalny){}

	};

	~MaszynaStanow();

	void start();

	StanGry& pobierzStan();

	static MaszynaStanow& pobierzInstancje();

private:

	StanGry aktualnyStan_;
	sf::RenderWindow oknoGlowne_;
	tgui::Gui gui;
	
	//
	sf::Texture obrazTla_;
	sf::Sprite tlo_;
	sf::Font czcionka_;
	sf::Shader testShadera_;
	tgui::ChatBox::Ptr chatbox_;
	tgui::Button::Ptr button_;
	//
	
	Watek watekGraficzny_;
	Watek watekObliczeniowy_;

	MaszynaStanow();
	MaszynaStanow( const MaszynaStanow& );
	MaszynaStanow( MaszynaStanow&& );
	MaszynaStanow& operator=(const MaszynaStanow&);

	void petlaGlowna();
	void pokazEkranStartowy();

	void dodajKomunikatLogow( Log::TypLogow typ, const std::string& komunikat );

};

