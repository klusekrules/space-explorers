#include "StanGry.h"

StanGry::StanGry(StanyGry stan, int numerSpecjalny, KrokCzasu krok )
	: stan_(stan), krok_(krok), numerSpecjalny_(numerSpecjalny), stanNastepny_(stan)
{
}

StanGry::StanGry(const StanGry& stan) 
	: stan_(stan.stan_), krok_(stan.krok_), numerSpecjalny_(stan.numerSpecjalny_), stanNastepny_(stan.stanNastepny_)
{
}

StanGry::StanGry(StanGry&& stan) 
	: stan_(stan.stan_), krok_(stan.krok_), numerSpecjalny_(stan.numerSpecjalny_), stanNastepny_(stan.stanNastepny_)
{
}

StanGry& StanGry::operator=(const StanGry& stan){ 
	stan_ = stan.stan_; 
	krok_ = stan.krok_;
	stanNastepny_ = stan.stanNastepny_;
	numerSpecjalny_ = stan.numerSpecjalny_;
	return *this;
}

StanGry::~StanGry(){
}

int StanGry::pobierzNumerSpecjalny() const { 
	return numerSpecjalny_; 
}

StanGry::StanyGry StanGry::pobierzStan() const { 
	return stan_; 
}

StanGry::KrokCzasu StanGry::pobierzKrok() const { 
	return krok_; 
}

void StanGry::ustawNumerSpecjalny( int numerSpecjalny ){ 
	numerSpecjalny_ = numerSpecjalny; 
}


bool StanGry::operator==( StanyGry stan ) const { 
	return stan_==stan; 
}

bool StanGry::operator!=( StanyGry stan ) const { 
	return stan_!=stan; 
}

bool StanGry::operator==( const StanGry &stan ) const { 
	return stan_==stan.stan_ && krok_ == stan.krok_ && numerSpecjalny_ == stan.numerSpecjalny_; 
}

bool StanGry::operator!=( const StanGry &stan ) const { 
	return stan_!=stan.stan_ || krok_ != stan.krok_ || numerSpecjalny_ != stan.numerSpecjalny_; 
}

void StanGry::ustawCzasKroku ( KrokCzasu krok ){ 
	krok_=krok; 
}

void StanGry::ustawStan ( StanyGry stan ){ 
	stan_=stan; 
}

void StanGry::ustawNastepnyStan ( StanyGry stan ){ 
	stanNastepny_=stan; 
}

void StanGry::przejdzDoNastepnegoStanu ( ){ 
	stan_=stanNastepny_; 
}

