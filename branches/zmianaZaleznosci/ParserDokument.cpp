#include "ParserDokument.h"


se::ParserDokument::ParserDokument(void)
{
}


se::ParserDokument::~ParserDokument(void)
{
}

std::shared_ptr<se::ParserElement> se::ParserDokument::pobierzElement( const char* ){
	return nullptr;
}

std::shared_ptr<se::ParserElement> se::ParserDokument::tworzElement( const char* ){
	return nullptr;
}

bool se::ParserDokument::usunElement( std::shared_ptr<ParserElement> ){
	return false;
}

bool se::ParserDokument::odczytaj( const char* ){
	return false;
}

bool se::ParserDokument::zapisz( const char* ){
	return false;
}

se::ParserDokument::operator bool()const{
	return false;
}