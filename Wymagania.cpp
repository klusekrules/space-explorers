#include "Wymagania.h"
#include "Logger.h"

Wymagania::Wymagania( )
	: koszty(nullptr), wymogi(nullptr)
{

}

Wymagania::Wymagania( CenaInterfejs* c, Warunek* w )
	: koszty(c), wymogi(w)
{
}
Wymagania::Wymagania( const Wymagania& w )
{
	if(w.koszty!=nullptr)
		koszty = w.koszty->Kopia();
	else
		koszty = nullptr;
	
	if(w.wymogi!=nullptr)
		wymogi = w.wymogi->Kopia();
	else
		wymogi = nullptr;
}

const Wymagania& Wymagania::operator=( const Wymagania& w ){
	if(koszty!=nullptr)
		delete koszty;
	if(w.koszty!=nullptr)
		koszty = w.koszty->Kopia();
	else
		koszty = nullptr;
	if(wymogi!=nullptr)
		delete wymogi;
	if(w.wymogi!=nullptr)
		wymogi = w.wymogi->Kopia();
	else
		wymogi = nullptr;
	return *this;
}

Wymagania::~Wymagania()
{
	if(koszty!=nullptr)
		delete koszty;
	if(wymogi!=nullptr)
		delete wymogi;
}

string Wymagania::toString() const{
	Logger str(className());
	if(koszty!=nullptr)
		str.addField("Koszty",*koszty);
	if(wymogi!=nullptr)
		str.addField("Warunki",*wymogi);
	return str.toString();
}