#pragma once
#include "stdafx.h"
#include "TypyProste\TypyProste.h"

class Zdarzenie
{
public:
	STyp::Identyfikator idStanu_;
	int numer_;
	STyp::Identyfikator idZdarzenia_;
	tgui::Callback zdarzenieGui_;
};

