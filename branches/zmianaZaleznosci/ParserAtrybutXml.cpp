#include "ParserAtrybutXml.h"
#include <string>

se::ParserAtrybutXml::ParserAtrybutXml( const tinyxml2::XMLAttribute* atrybut, tinyxml2::XMLElement* element )
	: atrybut_(atrybut), element_(element)
{
}

se::ParserAtrybutXml::~ParserAtrybutXml(void)
{
}

bool se::ParserAtrybutXml::ustawNazwe( const char* ){
	return false;
}

const char* se::ParserAtrybutXml::pobierzNazwe( ) const{
	if(atrybut_)
		return atrybut_->Name();
	return nullptr;
}

bool se::ParserAtrybutXml::ustawWartosc( const char* wartosc ){
	if(element_ && atrybut_ ){
		element_->SetAttribute(atrybut_->Name(), wartosc );
		return true;
	}
	return false;
}

const char* se::ParserAtrybutXml::pobierzWartosc( ) const{
	if(atrybut_)
		return atrybut_->Value();
	return nullptr;
}

bool se::ParserAtrybutXml::ustawWartoscInt( int wartosc ){
	if(element_ && atrybut_ ){
		element_->SetAttribute(atrybut_->Name(), wartosc );
		return true;
	}
	return false;
}

int se::ParserAtrybutXml::pobierzWartoscInt( ) const{
	if(atrybut_)
		return atrybut_->IntValue();
	return 0;
}

bool se::ParserAtrybutXml::ustawWartoscUnsignedInt( unsigned int wartosc ){
	if(element_ && atrybut_ ){
		element_->SetAttribute(atrybut_->Name(), wartosc );
		return true;
	}
	return false;
}

unsigned int se::ParserAtrybutXml::pobierzWartoscUnsignedInt( ) const{
	if(atrybut_)
		return atrybut_->UnsignedValue();
	return 0;
}

bool se::ParserAtrybutXml::ustawWartoscInt64( __int64 wartosc ){
	if(element_ && atrybut_ ){
		char temp[22];
		_i64toa_s(wartosc,temp,22,10);
		element_->SetAttribute(atrybut_->Name(), temp );
		return true;
	}
	return false;
}

__int64 se::ParserAtrybutXml::pobierzWartoscInt64( ) const{
	return std::stoll(atrybut_->Value(),nullptr,10);
}

bool se::ParserAtrybutXml::ustawWartoscUnsignedInt64( unsigned __int64 wartosc ){
	if(element_ && atrybut_ ){
		char temp[22];
		_ui64toa_s(wartosc,temp,22,10);
		element_->SetAttribute(atrybut_->Name(), temp );
		return true;
	}
	return false;
}

unsigned __int64 se::ParserAtrybutXml::pobierzWartoscUnsignedInt64( ) const{
	return std::stoull(atrybut_->Value(),nullptr,10);
}

bool se::ParserAtrybutXml::ustawWartoscFloat( float wartosc ){
	if(element_ && atrybut_ ){
		element_->SetAttribute(atrybut_->Name(), wartosc );
		return true;
	}
	return false;
}

float se::ParserAtrybutXml::pobierzWartoscFloat( ) const{
	if(atrybut_)
		return atrybut_->FloatValue();
	return 0;
}

bool se::ParserAtrybutXml::ustawWartoscDouble( double wartosc){
	if(element_ && atrybut_ ){
		element_->SetAttribute(atrybut_->Name(), wartosc );
		return true;
	}
	return false;
}

double se::ParserAtrybutXml::pobierzWartoscDouble( ) const{
	if(atrybut_)
		return atrybut_->DoubleValue();
	return 0;
}

bool se::ParserAtrybutXml::ustawWartoscLongDouble( long double wartosc ){
	if(element_ && atrybut_ ){
		char temp[22];
		_ui64toa_s(wartosc,temp,22,10);
		element_->SetAttribute(atrybut_->Name(), temp );
		return true;
	}
	return false;
}

long double se::ParserAtrybutXml::pobierzWartoscLongDouble( ) const{
	return std::stold(atrybut_->Value());
}

se::ParserAtrybutXml::operator bool()const{
	return false;
}
