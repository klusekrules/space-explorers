#include "ParserDokumentJSON.h"
#include "ParserElementJSON.h"
#include <fstream>

namespace SPar{
	std::shared_ptr<ParserElement> ParserDokumentJSON::pobierzElement(const char* nazwa){
		if (root_.isObject()){
			for (auto iter = root_.begin(); iter != root_.end(); ++iter){
				if (strcmp(iter.memberName(), nazwa) == 0){
					return std::make_shared<ParserElementJSON>(iter, root_.end());
				}
			}
		}
		return nullptr;
	}

	std::shared_ptr<ParserElement> ParserDokumentJSON::tworzElement(const char* nazwa){
		if (root_.isObject()){
			root_[nazwa] = Json::objectValue;
			return pobierzElement(nazwa);
		}
		return nullptr;
	}

	bool ParserDokumentJSON::usunElement(std::shared_ptr<ParserElement> element){
		if (element)
			return !root_.removeMember(element->pobierzNazwe()).isNull();
		return false;
	}

	bool ParserDokumentJSON::odczytaj(const char* nazwa){
		if (!nazwa)
			return false;
		nazwa_ = nazwa;
		std::ifstream plik(nazwa_);
		Json::Reader reader;
		return reader.parse(plik, root_);
	}

	bool ParserDokumentJSON::zapisz(const char* nazwa){
		if (nazwa){
			nazwa_ = nazwa;
			std::ifstream plik(nazwa_);
			Json::Reader reader;
			return reader.parse(plik, root_);
		}
		else{
			if (nazwa_.empty())
				return false;
			std::ifstream plik(nazwa_);
			Json::Reader reader;
			return reader.parse(plik, root_);
		}
	}

	ParserDokumentJSON::operator bool()const{
		return !root_.isNull();
	}

	std::string ParserDokumentJSON::error()const{
		Json::FastWriter printer;
		if (!root_.isNull()){
			return printer.write(root_);
		}
		else{
			return std::string("nullptr");
		}
	}

}
