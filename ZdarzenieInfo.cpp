#include "ZdarzenieInfo.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include "Aplikacja.h"
#include "BladStukturyStanu.h"

#define KOMUNIAKT_BRAK_PLIKU STyp::Tekst("Dla zdarzenia o ww id nie podano pliku skryptu, a wpisano metody do wykonania.")
#define KOMUNIAKT_BLAD_WCZYTYWANIA(plik) STyp::Tekst("Dla zdarzenia o ww id nie uda³o siê wczytac pliku lua." + plik)
#define KOMUNIAKT_BLAD_WYKONYWANIA STyp::Tekst("Dla zdarzenia o ww id nie uda³o siê wykonaæ inicjalizacji skryptu.")

namespace SpEx{
	ZdarzenieInfo::ZdarzenieInfo(XmlBO::ElementWezla wezel)
		: nastepnyStan_(nullptr), nastepnyNumer_(nullptr)
	{
		if (wezel){
			XmlBO::WczytajAtrybut<SpEx::STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, id_);
			luaFuncInside_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_STAN_LUA_INSIDE, std::string());
			luaFile_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_STAN_LUA_FILE, std::string());
			if (luaFile_.empty() && !luaFuncInside_.empty())
				throw BladStukturyStanu(EXCEPTION_PLACE, id_, KOMUNIAKT_BRAK_PLIKU);

			STyp::Identyfikator stan;
			if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_STAN_NASTEPNY, stan)){
				nastepnyStan_ = std::make_shared<STyp::Identyfikator>(stan);
			}

			if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_NUMER_NASTEPNY, stan)){
				nastepnyNumer_ = std::make_shared<int>(stan());
			}
			if (!luaFile_.empty()){
				skrypt_ = Aplikacja::pobierzInstancje().pobierzZarzadce().TworzSkrypt(wezel);
				if (!skrypt_)
					Utils::generujWyjatekBleduStruktury(wezel);
				if(!skrypt_->zaladuj(luaFile_))
					throw BladStukturyStanu(EXCEPTION_PLACE, id_, KOMUNIAKT_BLAD_WCZYTYWANIA(luaFile_));
				if (!skrypt_->wykonaj())
					throw BladStukturyStanu(EXCEPTION_PLACE, id_, KOMUNIAKT_BLAD_WYKONYWANIA);
			}
		}
	}

	bool ZdarzenieInfo::wykonaj(){
		if (luaFuncInside_.empty())
			return true;
		return skrypt_->wykonaj(luaFuncInside_);
	}

	const STyp::Identyfikator& ZdarzenieInfo::pobierzIdentyfikator() const{
		return id_;
	}

	std::shared_ptr< STyp::Identyfikator > ZdarzenieInfo::pobierzStan() const{
		return nastepnyStan_;
	}

	std::shared_ptr< int > ZdarzenieInfo::pobierzNumer() const{
		return nastepnyNumer_;
	}

	std::string ZdarzenieInfo::napis() const{
		SLog::Logger log(NAZWAKLASY(ZdarzenieInfo));
		log.dodajPole(NAZWAPOLA(id_), id_);
		log.dodajPole(NAZWAPOLA(luaFuncInside_), luaFuncInside_);
		log.dodajPole(NAZWAPOLA(luaFile_), luaFile_);
		log.dodajPole(NAZWAPOLA(nastepnyStan_), nastepnyStan_);
		if (nastepnyNumer_)
			log.dodajPole(NAZWAPOLA(nastepnyNumer_), STyp::Identyfikator(*nastepnyNumer_));
		return log.napis();
	}
};