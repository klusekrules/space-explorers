#include "ObserwatorWatkow.h"

SpEx::ObserwatorWatkow::ObserwatorWatkow()
	: synchronize_(), listaWatkow_(), Watek(true)
{
}

void SpEx::ObserwatorWatkow::wykonuj(){
	while (!czyZakonczyc()) {

		{
			std::lock_guard<std::mutex> temp(synchronize_);
			auto iEnd = listaWatkow_.end();
			for (auto iter = listaWatkow_.begin(); iter != iEnd; ) {
				if ((*iter)->zakonczony()) {
					listaWatkow_.erase(iter++);
				} else {
					++iter;
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void SpEx::ObserwatorWatkow::dodajWatek(std::shared_ptr<Watek>& watek){
	std::lock_guard<std::mutex> temp(synchronize_);
	listaWatkow_.emplace_back(watek);
}
