#include "ParserDokumentXml.h"
#include "ParserElementXml.h"

se::ParserDokumentXml::ParserDokumentXml(void)
{
}

se::ParserDokumentXml::~ParserDokumentXml(void)
{
}

std::shared_ptr<se::ParserElement> se::ParserDokumentXml::pobierzElement( const char* nazwa ){
	return std::make_shared<ParserElementXml>(dokument_.FirstChildElement(nazwa));
}

std::shared_ptr<se::ParserElement> se::ParserDokumentXml::tworzElement( const char* nazwa ){
	auto element = dokument_.NewElement(nazwa);
	dokument_.LinkEndChild(element);
	return std::make_shared<ParserElementXml>(element);
}

bool se::ParserDokumentXml::usunElement( std::shared_ptr<ParserElement> element ){
	return element->usunElement();
}

bool se::ParserDokumentXml::odczytaj( const char* nazwa ){
	if(!nazwa)
		return false;
	nazwa_ = nazwa;
	return dokument_.LoadFile(nazwa) == tinyxml2::XML_NO_ERROR;
}

bool se::ParserDokumentXml::zapisz( const char* nazwa ){
	if(nazwa){
		nazwa_ = nazwa;
		return dokument_.SaveFile(nazwa) == tinyxml2::XML_NO_ERROR;
	}else{
		if(nazwa_.empty())
			return false;
		return dokument_.SaveFile(nazwa_.c_str()) == tinyxml2::XML_NO_ERROR;
	}
}

se::ParserDokumentXml::operator bool()const{
	return !dokument_.Error();
}