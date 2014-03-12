#include "StanInfo.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include "Aplikacja.h"

namespace SpEx{
	StanInfo::StanInfo(XmlBO::ElementWezla wezel)
	{
		if (wezel){
			XmlBO::WczytajAtrybut<SpEx::STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, id_);
			luaFile_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_STAN_LUA_FILE, std::string());
			luaFuncIn_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_STAN_LUA_IN, std::string());
			luaFuncOut_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_STAN_LUA_OUT, std::string());
			luaFuncInside_ = XmlBO::WczytajAtrybut<std::string>(wezel, ATRYBUT_XML_STAN_LUA_INSIDE, std::string());

			if (luaFile_.empty() && !(luaFuncInside_.empty() && luaFuncOut_.empty() && luaFuncIn_.empty()))
				throw STyp::Wyjatek(EXCEPTION_PLACE, Aplikacja::pobierzInstancje().pobierzSladStosu(), STyp::Identyfikator(),
				STyp::Tekst("B³¹d struktury stanu."),
				STyp::Tekst("Nie podano pliku skryptu, a wpisano metody do wykonania."));

			XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_ZDARZENIE, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
				auto zdarzenie = std::make_shared<ZdarzenieInfo>(element);
				zdarzenia_.insert(std::make_pair(zdarzenie->pobierzIdentyfikator(), zdarzenie));
				return true;
			}));

			if (!luaFile_.empty()){
				skrypt_ = Aplikacja::pobierzInstancje().pobierzZarzadce().TworzSkrypt(wezel);
				if (!skrypt_)
					Utils::generujWyjatekBleduStruktury(wezel);
				skrypt_->zaladuj(luaFile_);
				skrypt_->wykonaj();
			}
		}
	}

	bool StanInfo::wykonaj(Akcja akcja){
		std::string funkcja, *ptr;
		ptr = &funkcja;
		switch (akcja)
		{
		case StanInfo::AkcjaWejsciowa:
			if (luaFuncIn_.empty())
				return true;
			ptr = &luaFuncIn_;
			break;
		case StanInfo::AkcjaWyjsciowa:
			if (luaFuncOut_.empty())
				return true;
			ptr = &luaFuncOut_;
			break;
		case StanInfo::AkcjaWewnetrzna:
			if (luaFuncInside_.empty())
				return true;
			ptr = &luaFuncInside_;
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

	std::string StanInfo::napis()const{
		SLog::Logger log(NAZWAKLASY(StanInfo));
		log.dodajPole(NAZWAPOLA(id_), id_);
		log.dodajPole(NAZWAPOLA(luaFuncIn_), luaFuncIn_);
		log.dodajPole(NAZWAPOLA(luaFuncOut_), luaFuncOut_);
		log.dodajPole(NAZWAPOLA(luaFuncInside_), luaFuncInside_);
		log.dodajPole(NAZWAPOLA(luaFile_), luaFile_);
		return log.napis();
	}
};
