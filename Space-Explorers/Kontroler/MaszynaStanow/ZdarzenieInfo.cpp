#include "ZdarzenieInfo.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\Utils.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Zarzadca\Fabrykator.h"
#include "Utils\StackThrow.h"

#define KOMUNIAKT_BLAD_WCZYTYWANIA(plik) STyp::Tekst("Dla zdarzenia o ww id nie uda�o si� wczytac pliku lua." + plik)

namespace SpEx{
	ZdarzenieInfo::ZdarzenieInfo(XmlBO::ElementWezla wezel)
		: nastepnyStan_(nullptr), nastepnyNumer_(nullptr)
	{
		if (wezel){
			XmlBO::WczytajAtrybut<SpEx::STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, id_);

			STyp::Identyfikator stan;
			if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_STAN_NASTEPNY, stan)){
				nastepnyStan_ = std::make_shared<STyp::Identyfikator>(stan);
			}

			if (XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_NUMER_NASTEPNY, stan)){
				nastepnyNumer_ = std::make_shared<int>(stan());
			}

			if (wezel->pobierzAtrybut(ATRYBUT_XML_SKRYPT_TYP)){

				funcInside_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_SKRYPT_FUNC_INSIDE, std::string());

				skrypt_ = Aplikacja::pobierzInstancje().pobierzFabrykator().tworzSkrypt(wezel);
				if (!skrypt_)
					Utils::generujWyjatekBleduStruktury(wezel);
			}
		}
	}

	bool ZdarzenieInfo::wykonaj(){
		if (!skrypt_)
			return true;
		return skrypt_->wykonaj(funcInside_);
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
		log.dodajPole(NAZWAPOLA(funcInside_), NAZWAKLASY2(funcInside_), funcInside_);
		log.dodajPole(NAZWAPOLA(nastepnyStan_), nastepnyStan_);
		if (nastepnyNumer_)
			log.dodajPole(NAZWAPOLA(nastepnyNumer_), STyp::Identyfikator(*nastepnyNumer_));
		return log.napis();
	}
};