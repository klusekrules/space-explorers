#pragma once
#include <memory>
#include "TGUI\Callback.hpp"
#include "TypyProste\TypyProste.h"

namespace SpEx{

	/**
	* \brief Struktura zdarzenia
	*
	* Struktura przechowuje informacje o zdarzeniu.
	* \author Daniel Wojdak
	* \version 1
	* \date 09-07-2014
	*/
	struct Zdarzenie
	{
		STyp::Identyfikator idStanu_; /// Identyfikator stanu, w kt�rym wyst�pi�o zdarzenie.
		int numer_; /// Numer dodatkowy.
		std::shared_ptr<STyp::Identyfikator> idNowegoStanu_; /// Domy�lny identyfikator nast�pnego stanu.
		STyp::Identyfikator idZdarzenia_; /// Identyfikator zdarzenia.
		tgui::Callback zdarzenieGui_; /// Dane dodatkowe o wyst�pieniu zdarzenia.
	};
};
