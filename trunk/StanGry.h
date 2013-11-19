#pragma once
#include "stdafx.h"
#include "Identyfikator.h"

class StanGry{
public:

	enum StanyGry{
		Niezainicjalizowana,
		Testowanie,
		EkranStartowy,
		Menu,
		ZmianaEkranu,
		Uruchomiona,
		Wylacznie
	};

	typedef std::chrono::duration<long double,std::milli> KrokCzasu;

	static StanyGry konwertuj( unsigned int );

	StanGry(const StanGry& stan);

	StanGry(StanGry&& stan);

	StanGry& operator=(const StanGry& stan);

	~StanGry();

	int pobierzNumerSpecjalny() const;

	StanyGry pobierzStan() const;
	
	Identyfikator pobierzIdEkranu() const;

	KrokCzasu pobierzKrok() const;

	void ustawNumerSpecjalny( int numerSpecjalny );

	bool operator==( StanyGry stan ) const;

	bool operator!=( StanyGry stan ) const;

	bool operator==( const StanGry &stan ) const;

	bool operator!=( const StanGry &stan ) const;

	void ustawCzasKroku ( KrokCzasu krok );

	void ustawStan ( StanyGry stan );

	void ustawIdEkranu ( Identyfikator ekran );

	void ustawNastepnyStan ( StanyGry stan );

	void przejdzDoNastepnegoStanu ( );
	
	StanGry(StanyGry stan, int numerSpecjalny, KrokCzasu krok, Identyfikator ekran );
private:
	StanyGry stan_;
	int numerSpecjalny_;
	Identyfikator idEkranu_;
	KrokCzasu krok_;

	
	StanyGry stanNastepny_;


};
