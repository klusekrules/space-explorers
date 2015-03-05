#include "SprawdzSumyKontrolneRPC.h"
#include "Logger\Logger.h"

namespace SpEx{

	const std::string SprawdzSumyKontrolneRPC::NazwaTypu_ = "SprawdzSumyKontrolne";
	
	std::string SprawdzSumyKontrolneRPC::napis() const{
		SLog::Logger logger(NAZWAKLASY(SprawdzSumyKontrolneRPC));
		logger.dodajKlase(MetodaRPC::napis());
		return logger.napis();
	}

	void SprawdzSumyKontrolneRPC::obslugaZadania(const Json::Value &, Json::Value&){}

	bool SprawdzSumyKontrolneRPC::obslugaOdpowiedzi(const Json::Value &){
		return false;
	}
}
