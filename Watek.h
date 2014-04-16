#pragma once
#include <thread>
#include <atomic>
#include <mutex>
#include "NonCopyable.h"
#include "NonMoveable.h"
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	class Watek
		: se::NonCopyable, se::NonMoveable
	{
	public:
		Watek(bool wstrzymany);
		virtual ~Watek(void);
		bool czekajNaZakonczenie();
		void odblokuj();
		void zakoncz();
		std::atomic<bool>& zakonczony();
		std::atomic<bool>& blad();
		STyp::Wyjatek& bladInfo();

	protected:
		std::atomic<bool> zakoncz_;
		std::mutex wstrzymany_;
		std::atomic<bool> zakonczony_;

		std::atomic<bool> blad_;
		STyp::Wyjatek bladInfo_;
		void ustawBlad(const STyp::Wyjatek& info);

		virtual void wykonuj();
		std::atomic<bool>& czyZakonczyc();
		std::thread* uchwyt_;
		void funkcjaWatku();
	};
};

