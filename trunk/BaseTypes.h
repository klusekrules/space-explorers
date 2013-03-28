#pragma once

#include <string>
#include "BaseInterface.h"

namespace SPG{
	/* Ogolne */
	typedef int					IdType; //+
	typedef unsigned int		Poziom; //+
	typedef float				Fluktuacja; //+
	typedef std::string			Tekst; //+
	typedef long double			IloscJednostek; //+
	typedef double				Objetosc; //+
	typedef double				Masa; //+
	typedef double				Dystans; //+
	typedef double				Predkosc; //+
	typedef double				Powierzchnia; //+
	typedef double				Parametr;//+


	/* Flota */
	typedef double	Obrazenia; //+
	typedef double	ZuzyciePaliwa; //+
	typedef double	MocSilnika; //+

	//TODO: Analiza czy potrzebne.
	typedef enum	RodzajNapedu{
		NiepoprawnyRodzaj,
		Spalinowy,
		Jonowy,
		Nadswietlny
	};
}
