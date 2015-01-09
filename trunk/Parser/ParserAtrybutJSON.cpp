#include "ParserAtrybutJSON.h"

#include <string>

namespace SPar{

	ParserAtrybutJSON::ParserAtrybutJSON(Json::ValueIterator iterator, Json::ValueIterator end)
		: iterator_(iterator), end_(end)
	{
	}

	std::shared_ptr<ParserAtrybut> ParserAtrybutJSON::pobierzNastepnyAtrybut() const{
		if (iterator_ != end_){
			auto iter = iterator_;
			++iter;
			if (iter != end_)
				return std::make_shared<ParserAtrybutJSON>(iter, end_);
		}
		return nullptr;
	}

	bool ParserAtrybutJSON::ustawNazwe(const char*){
		return false;
	}

	const char* ParserAtrybutJSON::pobierzNazwe() const{
		if (iterator_!=end_)
			return iterator_.memberName();
		return nullptr;
	}

	bool ParserAtrybutJSON::ustawWartosc(const char* wartosc){
		if (iterator_ != end_){
			*iterator_ = wartosc;
			return true;
		}
		return false;
	}

	const char* ParserAtrybutJSON::pobierzWartosc() const{
		if (iterator_ != end_)
			return iterator_->asCString();
		return nullptr;
	}

	bool ParserAtrybutJSON::ustawWartoscInt(int wartosc){
		if (iterator_ != end_){
			*iterator_ = wartosc;
			return true;
		}
		return false;
	}

	int ParserAtrybutJSON::pobierzWartoscInt() const{
		if (iterator_ != end_)
			return iterator_->asInt();
		return 0;
	}

	bool ParserAtrybutJSON::ustawWartoscUnsignedInt(unsigned int wartosc){
		if (iterator_ != end_){
			*iterator_ = wartosc;
			return true;
		}
		return false;
	}

	unsigned int ParserAtrybutJSON::pobierzWartoscUnsignedInt() const{
		if (iterator_ != end_)
			return iterator_->asUInt();
		return 0;
	}

	bool ParserAtrybutJSON::ustawWartoscInt64(__int64 wartosc){
		if (iterator_ != end_){
			*iterator_ = wartosc;
			return true;
		}
		return false;
	}

	__int64 ParserAtrybutJSON::pobierzWartoscInt64() const{
		if (iterator_ != end_)
			return iterator_->asInt64();
		return 0;
	}

	bool ParserAtrybutJSON::ustawWartoscUnsignedInt64(unsigned __int64 wartosc){
		if (iterator_ != end_){
			*iterator_ = wartosc;
			return true;
		}
		return false;
	}

	unsigned __int64 ParserAtrybutJSON::pobierzWartoscUnsignedInt64() const{
		if (iterator_ != end_)
			return iterator_->asUInt64();
		return 0;
	}

	bool ParserAtrybutJSON::ustawWartoscFloat(float wartosc){
		if (iterator_ != end_){
			*iterator_ = wartosc;
			return true;
		}
		return false;
	}

	float ParserAtrybutJSON::pobierzWartoscFloat() const{
		if (iterator_ != end_)
			return iterator_->asFloat();
		return 0;
	}

	bool ParserAtrybutJSON::ustawWartoscDouble(double wartosc){
		if (iterator_ != end_){
			*iterator_ = wartosc;
			return true;
		}
		return false;
	}

	double ParserAtrybutJSON::pobierzWartoscDouble() const{
		if (iterator_ != end_)
			return iterator_->asDouble();
		return 0;
	}

	bool ParserAtrybutJSON::ustawWartoscLongDouble(long double wartosc){
		if (iterator_ != end_){
			*iterator_ = std::to_string(wartosc);
			return true;
		}
		return false;
	}

	long double ParserAtrybutJSON::pobierzWartoscLongDouble() const{
		return std::stold(iterator_->asString());
	}

	ParserAtrybutJSON::operator bool()const{
		return iterator_ != end_;
	}

	std::string ParserAtrybutJSON::error()const{
		Json::FastWriter printer;
		if (iterator_ != end_){
			return printer.write(*iterator_);
		}
		else{
			return std::string("nullptr");
		}
	}

}