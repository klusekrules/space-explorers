#pragma once
#include "Main.h"
#include "CenaInterfejs.h"
#include "Warunek.h"

class Wymagania
{
public:
	Wymagania( CenaInterfejs* , Warunek* );
	Wymagania( const Wymagania& );
	const Wymagania& operator=( const Wymagania& );
	~Wymagania();
	
private:
	CenaInterfejs* koszty;
	Warunek* wymogi;
};

