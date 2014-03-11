#include "MenedzerTranzakcji.h"
#include "NiepowodzenieTranzakcji.h"
#include "Aplikacja.h"
namespace SpEx{
	void MenedzerTranzakcji::dodaj(Element operacja)
	{
		if (operacja)
			listaOperacji_.emplace_back(operacja);
	}

	bool MenedzerTranzakcji::wykonaj()
	{
		int iterator = 0;
		bool powodzenie = true;
		try{
			for (; iterator < static_cast<int>(listaOperacji_.size()); ++iterator){
				if (!listaOperacji_[iterator]->wykonaj()){
					powodzenie = false;
					break;
				}
			}
		}
		catch (STyp::Wyjatek& e){
			SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Warning, e.generujKomunikat());
			powodzenie = false;
		}
		catch (std::exception& e){
			SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Warning, e.what());
			powodzenie = false;
		}
		catch (...){
			powodzenie = false;
		}

		if (!powodzenie){
			try{
				for (--iterator; iterator >= 0; --iterator){
					if (!listaOperacji_[iterator]->cofnij()){
						throw SpEx::NiepowodzenieTranzakcji(EXCEPTION_PLACE, listaOperacji_[iterator]->napis());
					}
				}
			}
			catch (SpEx::NiepowodzenieTranzakcji& e){
				SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Warning, e.generujKomunikat());
				throw;
			}
			catch (STyp::Wyjatek& e){
				SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Warning, e.generujKomunikat());
				throw SpEx::NiepowodzenieTranzakcji(EXCEPTION_PLACE, listaOperacji_[iterator]->napis());
			}
			catch (std::exception& e){
				SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Warning, e.what());
				throw SpEx::NiepowodzenieTranzakcji(EXCEPTION_PLACE, listaOperacji_[iterator]->napis());
			}
			catch (...){
				throw SpEx::NiepowodzenieTranzakcji(EXCEPTION_PLACE, listaOperacji_[iterator]->napis());
			}
		}
		return powodzenie;
	}

	std::string MenedzerTranzakcji::napis() const{
		SLog::Logger str(NAZWAKLASY(MenedzerTranzakcji));
		for (const Element& element : listaOperacji_){
			str.dodajPole("Zlecenie", *element);
		}
		return str.napis();
	}
};
