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

