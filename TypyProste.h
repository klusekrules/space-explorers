#pragma once
#include <string>
#include "PodstawowyInterfejs.h"

/**
* Przypisania typów podstawowych do typów stosowanych w grze.
*/
namespace SPG{
	typedef int				Identyfikator;
	typedef unsigned int	Poziom;
	typedef long long		Klucz; // sizeof(Identyfikator) + sizeof(Poziom)
	typedef float			Fluktuacja;
	typedef std::string		Tekst;
	typedef long double		IloscJednostek;
	typedef double			Objetosc;
	typedef double			Masa;
	typedef double			Dystans;
	typedef double			Temperatura;
	typedef double			Predkosc;
	typedef double			Powierzchnia;
	typedef double			Parametr;
	typedef long double		Czas;
	typedef double			Obrazenia;
	typedef double			ZuzyciePaliwa;
	typedef double			MocSilnika;
}
