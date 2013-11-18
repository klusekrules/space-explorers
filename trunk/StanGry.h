#pragma once
#include "stdafx.h"


class StanGry{
	friend class MaszynaStanow;
public:

	enum StanyGry{
		Niezainicjalizowana,
		Testowanie,
		EkranStartowy,
		MenuGlowne,
		Uruchomiona,
		Wylacznie
	};

	typedef std::chrono::duration<long double,std::milli> KrokCzasu;

	StanGry(const StanGry& stan);

	StanGry(StanGry&& stan);

	StanGry& operator=(const StanGry& stan);

	~StanGry();

	int pobierzNumerSpecjalny() const;

	StanyGry pobierzStan() const;

	KrokCzasu pobierzKrok() const;

	void ustawNumerSpecjalny( int numerSpecjalny );

	bool operator==( StanyGry stan ) const;

	bool operator!=( StanyGry stan ) const;

	bool operator==( const StanGry &stan ) const;

	bool operator!=( const StanGry &stan ) const;

	void ustawCzasKroku ( KrokCzasu krok );

	void ustawStan ( StanyGry stan );

	void ustawNastepnyStan ( StanyGry stan );

	void przejdzDoNastepnegoStanu ( );

private:
	StanyGry stan_;
	StanyGry stanNastepny_;
	int numerSpecjalny_;
	KrokCzasu krok_;

	StanGry(StanyGry stan, int numerSpecjalny, KrokCzasu krok );

};
