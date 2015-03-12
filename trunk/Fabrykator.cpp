#include "Fabrykator.h"
#include "LuaSkrypt.h"
#include "DllSkrypt.h"
#include "Parser\XmlBO.h"
#include "Utils.h"
#include "Parser\ParserDokumentXml.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"
#include "MetodaRPC.h"
#include "StaleRPC.h"
#include "StackThrow.h"

namespace SpEx{
	std::shared_ptr<MetodaRPC> Fabrykator::tworzMetodeRPC(const Json::Value & root, Klient& klient) const{
		if (root.isObject()){
			auto value = root[METODA_RPC_METODA][METODA_RPC_NAZWA];
			if (value.isString()){
				auto iterator = metodRpcCallbacks_.find(value.asString());
				if (iterator != metodRpcCallbacks_.end())
					return iterator->second(root, klient);
			}
		}
		return nullptr;
	}

	std::shared_ptr<Skrypt> Fabrykator::tworzSkrypt(XmlBO::ElementWezla wezel) const{
		IdentyfikatorSkryptu id;
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_SKRYPT_TYP, id);
		return tworzSkrypt(id, wezel);
	}

	std::shared_ptr<Skrypt> Fabrykator::tworzSkrypt(const IdentyfikatorSkryptu& identyfikator, XmlBO::ElementWezla wezel) const{
		auto iterator = callbacks_.find(identyfikator());
		if (iterator == callbacks_.end())
			return nullptr;
		return iterator->second(wezel);
	}
	
	std::shared_ptr<Skrypt> Fabrykator::tworzSkrypt(const std::string& plik) const{
		std::string ext;
		if (!Utils::pobierzRozszezenie(plik, ext)){
			return nullptr;
		}

		SPar::ParserDokumentXml dokument;
		auto wezel = dokument.tworzElement("Skrypt");
		wezel->tworzAtrybut(ATRYBUT_XML_SKRYPT_FILE, plik.c_str());

		return tworzSkrypt(ext, wezel);
	}

	std::shared_ptr<SZmi::ZmianaInterfejs> Fabrykator::tworzZmiane(XmlBO::ElementWezla wezel) const{
		return fabrykaZmian_.tworz(wezel);
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