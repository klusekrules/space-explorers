#include "ParserElementXml.h"
#include "ParserAtrybutXml.h"

se::ParserElementXml::ParserElementXml( tinyxml2::XMLElement* element )
	: element_(element)
{
}

se::ParserElementXml::~ParserElementXml(void)
{
}

std::shared_ptr<se::ParserAtrybut> se::ParserElementXml::pobierzAtrybut( const char* atrybut ){
	if(element_){
		const tinyxml2::XMLAttribute* atr = const_cast< const tinyxml2::XMLElement* >(element_)->FindAttribute(atrybut);
		if(!atr)
			return nullptr;
		else
			return std::make_shared<se::ParserAtrybutXml>(atr,element_);
	}
	return nullptr;
}

std::shared_ptr<se::ParserAtrybut> se::ParserElementXml::tworzAtrybut( const char* atrybut, const char* wartosc ){
	if(!element_)
		return nullptr;
	element_->SetAttribute(atrybut,wartosc);
	return pobierzAtrybut(atrybut);
}

bool se::ParserElementXml::usunAtrybut( const char* atrybut ){
	if(!element_)
		return false;
	element_->DeleteAttribute(atrybut);
	return true;
}

se::ParserElementXml::operator bool()const{
	if(!element_)
		return false;
	return true;
}

std::shared_ptr<se::ParserElement> se::ParserElementXml::pobierzElement( const char* element ){
	if(!element_)
		return nullptr;
	auto wezel = element_->FirstChildElement(element);
	if(wezel)
		return std::make_shared<ParserElementXml>(wezel);
	else
		return nullptr;
}

std::shared_ptr<se::ParserElement> se::ParserElementXml::tworzElement( const char* element ){
	if(!element_)
		return nullptr;
	auto wezel = element_->GetDocument()->NewElement(element);
	if(!wezel)
		return nullptr;
	element_->LinkEndChild(wezel);
	return std::make_shared<ParserElementXml>(wezel);
}

bool se::ParserElementXml::usunElement(){
	auto node = element_->Parent();
	if(!node)
		return false;
	node->DeleteChild(element_);
	element_=nullptr;
	return true;
}