#pragma once
#include <memory>
#include "TGUI\Callback.hpp"
#include "TypyProste\TypyProste.h"

namespace SpEx{
	struct Zdarzenie
	{
		STyp::Identyfikator idStanu_;
		int numer_;
		std::shared_ptr<STyp::Identyfikator> idNowegoStanu_;
		STyp::Identyfikator idZdarzenia_;
		tgui::Callback zdarzenieGui_;
	};
};
