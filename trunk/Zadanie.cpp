#include "Zadanie.h"

Zadanie::Zadanie(){}

Zadanie::Zadanie( std::function<void()>& funkcja)
	: funkcja_(funkcja)
{
}

void Zadanie::wykonaj(){
	funkcja_();
}


Zadanie::~Zadanie(void)
{
}
