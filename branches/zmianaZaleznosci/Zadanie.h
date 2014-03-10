#pragma once
#include "stdafx.h"
namespace SpEx{
	class Zadanie
	{
	private:
		std::function<void()> funkcja_;
	public:
		Zadanie() = default;
		Zadanie(std::function<void()>&);
		void wykonaj();
		~Zadanie(void) = default;
	};
};
