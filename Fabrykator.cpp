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
		return logger.napis();
	}
};