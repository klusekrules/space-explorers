#include "TypyProste.h"

namespace STyp{
	template <class T>
	Wartosc pomnozWartosc(const Wartosc& wartosc, const T& other) { return wartosc() * other(); }


	template <class T>
	T pomnozPrzezIlosc(const T& wartosc, const Ilosc& other) { return wartosc() * other(); }
}