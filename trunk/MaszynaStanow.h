#pragma once
#include "stdafx.h"
#include "Logger\\Log.h"

#include "OknoGry.h"

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
		typedef std::chrono::duration<long double,std::milli> KrokCzasu;

		StanGry(const StanGry& stan) : stan_(stan.stan_), krok_(stan.krok_), numerSpecjalny_(stan.numerSpecjalny_), stanNastepny_(stan.stanNastepny_){}
		StanGry(StanGry&& stan) : stan_(stan.stan_), krok_(stan.krok_), numerSpecjalny_(stan.numerSpecjalny_), stanNastepny_(stan.stanNastepny_){}

		StanGry& operator=(const StanGry& stan){ 
			stan_ = stan.stan_; 
			krok_ = stan.krok_;
			stanNastepny_ = stan.stanNastepny_;
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
		
		void ustawCzasKroku ( KrokCzasu krok ){ krok_=krok; }

		void ustawStan ( StanyGry stan ){ stan_=stan; }

		void ustawNastepnyStan ( StanyGry stan ){ stanNastepny_=stan; }

		void przejdzDoNastepnegoStanu ( ){ stan_=stanNastepny_; }

	private:
		StanyGry stan_;
		StanyGry stanNastepny_;
		int numerSpecjalny_;
		KrokCzasu krok_;


		StanGry(StanyGry stan, int numerSpecjalny, KrokCzasu krok )
			: stan_(stan), krok_(krok), numerSpecjalny_(numerSpecjalny), stanNastepny_(stan){}

	};

	~MaszynaStanow();

	void start();

	StanGry& pobierzStan();

	static MaszynaStanow& pobierzInstancje();

private:

	StanGry aktualnyStan_;
		
	OknoGry watekGraficzny_;
	//Watek watekObliczeniowy_;

	MaszynaStanow();
	MaszynaStanow( const MaszynaStanow& );
	MaszynaStanow( MaszynaStanow&& );
	MaszynaStanow& operator=(const MaszynaStanow&);

	void petlaGlowna();
	void pokazEkranStartowy();

	void dodajKomunikatLogow( Log::TypLogow typ, const std::string& komunikat );

};

