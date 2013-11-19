#pragma once
#include "stdafx.h"
#include "Logger\\Log.h"
#include "OknoGry.h"
#include "StanGry.h"

class MaszynaStanow
{
public:
	
	~MaszynaStanow();

	void start();

	StanGry pobierzStan();

	static MaszynaStanow& pobierzInstancje();

	void scalStan( const StanGry& stan );

private:

	StanGry aktualnyStan_;
	std::mutex mutexStanu_; 

	StanGry nastepnyStan_;
		
	OknoGry watekGraficzny_;

	MaszynaStanow();
	MaszynaStanow( const MaszynaStanow& );
	MaszynaStanow( MaszynaStanow&& );
	MaszynaStanow& operator=(const MaszynaStanow&);

	void petlaGlowna();
	void pokazEkranStartowy();

	void dodajKomunikatLogow( Log::TypLogow typ, const std::string& komunikat );

	void przejdzDoNastepnegoStanu();

};

