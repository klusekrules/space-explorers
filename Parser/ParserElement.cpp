#include "ParserElement.h"

namespace SPar{
	ParserElement::ParserElement(void)
	{
	}


	ParserElement::~ParserElement(void)
	{
	}

	std::shared_ptr<ParserAtrybut> ParserElement::pobierzAtrybut(const char*){
		return nullptr;
	}

	std::shared_ptr<ParserAtrybut> ParserElement::tworzAtrybut(const char*, const char*){
		return nullptr;
	}

	bool ParserElement::usunAtrybut(const char*){
		return false;
	}

	ParserElement::operator bool()const{
		return false;
	}

	std::shared_ptr<ParserElement> ParserElement::pobierzElement(const char*){
		return nullptr;
	}
	std::shared_ptr<ParserElement> ParserElement::tworzElement(const char*){
		return nullptr;
	}

	bool ParserElement::usunElement(){
		return false;
	}
}
