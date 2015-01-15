#include "Fabrykator.h"
#include "LuaSkrypt.h"
#include "DllSkrypt.h"
#include "Parser\XmlBO.h"
#include "Utils.h"
#include "Parser\ParserDokumentXml.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{
	Fabrykator::Fabrykator(){
		LuaSkrypt::Rejestruj(*this);
		DllSkrypt::Rejestruj(*this);
	}

	bool Fabrykator::rejestracjaSkryptu(const IdentyfikatorSkryptu& id, KreatorSkryptu funkcja){
		if (funkcja == nullptr || id.isEmpty() || callbacks_.find(id) != callbacks_.end())
			return false;
		callbacks_[id] = funkcja;
		return true;
	}


	bool Fabrykator::rejestracjaMetodyRPC(const IdentyfikatorMetoryRPC& identyfikator, KreatorMetodyRPC funkcja){
		if (funkcja == nullptr || identyfikator.isEmpty() || metodRpcCallbacks_.find(identyfikator) != metodRpcCallbacks_.end())
			return false;
		metodRpcCallbacks_[identyfikator] = funkcja;
		return true;
	}

	std::unique_ptr<MetodaRPC> Fabrykator::TworzMetodeRPC(const std::string & nazwa, Klient& klient) const{
		if (!nazwa.empty()){
			auto iterator = metodRpcCallbacks_.find(nazwa);
			if (iterator == metodRpcCallbacks_.end())
				return nullptr;
			auto ptr = iterator->second(Json::Value(Json::nullValue), klient);
			if (ptr){
				ptr->nazwa_ = nazwa;
				ptr->id_unikalne_ = std::to_string(static_cast<unsigned long long>(identyfikatorZadania_()()));
				ptr->powtorzenie_ = 0;
				klient.autoryzujMetode(ptr->instancja_, ptr->autoryzacja_);
				ptr->czas_wywolania_ = SLog::Log::pobierzInstancje().pobierzDateCzas();
			}
			return std::move(ptr);
		}
		return nullptr;
	}

	std::unique_ptr<MetodaRPC> Fabrykator::TworzMetodeRPC(const Json::Value & root, Klient& klient) const{
		auto value = root["metoda"]["nazwa"];
		if (value.isString()){
			auto iterator = metodRpcCallbacks_.find(value.asString());
			if (iterator == metodRpcCallbacks_.end())
				return nullptr;
			return iterator->second(root, klient);
		}
		return nullptr;
	}

	std::shared_ptr<Skrypt> Fabrykator::TworzSkrypt(XmlBO::ElementWezla wezel) const{
		IdentyfikatorSkryptu id;
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_SKRYPT_TYP, id);
		auto iterator = callbacks_.find(id());
		if (iterator == callbacks_.end())
			return nullptr;
		return iterator->second(wezel);
	}

	std::shared_ptr<Skrypt> Fabrykator::TworzSkrypt(const IdentyfikatorSkryptu& identyfikator, XmlBO::ElementWezla wezel) const{
		auto iterator = callbacks_.find(identyfikator());
		if (iterator == callbacks_.end())
			return nullptr;
		return iterator->second(wezel);
	}
	
	std::shared_ptr<Skrypt> Fabrykator::TworzSkrypt(const std::string& plik) const{
		std::string ext;
		if (!Utils::pobierzRozszezenie(plik, ext)){
			return nullptr;
		}

		SPar::ParserDokumentXml dokument;
		auto wezel = dokument.tworzElement("Skrypt");
		wezel->tworzAtrybut(ATRYBUT_XML_SKRYPT_FILE, plik.c_str());

		auto iterator = callbacks_.find(ext);
		if (iterator == callbacks_.end())
			return nullptr;
		return iterator->second(wezel);
	}

	std::shared_ptr<SZmi::ZmianaInterfejs> Fabrykator::TworzZmiane(XmlBO::ElementWezla wezel) const{
		return fabrykaZmian_.Tworz(wezel);
	}

	SZmi::ZmianaFabryka& Fabrykator::pobierzFabrykeZmian(){
		return fabrykaZmian_;
	}

	std::string Fabrykator::napis() const{
		SLog::Logger logger(NAZWAKLASY(Fabrykator));
		logger.dodajPole(NAZWAPOLA(fabrykaZmian_), fabrykaZmian_);
		logger.rozpocznijPodKlase(NAZWAPOLA(callbacks_),"SpEx::Fabrykator::ScriptCallbacks");
		for (auto& element : callbacks_ ){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			std::stringstream streamKreator;
			streamKreator.imbue(std::locale("C"));
			streamKreator << "0x" << std::hex << (unsigned int)(element.second);
			logger.dodajPole("second", "SpEx::Fabrykator::KreatorSkryptu", streamKreator.str());
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();
		logger.rozpocznijPodKlase(NAZWAPOLA(metodRpcCallbacks_), "SpEx::Fabrykator::TablicaKreatorowMetodRPC");
		for (auto& element : metodRpcCallbacks_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			std::stringstream streamKreator;
			streamKreator.imbue(std::locale("C"));
			streamKreator << "0x" << std::hex << (unsigned int)(element.second);
			logger.dodajPole("second", "SpEx::Fabrykator::KreatorMetodyRPC", streamKreator.str());
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();
		return logger.napis();
	}
};