#pragma once
#include "Zadanie.h"
#include "Watek.h"
#include <future>
#include <list>

namespace SpEx{
	class WatekZarzadzany
		: public Watek
	{
	public:
		WatekZarzadzany(std::future<bool> wykonuj);
		void dodajZadanie(Zadanie& zadanie, std::future<bool> noweZadanie);
		virtual ~WatekZarzadzany(void) = default;
	protected:
		void wykonuj() override;
	private:

		std::mutex mutexNastepneNoweZadanie_;
		std::future<bool> nastepneNoweZadanie_;
		std::future<bool> noweZadanie_;

		std::mutex mutexZadanie_;
		std::list<Zadanie> zadania_;

		bool pobierzZadanie(Zadanie&);
		void ustawOczekiwanieNaNoweZadanie();
	};

};