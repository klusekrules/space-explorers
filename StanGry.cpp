#include "StanGry.h"


StanGry::StanyGry StanGry::konwertuj( unsigned int uStan ){
	switch (uStan)
	{
	case StanGry::Niezainicjalizowana: return StanGry::Niezainicjalizowana;
		break;
	case StanGry::Testowanie: return StanGry::Testowanie;
		break;
	case StanGry::EkranStartowy: return StanGry::EkranStartowy;
		break;
	case StanGry::Menu: return StanGry::Menu;
		break;
	case StanGry::ZmianaEkranu: return StanGry::ZmianaEkranu;
		break;
	case StanGry::Uruchomiona: return StanGry::Uruchomiona;
		break;
	case StanGry::Wylacznie: return StanGry::Wylacznie;
		break;
	default:
		break;
	}
	return StanGry::Niezainicjalizowana;
}


StanGry::StanGry(StanyGry stan, int numerSpecjalny, KrokCzasu krok, Identyfikator ekran )
	: stan_(stan), krok_(krok), numerSpecjalny_(numerSpecjalny), stanNastepny_(stan), idEkranu_(ekran)
{
}

StanGry::StanGry(const StanGry& stan) 
	: stan_(stan.stan_), krok_(stan.krok_), numerSpecjalny_(stan.numerSpecjalny_), stanNastepny_(stan.stanNastepny_), idEkranu_(stan.idEkranu_)
{
}

StanGry::StanGry(StanGry&& stan) 
	: stan_(stan.stan_), krok_(stan.krok_), numerSpecjalny_(stan.numerSpecjalny_), stanNastepny_(stan.stanNastepny_), idEkranu_(stan.idEkranu_)
{
}

StanGry& StanGry::operator=(const StanGry& stan){ 
	stan_ = stan.stan_; 
	krok_ = stan.krok_;
	stanNastepny_ = stan.stanNastepny_;
	numerSpecjalny_ = stan.numerSpecjalny_;
	idEkranu_ = stan.idEkranu_;
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
	return stan_==stan.stan_ && krok_ == stan.krok_ && numerSpecjalny_ == stan.numerSpecjalny_ && idEkranu_ == stan.idEkranu_; 
}

bool StanGry::operator!=( const StanGry &stan ) const { 
	return stan_!=stan.stan_ || krok_ != stan.krok_ || numerSpecjalny_ != stan.numerSpecjalny_ || idEkranu_ != stan.idEkranu_; 
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

Identyfikator StanGry::pobierzIdEkranu() const{
	return idEkranu_;
}

void StanGry::ustawIdEkranu ( Identyfikator ekran ){
	idEkranu_ = ekran;
}
