#include "ParserElement.h"


se::ParserElement::ParserElement(void)
{
}


se::ParserElement::~ParserElement(void)
{
}

std::shared_ptr<se::ParserAtrybut> se::ParserElement::pobierzAtrybut( const char* ){
	return nullptr;
}

std::shared_ptr<se::ParserAtrybut> se::ParserElement::tworzAtrybut( const char*, const char* ){
	return nullptr;
}

bool se::ParserElement::usunAtrybut( const char* ){
	return false;
}

se::ParserElement::operator bool()const{
	return false;
}

std::shared_ptr<se::ParserElement> se::ParserElement::pobierzElement( const char* ){
	return nullptr;
}
std::shared_ptr<se::ParserElement> se::ParserElement::tworzElement( const char* ){
	return nullptr;
}

bool se::ParserElement::usunElement( ){
	return false;
}