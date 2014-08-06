#include "FabrykaSkryptow.h"
#include "Utils.h"
#include "Parser\ParserDokumentXml.h"
#include "definicjeWezlowXML.h"

namespace SpEx{
	bool FabrykaSkryptow::rejestracjaSkryptu(const Identyfikator& id, KreatorSkryptu funkcja){
		if (funkcja == nullptr || id.isEmpty() || callbacks_.find(id) != callbacks_.end())
			return false;
		callbacks_[id] = funkcja;
		return true;
	}

	std::shared_ptr<Skrypt> FabrykaSkryptow::Tworz(XmlBO::ElementWezla wezel) const {
		Identyfikator id;
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, XML_ATRYBUT_TYP_SKRYPTU, id);
		auto iterator = callbacks_.find(id());
		if (iterator == callbacks_.end())
			return nullptr;
		return iterator->second(wezel);
	}

	std::shared_ptr<Skrypt> FabrykaSkryptow::Tworz(const Identyfikator& identyfikator, XmlBO::ElementWezla wezel) const {
		auto iterator = callbacks_.find(identyfikator());
		if (iterator == callbacks_.end())
			return nullptr;
		return iterator->second(wezel);
	}

	std::shared_ptr<Skrypt> FabrykaSkryptow::Tworz(const std::string& plik) const{
		std::string ext;
		if (!Utils::pobierzRozszezenie(plik, ext)){
			return nullptr;
		}

		SPar::ParserDokumentXml dokument;
		auto wezel = dokument.tworzElement("Skrypt");
		wezel->tworzAtrybut(ATRYBUT_XML_SKRYPT_FILE,plik.c_str());
		
		auto iterator = callbacks_.find(ext);
		if (iterator == callbacks_.end())
			return nullptr;
		return iterator->second(wezel);
	}
}
