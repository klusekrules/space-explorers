#include "TypyProste.h"

namespace STyp{
	template <class T>
	Wartosc pomnozWartosc(const Wartosc& wartosc, const T& other) { return wartosc() * other(); }
}