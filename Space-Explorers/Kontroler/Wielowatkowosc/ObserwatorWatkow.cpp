#include "ObserwatorWatkow.h"
#include "Logger\Log.h"

SpEx::ObserwatorWatkow::ObserwatorWatkow()
	: doUsuniecia_(), synchronize_(), listaWatkow_(), Watek("ObserwatorWatkow", true)
{
	odblokuj();
}

void SpEx::ObserwatorWatkow::wylaczJakPuste() {
	wylaczJakPuste_ = true;
}

void SpEx::ObserwatorWatkow::wykonuj(){
	while (!czyZakonczyc()) {

		{
			std::lock_guard<std::mutex> temp(synchronize_);
			auto iEnd = listaWatkow_.end();
			for (auto iter = listaWatkow_.begin(); iter != iEnd; ) {
				if ((*iter)->zakonczony()) {
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Wykryto zakoñczony w¹tek: " + (*iter)->pobierzNazweWatku());
					doUsuniecia_.emplace_back((*iter));
					listaWatkow_.erase(iter++);
				} else {
					++iter;
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		for (auto &watek : doUsuniecia_) {
			watek->czekajNaZakonczenie();
		}

		{
			std::lock_guard<std::mutex> temp(synchronize_);
			if (listaWatkow_.empty() && wylaczJakPuste_)
				break;
		}
	}
}

void SpEx::ObserwatorWatkow::dodajWatek(std::shared_ptr<Watek>& watek){
	if (watek != nullptr) {
		{
			std::lock_guard<std::mutex> temp(synchronize_);
			listaWatkow_.emplace_back(watek);
		}
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Dodano do obserwowania w¹tek: " + watek->pobierzNazweWatku());
	}
}
