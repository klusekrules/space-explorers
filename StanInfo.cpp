#include "StanInfo.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include "Aplikacja.h"
#include "BladStukturyStanu.h"
#include "Fabrykator.h"
#include "StackThrow.h"

#define KOMUNIAKT_BLAD_ZDARZENIA STyp::Tekst("B³¹d wczytywania zdarzeñ dla stanu: ")
#define KOMUNIAKT_BLAD_WCZYTYWANIA(plik) STyp::Tekst("Nie uda³o siê wczytac pliku lua." + plik)
#define KOMUNIAKT_BLAD_WYKONYWANIA STyp::Tekst("Nie uda³o siê wykonaæ inicjalizacji skryptu.")

namespace SpEx{
	StanInfo::StanInfo(XmlBO::ElementWezla wezel)
	{
		if (wezel){
			XmlBO::WczytajAtrybut<SpEx::STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, id_);

			try{
				XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_ZDARZENIE, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
					auto zdarzenie = std::make_shared<ZdarzenieInfo>(element);
					zdarzenia_.insert(std::make_pair(zdarzenie->pobierzIdentyfikator(), zdarzenie));
					return true;
				}));
			}catch(BladStukturyStanu& e){
				throw BladStukturyStanu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), id_, KOMUNIAKT_BLAD_ZDARZENIA + e.generujKomunikat());
			}

			if (wezel->pobierzAtrybut(ATRYBUT_XML_SKRYPT_TYP)){

				funcIn_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_SKRYPT_FUNC_IN, std::string());
				funcOut_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_SKRYPT_FUNC_OUT, std::string());
				funcInside_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_SKRYPT_FUNC_INSIDE, std::string());

				skrypt_ = Aplikacja::pobierzInstancje().pobierzFabrykator().TworzSkrypt(wezel);
				if (!skrypt_)
					Utils::generujWyjatekBleduStruktury(wezel);
			}
		}
	}

	bool StanInfo::wykonaj(Akcja akcja){
		std::string funkcja, *ptr;
		UNREFERENCED_PARAMETER(funkcja);
		ptr = &funkcja;
		switch (akcja)
		{
		case StanInfo::AkcjaWejsciowa:
			if (funcIn_.empty())
				return true;
			ptr = &funcIn_;
			break;
		case StanInfo::AkcjaWyjsciowa:
			if (funcOut_.empty())
				return true;
			ptr = &funcOut_;
			break;
		case StanInfo::AkcjaWewnetrzna:
			if (funcInside_.empty())
				return true;
			ptr = &funcInside_;
			break;
		default:
			return false;
		}
		return skrypt_->wykonaj(*ptr);
	}

	const STyp::Identyfikator& StanInfo::pobierzIdentyfikator() const{
		return id_;
	}

	std::shared_ptr<ZdarzenieInfo> StanInfo::pobierzZdarzenie(const STyp::Identyfikator& id) const{
		auto iter = zdarzenia_.find(id);
		if (iter == zdarzenia_.end())
			return nullptr;
		return iter->second;
	}

	const std::map < STyp::Identyfikator, std::shared_ptr<ZdarzenieInfo> >& StanInfo::pobierzListeZdarzen() const{
		return zdarzenia_;
	}

	std::string StanInfo::napis()const{
		SLog::Logger log(NAZWAKLASY(StanInfo));
		log.dodajPole(NAZWAPOLA(id_), id_);
		log.dodajPole(NAZWAPOLA(funcIn_), NAZWAKLASY2(funcIn_), funcIn_);
		log.dodajPole(NAZWAPOLA(funcOut_), NAZWAKLASY2(funcOut_), funcOut_);
		log.dodajPole(NAZWAPOLA(funcInside_), NAZWAKLASY2(funcInside_), funcInside_);
		return log.napis();
	}
};
