#include "ParserDokument.h"

namespace SPar{

	ParserDokument::ParserDokument(void)
	{
	}


	ParserDokument::~ParserDokument(void)
	{
	}

	std::shared_ptr<ParserElement> ParserDokument::pobierzElement(const char*){
		return nullptr;
	}

	std::shared_ptr<ParserElement> ParserDokument::tworzElement(const char*){
		return nullptr;
	}

	bool ParserDokument::usunElement(std::shared_ptr<ParserElement>){
		return false;
	}

	bool ParserDokument::odczytaj(const char*){
		return false;
	}

	bool ParserDokument::zapisz(const char*){
		return false;
	}

	ParserDokument::operator bool()const{
		return false;
	}
}
