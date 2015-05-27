#include "MenedzerTranzakcji.h"
#include "NiepowodzenieTranzakcji.h"
#include "Logger\Logger.h"

namespace SpEx{


	MenedzerTranzakcji::MenedzerTranzakcji(SLog::Log& log)
		: log_(log)
	{	
	}

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
#ifndef LOG_OFF_ALL
			log_.loguj(SLog::Log::Warning, e.generujKomunikat());
#endif
			powodzenie = false;
		}
		catch (std::exception& e){
#ifndef LOG_OFF_ALL
			log_.loguj(SLog::Log::Warning, e.what());
#endif
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
			catch (NiepowodzenieTranzakcji& e){
#ifndef LOG_OFF_ALL
				log_.loguj(SLog::Log::Warning, e.generujKomunikat());
#endif
				throw;
			}
			catch (STyp::Wyjatek& e){
#ifndef LOG_OFF_ALL
				log_.loguj(SLog::Log::Warning, e.generujKomunikat());
#endif
				throw SpEx::NiepowodzenieTranzakcji(EXCEPTION_PLACE, listaOperacji_[iterator]->napis());
			}
			catch (std::exception& e){
#ifndef LOG_OFF_ALL
				log_.loguj(SLog::Log::Warning, e.what());
#endif
				throw NiepowodzenieTranzakcji(EXCEPTION_PLACE, listaOperacji_[iterator]->napis());
			}
			catch (...){
				throw NiepowodzenieTranzakcji(EXCEPTION_PLACE, listaOperacji_[iterator]->napis());
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
