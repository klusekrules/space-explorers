#include "Operacja.h"
#include "Logger\Logger.h"

Operacja::Operacja(void)
{
}

Operacja::~Operacja(void)
{
}

bool Operacja::wykonaj(){
	return false;
}

bool Operacja::cofnij(){
	return false;
}

string Operacja::napis() const {
	Logger str (NAZWAKLASY(Operacja));
	return str.napis();
}
