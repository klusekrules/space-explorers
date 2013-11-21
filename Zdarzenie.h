#pragma once
#include "stdafx.h"
#include "Identyfikator.h"

class Zdarzenie
{
public:
	Zdarzenie(void);
	~Zdarzenie(void);
	Identyfikator idStanu_;
	int numer_;
	Identyfikator idZdarzenia_;
	tgui::Callback zdarzenieGui_;
};

