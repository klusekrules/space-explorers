#pragma once
#include "stdafx.h"
#include "Identyfikator.h"

__declspec(dllexport) struct Zdarzenie_t{
	int idStanu_;
	int numer_;
	int idZdarzenia_;
};

class Zdarzenie
{
public:
	Identyfikator idStanu_;
	int numer_;
	Identyfikator idZdarzenia_;
	tgui::Callback zdarzenieGui_;
};

