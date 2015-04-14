#include "Zadanie.h"
namespace SpEx{
	Zadanie::Zadanie(std::function<void()>& funkcja)
		: funkcja_(funkcja)
	{
	}

	void Zadanie::wykonaj(){
		funkcja_();
	}

};
