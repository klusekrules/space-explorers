#include "ParserAtrybutXml.h"
#include "WyjatekParser.h"
#include <string>

namespace SPar{

	ParserAtrybutXml::ParserAtrybutXml(const tinyxml2::XMLAttribute* atrybut, tinyxml2::XMLElement* element)
		: atrybut_(atrybut), element_(element)
	{
	}

	std::shared_ptr<ParserAtrybut> ParserAtrybutXml::pobierzNastepnyAtrybut() const{
		if (atrybut_ && element_){
			const tinyxml2::XMLAttribute* atr = atrybut_->Next();
			if (!atr)
				return nullptr;
			else
				return std::make_shared<ParserAtrybutXml>(atr, element_);
		}
		return nullptr;
	}

	bool ParserAtrybutXml::ustawNazwe(const char*){
		return false;
	}

	const char* ParserAtrybutXml::pobierzNazwe() const{
		if (atrybut_)
			return atrybut_->Name();
		return nullptr;
	}

	bool ParserAtrybutXml::ustawWartosc(const char* wartosc){
		if (element_ && atrybut_){
			element_->SetAttribute(atrybut_->Name(), wartosc);
			return true;
		}
		return false;
	}

	const char* ParserAtrybutXml::pobierzWartosc() const{
		if (atrybut_)
			return atrybut_->Value();
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::ustawWartoscBool(bool wartosc) const{
		if (element_ && atrybut_) {
			element_->SetAttribute(atrybut_->Name(), wartosc);
			return true;
		}
		return false;
	}

	bool ParserAtrybutXml::pobierzWartoscBool() const{
		if (atrybut_)
			return atrybut_->BoolValue();
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::pobierzWartoscBool(bool & wartosc) const{
		if (atrybut_) {
			return atrybut_->QueryBoolValue(&wartosc) == tinyxml2::XML_NO_ERROR;
		}
		return false;
	}

	bool ParserAtrybutXml::ustawWartoscInt(int wartosc){
		if (element_ && atrybut_){
			element_->SetAttribute(atrybut_->Name(), wartosc);
			return true;
		}
		return false;
	}

	int ParserAtrybutXml::pobierzWartoscInt() const{
		if (atrybut_)
			return atrybut_->IntValue();
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::pobierzWartoscInt(int & wartosc) const{
		if (atrybut_) {
			return atrybut_->QueryIntValue(&wartosc) == tinyxml2::XML_NO_ERROR;
		}
		return false;
	}

	bool ParserAtrybutXml::ustawWartoscUnsignedInt(unsigned int wartosc){
		if (element_ && atrybut_){
			element_->SetAttribute(atrybut_->Name(), wartosc);
			return true;
		}
		return false;
	}

	unsigned int ParserAtrybutXml::pobierzWartoscUnsignedInt() const{
		if (atrybut_)
			return atrybut_->UnsignedValue();
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::pobierzWartoscUnsignedInt(unsigned int & wartosc) const{
		if (atrybut_) {
			return atrybut_->QueryUnsignedValue(&wartosc) == tinyxml2::XML_NO_ERROR;
		}
		return false;
	}

	bool ParserAtrybutXml::ustawWartoscInt64(__int64 wartosc){
		if (element_ && atrybut_){
			char temp[22];
			_i64toa_s(wartosc, temp, 22, 10);
			element_->SetAttribute(atrybut_->Name(), temp);
			return true;
		}
		return false;
	}

	__int64 ParserAtrybutXml::pobierzWartoscInt64() const{
		if (atrybut_) {
			return _strtoi64(atrybut_->Value(), nullptr, 10);
		}
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::pobierzWartoscInt64(__int64 & wartosc) const{
		if (atrybut_) {
			wartosc = _strtoi64(atrybut_->Value(), nullptr, 10);
			return true;
		}
		return false;
	}

	bool ParserAtrybutXml::ustawWartoscUnsignedInt64(unsigned __int64 wartosc){
		if (element_ && atrybut_){
			char temp[22];
			_ui64toa_s(wartosc, temp, 22, 10);
			element_->SetAttribute(atrybut_->Name(), temp);
			return true;
		}
		return false;
	}

	unsigned __int64 ParserAtrybutXml::pobierzWartoscUnsignedInt64() const{
		if (atrybut_) {
			return _strtoui64(atrybut_->Value(), nullptr, 10);
		}
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::pobierzWartoscUnsignedInt64(unsigned __int64 & wartosc) const{
		if (atrybut_) {
			wartosc = _strtoui64(atrybut_->Value(), nullptr, 10);
			return true;
		}
		return false;
	}

	bool ParserAtrybutXml::ustawWartoscFloat(float wartosc){
		if (element_ && atrybut_){
			element_->SetAttribute(atrybut_->Name(), wartosc);
			return true;
		}
		return false;
	}

	float ParserAtrybutXml::pobierzWartoscFloat() const{
		if (atrybut_)
			return atrybut_->FloatValue();
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::pobierzWartoscFloat(float & wartosc) const{
		if (atrybut_) {
			return atrybut_->QueryFloatValue(&wartosc) == tinyxml2::XML_NO_ERROR;
		}
		return false;
	}

	bool ParserAtrybutXml::ustawWartoscDouble(double wartosc){
		if (element_ && atrybut_){
			element_->SetAttribute(atrybut_->Name(), wartosc);
			return true;
		}
		return false;
	}

	double ParserAtrybutXml::pobierzWartoscDouble() const{
		if (atrybut_)
			return atrybut_->DoubleValue();
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::pobierzWartoscDouble(double & wartosc) const{
		if (atrybut_) {
			return atrybut_->QueryDoubleValue(&wartosc) == tinyxml2::XML_NO_ERROR;
		}
		return false;
	}

	bool ParserAtrybutXml::ustawWartoscLongDouble(long double wartosc){
		if (element_ && atrybut_){
			element_->SetAttribute(atrybut_->Name(), std::to_string(wartosc).c_str());
			return true;
		}
		return false;
	}

	long double ParserAtrybutXml::pobierzWartoscLongDouble() const{
		if (element_ && atrybut_) {
			return std::stold(atrybut_->Value());
		}
		throw WyjatekParser(EXCEPTION_PLACE, std::string(), this, STyp::Tekst(" => iterator_ == end_"));
	}

	bool ParserAtrybutXml::pobierzWartoscLongDouble(long double & wartosc) const{
		if (atrybut_) {
			wartosc = std::stold(atrybut_->Value());
			return true;
		}
		return false;
	}

	ParserAtrybutXml::operator bool()const{
		if (!element_ || !atrybut_)
			return false;
		return true;
	}

	std::string ParserAtrybutXml::error()const{
		tinyxml2::XMLPrinter printer;
		if (element_){
			element_->Accept(&printer);
			return printer.CStr();
		}
		else{
			return std::string("nullptr");
		}
	}
}
