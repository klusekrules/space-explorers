#include "ParserAtrybutXml.h"
#include <string>

namespace SPar{

	ParserAtrybutXml::ParserAtrybutXml(const tinyxml2::XMLAttribute* atrybut, tinyxml2::XMLElement* element)
		: atrybut_(atrybut), element_(element)
	{
	}

	ParserAtrybutXml::~ParserAtrybutXml(void)
	{
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
		return nullptr;
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
		return 0;
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
		return 0;
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
		return std::stoll(atrybut_->Value(), nullptr, 10);
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
		return std::stoull(atrybut_->Value(), nullptr, 10);
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
		return 0;
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
		return 0;
	}

	bool ParserAtrybutXml::ustawWartoscLongDouble(long double wartosc){
		if (element_ && atrybut_){
			element_->SetAttribute(atrybut_->Name(), std::to_string(wartosc).c_str());
			return true;
		}
		return false;
	}

	long double ParserAtrybutXml::pobierzWartoscLongDouble() const{
		return std::stold(atrybut_->Value());
	}

	ParserAtrybutXml::operator bool()const{
		return false;
	}
}
