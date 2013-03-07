#include "Wymagania.h"


Wymagania::Wymagania( CenaInterfejs* c, Warunek* w )
	: koszty(c), wymogi(w)
{
}
Wymagania::Wymagania( const Wymagania& w)
	:koszty(w.koszty->Kopia()), wymogi(w.wymogi->Kopia())
{
}

const Wymagania& Wymagania::operator=( const Wymagania& w ){
	delete koszty;
	koszty = w.koszty->Kopia();

	delete wymogi;
	wymogi = w.wymogi->Kopia();
	return *this;
}

Wymagania::~Wymagania()
{
	delete koszty;
	delete wymogi;
}
