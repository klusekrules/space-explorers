#pragma once
#include "stdafx.h"
#include "Identyfikator.h"

class Zdarzenie
{
public:
	Identyfikator idStanu_;
	int numer_;
	Identyfikator idZdarzenia_;
	tgui::Callback zdarzenieGui_;
};

