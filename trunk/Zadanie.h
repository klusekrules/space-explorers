#pragma once
#include "stdafx.h"

class Zadanie
{
private:
	std::function<void()> funkcja_;
public:
	Zadanie();
	Zadanie( std::function<void()>& );
	void wykonaj();
	~Zadanie(void);
};

