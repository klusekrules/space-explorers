#pragma once
#include "Main.h"
#include "CenaInterfejs.h"
#include "Warunek.h"
#include "LoggerInterface.h"

class Wymagania :
	public LoggerInterface < Wymagania >
{
public:
	Wymagania( );
	Wymagania( CenaInterfejs* , Warunek* );
	Wymagania( const Wymagania& );
	const Wymagania& operator=( const Wymagania& );
	~Wymagania();

	string toString() const override;

private:

	CenaInterfejs* koszty;
	Warunek* wymogi;
};
