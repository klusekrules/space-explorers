#pragma once
#include "stdafx.h"
#include "TypyProste\TypyProste.h"

namespace SpEx{
	struct Zdarzenie
	{
		STyp::Identyfikator idStanu_;
		int numer_;
		STyp::Identyfikator idZdarzenia_;
		tgui::Callback zdarzenieGui_;
	};
};
